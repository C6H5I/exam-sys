# pragma once

#include "headers.hpp"
#include "database.hpp"

class Manager{
    DatabaseManager db;
    void sign_in();
    void sign_up();
    
public:
    void run();
};

