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
    void Read_Dir_Config(); //��ȡ�����ļ�
    void Set_UserCheck(std::shared_ptr<UserCheck> userCheck);
protected:
    // һԪ RPC���ļ�����
    virtual ::grpc::Status FileOperation(
        ::grpc::ServerContext* context,
        const ::file_system::FileOperationRequest* request,
        ::file_system::OperationResponse* response
    );

    // һԪ RPC���ϴ��ļ�����Ԫ����Э�̣�
    virtual ::grpc::Status UploadFileRequest(
        ::grpc::ServerContext* context,
        const ::file_system::FileMetadata* request,
        ::file_system::UploadFileResponse* response
    );

    // �ͻ�����ʽ�ϴ����ϵ�������
    virtual ::grpc::Status UploadFile(
        ::grpc::ServerContext* context,
        ::grpc::ServerReader<::file_system::FileChunk>* reader,
        ::file_system::UploadStatus* response
    );

    // �������ʽ����
    virtual ::grpc::Status DownloadFile(
        ::grpc::ServerContext* context,
        const ::file_system::FileRequest* request,
        ::grpc::ServerWriter<::file_system::FileChunk>* writer
    );

    // һԪ RPC����ѯ�ϴ�״̬
    virtual ::grpc::Status CheckUploadStatus(
        ::grpc::ServerContext* context,
        const ::file_system::FileMetadata* request,
        ::file_system::UploadStatus* response
    );

    // һԪ RPC���ϲ��ֿ�����
    virtual ::grpc::Status MergeChunkRequest(
        ::grpc::ServerContext* context,
        const ::file_system::FileMetadata* request,
        ::file_system::OperationResponse* response
    );

    // �������ʽ�ļ�����
    virtual ::grpc::Status FindFile(
        ::grpc::ServerContext* context,
        const ::file_system::FindFileRequest* request,
        ::grpc::ServerWriter<::file_system::FileMetadata>* writer
    );

    // type = 0Ϊ�ϴ����
    // type = 1Ϊ���ؼ��
    //bool ValidateMetadata(const file_system::FileMetadata& data, std::shared_ptr<FileDetail> detail, int type);
    

private:
    std::shared_ptr<UserCheck> m_userCheck;
    std::map<std::string, std::shared_ptr<FileDetail>> File_Queue;//�ϴ������ض��ᱻ���뵽�ö����� ��ֹ�����
    std::mutex                        File_Queue_Mutex;
};