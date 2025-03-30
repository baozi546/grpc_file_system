#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include "define.grpc.pb.h"
#include "define.pb.h"
#include "FileDetail.h"
#include <map>
#include <mutex>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;

class FileServer final : public file_system::FileService::Service{
public:
    FileServer();
    
    /*Status FileUpload(ServerContext* context,
        ServerReaderWriter<file_system::ReceiveResponse, file_system::UploadRequest>* stream) override;
    Status FileDownload(ServerContext* context,
        ServerReaderWriter<file_system::DownloadResponse, file_system::DownloadRequest>* stream) override;
    Status FileModify(ServerContext* context,
        const file_system::ModifyRequest* request, file_system::OperationStatus* response) override;
    Status FileLists(ServerContext* context,
           const file_system::ListRequest* request, file_system::FileList* response) override;*/
 
protected:
    // type = 0为上传检测
    // type = 1为下载检测
    bool ValidateMetadata(const file_system::FileMetadata& data, std::shared_ptr<FileDetail> detail, int type);
    

private:
    std::map<std::string, std::shared_ptr<FileDetail>> File_Queue;//上传和下载都会被加入到该队列中 防止误操作
    std::mutex                        File_Queue_Mutex;
};