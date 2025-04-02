#include "FileServer.h"
#include <filesystem>
#include <fstream>
#include "tools.h"
#include "FileOperation.h"
FileServer::FileServer() {}

void FileServer::Read_Dir_Config()
{
}

void FileServer::Set_UserCheck(std::shared_ptr<UserCheck> userCheck)
{
	m_userCheck = userCheck;
}

::grpc::Status FileServer::FileOperation(::grpc::ServerContext* context, const::file_system::FileOperationRequest* request, ::file_system::OperationResponse* response)
{
	file_system::FileOperationType type = request->type();

	switch (type)
	{
	case file_system::CREATE:

		break;
	case file_system::REMOVE:
		break;
	case file_system::RENAME:
		break;
	case file_system::COPY:
		break;
	case file_system::FileOperationType_INT_MIN_SENTINEL_DO_NOT_USE_:
		break;
	case file_system::FileOperationType_INT_MAX_SENTINEL_DO_NOT_USE_:
		break;
	default:
		break;
	}

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::UploadFileRequest(::grpc::ServerContext* context, const::file_system::FileMetadata* request, ::file_system::UploadFileResponse* response)
{
	return ::grpc::Status::OK;
}

::grpc::Status FileServer::UploadFile(::grpc::ServerContext* context, ::grpc::ServerReader<::file_system::FileChunk>* reader, ::file_system::UploadStatus* response)
{
	return ::grpc::Status();
}

::grpc::Status FileServer::DownloadFile(::grpc::ServerContext* context, const::file_system::FileRequest* request, ::grpc::ServerWriter<::file_system::FileChunk>* writer)
{
	return ::grpc::Status();
}

::grpc::Status FileServer::CheckUploadStatus(::grpc::ServerContext* context, const::file_system::FileMetadata* request, ::file_system::UploadStatus* response)
{
	return ::grpc::Status();
}

::grpc::Status FileServer::MergeChunkRequest(::grpc::ServerContext* context, const::file_system::FileMetadata* request, ::file_system::OperationResponse* response)
{
	return ::grpc::Status();
}

::grpc::Status FileServer::FindFile(::grpc::ServerContext* context, const::file_system::FindFileRequest* request, ::grpc::ServerWriter<::file_system::FileMetadata>* writer)
{
	return ::grpc::Status();
}



