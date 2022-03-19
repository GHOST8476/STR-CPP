#include <gtest/gtest.h>
#include <str/stackstr>

TEST(StackString, Constructor)
{
    using stackstr_t = str::stackstr<50>;

    stackstr_t str1;
    stackstr_t str2('a');
    stackstr_t str3('b', 25);
    stackstr_t str4("hello world\0 hi world");
    stackstr_t str5("hello world\0 hi world", 22);
    stackstr_t str6(str5.begin(), str5.end());
    stackstr_t str7({ 'h', 'e', 'l', 'l', 'o' });
    stackstr_t str8(str5);
    stackstr_t str9(str5.base());
}