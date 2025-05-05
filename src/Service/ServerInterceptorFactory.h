#ifndef SERVERINTERCEPTORFACTORY_H
#define SERVERINTERCEPTORFACTORY_H

#include <grpcpp/grpcpp.h>          // ����ServerInterceptor����
#include <grpcpp/impl/codegen/server_interceptor.h>
#include "grpcpp/impl/interceptor_common.h"


class ServerFileInterceptor : public grpc::experimental::Interceptor {
public:
    explicit ServerFileInterceptor(const grpc::experimental::ServerRpcInfo* info) {
        // ������񷽷�Ԫ��Ϣ
        auto name =  SplitMethodName(info->method());
        server_name_ = name[0];
    }
    std::vector<std::string> SplitMethodName(const std::string& full_method);


    void Intercept(grpc::experimental::InterceptorBatchMethods* methods) override;

private:
    std::string server_name_;

};

class ServerInterceptorFactory : public grpc::experimental::ServerInterceptorFactoryInterface {
public:
    grpc::experimental::Interceptor* CreateServerInterceptor(
        grpc::experimental::ServerRpcInfo* info) override {
        return new ServerFileInterceptor(info); // ���ݷ��񷽷���Ϣ
    }
};

#endif