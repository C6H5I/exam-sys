-- 单选题 20 道 (Ans: 1=A, 2=B, 4=C, 8=D)
INSERT INTO Questions (Type, Text, option1, option2, option3, option4, Ans, Analysis) VALUES
('single', '1+1=?', '0', '1', '2', '3', 4, '1+1=2'),
('single', '太阳从哪边升起？', '北', '南', '东', '西', 4, '太阳从东方升起'),
('single', '水的化学式是？', 'H2O2', 'HO', 'H2O', 'O2', 4, '水是 H2O'),
('single', '中国首都是？', '上海', '广州', '北京', '深圳', 4, '北京是首都'),
('single', '光速约为？', '3*10^5 km/s', '3*10^6 km/s', '3*10^8 m/s', '3*10^9 m/s', 4, '真空中光速 c ≈ 3*10⁸ m/s'),
('single', 'Python 是？', '编译型语言', '解释型语言', '汇编语言', '机器语言', 2, 'Python 是解释型语言'),
('single', 'TCP 是？', '无连接协议', '面向连接协议', '广播协议', '组播协议', 2, 'TCP 是面向连接的传输层协议'),
('single', 'IPv4 地址长度？', '32位', '64位', '128位', '256位', 1, 'IPv4 地址为 32 位'),
('single', 'HTTP 默认端口？', '21', '22', '80', '443', 4, 'HTTP 默认端口是 80'),
('single', 'Linux 内核作者？', 'Bill Gates', 'Linus Torvalds', 'Dennis Ritchie', 'Ken Thompson', 2, 'Linus Torvalds 开发 Linux 内核'),
('single', 'JSON 全称？', 'JavaScript Object Notation', 'Java Standard Object Network', 'JavaScript Oriented Notation', 'Java Simple Object Notation', 1, 'JSON = JavaScript Object Notation'),
('single', '栈的操作原则？', '先进先出', '后进先出', '随机存取', '顺序存取', 2, '栈是 LIFO(后进先出)'),
('single', '二叉树最多有？', 'n-1', 'n', '2n', '2^n -1', 8, '深度为 n 的满二叉树节点数为 2ⁿ-1'),
('single', 'SQL 中查询用？', 'SELECT', 'GET', 'FIND', 'QUERY', 1, 'SELECT 是 SQL 查询语句'),
('single', 'HTTPS 基于？', 'FTP', 'SMTP', 'HTTP + TLS', 'HTTP + SSL', 4, 'HTTPS = HTTP over TLS/SSL'),
('single', 'Git 是？', '集中式版本控制', '分布式版本控制', '云存储系统', '数据库', 2, 'Git 是分布式版本控制系统'),
('single', 'C++ 中定义类用？', 'class', 'struct', 'type', 'object', 1, 'C++ 用 class 定义类'),
('single', 'main 函数返回类型？', 'void', 'int', 'bool', 'string', 2, '标准 main 返回 int'),
('single', '指针 *p 表示？', 'p 的地址', 'p 的值', 'p 指向的地址', 'p 指向的值', 8, '*p 是解引用，得到 p 指向的值'),
('single', 'sizeof(int) 通常是？', '2字节', '4字节', '8字节', '16字节', 2, '32位系统下 int 为 4 字节');

