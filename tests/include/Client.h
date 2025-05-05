#ifndef  CLIENT_H
#define  CLIENT_H

#include <grpcpp/grpcpp.h>
#include "define.grpc.pb.h"
#include "define.pb.h"
#include <grpcpp/channel.h>

class Client {

public:
    Client(const std::string & ip);
    bool login(const std::string& username, const std::string& password , std::string& token);
    bool Dir_Create(const std::string token, const std::string root_path , std::string name);
    bool File_Remove(const std::string token,file_system::FileMetadata file, const std::string& type);
    bool File_Rename(const std::string token, const std::string root_path, std::string old_name, std::string new_name, const std::string& type);
    bool Get_List(const std::string token, const std::string root_path , std::vector<file_system::FileMetadata>& list);
    bool Find_File(const std::string token, const std::string root_path ,const std::string name, std::vector<file_system::FileMetadata>& list);
    bool UpTaskCreate(const std::string token, const file_system::FileMetadata& file, std::string& file_id);
    bool UpChunkStream(const std::string token, std::vector<file_system::FileChunk>& chunk_list,file_system::UploadStatus&resoonse);
    bool MergeChunk(const std::string token, const file_system::FileMetadata& metedata ,std::string& long_task_id);
    bool DownTaskCreate(const std::string token, const file_system::FileMetadata& file,std::string& file_id);
    bool DownChunkStream(const std::string token,const file_system::FileRequest request, std::vector<file_system::FileChunk>& chunk_list);
    //bool FileChunkUp(const std::string token, const std::string file_id, const std::string chunk_id, const std::string chunk_data)

private:
    std::unique_ptr<::file_system::AuthService::Stub> Auth_stub_;
    std::unique_ptr<::file_system::FileService::Stub> File_stub_;
};

#endif // !
