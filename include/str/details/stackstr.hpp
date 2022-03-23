#pragma once
#include "str.hpp"

STR_NAMESPACE_MAIN_BEGIN

template <size_t Size, typename Char, typename CharTraits = std::char_traits<char>>
class basic_stackstr : public basic_str<Char, CharTraits, std::allocator<Char>>
{
    using this_t = basic_stackstr<Size, Char, CharTraits>;

public:
    using base_t = basic_str<Char, CharTraits, std::allocator<Char>>;
    using value_type = typename base_t::value_type;
    using traits_type = typename base_t::traits_type;
    using size_type = typename base_t::size_type;
    using difference_type = typename base_t::difference_type;
    using reference = typename base_t::reference;
    using const_reference = typename base_t::const_reference;
    using pointer = typename base_t::pointer;
    using const_pointer = typename base_t::const_pointer;
    using iterator = typename base_t::iterator;
    using const_iterator = typename base_t::const_iterator;
    using reverse_iterator = typename base_t::reverse_iterator;
    using const_reverse_iterator = typename base_t::const_reverse_iterator;

public:
    //////////////////////////////////////////////////////////////////////
    // CONSTRUCTORS / DESTRUCTOR
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR basic_stackstr() STR_NOEXCEPT
    {
        data_[0] = '\0';

#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
        data_[Size] = '\0';
#endif
    }

    STR_CONSTEXPR ~basic_stackstr() STR_NOEXCEPT = default;

    STR_CONSTEXPR basic_stackstr(value_type ch)
    {
        append(ch, Size);
    }
    STR_CONSTEXPR basic_stackstr(value_type ch, size_type count)
    {
        append(ch, count);
    }

    STR_CONSTEXPR basic_stackstr(const value_type *s)
    {
        append(s);
    }
    STR_CONSTEXPR basic_stackstr(const value_type *s, size_type count)
    {
        append(s, count);
    }

    template <typename InputIt>
    STR_CONSTEXPR basic_stackstr(InputIt first, InputIt last)
    {
        append(first, last);
    }

    STR_CONSTEXPR basic_stackstr(std::initializer_list<value_type> ilist)
    {
        append(ilist);
    }

    template <typename String>
    STR_CONSTEXPR basic_stackstr(const String &str, size_type str_index = 0, size_type str_count = npos)
    {
        append(str, str_index, str_count);
    }

    //////////////////////////////////////////////////////////////////////
    // ELEMENT ACCESS
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR pointer data() STR_NOEXCEPT override
    {
        return data_;
    }

    STR_CONSTEXPR const_pointer data() const STR_NOEXCEPT override
    {
        return data_;
    }

    //////////////////////////////////////////////////////////////////////
    // CAPACITY
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR size_type size() const STR_NOEXCEPT override
    {
        return size_;
    }

    STR_CONSTEXPR void set_size_(size_type size) STR_NOEXCEPT override
    {
        size_ = size;
    }

    STR_CONSTEXPR size_type max_size() const STR_NOEXCEPT override
    {
        return Size;
    }

    STR_CONSTEXPR size_type capacity() const STR_NOEXCEPT override
    {
        return Size;
    }

    //////////////////////////////////////////////////////////////////////
    // OPERATIONS
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR void resize(size_type count, value_type c) override {}

protected:
#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
    Char data_[Size + 1];
#else
    Char data_[Size];
#endif

    size_type size_ = 0;
};

//////////////////////////////////////////////////////////////////////
// TypeDefs
//////////////////////////////////////////////////////////////////////

template <size_t Size>
using stackstr = basic_stackstr<Size, char>;

template <size_t Size>
using wstackstr = basic_stackstr<Size, wchar_t>;

template <size_t Size>
using u8stackstr = basic_stackstr<Size, char8_t>;

template <size_t Size>
using u16stackstr = basic_stackstr<Size, char16_t>;

template <size_t Size>
using u32stackstr = basic_stackstr<Size, char32_t>;

//////////////////////////////////////////////////////////////////////
// Numeric Conversions
//////////////////////////////////////////////////////////////////////

template <class Int>
stackstr<21> to_stackstr(Int value)
{
    stackstr<21> str; // can hold -2^63 and 2^64 - 1, plus NUL
    details::convert_num_to_str(str.data(), str.size(), value);
    return str;
}

STR_NAMESPACE_MAIN_END