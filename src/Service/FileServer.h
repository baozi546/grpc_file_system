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
#include "FileDirTree.h"
#include  <queue>
#include "tools.h"
#include "element_define.h"
#include "ThreadPool.h"

using grpc::Server;
//using grpc::ServerBuilder;
//using grpc::ServerContext;
//using grpc::ServerReaderWriter;
//using grpc::Status;

class FileServer final : public file_system::FileService::Service {
public:
    FileServer();
    void Read_Dir_Config(); //��ȡ�����ļ�
    bool split_directory_path(const std::string& input_path, std::queue<std::string>& output);

private:
    bool File_Update_Queue_Add(const std::string username,const ::file_system::FileMetadata& metadata);//����ϴ�����
    bool File_Chunk_Write(const std::string username, const file_system::FileChunk& chunk);
    bool File_Download_Queue_Add(const std::string username, const file_system::FileMetadata& metadata); //�����������

private:
    int FileCreate(std::string username,
        const::file_system::CreateRequest& request, ::file_system::OperationResponse* response);
    int FileRemove(std::string username,
        const::file_system::RemoveRequest& request, ::file_system::OperationResponse* response);
    int FileRename(std::string username,
        const::file_system::ReNameRequest& request, ::file_system::OperationResponse* response);

    int GetFileList(std::string username, 
        const::file_system::GetFileListRequest* request,::grpc::ServerWriter<::file_system::FileMetadata>* writer);
    int FileFile(std::string username,
        const ::file_system::FindFileRequest* request, ::grpc::ServerWriter<::file_system::FileMetadata>* writer);

    int FileUpTaskCreate(std::string username,
        const::file_system::FileMetadata* request, ::file_system::UploadFileResponse* response);
    int FileUpdateStream(std::string username,
        ::grpc::ServerReader<::file_system::FileChunk>* reader, ::file_system::UploadStatus* response);
    
    int FileMergeChunk(std::string username,
        const::file_system::FileMetadata* request, ::file_system::OperationResponse* response);
    int FileDownTaskCreate(std::string username,
        const::file_system::FileMetadata* request, ::file_system::DownloadFileResponse* response);
    int FileDownloadStream(std::string username,
        const ::file_system::FileRequest* request,::grpc::ServerWriter<::file_system::FileChunk>* writer);

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

    virtual ::grpc::Status DownloadFileRequest(
        ::grpc::ServerContext* context,
        const ::file_system::FileMetadata* request,
        ::file_system::DownloadFileResponse response
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

    virtual ::grpc::Status GetFileList(
        ::grpc::ServerContext* context,
        const ::file_system::GetFileListRequest* request,
        ::grpc::ServerWriter<::file_system::FileMetadata>* writer
    );

    virtual ::grpc::Status ProgressCheck(
        ::grpc::ServerContext* context,
        const ::file_system::ProgressRequest* request,
        ::file_system::ProgressRespond* response
    );
    // type = 0Ϊ�ϴ����
    // type = 1Ϊ���ؼ��
    //bool ValidateMetadata(const file_system::FileMetadata& data, std::shared_ptr<FileDetail> detail, int type);


private:
    
    TaskQueue<FileDetail> Update_File_Queue;
    TaskQueue<FileMeteData> Download_File_Queue;
    TaskQueue<FileMeteData> m_file;

    TaskQueue<std::shared_ptr<std::atomic_int>> m_long_task_progress;

    std::map<std::string,std::shared_ptr<FileDirTree>> m_dir_tree; //�����ļ�Ŀ¼��
    std::shared_ptr<std::mt19937_64> m_random_task = nullptr;
    //std::vector<std::pair<std::mutex,std::map<std::string, std::map<FileDetail>>> m_file_detail_map;
};