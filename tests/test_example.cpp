#include <gtest/gtest.h>
#include "Client.h"
#include "tools.h"
#include <filesystem>
class MyClassTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试用例执行前调用（构造对象）
        obj_ = new Client("127.0.0.1:8888");
    }

    void TearDown() override {
        // 在每个测试用例执行后调用（释放资源）
        delete obj_;
    }

    Client* obj_;  // 被测对象
};

// 测试用例
TEST_F(MyClassTest, LoginTest) {
    std::string token;
    EXPECT_TRUE(obj_->login("admin","admin",token));//admin 直接返回token admin 
    EXPECT_EQ(token,"admin");
  
}

TEST_F(MyClassTest, Loginnormal) {
    std::string token;
    EXPECT_TRUE(obj_->login("zzh", "123456", token));//admin 直接返回token admin 
    std::cout << token << std::endl;
}

TEST_F(MyClassTest, Create_Dir_Test) {
    std::string token;
    EXPECT_TRUE(obj_->login("zzh", "123456", token));//admin 直接返回token admin 
    EXPECT_TRUE(obj_->Dir_Create(token,"", "zzh"));
    std::vector<file_system::FileMetadata> lists;
    obj_->Get_List(token, "", lists);
    std::vector<std::string> names;
    EXPECT_EQ(lists.size(), 1);
    for (int i = 0; i < lists.size(); i++)
    {
        std::cout << lists[i].file_name() << std::endl;
    }
}

TEST_F(MyClassTest, UpTest) {
    std::string token;
    EXPECT_TRUE(obj_->login("zzh", "123456", token));

    std::wstring test_path = L"D:\\Project\\grpc_file_system\\tests\\testData\\test.txt";
    std::ifstream file(test_path, std::ios::binary);
    std::vector <file_system::FileChunk> lists;
    EXPECT_TRUE(file.is_open());

    char *buffer = new char[CHUNK_SIZE];
    file_system::FileChunk chunk;
    std::string file_data;
    while (true) {
        file.read(buffer, CHUNK_SIZE);
        int count = file.gcount();

        if (count == 0) break;

        std::string chunk_md5;
        chunk.set_data(buffer, count);
        chunk.set_chunk_size(count);
        lists.push_back(chunk);
        file_data += chunk.data();
        chunk_md5 = tools::calculate_md5(buffer , count);
    }

    std::string md5 = tools::calculate_md5(file_data.c_str(),file_data.size());
    delete[] buffer;
    
    file_system::FileMetadata metadata;
    metadata.set_file_name("test.txt");
    metadata.set_file_size(file_data.size());
    metadata.set_parent_path("");
    
    std::string file_id;
    EXPECT_TRUE(obj_->UpTaskCreate(token, metadata, file_id));
    for (auto& chunk : lists)
    {
        chunk.set_file_id(file_id);
    }
    std::cout << file_id << std::endl;
    file_system::UploadStatus status;
    EXPECT_TRUE(obj_->UpChunkStream(token, lists , status));
    for (auto [key, ok] : status.chunk_status()) {
        std::cout << key << " " << ( ok? "True" : "False") << std::endl;
    }
    std::string long_task_id;
    metadata.set_file_id(file_id);
    EXPECT_TRUE(obj_->MergeChunk(token, metadata, long_task_id));
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
    system("pause");
    return 0;
}
