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
#include "UserCheck.h"

using grpc::Server;
//using grpc::ServerBuilder;
//using grpc::ServerContext;
//using grpc::ServerReaderWriter;
//using grpc::Status;

class FileServer final : public file_system::FileService::Service{
public:
    FileServer();
    void Read_Dir_Config(); //读取配置文件
    void Set_UserCheck(std::shared_ptr<UserCheck> userCheck);
protected:
    // 一元 RPC：文件操作
    virtual ::grpc::Status FileOperation(
        ::grpc::ServerContext* context,
        const ::file_system::FileOperationRequest* request,
        ::file_system::OperationResponse* response
    );

    // 一元 RPC：上传文件请求（元数据协商）
    virtual ::grpc::Status UploadFileRequest(
        ::grpc::ServerContext* context,
        const ::file_system::FileMetadata* request,
        ::file_system::UploadFileResponse* response
    );

    // 客户端流式上传（断点续传）
    virtual ::grpc::Status UploadFile(
        ::grpc::ServerContext* context,
        ::grpc::ServerReader<::file_system::FileChunk>* reader,
        ::file_system::UploadStatus* response
    );

    // 服务端流式下载
    virtual ::grpc::Status DownloadFile(
        ::grpc::ServerContext* context,
        const ::file_system::FileRequest* request,
        ::grpc::ServerWriter<::file_system::FileChunk>* writer
    );

    // 一元 RPC：查询上传状态
    virtual ::grpc::Status CheckUploadStatus(
        ::grpc::ServerContext* context,
        const ::file_system::FileMetadata* request,
        ::file_system::UploadStatus* response
    );

    // 一元 RPC：合并分块请求
    virtual ::grpc::Status MergeChunkRequest(
        ::grpc::ServerContext* context,
        const ::file_system::FileMetadata* request,
        ::file_system::OperationResponse* response
    );

    // 服务端流式文件搜索
    virtual ::grpc::Status FindFile(
        ::grpc::ServerContext* context,
        const ::file_system::FindFileRequest* request,
        ::grpc::ServerWriter<::file_system::FileMetadata>* writer
    );

    // type = 0为上传检测
    // type = 1为下载检测
    //bool ValidateMetadata(const file_system::FileMetadata& data, std::shared_ptr<FileDetail> detail, int type);
    

private:
    std::shared_ptr<UserCheck> m_userCheck;
    std::map<std::string, std::shared_ptr<FileDetail>> File_Queue;//上传和下载都会被加入到该队列中 防止误操作
    std::mutex                        File_Queue_Mutex;
};