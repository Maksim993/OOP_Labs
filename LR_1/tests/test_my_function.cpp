#include <gtest/gtest.h>
#include "my_function.h"

TEST(PalindromeTest, Test1) {
    EXPECT_TRUE(isPalindrome(""));
}

TEST(PalindromeTest, Test2) {
    EXPECT_TRUE(isPalindrome("a"));
}

TEST(PalindromeTest, Test3) {
    EXPECT_TRUE(isPalindrome("radar"));
}

TEST(PalindromeTest, Test4) {
    EXPECT_FALSE(isPalindrome("hello"));
}

TEST(PalindromeTest, Test5) {
    EXPECT_TRUE(isPalindrome("mam"));
}

TEST(PalindromeTest, Test6) {
    EXPECT_TRUE(isPalindrome("Madam"));
}

TEST(PalindromeTest, Test7) {
    EXPECT_TRUE(isPalindrome("12321"));
}

TEST(PalindromeTest, Test8) {
    EXPECT_FALSE(isPalindrome("12345"));
}