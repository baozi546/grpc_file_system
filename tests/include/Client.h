#ifndef  CLIENT_H
#define  CLIENT_H

#include <grpcpp/grpcpp.h>
#include "define.grpc.pb.h"
#include <grpcpp/channel.h>

class Client {

public:
    Client(const std::string & ip);
    bool login(const std::string& username, const std::string& password , std::string& token);

private:
    std::unique_ptr<::file_system::AuthService::Stub> Auth_stub_;
    std::unique_ptr<::file_system::FileService::Stub> File_stub_;
};

#endif // !
