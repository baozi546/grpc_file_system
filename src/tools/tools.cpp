#include "tools.h"

std::wstring tools::StringToWString(const std::string& str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    std::wstring wstr(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], len);
    return wstr;
}

std::string tools::WStringToString(const std::wstring& wstr)
{
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string str(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], len, NULL, NULL);
    return str;
}

std::string tools::calculate_md5(const char* data,const int size)
{
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, data, size);
    MD5_Final(digest, &ctx);

    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return ss.str();
}

bool tools::Check_Filename(std::string filename)
{
    if (filename.empty())
        return false;
    const std::string invalid_chars = "/\\:*?\"<>|";
    if (filename.find_first_of(invalid_chars) != std::string::npos)
        return false;
    if (filename.length() > 255)
        return false;
    if (filename[0] == '.')
        return false;
    return true;
}


tools::logger& tools::logger::Get()
{
    static logger my;
    return my;
}
void tools::logger::Info(const std::string& message)
{
    if(level >= 0)
    logger_ptr_->info(message);
}
void tools::logger::Warning(const std::string& message)
{
    if (level >= 1)
    logger_ptr_->warn(message);
}
void tools::logger::Error(const std::string& message)
{
    if (level >= 2)
    logger_ptr_->error(message);
}
void tools::logger::Debug(const std::string& message)
{
    if (level >= 3)
    logger_ptr_->debug(message);
}
void tools::logger::Set_Level(int level)
{
    this->level = level;
}
tools::logger::logger(){
    logger_ptr_ = spdlog::stdout_color_mt("File_System");
}