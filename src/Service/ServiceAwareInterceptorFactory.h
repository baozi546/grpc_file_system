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

// �����֪��������ͬʱ������ͨ����ʽ����
class ServiceAwareInterceptor : public Interceptor {
    const std::string service_name_;
public:
    explicit ServiceAwareInterceptor(const std::string& service_name)
        : service_name_(service_name) {
    }

    void Intercept(InterceptorBatchMethods* methods) override {
        // �������ض�����
        if (service_name_ != "special.service") return;

        // ����ͬ�׶�
        if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {

            std::cout << "[Interceptor] Service: " << service_name_
                << " | Method: " << methods->GetSendInitialMetadata()->GetMethodName()
                << std::endl;
        }

        methods->Proceed();  // ����������

        if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {

            std::cout << "[Interceptor] Received message for " << service_name_ << std::endl;
        }
    }
};

// ��ʽר��������
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

// ������������ʵ�ַ��񼶹��ˣ�
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
            return nullptr;  // ��Ŀ���������

        // ���ݵ������ʹ�����ͬ������
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

// ����ʵ��ʾ��
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

    // ע��������
    SpecialServiceImpl special_service;
    NormalServiceImpl normal_service;
    builder.RegisterService(&special_service);
    builder.RegisterService(&normal_service);

    // ���÷����֪������������special.service��Ч��
    std::vector<std::string> target_services = { "special.service" };
    builder.experimental().SetInterceptorCreators(
        { new ServiceAwareInterceptorFactory(target_services) });

    // ��������
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return 0;
}


#endif