#include "FileServer.h"
#include "tools.h"
#include <filesystem>

int main()
{
    std::filesystem::create_directory("./data");
    std::filesystem::create_directory("./data/tmp");
    std::filesystem::create_directory("./data/save");
    std::string server_address("0.0.0.0:8888");

    ServerBuilder builder;
    FileServer service;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}