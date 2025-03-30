protoc -I ./ --grpc_out=.  --plugin=protoc-gen-grpc="D:\Git\vcpkg\installed\x64-windows\tools\grpc\grpc_cpp_plugin.exe" ./define.proto
protoc -I ./ --cpp_out=. ./define.proto