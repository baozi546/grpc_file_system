#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include <iostream>
#include <memory>
#include <string>
#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include "define.grpc.pb.h"
#include "define.pb.h"
#include <map>
#include <mutex>
#include "UserCheck.h"

using grpc::Server;
class AuthServer final : public file_system::AuthService::Service {
public:
     AuthServer();
     void Read_Dir_Config();
     void Set_UserCheck(std::shared_ptr<UserCheck> userCheck);
protected:
    virtual grpc::Status Login(grpc::ServerContext* context,
        const file_system::LoginRequest* request,
        file_system::OperationResponse* response) override;

    virtual grpc::Status CheckPermission(grpc::ServerContext* context,
        const file_system::PermissionRequest* request,
        file_system::PermissionResponse* response) override;
private:
    std::shared_ptr<UserCheck> m_userCheck;
};



#endif // !
