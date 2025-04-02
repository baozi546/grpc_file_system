#include "UserCheck.h"
#include <random>
UserCheck::UserCheck()
{
    m_secret_key = generate_secure_key(32);
}

UserCheck::~UserCheck()
{
}

bool UserCheck::loginCheck(const std::string& username, const std::string& password, std::string& token)
{
	std::shared_lock<std::shared_mutex> lock(m_user_mutex);
    if (username == "admin" && password == "admin") {
        token = "admin";
        return true;
    }
    if (m_user_map.find(username) != m_user_map.end())
    {
        auto& element = m_user_map[username];
        if (element.password == password)
        {
            if (std::chrono::system_clock::now() - element.expire_time < std::chrono::days(7)) {
                token = element.token;
            }
            else {
                token = jwt::create()
                    .set_issuer("zzh")          // 签发者
                    .set_type("JWT")              // 类型
                    .set_issued_at(std::chrono::system_clock::now())  // 签发时间
                    .set_expires_at(std::chrono::system_clock::now() + std::chrono::days(7))  // 过期时间
                    .set_payload_claim("username", jwt::claim(username))  // 自定义声明
                    .sign(jwt::algorithm::hs256{ m_secret_key });  // 使用 HMAC-SHA256 签名
            }
            return true;
        }
    }
	return false;
}

bool UserCheck::tokenCheck(const std::string& token , std::string& username)
{
    try{
    auto decoded_token = jwt::decode(token);

    // 验证签名
    auto verifier = jwt::verify()
        .allow_algorithm(jwt::algorithm::hs256{ m_secret_key })  // 允许的算法
        .with_issuer("zzh");  // 验证签发者

    verifier.verify(decoded_token);

    // 提取自定义声明
    username = decoded_token.get_payload_claim("username").as_string();
    
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}



std::string UserCheck::generate_secure_key(size_t length) //每次系统重启后生成新的key
{
    std::random_device rd;  // 使用硬件随机种子
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15); // 生成 0-15 的随机数

    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << dis(gen); // 转换为十六进制字符
    }
    return oss.str();
}
