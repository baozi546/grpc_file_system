#ifndef SERVICEAWAREINTERCEPTORFACTORY_H
#define SERVICEAWAREINTERCEPTORFACTORY_H

#include <grpcpp/grpcpp.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/experimental/server_interceptors.h>
#include <unordered_set>

using grpc::experimental::Interceptor;
using grpc::experimental::InterceptorBatchMethods;
using grpc::experimental::ServerInterceptorFactoryInterface;
using grpc::experimental::ServerRpcInfo;

// 服务感知拦截器（同时处理普通和流式请求）
class ServiceAwareInterceptor : public Interceptor {
    const std::string service_name_;
public:
    explicit ServiceAwareInterceptor(const std::string& service_name)
        : service_name_(service_name) {
    }

    void Intercept(InterceptorBatchMethods* methods) override {
        // 仅处理特定服务
        if (service_name_ != "special.service") return;

        // 处理不同阶段
        if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {

            std::cout << "[Interceptor] Service: " << service_name_
                << " | Method: " << methods->GetSendInitialMetadata()->GetMethodName()
                << std::endl;
        }

        methods->Proceed();  // 继续处理链

        if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {

            std::cout << "[Interceptor] Received message for " << service_name_ << std::endl;
        }
    }
};

// 流式专用拦截器
class StreamingInterceptor : public Interceptor {
    const std::string service_name_;
public:
    explicit StreamingInterceptor(const std::string& service_name)
        : service_name_(service_name) {
    }

    void Intercept(InterceptorBatchMethods* methods) override {
        if (service_name_ != "special.service") return;

        if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)) {

            std::cout << "[Stream] Receiving message for " << service_name_ << std::endl;
        }

        methods->Proceed();

        if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {

            std::cout << "[Stream] Sending response for " << service_name_ << std::endl;
        }
    }
};

// 拦截器工厂（实现服务级过滤）
class ServiceAwareInterceptorFactory : public ServerInterceptorFactoryInterface {
    std::unordered_set<std::string> target_services_;
public:
    explicit ServiceAwareInterceptorFactory(
        const std::vector<std::string>& services) {
        target_services_.insert(services.begin(), services.end());
    }

    Interceptor* CreateServerInterceptor(ServerRpcInfo* info) override {
        const std::string service_name =
            info->method()->service()->name()->ToString();

        if (!target_services_.count(service_name))
            return nullptr;  // 非目标服务不拦截

        // 根据调用类型创建不同拦截器
        switch (info->type()) {
        case ServerRpcInfo::Type::UNARY:
            return new ServiceAwareInterceptor(service_name);
        case ServerRpcInfo::Type::BIDI_STREAMING:
        case ServerRpcInfo::Type::CLIENT_STREAMING:
        case ServerRpcInfo::Type::SERVER_STREAMING:
            return new StreamingInterceptor(service_name);
        default:
            return nullptr;
        }
    }
};

// 服务实现示例
class SpecialServiceImpl : public SpecialService::Service {
    Status UnaryCall(ServerContext* ctx, const Request* req, Response* res) override {
        res->set_data("Special response");
        return Status::OK;
    }

    Status StreamingCall(ServerContext* ctx,
        ServerReaderWriter<Response, Request>* stream) override {
        Request req;
        while (stream->Read(&req)) {
            Response res;
            res.set_data("Stream data");
            stream->Write(res);
        }
        return Status::OK;
    }
};

class NormalServiceImpl : public NormalService::Service {
    Status NormalCall(ServerContext* ctx, const Request* req, Response* res) override {
        res->set_data("Normal response");
        return Status::OK;
    }
};

int main() {
    grpc::ServerBuilder builder;

    // 注册多个服务
    SpecialServiceImpl special_service;
    NormalServiceImpl normal_service;
    builder.RegisterService(&special_service);
    builder.RegisterService(&normal_service);

    // 配置服务感知拦截器（仅对special.service生效）
    std::vector<std::string> target_services = { "special.service" };
    builder.experimental().SetInterceptorCreators(
        { new ServiceAwareInterceptorFactory(target_services) });

    // 启动服务
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return 0;
}


#endif