#include <gtest/gtest.h>
#include <str/stackstr>

using str_t = str::basic_str<char>;
using derstr_t = str::basic_stackstr<200, char>;

TEST(BaseString, ElementAccess)
{
    str_t &str = derstr_t("hello world");

    // does not perform bound checking
    ASSERT_NO_THROW(str[50]);

    // performs bound checking
    ASSERT_THROW(str.at(50), std::out_of_range);

    // access any element
    ASSERT_EQ(str.at(4), 'o');

    // first element
    ASSERT_EQ(str.front(), 'h');

    // last element
    ASSERT_EQ(str.back(), 'd');

    // pointer to the first element
    ASSERT_EQ(*str.data(), str.front());

    // const pointer to the first element
    ASSERT_EQ(str.c_str(), str.data());
}