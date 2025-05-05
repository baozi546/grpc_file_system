#include "FileServer.h"
#include "AuthServer.h"
#include "tools.h"
#include <filesystem>
#include "ServerInterceptorFactory.h"
int main()
{
    std::filesystem::create_directory(DATA_PATH);
    std::filesystem::create_directory(UPDATE_PATH);
    std::filesystem::create_directory(DOWNLOAD_PATH);
    std::filesystem::create_directory("./data/conf");
    std::string server_address("0.0.0.0:8888");
    
    grpc::ServerBuilder builder;
    FileServer fileService;
    AuthServer authService;


    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&fileService);
    builder.RegisterService(&authService);

    std::vector<std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>>
        creators;
    for (auto i = 0; i < 1; i++) {
        creators.push_back(std::make_unique<ServerInterceptorFactory>());
    }
    builder.experimental().SetInterceptorCreators(
        std::move(creators)
    );
    builder.SetMaxReceiveMessageSize(1024 * 1024 * 20);
    builder.SetMaxSendMessageSize(1024 * 1024 * 20);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}