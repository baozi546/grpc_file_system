#include "ServerInterceptorFactory.h"
#include "UserCheck.h"
#include "tools.h"


std::vector<std::string> ServerFileInterceptor::SplitMethodName(const std::string& full_method)
{
    std::vector<std::string> parts;
    size_t start = (full_method[0] == '/') ? 1 : 0; // 跳过开头的斜杠
    size_t pos = full_method.find('/', start);
    if (pos != std::string::npos) {
        parts.push_back(full_method.substr(start, pos - start)); // 服务名（如 "helloworld.Greeter"）
        parts.push_back(full_method.substr(pos + 1));           // 方法名（如 "SayHello"）
    }
    return parts;
}

void ServerFileInterceptor::Intercept(grpc::experimental::InterceptorBatchMethods* methods){
    if (methods->QueryInterceptionHookPoint(
        grpc::experimental::InterceptionHookPoints::POST_RECV_INITIAL_METADATA)) {
        if (server_name_ == "file_system.FileService") {
            auto metadata = methods->GetRecvInitialMetadata();
            std::string token;
            GetMetadataValue((*metadata), "token", token);

            std::string username;
            if (UserCheck::getInstance().tokenCheck(token, username)) {
                username = " " + username;
                metadata->insert({ "username", username});
            }/*
            else
            {
                grpc::Status error_status(grpc::StatusCode::UNAUTHENTICATED, "Invalid token");
                methods->ModifySendStatus(error_status);
            }*/
        }
    }
    methods->Proceed();
}

