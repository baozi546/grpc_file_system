#include "AuthServer.h"
#include "tools.h"
#include "UserCheck.h"

AuthServer::AuthServer()
{

}

void AuthServer::Read_Dir_Config()
{
}


grpc::Status AuthServer::Login(grpc::ServerContext* context, const file_system::LoginRequest* request, file_system::OperationResponse* response)
{
    LOG_INFO("Login request received");
    std::string token;
    if (UserCheck::getInstance().loginCheck(request->username(), request->password(), token)) {
        LOG_INFO("Login success");
        response->set_success(true);
        response->set_extensions(token);
    }
    else {
        LOG_ERROR("Login failed");
        response->set_success(false);
        response->set_error_detail("username or passwork error");
    }

	return grpc::Status::OK;
}

grpc::Status AuthServer::CheckPermission(grpc::ServerContext* context, const file_system::PermissionRequest* request, file_system::PermissionResponse* response)
{
    return grpc::Status::OK;
}
