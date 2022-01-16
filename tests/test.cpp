// Copyright Davydov Nikolay 2021

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "unique_ptr.hpp"

using namespace my_unique_ptr;

TEST(UNIQUE_PTR, Constructors) {
    unique_ptr<int> unique_ptr1;
    unique_ptr<int> unique_ptr2(new int(400));
    unique_ptr<int> unique_ptr3(nullptr);

    EXPECT_TRUE(unique_ptr2.operator bool());
    EXPECT_FALSE(unique_ptr1.operator bool());
    EXPECT_FALSE(unique_ptr3.operator bool());

    unique_ptr<int> unique_ptr4(std::move(unique_ptr2));
    EXPECT_TRUE(unique_ptr4.operator bool());

    unique_ptr1 = std::move(unique_ptr4);
    EXPECT_TRUE(unique_ptr1.operator bool());

    unique_ptr<std::string> unique_ptr_str1(new std::string("Hello"));
    EXPECT_TRUE(unique_ptr_str1.operator bool());
    unique_ptr<std::string> unique_ptr_str2(std::move(unique_ptr_str1));
    EXPECT_TRUE(unique_ptr_str2.operator bool());
    unique_ptr<std::string> unique_ptr_str3;
    EXPECT_FALSE(unique_ptr_str3.operator bool());
    unique_ptr_str3 = std::move(unique_ptr_str2);
    EXPECT_TRUE(unique_ptr_str3.operator bool());

    unique_ptr<int> unique_ptr_arr1(new int[10]);
    EXPECT_TRUE(unique_ptr_arr1.operator bool());
    unique_ptr<int> unique_ptr_arr2(std::move(unique_ptr_arr1));
    EXPECT_TRUE(unique_ptr_arr2.operator bool());
}

TEST(UNIQUE_PTR, Access) {
    unique_ptr<int> unique_ptr1;
    EXPECT_FALSE(unique_ptr1);

    unique_ptr<int> unique_ptr2(new int(10));
    EXPECT_EQ(*unique_ptr2, 10);

    unique_ptr1 = std::move(unique_ptr2);
    EXPECT_EQ(*unique_ptr1, 10);

    unique_ptr<std::string> unique_ptr3(new std::string("Hello"));
    EXPECT_EQ(*unique_ptr3, "Hello");
}

TEST(UNIQUE_PTR, Get) {
    unique_ptr<int> unique_ptr1;
    EXPECT_EQ(unique_ptr1.get(), nullptr);

    int* ptr = new int(10);
    unique_ptr<int> unique_ptr2(ptr);
    EXPECT_EQ(unique_ptr2.get(), ptr);

    unique_ptr1 = std::move(unique_ptr2);
    EXPECT_EQ(unique_ptr1.get(), ptr);

    auto ptr2 = new char[10];
    unique_ptr<char> unique_ptr3;
    unique_ptr3.reset(ptr2);
    EXPECT_EQ(unique_ptr3.get(), ptr2);
}

TEST(UNIQUE_PTR, Reset) {
    unique_ptr<int> unique_ptr1;
    EXPECT_FALSE(unique_ptr1);

    unique_ptr1.reset(new int(10));
    EXPECT_EQ(*unique_ptr1, 10);

    unique_ptr<std::string> unique_ptr2(new std::string("Hello"));
    EXPECT_EQ(*unique_ptr2, "Hello");
    auto* str = new std::string("World");
    unique_ptr2.reset(str);
    EXPECT_EQ(*unique_ptr2, "World");
}

TEST(UNIQUE_PTR, SWAP) {
    unique_ptr<int> unique_ptr1(new int(20));
    unique_ptr<int> unique_ptr2(new int(10));
    EXPECT_EQ(*unique_ptr1, 20);
    EXPECT_EQ(*unique_ptr2, 10);

    unique_ptr1.swap(unique_ptr2);
    EXPECT_EQ(*unique_ptr2, 20);
    EXPECT_EQ(*unique_ptr1, 10);
}

TEST(UNIQUE_PTR, Release) {
    unique_ptr<int> unique_ptr1(new int(20));
    EXPECT_EQ(*unique_ptr1, 20);

    auto ptr = unique_ptr1.release();
    EXPECT_FALSE(unique_ptr1);
    EXPECT_EQ(*ptr, 20);
    delete ptr;

}

TEST(UNIQUE_PTR, MakeUnique) {
    unique_ptr<int> unique_p = my_unique_ptr::make_unique<int>(100);

    EXPECT_EQ(*unique_p, 100);
}