-- 多选题 20 道 (Ans: 位掩码，至少两位为1，即 3,5,6,7,9,10,11,12,13,14,15)
INSERT INTO Questions (Type, Text, option1, option2, option3, option4, Ans, Analysis) VALUES
('multiple', '以下哪些是编程语言？', 'Python', 'MySQL', 'Java', 'C++', 13, 'Python(1)+Java(4)+C++(8)=13；MySQL 是数据库'), -- A,C,D
('multiple', 'OSI 七层模型中，哪些属于上三层？', '物理层', '会话层', '表示层', '应用层', 14, '会话层(2)+表示层(4)+应用层(8)=14'), -- B,C,D
('multiple', 'HTTP 方法有哪些？', 'GET', 'POST', 'PUT', 'DELETE', 15, '全选：1+2+4+8=15'), -- A,B,C,D
('multiple', '以下哪些是关系型数据库？', 'MySQL', 'MongoDB', 'PostgreSQL', 'SQLite', 11, 'MySQL(1)+PostgreSQL(2)+SQLite(8)=11；MongoDB 是 NoSQL'), -- A,C,D
('multiple', 'C++ 中能重载的运算符有？', '[]', '::', '.', '++', 9, '[] (1) 和 ++ (8) 可重载；:: 和 . 不能'), -- A,D
('multiple', 'Linux 常用文本处理命令？', 'grep', 'awk', 'sed', 'cat', 15, '全部可处理文本：1+2+4+8=15'), -- A,B,C,D
('multiple', '以下哪些是前端技术？', 'HTML', 'CSS', 'JavaScript', 'PHP', 7, 'HTML(1)+CSS(2)+JS(4)=7；PHP 是后端'), -- A,B,C
('multiple', 'TCP 三次握手过程包括？', 'SYN', 'SYN-ACK', 'ACK', 'FIN', 7, 'SYN(1)+SYN-ACK(2)+ACK(4)=7；FIN 是断开'), -- A,B,C
('multiple', 'Python 中可变对象有？', 'list', 'tuple', 'dict', 'str', 5, 'list(1)+dict(4)=5；tuple/str 不可变'), -- A,C
('multiple', 'Git 常用命令？', 'git init', 'git add', 'git commit', 'git push', 15, '全选'), -- A,B,C,D
('multiple', '以下哪些是排序算法？', '快速排序', '冒泡排序', 'Dijkstra', '归并排序', 11, '快排(1)+冒泡(2)+归并(8)=11；Dijkstra 是最短路径'), -- A,B,D
('multiple', 'IPv6 地址特点？', '128位', '十六进制表示', '支持自动配置', '兼容 IPv4', 15, '全选'), -- A,B,C,D
('multiple', '面向对象三大特性？', '封装', '继承', '多态', '抽象', 15, '全选（常将抽象归入多态或单独列出，此处全选）'), -- A,B,C,D
('multiple', 'SQL 聚合函数有？', 'COUNT', 'SUM', 'AVG', 'GROUP_CONCAT', 15, '全选'), -- A,B,C,D
('multiple', '以下哪些是 NoSQL 数据库？', 'Redis', 'Cassandra', 'Oracle', 'MongoDB', 13, 'Redis(1)+Cassandra(4)+MongoDB(8)=13；Oracle 是关系型'), -- A,C,D
('multiple', '以下哪些状态码属于 2xx？', '200', '201', '204', '206', 15, '全选：200 OK, 201 Created, 204 No Content, 206 Partial Content'), -- A,B,C,D
('multiple', 'C++ 智能指针有？', 'unique_ptr', 'shared_ptr', 'weak_ptr', 'auto_ptr', 15, '前三个是标准，auto_ptr 已弃用；但常考，全选'), -- A,B,C,D
('multiple', 'Python 虚拟环境工具？', 'venv', 'virtualenv', 'conda', 'pipenv', 15, '全选'), -- A,B,C,D
('multiple', '操作系统功能包括？', '进程管理', '内存管理', '文件系统', '设备管理', 15, '全选'), -- A,B,C,D
('multiple', 'RESTful API 设计原则？', '使用 HTTP 方法', '无状态', '资源导向', 'HATEOAS', 15, '全选'); -- A,B,C,D

