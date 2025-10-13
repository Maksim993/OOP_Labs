#include <gtest/gtest.h>
#include "Eleven.h"

TEST(ElevenTest, Basic) {
    Eleven num;
    EXPECT_EQ(num.to_string(), "0");
}

TEST(ElevenTest, FromString) {
    Eleven num("1A3");
    EXPECT_EQ(num.to_string(), "1A3");
}

TEST(ElevenTest, FromList) {
    Eleven num({1, 10, 3});
    EXPECT_EQ(num.to_string(), "1A3");
}

TEST(ElevenTest, Compare) {
    Eleven a("123");
    Eleven b("124");
    EXPECT_TRUE(b.greater(a));
    EXPECT_TRUE(a.less(b));
}

TEST(ElevenTest, Math) {
    Eleven a("12");
    Eleven b("1");
    Eleven res = a.plus(b);
    EXPECT_EQ(res.to_string(), "13");
    
    Eleven c("13");
    Eleven d("1");
    Eleven res2 = c.minus(d);
    EXPECT_EQ(res2.to_string(), "12");
}

TEST(ElevenTest, Errors) {
    Eleven a("1");
    Eleven b("2");
    EXPECT_THROW(a.minus(b), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}