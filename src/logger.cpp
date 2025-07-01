#include "logger.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>

namespace fs = std::filesystem;

Logger::Logger() : toFile(false) {}

Logger::Logger(const std::string& filename) : toFile(true) {
    fs::path path(filename);

    if (!path.parent_path().empty()) {
        fs::create_directories(path.parent_path());
    }

    logfile.open(filename, std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Logger ERROR: Failed to open log file: " << filename << std::endl;
        toFile = false;
    }
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

