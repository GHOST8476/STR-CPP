#include <gtest/gtest.h>
#include <str/stackstr>
#include <str/heapstr>

using str_t = str::basic_str<char>;
using stackstr_t = str::basic_stackstr<200, char>;
using heapstr_t = str::basic_heapstr<char>;

TEST(BaseString, ElementAccess)
{
    str_t &str = stackstr_t("hello world");

    ASSERT_NO_THROW(str[50]);                    // does not perform bound checking
    ASSERT_THROW(str.at(50), std::out_of_range); // performs bound checking

    ASSERT_EQ(str.at(4), 'o');   // access any element
    ASSERT_EQ(str.front(), 'h'); // first element
    ASSERT_EQ(str.back(), 'd');  // last element

    ASSERT_EQ(*str.data(), str.front()); // pointer to the first element
    ASSERT_EQ(str.c_str(), str.data());  // const pointer to the first element
}

TEST(BaseString, Iterators)
{
    str_t &str = stackstr_t("hello world");

    ASSERT_EQ(*str.begin(), 'h');     // iterator to the first element
    ASSERT_EQ(*(str.end() - 1), 'd'); // iterator to the last element
    ASSERT_EQ(*str.it(4), 'o');       // iterator to the index element

    ASSERT_EQ(*str.rbegin(), 'd');     // reverse iterator to the first (end()) element
    ASSERT_EQ(*str.rit(4), 'w');       // reverse iterator to the index it(size() - index) element
    ASSERT_EQ(*(str.rend() - 1), 'h'); // reverse iterator to the last (begin()) element

    ASSERT_EQ(str.toindex(str.begin() + 5), 5); // return index from iterator
}

TEST(BaseString, Capacity)
{
    str_t &str1 = heapstr_t();
    ASSERT_EQ(str1.empty(), true);

    str_t &str = heapstr_t("hello world");
    ASSERT_EQ(str.size(), 11);
    ASSERT_EQ(str.length(), 11);
    ASSERT_EQ(str.capacity(), 11);

    str.reserve(50);
    ASSERT_EQ(str.capacity(), 50);

    str.shrink_to_fit();
    ASSERT_EQ(str.capacity(), str.size());
}