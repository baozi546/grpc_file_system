#include "FileServer.h"
#include "AuthServer.h"
#include "tools.h"
#include <filesystem>
int main()
{
    std::filesystem::create_directory("./data");
    std::filesystem::create_directory("./data/tmp");
    std::filesystem::create_directory("./data/save");
    std::string server_address("0.0.0.0:8888");

    grpc::ServerBuilder builder;
    FileServer fileService;
    AuthServer authService;


    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&fileService);
    builder.RegisterService(&authService);
    std::shared_ptr<UserCheck> userCheck = std::make_shared<UserCheck>();
    fileService.Set_UserCheck(userCheck);
    authService.Set_UserCheck(userCheck);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}