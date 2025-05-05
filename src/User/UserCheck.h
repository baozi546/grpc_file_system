#ifndef  USERCHECK_H
#define  USERCHECK_H
#include <jwt-cpp/jwt.h>
#include <memory>
#include <shared_mutex>
class UserCheck {

public:

    UserCheck();
    ~UserCheck();

    static UserCheck& getInstance();

    bool loginCheck(const std::string& username, const std::string& password, std::string& token);

    bool tokenCheck(const std::string& token, std::string& username);

protected:
    std::string generate_secure_key(size_t length = 32);
private:
    struct user_info {
        std::string username;
        std::string password;
        std::string token;
        std::string user_type;
        std::chrono::time_point<std::chrono::system_clock> expire_time;
    };
    std::map<std::string, user_info> m_user_map;
    std::shared_mutex m_user_mutex;
    std::string m_secret_key;
};

#endif
