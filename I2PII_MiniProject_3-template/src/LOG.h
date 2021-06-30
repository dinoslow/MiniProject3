/**
 * @file LOG.h
 * @author Me (https://hackmd.io/zTTsOA9pRZGhzlqwiIAi8A)
 * @version 0.1
 * @date 2021-06-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DEBUGLOG
#define DEBUGLOG
#include <bits/stdc++.h>

class LOG {
   public:
    enum TYPE {
        INFO,
        ERROR,
        NONE
    };
    static std::ofstream LOGFOUT;
    TYPE type;
    LOG(TYPE type = NONE) : type(type) {}
    ~LOG() {}
    template <class T>
    LOG& operator<<(const T& msg) {
        switch (this->type) {
            case INFO:
                LOGFOUT << "[INFO]: ";
                break;
            case ERROR:
                LOGFOUT << "[ERROR]: ";
                break;
            default:
                break;
        }
        this->LOGFOUT << msg;
        this->LOGFOUT.flush();
        return *this;
    }
    static void initialize() {
        LOGFOUT.open("debuglog.txt", std::ofstream::ate | std::ofstream::app);
    }
    static void terminate() {
        LOGFOUT.close();
    }
};
std::ofstream LOG::LOGFOUT;

#endif