#include <gtest/gtest.h>
#include "Client.h"

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
TEST_F(MyClassTest, DefaultConstructor) {
    std::string token;
    EXPECT_TRUE(obj_->login("admin","admin",token));//admin 直接返回token admin 
    EXPECT_EQ(token,"admin");
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
    system("pause");
    return 0;
}
