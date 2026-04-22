#ifndef LOG_H 
#define LOG_H 

#include <iostream>
#include <sstream> 

enum LogLevel { INFO, ERROR }; 

template<typename... T> 
void LOG(LogLevel level, T&&... args) {
    std::ostringstream ss;
    (ss << ... << args); 

    switch (level) {
        case INFO: std::cout << "[INFO] " << ss.str() << '\n'; break;
        case ERROR: std::cout << "\033[31m[ERROR] \033[0m" << ss.str() << '\n'; break;
    }
}

#endif 