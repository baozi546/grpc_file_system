#include <gtest/gtest.h>

TEST(MyLibTestSuite, AddFunction) {
	EXPECT_EQ(1 + 1, 5);
	EXPECT_EQ(0, 0);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
