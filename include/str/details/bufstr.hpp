#pragma once
#include "str.hpp"

STR_NAMESPACE_MAIN_BEGIN

template <typename Size, typename Char, typename CharTraits = std::char_traits<char>, typename Allocator = std::allocator<Char>>
class basic_bufstr : public basic_str<Char, CharTraits, Allocator>
{
    using this_t = basic_bufstr<Size, Char, CharTraits, Allocator>;

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

    STR_CONSTEXPR ~basic_bufstr() STR_NOEXCEPT = default;

    STR_CONSTEXPR basic_bufstr(const Allocator &alloc = Allocator())
        : alloc_{alloc} {}

    template <typename OtherCharTraits, typename OtherAllocator>
    STR_CONSTEXPR basic_bufstr(basic_bufstr<Char, OtherCharTraits, OtherAllocator> &&other,
                               const Allocator &alloc = Allocator()) : alloc_{alloc}
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    STR_CONSTEXPR basic_bufstr(size_type size, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        resize(size);
    }

    STR_CONSTEXPR basic_bufstr(value_type ch, size_type count, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(ch, count);
    }

    STR_CONSTEXPR basic_bufstr(const value_type *s, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(s);
    }
    STR_CONSTEXPR basic_bufstr(const value_type *s, size_type count, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(s, count);
    }

    template <typename InputIt>
    STR_CONSTEXPR basic_bufstr(InputIt first, InputIt last, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(first, last);
    }

    STR_CONSTEXPR basic_bufstr(std::initializer_list<value_type> ilist, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(ilist);
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_bufstr(const StringLike &str, size_type str_index = 0, const Allocator &alloc = Allocator())
        : alloc_{alloc}
    {
        append(str, str_index, npos);
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_bufstr(const StringLike &str, size_type str_index, size_type str_count = npos, const Allocator &alloc = Allocator())
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
        return std::max(Size, capacity_);
    }

    //////////////////////////////////////////////////////////////////////
    // OPERATIONS
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR void resize(size_type cap, value_type ch) override
    {
        assert_length_(cap);

        if (capacity_ == cap)
            return;

        // if stack memory is large enough, use it
        if (cap <= Size)
        {
            if (!is_stack())
            {
                std::memset(stack_, heap_, cap);

#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
                stack_[cap] = '\0';
#endif
                data_ = stack_;

                // deallocate heap
                if (heap_)
                {
                    auto old_heap = heap_;
                    auto old_capacity = capacity_;

                    heap_ = nullptr;
                    capacity_ = 0;

                    alloc_.deallocate(old_heap, old_capacity);
                }
            }

            return;
        }

        // requirement is larger than stack memory,
        // so allocate on heap
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
            }
            else
            {
                std::memcpy(ptr, data_, size_);
                std::memset(ptr + cap, ch, cap - size_);
            }

#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
            ptr[cap] = '\0';
#endif
        }

        // cache old data for exception safety
        auto old_ptr = data_;
        auto old_cap = capacity_;

        // write new data, old data is cached
        heap_ = ptr;
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

    STR_CONSTEXPR bool is_stack() const STR_NOEXCEPT
    {
        return data_ == stack_ ? true : false;
    }

    STR_CONSTEXPR bool is_heap() const STR_NOEXCEPT
    {
        return data_ == heap_ ? true : false;
    }

protected:
#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
    value_type stack_[Size + 1];
#else
    value_type stack_[Size];
#endif
    value_type *heap_ = nullptr;
    value_type *data_ = stack_;
    size_type size_ = 0;
    size_type capacity_ = 0;
    Allocator alloc_;
};

template <size_t Size>
using bufstr = basic_bufstr<Size, char>;

template <size_t Size>
using wbufstr = basic_bufstr<Size, wchar_t>;

template <size_t Size>
using u8bufstr = basic_bufstr<Size, char8_t>;

template <size_t Size>
using u16bufstr = basic_bufstr<Size, char16_t>;

template <size_t Size>
using u32bufstr = basic_bufstr<Size, char32_t>;

STR_NAMESPACE_MAIN_END