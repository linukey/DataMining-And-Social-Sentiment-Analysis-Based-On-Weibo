/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#ifndef __LINUKEY_LOG_H__
#define __LINUKEY_LOG_H__

#include <iostream>
#include <fstream>

namespace linukey{
namespace log{

enum LOG_LEVEL{
    TRACE = 0,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

const vector<std::string> LOG_LEVEL_STR{
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

const std::string positive_log_file="webserver.log1";
const std::string negative_log_file="webserver.log2";

static void LOGOUT(LOG_LEVEL level, std::string message) {
    std::string log_file;
    switch (level){
        case TRACE:
        case DEBUG:
        case INFO:
            log_file = positive_log_file;
        break;

        case WARN:
        case ERROR:
        case FATAL:
            log_file = negative_log_file;
        break;

        default:
            log_file = negative_log_file;
    };

    std::ofstream fout(log_file, std::ios::app);

    if (!fout.is_open()) {
        std::cerr << "open log file fatal!" << std::endl;
    }

    time_t rawtime;
    time(&rawtime);
    std::string time_str(ctime(&rawtime));

    fout << LOG_LEVEL_STR[level] << ":" <<  message << " " << time_str;
    fout.close();
}

}
}

#endif
