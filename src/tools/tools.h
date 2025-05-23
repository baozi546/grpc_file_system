#pragma once
#include <windows.h>
#include <string>
#include <openssl/md5.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>
#include <map>
namespace grpc
{
    class string_ref;
}

//#define LOG_INFO(X) tools::logger::Get().Info(X)
//#define LOG_WARNING(X) tools::logger::Get().Warning(X)
//#define LOG_ERROR(X) tools::logger::Get().Error(X)
//#define LOG_DEBUG(X) tools::logger::Get().Debug(X)
#define BLOCK_SIZE 1024 * 1024 * 4

#define LOG_INFO(X) std::cout << "[INFO]" << X << std::endl;
#define LOG_WARNING(X) std::cout << "[WARNING]" << X << std::endl;
#define LOG_ERROR(X) std::cout << "[ERROR]" << X << std::endl;
#define LOG_DEBUG(X) std::cout << "[DEBUG]" << X << std::endl;

#define DATA_PATH "./data"
#define UPDATE_PATH "./data/tmp_update"
#define DOWNLOAD_PATH "./data/tmp_download"
#define SAVE_PATH "./data/save"

#define CHUNK_SIZE 1024 * 1024 * 4

#define GetMetadataValue(InData,Key,OutValue){\
    auto it = InData.find(Key);\
    OutValue = (it != InData.end()) ? std::string(it->second.data(), it->second.size()) : "";\
};\


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

    bool Check_Filename(std::string filename);

}
