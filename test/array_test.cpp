//
// Created by Piotr Brodzik on 06.05.2020.
//

#include <gtest/gtest.h>
#include "../include/array.hpp"

template<typename T>
class ArrayTest : public ::testing::Test {
};

using MyTypes = ::testing::Types<int, float, double>;
TYPED_TEST_CASE(ArrayTest, MyTypes);

TYPED_TEST(ArrayTest, sanity_check) {
    Array<TypeParam> arr(5);
    arr.Set(1, 123);
    EXPECT_EQ(123, arr.Get(1));
}

TYPED_TEST(ArrayTest, copy_constructor_performs_deep_copy) {
    Array<TypeParam> arr(10);
    arr.Set(1, 3);

    Array<TypeParam> arr2 = arr;
    arr2.Set(1, 7);

    EXPECT_EQ(3, arr.Get(1));
}

TYPED_TEST(ArrayTest, copy_assignment_operator_performs_deep_copy) {
    Array<TypeParam> arr(10);
    arr.Set(1, 3);

    Array<TypeParam> arr2(2);
    arr2 = arr;
    arr2.Set(1, 7);

    EXPECT_EQ(3, arr.Get(1));
}

TYPED_TEST(ArrayTest, throw_when_cannot_allocate_memory) {

    try {
        Array<TypeParam> arr(-1);
        FAIL() << "Expected std::bad_alloc";
    }
    catch (std::bad_alloc const &err) {
        EXPECT_EQ(err.what(), std::string("std::bad_alloc"));
    }
}

TEST(ArrayTest, member_variables_are_initialized) {
    Array<int> arr(0);
    EXPECT_EQ(nullptr, arr.m_pData);
}

TYPED_TEST(ArrayTest, throw_when_out_of_range) {
    Array<TypeParam> arr(5);
    EXPECT_THROW(arr.Get(10), std::out_of_range);
}


