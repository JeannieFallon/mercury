#include "logger.h"
#include <iostream>
#include <string>
#include <curl/curl.h>

// Helper func for response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    // Init logging
    Logger logger("log/mercury.log");
    logger.log(INFO, "Mercury reporting for duty!");

    CURL* curl;
    CURLcode res;

    // FIXME hardcoded test prompt for development
    std::string prompt = "Summarize this test log message and suggest recommended actions: Unauthorized SSH attempt from 192.168.1.50";

    // Local ollama server
    std::string url = "http://127.0.0.1:11434/api/generate";
    std::string jsonData = R"({"model":"llama3.1","prompt":")" + prompt + R"(","stream":false})";
    std::string response;



    curl = curl_easy_init();
    if(curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Ollama response: " << response << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        std::cerr << "Failed to initialize curl" << std::endl;
    }

    logger.log(INFO, "Mercury out!");
    return 0;
}
