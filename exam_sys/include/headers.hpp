#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <atomic>

using namespace std;

const int Msize = 1e5;


inline int getch() {
    // 静态状态：确保整个程序中只有一套终端管理
    static std::atomic<int> ref_count{0};
    static termios original_term{};
    static bool raw_mode_set = false;

    // 1. 进入临界区：首次调用时设置 raw 模式
    if (++ref_count == 1) {
        tcgetattr(STDIN_FILENO, &original_term);
        termios newt = original_term;
        newt.c_lflag &= ~(ICANON | ECHO);  // 关闭行缓冲和回显
        newt.c_cc[VMIN] = 1;              // 阻塞：至少读 1 字节才返回
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &newt);
        raw_mode_set = true;
    }

    // 2. 阻塞读一个字符（这才是“卡住程序”的关键！）
    char ch;
    ssize_t n = read(STDIN_FILENO, &ch, 1);

    // 3. 退出临界区：最后一次调用时恢复终端
    if (--ref_count == 0) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_term);
        raw_mode_set = false;
    }

    return (n == 1) ? static_cast<unsigned char>(ch) : -1;
}

inline bool kbhit() {
    // 静态状态：记录是否已进入 raw 模式（避免重复设置）
    static std::atomic<bool> raw_mode_active{false};
    static termios original_term{};

    // 1. 尝试进入 raw 模式（仅第一次）
    if (!raw_mode_active.load(std::memory_order_relaxed)) {
        if (tcgetattr(STDIN_FILENO, &original_term) == 0) {
            termios newt = original_term;
            newt.c_lflag &= ~(ICANON | ECHO);
            newt.c_cc[VMIN] = 0;
            newt.c_cc[VTIME] = 0;
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &newt);
            raw_mode_active.store(true, std::memory_order_relaxed);
        }
    }

    // 2. 非阻塞检测输入
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    timeval tv{0, 0};

    int ret = select(STDIN_FILENO + 1, &read_fds, nullptr, nullptr, &tv);
    return ret > 0 && FD_ISSET(STDIN_FILENO, &read_fds);
}

inline void cls() {
    std::cout << "\033[2J\033[H";
}

inline string getHiddenInput(const string& prompt) {
    cout << prompt << endl;
    string input;
    int ch;
    while ((ch = getch()) != '\n' && ch != '\r') { 
        if (ch == 127 || ch == '\b') { 
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b" << flush; 
            }
            else cout << '\a';
        } else {
            input.push_back(ch);
            cout << '*' << flush;
        }
    }
    cout << '\n';
    return input;
}

class KbHit {
private:
    termios original_term;
    bool raw_mode_set = false;

    bool enter_raw_mode() {
        if (raw_mode_set) return true; // 已设置过
        if (tcgetattr(STDIN_FILENO, &original_term) != 0)
            return false;

        termios new_term = original_term;
        new_term.c_lflag &= ~(ICANON | ECHO); // 关闭行缓冲和回显
        new_term.c_cc[VMIN] = 0;              // 非阻塞读
        new_term.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term) != 0)
            return false;

        raw_mode_set = true;
        return true;
    }

    void leave_raw_mode() {
        if (raw_mode_set) {
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_term);
            raw_mode_set = false;
        }
    }

public:
    KbHit() {
        enter_raw_mode();
    }

    ~KbHit() {
        leave_raw_mode();
    }

    // 检测是否有按键（非阻塞）
    bool kbhit() {
        if (!raw_mode_set) return false;

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        timeval tv{0, 0};
        int ret = select(STDIN_FILENO + 1, &read_fds, nullptr, nullptr, &tv);
        return ret > 0 && FD_ISSET(STDIN_FILENO, &read_fds);
    }

    // 读取一个字符（非阻塞）
    int getch() {
        if (!raw_mode_set) return -1;

        char ch;
        ssize_t n = read(STDIN_FILENO, &ch, 1);
        return (n == 1) ? static_cast<unsigned char>(ch) : -1;
    }
};

