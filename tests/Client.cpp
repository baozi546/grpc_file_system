#include "Client.h"

Client::Client(const std::string& ip)
{
	Auth_stub_ = std::make_unique<file_system::AuthService::Stub>(grpc::CreateChannel(ip, grpc::InsecureChannelCredentials()));
	File_stub_ = std::make_unique<file_system::FileService::Stub>(grpc::CreateChannel(ip, grpc::InsecureChannelCredentials()));
}

bool Client::login(const std::string& username, const std::string& password, std::string& token)
{
    file_system::LoginRequest request;
    file_system::OperationResponse response;

    request.set_username(username);
    request.set_password(password);

    grpc::ClientContext context;
    grpc::Status status = Auth_stub_->Login(&context, request, &response);//·¢ËÍ
    if (status.ok()) {
        if (response.success()) {
            token = response.extensions();
            return true;
        }
        else {
            std::cout<<response.error_detail()<<std::endl;
            return false;
        }
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }
}
