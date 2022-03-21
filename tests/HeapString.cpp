#include <gtest/gtest.h>
#include <str/heapstr>

TEST(HeapString, Constructor)
{
    using heapstr_t = str::heapstr;

    heapstr_t str1;
    heapstr_t str2('b', 25);
    heapstr_t str3("hello world\0 hi world");
    heapstr_t str4("hello world\0 hi world", 22);
    heapstr_t str5(str4.begin(), str4.end());
    heapstr_t str6({ 'h', 'e', 'l', 'l', 'o' });
    heapstr_t str7(str4);
    heapstr_t str8(str4.base());
}