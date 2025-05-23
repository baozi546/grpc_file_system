// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: define.proto

#include "define.pb.h"
#include "define.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace file_system {

static const char* AuthService_method_names[] = {
  "/file_system.AuthService/Login",
  "/file_system.AuthService/CheckPermission",
};

std::unique_ptr< AuthService::Stub> AuthService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< AuthService::Stub> stub(new AuthService::Stub(channel, options));
  return stub;
}

AuthService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Login_(AuthService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CheckPermission_(AuthService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status AuthService::Stub::Login(::grpc::ClientContext* context, const ::file_system::LoginRequest& request, ::file_system::OperationResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::LoginRequest, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Login_, context, request, response);
}

void AuthService::Stub::async::Login(::grpc::ClientContext* context, const ::file_system::LoginRequest* request, ::file_system::OperationResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::LoginRequest, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void AuthService::Stub::async::Login(::grpc::ClientContext* context, const ::file_system::LoginRequest* request, ::file_system::OperationResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::OperationResponse>* AuthService::Stub::PrepareAsyncLoginRaw(::grpc::ClientContext* context, const ::file_system::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::OperationResponse, ::file_system::LoginRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Login_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::OperationResponse>* AuthService::Stub::AsyncLoginRaw(::grpc::ClientContext* context, const ::file_system::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncLoginRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status AuthService::Stub::CheckPermission(::grpc::ClientContext* context, const ::file_system::PermissionRequest& request, ::file_system::PermissionResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::PermissionRequest, ::file_system::PermissionResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CheckPermission_, context, request, response);
}

void AuthService::Stub::async::CheckPermission(::grpc::ClientContext* context, const ::file_system::PermissionRequest* request, ::file_system::PermissionResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::PermissionRequest, ::file_system::PermissionResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckPermission_, context, request, response, std::move(f));
}

void AuthService::Stub::async::CheckPermission(::grpc::ClientContext* context, const ::file_system::PermissionRequest* request, ::file_system::PermissionResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckPermission_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::PermissionResponse>* AuthService::Stub::PrepareAsyncCheckPermissionRaw(::grpc::ClientContext* context, const ::file_system::PermissionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::PermissionResponse, ::file_system::PermissionRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CheckPermission_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::PermissionResponse>* AuthService::Stub::AsyncCheckPermissionRaw(::grpc::ClientContext* context, const ::file_system::PermissionRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCheckPermissionRaw(context, request, cq);
  result->StartCall();
  return result;
}

AuthService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      AuthService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< AuthService::Service, ::file_system::LoginRequest, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](AuthService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::LoginRequest* req,
             ::file_system::OperationResponse* resp) {
               return service->Login(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      AuthService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< AuthService::Service, ::file_system::PermissionRequest, ::file_system::PermissionResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](AuthService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::PermissionRequest* req,
             ::file_system::PermissionResponse* resp) {
               return service->CheckPermission(ctx, req, resp);
             }, this)));
}

AuthService::Service::~Service() {
}

::grpc::Status AuthService::Service::Login(::grpc::ServerContext* context, const ::file_system::LoginRequest* request, ::file_system::OperationResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AuthService::Service::CheckPermission(::grpc::ServerContext* context, const ::file_system::PermissionRequest* request, ::file_system::PermissionResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* FileService_method_names[] = {
  "/file_system.FileService/FileOperation",
  "/file_system.FileService/UploadFileRequest",
  "/file_system.FileService/UploadFile",
  "/file_system.FileService/DownloadFileRequest",
  "/file_system.FileService/DownloadFile",
  "/file_system.FileService/CheckUploadStatus",
  "/file_system.FileService/MergeChunkRequest",
  "/file_system.FileService/ProgressCheck",
  "/file_system.FileService/FindFile",
  "/file_system.FileService/GetFileList",
};

std::unique_ptr< FileService::Stub> FileService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< FileService::Stub> stub(new FileService::Stub(channel, options));
  return stub;
}

FileService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_FileOperation_(FileService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UploadFileRequest_(FileService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UploadFile_(FileService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  , rpcmethod_DownloadFileRequest_(FileService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DownloadFile_(FileService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_CheckUploadStatus_(FileService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_MergeChunkRequest_(FileService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ProgressCheck_(FileService_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_FindFile_(FileService_method_names[8], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_GetFileList_(FileService_method_names[9], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::Status FileService::Stub::FileOperation(::grpc::ClientContext* context, const ::file_system::FileOperationRequest& request, ::file_system::OperationResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::FileOperationRequest, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_FileOperation_, context, request, response);
}

void FileService::Stub::async::FileOperation(::grpc::ClientContext* context, const ::file_system::FileOperationRequest* request, ::file_system::OperationResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::FileOperationRequest, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_FileOperation_, context, request, response, std::move(f));
}

void FileService::Stub::async::FileOperation(::grpc::ClientContext* context, const ::file_system::FileOperationRequest* request, ::file_system::OperationResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_FileOperation_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::OperationResponse>* FileService::Stub::PrepareAsyncFileOperationRaw(::grpc::ClientContext* context, const ::file_system::FileOperationRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::OperationResponse, ::file_system::FileOperationRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_FileOperation_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::OperationResponse>* FileService::Stub::AsyncFileOperationRaw(::grpc::ClientContext* context, const ::file_system::FileOperationRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncFileOperationRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status FileService::Stub::UploadFileRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::file_system::UploadFileResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::FileMetadata, ::file_system::UploadFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_UploadFileRequest_, context, request, response);
}

void FileService::Stub::async::UploadFileRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::UploadFileResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::FileMetadata, ::file_system::UploadFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UploadFileRequest_, context, request, response, std::move(f));
}

void FileService::Stub::async::UploadFileRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::UploadFileResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UploadFileRequest_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::UploadFileResponse>* FileService::Stub::PrepareAsyncUploadFileRequestRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::UploadFileResponse, ::file_system::FileMetadata, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_UploadFileRequest_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::UploadFileResponse>* FileService::Stub::AsyncUploadFileRequestRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncUploadFileRequestRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientWriter< ::file_system::FileChunk>* FileService::Stub::UploadFileRaw(::grpc::ClientContext* context, ::file_system::UploadStatus* response) {
  return ::grpc::internal::ClientWriterFactory< ::file_system::FileChunk>::Create(channel_.get(), rpcmethod_UploadFile_, context, response);
}

void FileService::Stub::async::UploadFile(::grpc::ClientContext* context, ::file_system::UploadStatus* response, ::grpc::ClientWriteReactor< ::file_system::FileChunk>* reactor) {
  ::grpc::internal::ClientCallbackWriterFactory< ::file_system::FileChunk>::Create(stub_->channel_.get(), stub_->rpcmethod_UploadFile_, context, response, reactor);
}

::grpc::ClientAsyncWriter< ::file_system::FileChunk>* FileService::Stub::AsyncUploadFileRaw(::grpc::ClientContext* context, ::file_system::UploadStatus* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::file_system::FileChunk>::Create(channel_.get(), cq, rpcmethod_UploadFile_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::file_system::FileChunk>* FileService::Stub::PrepareAsyncUploadFileRaw(::grpc::ClientContext* context, ::file_system::UploadStatus* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::file_system::FileChunk>::Create(channel_.get(), cq, rpcmethod_UploadFile_, context, response, false, nullptr);
}

::grpc::Status FileService::Stub::DownloadFileRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::file_system::DownloadFileResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::FileMetadata, ::file_system::DownloadFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_DownloadFileRequest_, context, request, response);
}

void FileService::Stub::async::DownloadFileRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::DownloadFileResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::FileMetadata, ::file_system::DownloadFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DownloadFileRequest_, context, request, response, std::move(f));
}

void FileService::Stub::async::DownloadFileRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::DownloadFileResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DownloadFileRequest_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::DownloadFileResponse>* FileService::Stub::PrepareAsyncDownloadFileRequestRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::DownloadFileResponse, ::file_system::FileMetadata, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_DownloadFileRequest_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::DownloadFileResponse>* FileService::Stub::AsyncDownloadFileRequestRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncDownloadFileRequestRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReader< ::file_system::FileChunk>* FileService::Stub::DownloadFileRaw(::grpc::ClientContext* context, const ::file_system::FileRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::file_system::FileChunk>::Create(channel_.get(), rpcmethod_DownloadFile_, context, request);
}

void FileService::Stub::async::DownloadFile(::grpc::ClientContext* context, const ::file_system::FileRequest* request, ::grpc::ClientReadReactor< ::file_system::FileChunk>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::file_system::FileChunk>::Create(stub_->channel_.get(), stub_->rpcmethod_DownloadFile_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::file_system::FileChunk>* FileService::Stub::AsyncDownloadFileRaw(::grpc::ClientContext* context, const ::file_system::FileRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::file_system::FileChunk>::Create(channel_.get(), cq, rpcmethod_DownloadFile_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::file_system::FileChunk>* FileService::Stub::PrepareAsyncDownloadFileRaw(::grpc::ClientContext* context, const ::file_system::FileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::file_system::FileChunk>::Create(channel_.get(), cq, rpcmethod_DownloadFile_, context, request, false, nullptr);
}

::grpc::Status FileService::Stub::CheckUploadStatus(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::file_system::UploadStatus* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::FileMetadata, ::file_system::UploadStatus, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CheckUploadStatus_, context, request, response);
}

void FileService::Stub::async::CheckUploadStatus(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::UploadStatus* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::FileMetadata, ::file_system::UploadStatus, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckUploadStatus_, context, request, response, std::move(f));
}

void FileService::Stub::async::CheckUploadStatus(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::UploadStatus* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckUploadStatus_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::UploadStatus>* FileService::Stub::PrepareAsyncCheckUploadStatusRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::UploadStatus, ::file_system::FileMetadata, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CheckUploadStatus_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::UploadStatus>* FileService::Stub::AsyncCheckUploadStatusRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCheckUploadStatusRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status FileService::Stub::MergeChunkRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::file_system::OperationResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::FileMetadata, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_MergeChunkRequest_, context, request, response);
}

void FileService::Stub::async::MergeChunkRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::OperationResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::FileMetadata, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_MergeChunkRequest_, context, request, response, std::move(f));
}

void FileService::Stub::async::MergeChunkRequest(::grpc::ClientContext* context, const ::file_system::FileMetadata* request, ::file_system::OperationResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_MergeChunkRequest_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::OperationResponse>* FileService::Stub::PrepareAsyncMergeChunkRequestRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::OperationResponse, ::file_system::FileMetadata, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_MergeChunkRequest_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::OperationResponse>* FileService::Stub::AsyncMergeChunkRequestRaw(::grpc::ClientContext* context, const ::file_system::FileMetadata& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncMergeChunkRequestRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status FileService::Stub::ProgressCheck(::grpc::ClientContext* context, const ::file_system::ProgressRequest& request, ::file_system::ProgressRespond* response) {
  return ::grpc::internal::BlockingUnaryCall< ::file_system::ProgressRequest, ::file_system::ProgressRespond, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ProgressCheck_, context, request, response);
}

void FileService::Stub::async::ProgressCheck(::grpc::ClientContext* context, const ::file_system::ProgressRequest* request, ::file_system::ProgressRespond* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::file_system::ProgressRequest, ::file_system::ProgressRespond, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ProgressCheck_, context, request, response, std::move(f));
}

void FileService::Stub::async::ProgressCheck(::grpc::ClientContext* context, const ::file_system::ProgressRequest* request, ::file_system::ProgressRespond* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ProgressCheck_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::file_system::ProgressRespond>* FileService::Stub::PrepareAsyncProgressCheckRaw(::grpc::ClientContext* context, const ::file_system::ProgressRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::file_system::ProgressRespond, ::file_system::ProgressRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ProgressCheck_, context, request);
}

::grpc::ClientAsyncResponseReader< ::file_system::ProgressRespond>* FileService::Stub::AsyncProgressCheckRaw(::grpc::ClientContext* context, const ::file_system::ProgressRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncProgressCheckRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReader< ::file_system::FileMetadata>* FileService::Stub::FindFileRaw(::grpc::ClientContext* context, const ::file_system::FindFileRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::file_system::FileMetadata>::Create(channel_.get(), rpcmethod_FindFile_, context, request);
}

void FileService::Stub::async::FindFile(::grpc::ClientContext* context, const ::file_system::FindFileRequest* request, ::grpc::ClientReadReactor< ::file_system::FileMetadata>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::file_system::FileMetadata>::Create(stub_->channel_.get(), stub_->rpcmethod_FindFile_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::file_system::FileMetadata>* FileService::Stub::AsyncFindFileRaw(::grpc::ClientContext* context, const ::file_system::FindFileRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::file_system::FileMetadata>::Create(channel_.get(), cq, rpcmethod_FindFile_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::file_system::FileMetadata>* FileService::Stub::PrepareAsyncFindFileRaw(::grpc::ClientContext* context, const ::file_system::FindFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::file_system::FileMetadata>::Create(channel_.get(), cq, rpcmethod_FindFile_, context, request, false, nullptr);
}

::grpc::ClientReader< ::file_system::FileMetadata>* FileService::Stub::GetFileListRaw(::grpc::ClientContext* context, const ::file_system::GetFileListRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::file_system::FileMetadata>::Create(channel_.get(), rpcmethod_GetFileList_, context, request);
}

void FileService::Stub::async::GetFileList(::grpc::ClientContext* context, const ::file_system::GetFileListRequest* request, ::grpc::ClientReadReactor< ::file_system::FileMetadata>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::file_system::FileMetadata>::Create(stub_->channel_.get(), stub_->rpcmethod_GetFileList_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::file_system::FileMetadata>* FileService::Stub::AsyncGetFileListRaw(::grpc::ClientContext* context, const ::file_system::GetFileListRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::file_system::FileMetadata>::Create(channel_.get(), cq, rpcmethod_GetFileList_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::file_system::FileMetadata>* FileService::Stub::PrepareAsyncGetFileListRaw(::grpc::ClientContext* context, const ::file_system::GetFileListRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::file_system::FileMetadata>::Create(channel_.get(), cq, rpcmethod_GetFileList_, context, request, false, nullptr);
}

FileService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FileService::Service, ::file_system::FileOperationRequest, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::FileOperationRequest* req,
             ::file_system::OperationResponse* resp) {
               return service->FileOperation(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FileService::Service, ::file_system::FileMetadata, ::file_system::UploadFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::FileMetadata* req,
             ::file_system::UploadFileResponse* resp) {
               return service->UploadFileRequest(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[2],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< FileService::Service, ::file_system::FileChunk, ::file_system::UploadStatus>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReader<::file_system::FileChunk>* reader,
             ::file_system::UploadStatus* resp) {
               return service->UploadFile(ctx, reader, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FileService::Service, ::file_system::FileMetadata, ::file_system::DownloadFileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::FileMetadata* req,
             ::file_system::DownloadFileResponse* resp) {
               return service->DownloadFileRequest(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[4],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< FileService::Service, ::file_system::FileRequest, ::file_system::FileChunk>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::FileRequest* req,
             ::grpc::ServerWriter<::file_system::FileChunk>* writer) {
               return service->DownloadFile(ctx, req, writer);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FileService::Service, ::file_system::FileMetadata, ::file_system::UploadStatus, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::FileMetadata* req,
             ::file_system::UploadStatus* resp) {
               return service->CheckUploadStatus(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FileService::Service, ::file_system::FileMetadata, ::file_system::OperationResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::FileMetadata* req,
             ::file_system::OperationResponse* resp) {
               return service->MergeChunkRequest(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FileService::Service, ::file_system::ProgressRequest, ::file_system::ProgressRespond, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::ProgressRequest* req,
             ::file_system::ProgressRespond* resp) {
               return service->ProgressCheck(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[8],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< FileService::Service, ::file_system::FindFileRequest, ::file_system::FileMetadata>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::FindFileRequest* req,
             ::grpc::ServerWriter<::file_system::FileMetadata>* writer) {
               return service->FindFile(ctx, req, writer);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileService_method_names[9],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< FileService::Service, ::file_system::GetFileListRequest, ::file_system::FileMetadata>(
          [](FileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::file_system::GetFileListRequest* req,
             ::grpc::ServerWriter<::file_system::FileMetadata>* writer) {
               return service->GetFileList(ctx, req, writer);
             }, this)));
}

FileService::Service::~Service() {
}

::grpc::Status FileService::Service::FileOperation(::grpc::ServerContext* context, const ::file_system::FileOperationRequest* request, ::file_system::OperationResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::UploadFileRequest(::grpc::ServerContext* context, const ::file_system::FileMetadata* request, ::file_system::UploadFileResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::UploadFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::file_system::FileChunk>* reader, ::file_system::UploadStatus* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::DownloadFileRequest(::grpc::ServerContext* context, const ::file_system::FileMetadata* request, ::file_system::DownloadFileResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::DownloadFile(::grpc::ServerContext* context, const ::file_system::FileRequest* request, ::grpc::ServerWriter< ::file_system::FileChunk>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::CheckUploadStatus(::grpc::ServerContext* context, const ::file_system::FileMetadata* request, ::file_system::UploadStatus* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::MergeChunkRequest(::grpc::ServerContext* context, const ::file_system::FileMetadata* request, ::file_system::OperationResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::ProgressCheck(::grpc::ServerContext* context, const ::file_system::ProgressRequest* request, ::file_system::ProgressRespond* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::FindFile(::grpc::ServerContext* context, const ::file_system::FindFileRequest* request, ::grpc::ServerWriter< ::file_system::FileMetadata>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileService::Service::GetFileList(::grpc::ServerContext* context, const ::file_system::GetFileListRequest* request, ::grpc::ServerWriter< ::file_system::FileMetadata>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace file_system

