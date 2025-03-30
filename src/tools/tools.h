#pragma once
#include <windows.h>
#include <string>
#include <openssl/md5.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>

#define LOG_INFO(X) tools::logger::Get().Info(X)
#define LOG_WARNING(X) tools::logger::Get().Warning(X)
#define LOG_ERROR(X) tools::logger::Get().Error(X)
#define LOG_DEBUG(X) tools::logger::Get().Debug(X)

namespace tools {

    class logger {
    public:
        static logger& Get();
        void Info(const std::string& message);
        void Warning(const std::string& message);
        void Error(const std::string& message);
        void Debug(const std::string& message);
        void Set_Level(int level);
    private:
        logger();
        int level = 3;
        std::shared_ptr<spdlog::logger> logger_ptr_;
    };

    std::wstring StringToWString(const std::string& str);

    std::string WStringToString(const std::wstring& wstr);

    std::string calculate_md5(const char* data, const int size);
}