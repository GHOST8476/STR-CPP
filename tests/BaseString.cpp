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

TEST(BaseString, Iterators)
{
    str_t &str = derstr_t("hello world");

    ASSERT_EQ(*str.begin(), 'h');     // iterator to the first element
    ASSERT_EQ(*(str.end() - 1), 'd'); // iterator to the last element
    ASSERT_EQ(*str.it(4), 'o');       // iterator to the index element

    ASSERT_EQ(*str.rbegin(), 'd');     // reverse iterator to the first (end()) element
    ASSERT_EQ(*str.rit(4), 'w');       // reverse iterator to the index it(size() - index) element
    ASSERT_EQ(*(str.rend() - 1), 'h'); // reverse iterator to the last (begin()) element

    ASSERT_EQ(str.toindex(str.begin() + 5), 5); // return index from iterator
}