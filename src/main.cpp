#include "logger.h"
#include <iostream>

int main() {

    Logger logger("log/mercury.log");

    logger.log(INFO, "Mercury reporting for duty!");

    std::cout << "Hello, Clarice." << std::endl;
    return 0;
}
