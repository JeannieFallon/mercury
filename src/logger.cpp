#include "logger.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>

Logger::Logger() : toFile(false) {}

Logger::Logger(const std::string& filename) : toFile(true) {
    // Create log dir if needed
    size_t pos = filename.find_last_of('/');
    if (pos != std::string::npos) {
        std::string dir = filename.substr(0, pos);
        mkdir(dir.c_str(), 0755);   // POSIX
    }

    logfile.open(filename, std::ios::app);
}

Logger::~Logger() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    std::string prefix;
    switch (level) {
        case DEBUG: prefix = "[DEBUG] "; break;
        case INFO:  prefix = "[INFO] "; break;
        case WARN:  prefix = "[WARN] "; break;
        case ERROR: prefix = "[ERROR] "; break;
    }

    std::string line = timestamp() + " " + prefix + message;

    std::cout << line << std::endl;

    if (toFile && logfile.is_open()) {
        logfile << line << std::endl;
    }
}

std::string Logger::timestamp() {
    using std::chrono::system_clock;
    auto now = system_clock::now();
    std::time_t now_c = system_clock::to_time_t(now);

    std::ostringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

