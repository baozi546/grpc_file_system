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
                    .set_issuer("zzh")          // ǩ����
                    .set_type("JWT")              // ����
                    .set_issued_at(std::chrono::system_clock::now())  // ǩ��ʱ��
                    .set_expires_at(std::chrono::system_clock::now() + std::chrono::days(7))  // ����ʱ��
                    .set_payload_claim("username", jwt::claim(username))  // �Զ�������
                    .sign(jwt::algorithm::hs256{ m_secret_key });  // ʹ�� HMAC-SHA256 ǩ��
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

    // ��֤ǩ��
    auto verifier = jwt::verify()
        .allow_algorithm(jwt::algorithm::hs256{ m_secret_key })  // ������㷨
        .with_issuer("zzh");  // ��֤ǩ����

    verifier.verify(decoded_token);

    // ��ȡ�Զ�������
    username = decoded_token.get_payload_claim("username").as_string();
    
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}



std::string UserCheck::generate_secure_key(size_t length) //ÿ��ϵͳ�����������µ�key
{
    std::random_device rd;  // ʹ��Ӳ���������
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15); // ���� 0-15 �������

    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << dis(gen); // ת��Ϊʮ�������ַ�
    }
    return oss.str();
}
