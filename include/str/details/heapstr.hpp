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

    STR_CONSTEXPR ~basic_heapstr() STR_NOEXCEPT = default;

    STR_CONSTEXPR basic_heapstr(const Allocator &alloc = Allocator())
        : alloc_{alloc} {}

    template <typename OtherCharTraits, typename OtherAllocator>
    STR_CONSTEXPR basic_heapstr(basic_heapstr<Char, OtherCharTraits, OtherAllocator> &&other,
                                const Allocator &alloc = Allocator()) : alloc_{alloc}
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    STR_CONSTEXPR basic_heapstr(size_type size, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        resize(size);
    }

    STR_CONSTEXPR basic_heapstr(value_type ch, size_type count, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(ch, count);
    }

    STR_CONSTEXPR basic_heapstr(const value_type *s, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(s);
    }
    STR_CONSTEXPR basic_heapstr(const value_type *s, size_type count, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(s, count);
    }

    template <typename InputIt>
    STR_CONSTEXPR basic_heapstr(InputIt first, InputIt last, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(first, last);
    }

    STR_CONSTEXPR basic_heapstr(std::initializer_list<value_type> ilist, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(ilist);
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_heapstr(const StringLike &str, size_type str_index = 0, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(str, str_index, npos);
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_heapstr(const StringLike &str, size_type str_index, size_type str_count = npos, const Allocator &alloc = Allocator())
        : alloc_{alloc}
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
        return alloc_.max_size();
    }

    STR_CONSTEXPR size_type capacity() const STR_NOEXCEPT override
    {
        return capacity_;
    }

    //////////////////////////////////////////////////////////////////////
    // OPERATIONS
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR void resize(size_type cap, value_type ch) override
    {
        assert_length_(cap);

        if (capacity_ == cap)
            return;

        pointer ptr = nullptr;
        if (cap > 0)
        {

#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
            ptr = alloc_.allocate(cap + 1);
#else
            ptr = alloc_.allocate(cap);
#endif
            if (ptr == nullptr)
                return;

            if (cap < size_)
            {
                std::memcpy(ptr, data_, cap - 1);

#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
                ptr[cap] = '\0';
#endif
            }
            else
            {
                std::memcpy(ptr, data_, size_);
                std::memset(ptr + cap, ch, cap - size_);
            }
        }

        // cache old data for exception safety
        auto old_ptr = data_;
        auto old_cap = capacity_;

        // write new data, old data is cached
        data_ = ptr;
        capacity_ = cap;
        size_ = std::min(size_, capacity_);

        // use old data, new data is written already,
        // an exception will have no effect now
        if (old_ptr)
        {
            alloc_.deallocate(old_ptr, old_cap);
        }
    }

protected:
    pointer data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
    Allocator alloc_;
};

//////////////////////////////////////////////////////////////////////
// operator +
//////////////////////////////////////////////////////////////////////

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(const basic_str<Char, CharTraits, Allocator> &lhs,
          const basic_str<Char, CharTraits, Allocator> &rhs)
{
    auto str = basic_heapstr<Char, CharTraits, Allocator>(
        lhs.size() + rhs.size());

    str.append(lhs);
    str.append(rhs);

    return str;
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(const basic_str<Char, CharTraits, Allocator> &lhs, const Char *rhs)
{
    auto lhslen = CharTraits::length(rhs);
    auto str = basic_heapstr<Char, CharTraits, Allocator>(
        lhs.size() + lhslen);

    str.append(lhs);
    str.append(rhs, lhslen);

    return str;
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(const basic_str<Char, CharTraits, Allocator> &lhs, Char rhs)
{
    auto str = basic_heapstr<Char, CharTraits, Allocator>(
        lhs.size() + 1);

    str.append(lhs);
    str.append(rhs);

    return str;
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(const Char *lhs, const basic_str<Char, CharTraits, Allocator> &rhs)
{
    auto lhslen = CharTraits::length(lhs);
    auto str = basic_heapstr<Char, CharTraits, Allocator>(
        rhs.size() + lhslen);

    str.append(lhs, lhslen);
    str.append(rhs);

    return str;
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(Char lhs, const basic_str<Char, CharTraits, Allocator> &rhs)
{
    auto str = basic_heapstr<Char, CharTraits, Allocator>(
        rhs.size() + 1);

    str.append(lhs);
    str.append(rhs);

    return str;
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(basic_heapstr<Char, CharTraits, Allocator> &&lhs,
          basic_heapstr<Char, CharTraits, Allocator> &&rhs)
{
    auto reqcap = lhs.size() + rhs.size();

    // if lhs dont have enough capacity but rhs has, move into rhs
    if (lhs.capacity() < reqcap && rhs.capacity() > reqcap)
    {
        return std::move(str.insert(0, lhs));
    }

    return std::move(lhs.append(rhs));
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(basic_str<Char, CharTraits, Allocator> &&lhs,
          const basic_str<Char, CharTraits, Allocator> &rhs)
{
    return std::move(lhs.append(rhs));
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(basic_str<Char, CharTraits, Allocator> &&lhs, const Char *rhs)
{
    return std::move(lhs.append(rhs));
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(basic_str<Char, CharTraits, Allocator> &&lhs, Char rhs)
{
    return std::move(lhs.append(rhs));
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(const basic_str<Char, CharTraits, Allocator> &lhs,
          basic_str<Char, CharTraits, Allocator> &&rhs)
{
    return std::move(rhs.insert(0, lhs));
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(const Char *lhs, basic_str<Char, CharTraits, Allocator> &&rhs)
{
    return std::move(rhs.append(lhs));
}

template <typename Char, typename CharTraits, typename Allocator>
basic_heapstr<Char, CharTraits, Allocator>
operator+(Char lhs, basic_str<Char, CharTraits, Allocator> &&rhs)
{
    return std::move(rhs.append(lhs));
}

//////////////////////////////////////////////////////////////////////
// typedefs
//////////////////////////////////////////////////////////////////////

using heapstr = basic_heapstr<char>;
using wheapstr = basic_heapstr<wchar_t>;
using u8heapstr = basic_heapstr<char8_t>;
using u16heapstr = basic_heapstr<char16_t>;
using u32heapstr = basic_heapstr<char32_t>;

STR_NAMESPACE_MAIN_END