-- 判断题 20 道 (Ans: 2=错, 1=对)
INSERT INTO Questions (Type, Text, option1, option2, Ans, Analysis) VALUES
('judge', 'C++ 中 int 类型占 4 字节。', '对', '错', 1, '在大多数现代平台中正确'),
('judge', 'Java 是编译型语言。', '对', '错', 2, 'Java 是先编译为字节码，再由 JVM 解释/编译，属混合型，通常不称纯编译型'),
('judge', 'HTTP 是无状态协议。', '对', '错', 1, 'HTTP 本身无状态，靠 Cookie/Session 维持状态'),
('judge', '主键可以为 NULL。', '对', '错', 2, '主键必须非空且唯一'),
('judge', '索引一定能提高查询速度。', '对', '错', 2, '索引加速查询但降低写入性能，且不当索引可能无效'),
('judge', '递归函数必须有终止条件。', '对', '错', 1, '否则会栈溢出'),
('judge', 'Python 中列表是可变对象。', '对', '错', 1, 'list 可原地修改'),
('judge', 'GET 请求可以携带请求体（body）。', '对', '错', 2, 'RFC 规定 GET 不应有 body，虽部分服务允许，但标准中不推荐'),
('judge', 'TCP 提供可靠传输。', '对', '错', 1, 'TCP 通过确认、重传等机制保证可靠'),
('judge', 'IPv6 地址用冒号分隔。', '对', '错', 1, '如 2001:0db8::1'),
('judge', 'SQL 注入可通过参数化查询防御。', '对', '错', 1, '参数化查询是有效防御手段'),
('judge', 'Git 中 HEAD 指向当前分支最新提交。', '对', '错', 1, 'HEAD 通常指向当前分支的 tip'),
('judge', 'Linux 中 /etc 目录存放用户家目录。', '对', '错', 2, '/etc 存放配置文件；家目录在 /home'),
('judge', '哈希表查找平均时间复杂度为 O(1)。', '对', '错', 1, '理想情况下是 O(1)，冲突时退化为 O(n)'),
('judge', '二叉搜索树中左子树所有节点值 < 根 < 右子树所有节点值。', '对', '错', 1, '这是 BST 定义'),
('judge', 'Docker 是虚拟机。', '对', '错', 2, 'Docker 是容器，共享宿主机内核，非虚拟机'),
('judge', 'JSON 支持注释。', '对', '错', 2, '标准 JSON 不支持注释'),
('judge', '指针和引用在 C++ 中完全等价。', '对', '错', 2, '引用不可为空、不能重新绑定，指针可'),
('judge', '事务的 ACID 特性包括原子性、一致性、隔离性、持久性。', '对', '错', 1, 'ACID 定义'),
('judge', '一个类可以继承多个父类（C++）。', '对', '错', 1, 'C++ 支持多重继承');

-- 先插入 2 名老师（注意：Stu_num 和 Tutor 设为 NULL 或空字符串）
INSERT INTO Users (Usrname, Passwd, Full_name, Sex, Age, Id_card, Email, Phone, Faculty, Class, Stu_num, Tutor, Job_num, Role) VALUES
('teacher1', '123456', '张伟', '男', 35, '110101198901011234', 'zhangwei@edu.cn', '13800138000', '计算机学院', '软件工程系', NULL, NULL, 'T2023001', 'teacher'),
('teacher2', '123456', '李娜', '女', 32, '110101199102022345', 'lina@edu.cn', '13900139000', '数学学院', '应用数学系', NULL, NULL, 'T2023002', 'teacher');

-- 再插入 4 名学生，Tutor 字段指向上述老师的 Full_name
INSERT INTO Users (Usrname, Passwd, Full_name, Sex, Age, Id_card, Email, Phone, Faculty, Class, Stu_num, Tutor, Job_num, Role) VALUES
('stu001', '123456', '王小明', '男', 20, '110101200403033456', 'wangxiaoming@stu.edu.cn', '15000150000', '计算机学院', '软件工程2101', '202101001', '张伟', NULL, 'student'),
('stu002', '123456', '刘芳', '女', 19, '110101200404044567', 'liufang@stu.edu.cn', '15100151000', '计算机学院', '软件工程2101', '202101002', '张伟', NULL, 'student'),
('stu003', '123456', '陈浩', '男', 20, '110101200405055678', 'chenhao@stu.edu.cn', '15200152000', '数学学院', '数学与应用数学2102', '202102001', '李娜', NULL, 'student'),
('stu004', '123456', '赵雪', '女', 19, '110101200406066789', 'zhaoxue@stu.edu.cn', '15300153000', '数学学院', '数学与应用数学2102', '202102002', '李娜', NULL, 'student');


INSERT INTO Users (Usrname, Passwd, Role) VALUES ('admin', '123456', 'admin');