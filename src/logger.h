#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    Logger();
    Logger(const std::string& filename);
    ~Logger();

    void log(LogLevel level, const std::string& message);

private:
    std::ofstream logfile;
    bool toFile;
    std::string timestamp();
};

#endif  // LOGGER_H
