#include <gtest/gtest.h>
#include "Client.h"

class MyClassTest : public ::testing::Test {
protected:
    void SetUp() override {
        // ��ÿ����������ִ��ǰ���ã��������
        obj_ = new Client("127.0.0.1:8888");
    }

    void TearDown() override {
        // ��ÿ����������ִ�к���ã��ͷ���Դ��
        delete obj_;
    }

    Client* obj_;  // �������
};

// ��������
TEST_F(MyClassTest, DefaultConstructor) {
    std::string token;
    EXPECT_TRUE(obj_->login("admin","admin",token));//admin ֱ�ӷ���token admin 
    EXPECT_EQ(token,"admin");
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
    system("pause");
    return 0;
}
