#pragma once
#include "str.hpp"

STR_NAMESPACE_MAIN_BEGIN

template <typename Char, typename CharTraits = std::char_traits<char>, typename Allocator = std::allocator<Char>>
class basic_heapstr : public basic_str<Char, CharTraits, Allocator>
{
    using this_t = basic_heapstr<Char, CharTraits, Allocator>;

public:
    using base_t = basic_str<Char, CharTraits, Allocator>;
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

    STR_CONSTEXPR basic_heapstr() STR_NOEXCEPT = default;
    STR_CONSTEXPR ~basic_heapstr() STR_NOEXCEPT = default;

    STR_CONSTEXPR basic_heapstr(size_type size)
    {
        resize(size);
    }

    STR_CONSTEXPR basic_heapstr(value_type ch, size_type count)
    {
        append(ch, count);
    }

    STR_CONSTEXPR basic_heapstr(const value_type *s)
    {
        append(s);
    }
    STR_CONSTEXPR basic_heapstr(const value_type *s, size_type count)
    {
        append(s, count);
    }

    template <typename InputIt>
    STR_CONSTEXPR basic_heapstr(InputIt first, InputIt last)
    {
        append(first, last);
    }

    STR_CONSTEXPR basic_heapstr(std::initializer_list<value_type> ilist)
    {
        append(ilist);
    }

    template <typename String>
    STR_CONSTEXPR basic_heapstr(const String &str, size_type str_index = 0, size_type str_count = npos)
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

    STR_CONSTEXPR void reserve(size_type size) override
    {
        if (capacity_ < size)
        {
            resize(size);
        }
    }

    STR_CONSTEXPR size_type capacity() const STR_NOEXCEPT override
    {
        return capacity_;
    }

    STR_CONSTEXPR void shrink_to_fit() override
    {
        if (size_ == capacity_)
            return;

        resize(size_);
    }

    //////////////////////////////////////////////////////////////////////
    // OPERATIONS
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR void clear() STR_NOEXCEPT override
    {
        size_ = 0;
        if (data_)
        {
            data_[0] = '\0';
        }
    }

    STR_CONSTEXPR void resize(size_type count, value_type ch) override
    {
        assert_length_(count);
        if (capacity_ == count)
            return;

        pointer ptr = nullptr;
        if (count > 0)
        {
            ptr = alloc_.allocate(count);
            if (ptr == nullptr)
                return;

            if (count < size_)
            {
                std::memcpy(ptr, ptr_, count - 1);
                ptr[count] = '\0';
            }
            else
            {
                std::memcpy(ptr, ptr_, size_);
                std::memset(ptr + count, ch, count - size_);
            }
        }

        // cache old data for exception safety
        auto old_ptr = ptr_;
        auto old_cap = capacity_;

        // write new data, old data is cached
        ptr_ = ptr;
        capacity_ = count;
        size_ = std::min(size_, capacity_);

        // use old data, new data is written already,
        // an exception will have no effect now
        if (old_ptr)
        {
            alloc_.deallocate(old_ptr, old_cap);
        }
    }

    STR_CONSTEXPR void swap(basic_str &other) override {}

protected:
    value_type *data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
    Allocator alloc_;
};

template <size_t Size>
using heapstr = basic_heapstr<Size, char>;

template <size_t Size>
using wheapstr = basic_heapstr<Size, wchar_t>;

template <size_t Size>
using u8heapstr = basic_heapstr<Size, char8_t>;

template <size_t Size>
using u16heapstr = basic_heapstr<Size, char16_t>;

template <size_t Size>
using u32heapstr = basic_heapstr<Size, char32_t>;

STR_NAMESPACE_MAIN_END