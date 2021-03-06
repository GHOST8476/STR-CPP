#pragma once
#include "common.hpp"
#include "details.hpp"
#include "strtraits.hpp"
#include <type_traits>
#include <exception>
#include <stdexcept>
#include <memory>
#include <iostream>

STR_NAMESPACE_MAIN_BEGIN

template <typename Char, typename CharTraits = std::char_traits<Char>, typename Allocator = std::allocator<Char>>
class basic_str
{
public:
    class iterator;
    class const_iterator;

    using value_type = Char;
    using traits_type = CharTraits;
    using allocator_type = Allocator;
    using allocator_traits = std::allocator_traits<allocator_type>;
    using size_type = typename allocator_traits::size_type;
    using difference_type = typename allocator_traits::difference_type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = typename allocator_traits::pointer;
    using const_pointer = typename allocator_traits::const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_type npos = -1;

public:
    //////////////////////////////////////////////////////////////////////
    // BASE
    //////////////////////////////////////////////////////////////////////
    STR_CONSTEXPR basic_str &base() STR_NOEXCEPT
    {
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ELEMENT ACCESS
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Accesses the specified character with bounds checking.
    /// std::out_of_range will be thrown on invalid access.
    STR_CONSTEXPR reference at(size_type index)
    {
        assert_range_(index);
        return operator[](index);
    }
    STR_CONSTEXPR const_reference at(size_type index) const
    {
        assert_range_(index);
        return operator[](index);
    }

    /// Accesses the specified character.
    /// @note no bound checking is performed.
    STR_CONSTEXPR reference operator[](size_type pos)
    {
        return *(data() + pos);
    }
    STR_CONSTEXPR const_reference operator[](size_type pos) const
    {
        return *(data() + pos);
    }

    /// Returns reference to the first character in the string.
    /// @note The behavior is undefined if empty() == true.
    /// @details Returns operator[0]
    STR_CONSTEXPR reference front()
    {
        return operator[](0);
    }
    STR_CONSTEXPR const_reference front() const
    {
        return operator[](0);
    }

    /// Returns reference to the last character in the string.
    /// @note the behavior is undefined if empty() == true.
    /// @details Returns operator[size() - 1]
    STR_CONSTEXPR reference back()
    {
        return operator[](size() - 1);
    }
    STR_CONSTEXPR const_reference back() const
    {
        return operator[](size() - 1);
    }

    /// Returns a pointer to the first character of a string.
    STR_CONSTEXPR_VFUNC pointer data() STR_NOEXCEPT = 0;
    STR_CONSTEXPR_VFUNC const_pointer data() const STR_NOEXCEPT = 0;

    /// Returns a const pointer to the first character of a string.
    STR_CONSTEXPR const_pointer c_str() const STR_NOEXCEPT
    {
        return data();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ITERATORS
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Returns index to which iterator is pointing.
    STR_CONSTEXPR size_type toindex(const_iterator pos) const
    {
        return static_cast<size_type>(std::distance(cbegin(), pos));
    }

    /// Returns an iterator to the given index.
    STR_CONSTEXPR iterator it(size_type index) STR_NOEXCEPT
    {
        return iterator(data() + index);
    }
    STR_CONSTEXPR const_iterator it(size_type index) const STR_NOEXCEPT
    {
        return const_iterator(data() + index);
    }
    STR_CONSTEXPR const_iterator cit(size_type index) const STR_NOEXCEPT
    {
        return const_iterator(data() + index);
    }

    /// Returns an iterator to the first character of the string.
    STR_CONSTEXPR iterator begin() STR_NOEXCEPT
    {
        return it(0);
    }
    STR_CONSTEXPR const_iterator begin() const STR_NOEXCEPT
    {
        return it(0);
    }
    STR_CONSTEXPR const_iterator cbegin() const STR_NOEXCEPT
    {
        return cit(0);
    }

    /// Returns an iterator to the character following the last character of the string (null character).
    STR_CONSTEXPR iterator end() STR_NOEXCEPT
    {
        return it(size());
    }
    STR_CONSTEXPR const_iterator end() const STR_NOEXCEPT
    {
        return it(size());
    }
    STR_CONSTEXPR const_iterator cend() const STR_NOEXCEPT
    {
        return cit(size());
    }

    /// Returns a reverse iterator to the given index.
    /// Indexing starts in reverse order
    STR_CONSTEXPR reverse_iterator rit(size_type index) STR_NOEXCEPT
    {
        return reverse_iterator(it(size() - index));
    }
    STR_CONSTEXPR const_reverse_iterator rit(size_type index) const STR_NOEXCEPT
    {
        return const_reverse_iterator(it(size() - index));
    }
    STR_CONSTEXPR const_reverse_iterator crit(size_type index) const STR_NOEXCEPT
    {
        return const_reverse_iterator(cit(size() - index));
    }

    /// Returns a reverse iterator to the first character of the reversed string.
    STR_CONSTEXPR reverse_iterator rbegin() STR_NOEXCEPT
    {
        return rit(0);
    }
    STR_CONSTEXPR const_reverse_iterator rbegin() const STR_NOEXCEPT
    {
        return rit(0);
    }
    STR_CONSTEXPR const_reverse_iterator crbegin() const STR_NOEXCEPT
    {
        return crit(0);
    }

    /// Returns a reverse iterator to the character following the last character of the reversed string.
    STR_CONSTEXPR reverse_iterator rend() STR_NOEXCEPT
    {
        return rit(size());
    }
    STR_CONSTEXPR const_reverse_iterator rend() const STR_NOEXCEPT
    {
        return rit(size());
    }
    STR_CONSTEXPR const_reverse_iterator crend() const STR_NOEXCEPT
    {
        return crit(size());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CAPACITY
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Checks whether the string is empty.
    STR_NODISCARD STR_CONSTEXPR bool empty() const STR_NOEXCEPT
    {
        return size() == 0;
    }

    /// Returns the count of characters.
    STR_CONSTEXPR_VFUNC size_type size() const STR_NOEXCEPT = 0;
    STR_CONSTEXPR size_type length() const STR_NOEXCEPT
    {
        return size();
    }

    /// Returns the maximum number of elements the string is able to hold.
    STR_CONSTEXPR_VFUNC size_type max_size() const STR_NOEXCEPT = 0;

    /// Returns the number of characters that the string has currently allocated space for.
    STR_CONSTEXPR_VFUNC size_type capacity() const STR_NOEXCEPT = 0;

    /// Reserves at least new_cap storage.
    /// If new_cap is less than or equal to the current capacity(), there is no effect.
    STR_CONSTEXPR void reserve(size_type required)
    {
        if (capacity() < required)
        {
            resize(required);
        }
    }

    /// Requests the removal of unused capacity.
    STR_CONSTEXPR void shrink_to_fit()
    {
        if (size() == capacity())
            return;

        resize(size());
    }

    STR_CONSTEXPR allocator_type get_allocator() const STR_NOEXCEPT
    {
        return allocator_type();
    }

protected:
    STR_CONSTEXPR_VFUNC void set_size_(size_type size) STR_NOEXCEPT = 0;

public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// OPERATIONS
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    /// Clear
    //////////////////////////////////////////////////////////////////////

    /// Clears the contents.
    STR_CONSTEXPR void clear() STR_NOEXCEPT
    {
        set_size_(0);
        if (data())
            *data() = '\0';
    }

    //////////////////////////////////////////////////////////////////////
    /// insert
    //////////////////////////////////////////////////////////////////////

    /// Inserts character ch before the character pointed by index.
    STR_CONSTEXPR basic_str &insert(size_type index, value_type ch)
    {
        insert_(index, ch, 1);
        return *this;
    }

    /// Inserts count copies of character ch at the position index
    STR_CONSTEXPR_VFUNC basic_str &insert(size_type index, value_type ch, size_type count)
    {
        insert_(index, ch, count);
        return *this;
    }

    /// Inserts null-terminated character string pointed to by s at the position index.
    /// the length of the string is determined by the first null character using CharTraits::length(s).
    STR_CONSTEXPR basic_str &insert(size_type index, const value_type *s)
    {
        insert_(index, s, traits_type::length(s));
        return *this;
    }

    /// Inserts the characters in the range [s, s+count) at the position index.
    /// the range can contain null characters.
    STR_CONSTEXPR basic_str &insert(size_type index, const value_type *s, size_type count)
    {
        insert_(index, s, count);
        return *this;
    }

    /// Inserts characters from the range [first, last) before the element (if any) pointed by index.
    template <typename InputIt>
    STR_CONSTEXPR basic_str &insert(size_type index, InputIt first, InputIt last)
    {
        insert_(index, first, static_cast<size_type>(std::distance(first, last)));
        return *this;
    }

    /// Inserts elements from initializer list ilist before the element (if any) pointed by pos
    STR_CONSTEXPR basic_str &insert(size_type index, std::initializer_list<value_type> ilist)
    {
        insert_(index, ilist.begin(), static_cast<size_type>(ilist.size()));
        return *this;
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_str &insert(size_type index, const StringLike &str, size_type str_index = 0, size_type str_count = npos)
    {
        auto tup = getdata_(str);
        auto str_size = std::get<1>(tup);
        assert_range_(index, 0, str_size, "'str_index' was out of range[0, str.size()] for 'str'");

        if (str_count == npos || str_count > str_size - str_index)
        {
            str_count = str_size - str_index;
        }

        insert_(index, std::get<0>(tup) + str_index, str_count);
        return *this;
    }

    /// Inserts character ch before the character pointed by pos.
    STR_CONSTEXPR iterator insert(const_iterator pos, value_type ch)
    {
        auto i = toindex(pos);
        insert(i, ch);
        return it(i);
    }

    /// Inserts count copies of character ch before the element (if any) pointed by pos
    STR_CONSTEXPR iterator insert(const_iterator pos, value_type ch, size_type count)
    {
        auto i = toindex(pos);
        insert(i, ch, count);
        return it(i);
    }

    /// Inserts null-terminated character string pointed to by s at the position pos.
    /// The length of the string is determined by the first null character using CharTraits::length(s).
    STR_CONSTEXPR iterator insert(const_iterator pos, const value_type *s)
    {
        auto i = toindex(pos);
        insert(i, s);
        return it(i);
    }

    /// Inserts the characters in the range [s, s+count) at the position pos.
    /// The range can contain null characters.
    STR_CONSTEXPR iterator insert(const_iterator pos, const value_type *s, size_type count)
    {
        auto i = toindex(pos);
        insert(i, s, count);
        return it(i);
    }

    /// Inserts characters from the range [first, last) before the element (if any) pointed by pos.
    template <typename InputIt>
    STR_CONSTEXPR iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        auto i = toindex(pos);
        insert(i, first, last);
        return it(i);
    }

    /// Inserts elements from initializer list ilist before the element (if any) pointed by pos
    STR_CONSTEXPR iterator insert(const_iterator pos, std::initializer_list<value_type> ilist)
    {
        auto i = toindex(pos);
        insert(i, ilist);
        return it(i);
    }

    template <typename StringLike>
    STR_CONSTEXPR iterator insert(const_iterator pos, const StringLike &str, size_type str_index = 0, size_type str_count = npos)
    {
        auto i = toindex(pos);
        insert(i, str, str_index, str_count);
        return it(i);
    }

protected:
    STR_CONSTEXPR_VFUNC void insert_(size_type index, size_type count)
    {
        assert_length_(index, "'index' was out of 'max_length'");
        assert_length_(count, "'count' was out of 'max_length'");
        assert_range_(index, "'index' was out of range");

        auto len = size();
        reserve(len + count);

        assert_space_(count);
        auto ptr = data();

        // pos of new null character
        size_type i = len + count - 1;

        // write null character
        ptr[i--] = '\0';

        // move characters back
        for (; i >= index + count; i--)
            ptr[i] = ptr[i - count];

        set_size_(len + count);
    }

    STR_CONSTEXPR void insert_(size_type index, value_type ch, size_type count)
    {
        insert_(index, count);

        /// write character
        auto ptr = data() + index;
        for (size_type i = 0; i < count; i++)
        {
            ptr[i] = ch;
        }
    }

    STR_CONSTEXPR void insert_(size_type index, const value_type *s, size_type count)
    {
        assert_null_(s, "cannot insert null string");
        insert_(index, count);

        /// write string
        auto ptr = data() + index;
        for (size_type i = 0; i < count; i++)
        {
            ptr[i] = s[i];
        }
    }

    template <typename It>
    STR_CONSTEXPR void insert_(size_type index, It it, size_type count)
    {
        insert_(index, count);

        /// write string
        auto ptr = data() + index;
        for (size_type i = 0; i < count; i++)
        {
            ptr[i] = *it;
            it++;
        }
    }

public:
    //////////////////////////////////////////////////////////////////////
    /// erase
    //////////////////////////////////////////////////////////////////////

    /// Removes the character at index
    STR_CONSTEXPR basic_str &erase(size_type index)
    {
        erase_(index, 1);
        return *this;
    }

    /// Removes the characters in the range [index, index+count)
    STR_CONSTEXPR basic_str &erase(size_type index, size_type count)
    {
        erase_(index, count);
        return *this;
    }

    /// Removes the character at position
    STR_CONSTEXPR iterator erase(const_iterator pos)
    {
        auto i = toindex(pos);
        erase(i);
        return it(i);
    }

    /// Removes the characters in the range [pos, pos+count)
    STR_CONSTEXPR iterator erase(const_iterator pos, size_type count)
    {
        auto i = toindex(pos);
        erase(i, count);
        return it(i);
    }

    /// Removes the characters in the range [pos, last)
    STR_CONSTEXPR iterator erase(const_iterator first, const_iterator last)
    {
        auto i = toindex(first);
        auto count = static_cast<size_type>(std::distance(first, last));
        return erase(i, count);
        return it(1);
    }

protected:
    STR_CONSTEXPR_VFUNC void erase_(size_type index, size_type count)
    {
        assert_range_(index);
        count = std::min(size() - index, count);

        auto ptr = data();

        // move characters forward
        for (size_type i = index; i < index + count; i++)
            ptr[i] = ptr[i + count];

        // write null character
        ptr[index + count] = '\0';

        set_size_(size() - count);
    }

public:
    //////////////////////////////////////////////////////////////////////
    /// push_back
    //////////////////////////////////////////////////////////////////////

    /// appends the character ch to the end of the string
    /// If size() > max_size(), throws std::length_error
    STR_CONSTEXPR void push_back(value_type ch)
    {
        insert(size(), ch);
    }

    //////////////////////////////////////////////////////////////////////
    /// pop_back
    //////////////////////////////////////////////////////////////////////

    /// Removes the last character from the string
    /// no effect if string is empty
    STR_CONSTEXPR void pop_back()
    {
        erase(size(), 1);
    }

    //////////////////////////////////////////////////////////////////////
    /// append
    //////////////////////////////////////////////////////////////////////

    /// appends character c
    STR_CONSTEXPR basic_str &append(value_type c)
    {
        return insert(size(), c);
    }

    /// appends count copies of character c
    STR_CONSTEXPR basic_str &append(value_type c, size_type count)
    {
        return insert(size(), c, count);
    }

    /// appends the null-terminated character string pointed to by s.
    STR_CONSTEXPR basic_str &append(const value_type *s)
    {
        return insert(size(), s);
    }

    /// appends characters in the range [s, s + count).
    /// this range can contain null characters.
    STR_CONSTEXPR basic_str &append(const value_type *s, size_type count)
    {
        return insert(size(), s, count);
    }

    /// appends characters in the range [first, last).
    template <typename InputIt>
    STR_CONSTEXPR basic_str &append(InputIt first, InputIt last)
    {
        return insert(size(), first, last);
    }

    /// appends characters from the initializer list ilist.
    STR_CONSTEXPR basic_str &append(std::initializer_list<value_type> ilist)
    {
        return insert(size(), ilist);
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_str &append(const StringLike &str, size_type str_index = 0, size_type str_count = npos)
    {
        return insert(size(), str, str_index, str_count);
    }

    //////////////////////////////////////////////////////////////////////
    /// operator+=
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR basic_str &operator+=(value_type ch)
    {
        return append(ch);
    }

    STR_CONSTEXPR basic_str &operator+=(const value_type *s)
    {
        return append(s);
    }

    STR_CONSTEXPR basic_str &operator+=(std::initializer_list<value_type> ilist)
    {
        return append(ilist);
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_str &operator+=(const StringLike &str)
    {
        return append(str);
    }

    //////////////////////////////////////////////////////////////////////
    /// Assign
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR basic_str &assign(value_type ch)
    {
        assign_(ch, 1);
        return *this;
    }
    STR_CONSTEXPR basic_str &assign(value_type ch, size_type count)
    {
        assign_(ch, count);
        return *this;
    }

    STR_CONSTEXPR basic_str &assign(const value_type *s)
    {
        assign_(s, traits_type::length(s));
        return *this;
    }
    STR_CONSTEXPR basic_str &assign(const value_type *s, size_type count)
    {
        assign_(s, count);
        return *this;
    }

    template <typename InputIt>
    STR_CONSTEXPR basic_str &assign(InputIt first, InputIt last)
    {
        assign_(first, std::distance(first, last));
        return *this;
    }
    STR_CONSTEXPR basic_str &assign(std::initializer_list<value_type> ilist)
    {
        assign_(ilist.begin(), ilist.size());
        return *this;
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_str &assign(const StringLike &str)
    {
        assign_(getptr_(str), getsize_(str));
        return *this;
    }
    template <typename StringLike>
    STR_CONSTEXPR basic_str &assign(const StringLike &str, size_type pos, size_type count = npos)
    {
        auto len = getsize_(str);
        if (count == npos || count > len - pos)
        {
            count = len;
        }

        assign_(getptr_(str) + pos, count);
        return *this;
    }

protected:
    STR_CONSTEXPR void assign_(value_type ch, size_type count)
    {
        struct it
        {
            value_type ch;
            operator*() { return ch; }
            operator++(int) {}
        };

        // pass as iterator
        assign_<it>(it(ch), count);
    }

    STR_CONSTEXPR void assign_(const value_type *s, size_type count)
    {
        // pass as iterator
        assign_<const value_type *>(s, count);
    }

    template <typename InputIt>
    STR_CONSTEXPR void assign_(InputIt first, size_type count)
    {
        assert_length_(count);
        if (capacity() < count)
        {
            reserve(count);
        }

        assert_space_(count);

        /// write string
        auto ptr = data();
        for (size_type i = 0; i < count; i++)
        {
            ptr[i] = *it;
            it++;
        }

#ifdef STR_TWEAKS_ALWAYS_NULLTERMINATE
        ptr[count] = '\0';
#endif
    }

    //////////////////////////////////////////////////////////////////////
    /// Operator =
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR basic_str &operator=(value_type ch)
    {
        return assign(ch);
    }

    STR_CONSTEXPR basic_str &operator=(const value_type *s)
    {
        return assign(s);
    }

    STR_CONSTEXPR basic_str &operator=(std::initializer_list<value_type> ilist)
    {
        return assign(ilist);
    }

    template <typename StringLike>
    STR_CONSTEXPR basic_str &operator=(const StringLike &str)
    {
        return assign(str);
    }

    //////////////////////////////////////////////////////////////////////
    /// Compare
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR int compare(const value_type *s) const
    {
        return compare_(0, size(), s, size());
    }

    STR_CONSTEXPR int compare(const value_type *s, size_type count2) const
    {
        return compare_(0, size(), s, count2);
    }

    STR_CONSTEXPR int compare(size_type index1, size_type count1, const value_type *s) const
    {
        return compare_(index1, count1, s, count1);
    }

    STR_CONSTEXPR int compare(size_type index1, size_type count1, const value_type *s, size_type count2) const
    {
        return compare_(index1, count1, s, count2);
    }

    template <typename StringLike>
    STR_CONSTEXPR int compare(const StringLike &str) const STR_NOEXCEPT
    {
        return compare_(0, size(), getptr_(sv), getsize_(sv));
    }

    template <typename StringLike>
    STR_CONSTEXPR int compare(const StringLike &str, size_type index2, size_type count2) const
    {
        return compare_(0, size(), getptr_(sv) + index2, count2);
    }

    template <typename StringLike>
    STR_CONSTEXPR int compare(size_type index1, size_type count1, const StringLike &str) const
    {
        return compare_(index1, count1, getptr_(sv), getsize_(sv));
    }

    template <typename StringLike>
    STR_CONSTEXPR int compare(size_type index1, size_type count1, const StringLike &str, size_type index2, size_type count2 = npos) const
    {
        return compare_(index1, count1, getptr_(sv) + index2, getsize_(sv));
    }

protected:
    STR_CONSTEXPR int compare_(size_type index1, size_type count1, const value_type *s, size_type count2) const
    {
        return traits_type::compare(data() + pos1, s, sdt::min(count1, count2));
    }

    //////////////////////////////////////////////////////////////////////
    /// starts_with
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR bool starts_with(value_type c) const STR_NOEXCEPT
    {
        return front() == c;
    }

    STR_CONSTEXPR bool starts_with(const value_type *s) const
    {
        return compare(s) == 0;
    }

    STR_CONSTEXPR bool starts_with(const value_type *s, size_type count) const
    {
        return compare(s, count) == 0;
    }

    template <typename StringLike>
    STR_CONSTEXPR bool starts_with(const StringLike &str) const STR_NOEXCEPT
    {
        return compare(str);
    }

    template <typename StringLike>
    STR_CONSTEXPR bool starts_with(const StringLike &str, size_type pos, size_type count) const STR_NOEXCEPT
    {
        return compare(str, pos, count);
    }

    //////////////////////////////////////////////////////////////////////
    /// ends_with
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR bool ends_with(value_type c) const STR_NOEXCEPT
    {
        return back() == c;
    }

    STR_CONSTEXPR bool ends_with(const value_type *s) const
    {
        return ends_with(s, static_cast<size_type>(char_trait_t::length(s)));
    }

    STR_CONSTEXPR bool ends_with(const value_type *s, size_type count) const
    {
        return compare(size() - count, count, s, count) == 0;
    }

    template <typename StringLike>
    STR_CONSTEXPR bool ends_with(const StringLike &str) const STR_NOEXCEPT
    {
        return ends_with(getptr_(str), getsize_(str));
    }

    template <typename StringLike>
    STR_CONSTEXPR bool ends_with(const StringLike &str, size_type pos, size_type count) const STR_NOEXCEPT
    {
        return ends_with(getptr_(str) + pos, count);
    }

    //////////////////////////////////////////////////////////////////////
    /// Contains
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR bool contains(value_type c) const STR_NOEXCEPT_IF(find(c))
    {
        return find(c) != npos;
    }

    STR_CONSTEXPR bool contains(const value_type *s) const STR_NOEXCEPT_IF(find(s))
    {
        return find(s) != npos;
    }

    template <typename StringLike>
    STR_CONSTEXPR bool contains(const StringLike &str) const STR_NOEXCEPT_IF(find(sv))
    {
        return find(sv) != npos;
    }

    //////////////////////////////////////////////////////////////////////
    /// Copy
    //////////////////////////////////////////////////////////////////////

    /// Copies the substring [index, index+count) to character string pointed to by dest
    /// @return number of characters copied
    STR_CONSTEXPR size_type copy(value_type *dest, size_type count, size_type index = 0) const
    {
        assert_range_(index);
        count = std::min(size() - index + count, count);
        traits_type::copy(dest, data() + pos, count);
        return count;
    }

    //////////////////////////////////////////////////////////////////////
    /// Resize
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR void resize(size_type count)
    {
        resize(count, '\0');
    }

    STR_CONSTEXPR_VFUNC void resize(size_type count, value_type c) = 0;

    //////////////////////////////////////////////////////////////////////
    /// Resize_and_overwrite
    //////////////////////////////////////////////////////////////////////

    template <typename Operation>
    STR_CONSTEXPR void resize_and_overwrite(size_type count, Operation op);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SEARCH
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    /// find
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR size_type find(value_type ch, size_type index = 0) const STR_NOEXCEPT
    {
        return find_(ch, index);
    }

    STR_CONSTEXPR size_type find(const value_type *s, size_type index = 0) const
    {
        return find_(s, index, traits_type::length(s));
    }

    STR_CONSTEXPR size_type find(const value_type *s, size_type index, size_type count) const
    {
        return find_(s, index, count);
    }

    template <typename StringLike>
    STR_CONSTEXPR size_type find(const StringLike &str, size_type index = 0, size_type count = npos) const STR_NOEXCEPT
    {
        auto len = getsize_(str);
        if (count == npos || count > len - index)
        {
            count = len;
        }

        return find_(getptr_(str), index, count);
    }

protected:
    STR_CONSTEXPR size_type find_(const value_type ch, size_type index) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i < len; i++)
        {
            if (traits_type::eq(ptr[i], ch))
                return i;
        }

        return npos;
    }

    STR_CONSTEXPR size_type find_(const value_type *s, size_type index, size_type count) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();

        for (; index < len - count, index++)
        {
            // find first character
            for (size_type i = index; i < len; i++)
            {
                if (traits_type::eq(ptr[i], ch))
                    return i;
            }

            // fail if even the first character was not found
            if (ptr == nullptr)
                return npos;

            // if found compare the string
            if (traits_type::compare(ptr, s, count) == 0)
                return index;
        }

        return npos;
    }

public:
    //////////////////////////////////////////////////////////////////////
    /// rfind
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR size_type rfind(value_type ch, size_type index = npos) const STR_NOEXCEPT
    {
        return rfind_(ch, index);
    }

    STR_CONSTEXPR size_type rfind(const value_type *s, size_type index = npos) const
    {
        return rfind_(s, index, traits_type::length(s));
    }

    STR_CONSTEXPR size_type rfind(const value_type *s, size_type index, size_type count) const
    {
        return rfind_(s, index, count);
    }

    template <typename StringLike>
    STR_CONSTEXPR size_type rfind(const StringLike &str, size_type index = npos, size_type count = npos) const STR_NOEXCEPT
    {
        index = std::min(count, getsize_(str) - 1);

        auto len = getsize_(str);
        if (count == npos || count > len - index)
        {
            count = len;
        }

        return rfind_(getptr_(str), index, count);
    }

protected:
    STR_CONSTEXPR size_type rfind_(const value_type ch, size_type index) const
    {
        assert_range_(index);

        auto ptr = data();
        for (size_type i = index; i >= 0; i--)
        {
            if (traits_type::eq(ptr[i], ch))
                return i;
        }

        return npos;
    }

    STR_CONSTEXPR size_type rfind_(const value_type *s, size_type index, size_type count) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();

        for (; index > count; index--)
        {
            // find first character
            for (size_type i = len; i >= 0; i--)
            {
                if (traits_type::eq(ptr[i], ch))
                {
                    index = i;
                    break;
                }
            }

            // fail if even the first character was not found
            if (index == npos)
                return npos;

            // if found compare the string
            if (traits_type::compare(ptr + index, s, count) == 0)
                return index;
        }

        return npos;
    }

public:
    //////////////////////////////////////////////////////////////////////
    /// find_first_of
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR size_type find_first_of(value_type ch, size_type index = 0) const STR_NOEXCEPT
    {
        return find_first_of_(ch, index);
    }

    STR_CONSTEXPR size_type find_first_of(const value_type *s, size_type index = 0) const
    {
        return find_first_of_(s, index, traits_type::length(s));
    }

    STR_CONSTEXPR size_type find_first_of(const value_type *s, size_type index, size_type count) const
    {
        return find_first_of_(s, index, count);
    }

    template <typename StringLike>
    STR_CONSTEXPR size_type find_first_of(const StringLike &str, size_type index = 0, size_type count = npos) const STR_NOEXCEPT
    {
        auto len = getsize_(str);
        if (count == npos || count > len - index)
        {
            count = len;
        }

        return find_first_of_(getptr_(str), index, count);
    }

protected:
    STR_CONSTEXPR size_type find_first_of_(const value_type ch, size_type index) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i < len; i++)
        {
            if (traits_type::eq(ptr[i], ch))
                return i;
        }

        return npos;
    }

    STR_CONSTEXPR size_type find_first_of_(const value_type *s, size_type index, size_type count) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i < len; i++)
            for (size_type j = 0; j < count; j++)
            {
                if (traits_type::eq(ptr[i], s[j]))
                    return i;
            }

        return npos;
    }

public:
    //////////////////////////////////////////////////////////////////////
    /// find_first_not_of
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR size_type find_first_not_of(value_type ch, size_type index = 0) const STR_NOEXCEPT
    {
        return find_first_not_of_(ch, index);
    }

    STR_CONSTEXPR size_type find_first_not_of(const value_type *s, size_type index = 0) const
    {
        return find_first_not_of_(s, index, traits_type::length(s));
    }

    STR_CONSTEXPR size_type find_first_not_of(const value_type *s, size_type index, size_type count) const
    {
        return find_first_not_of_(s, index, count);
    }

    template <typename StringLike>
    STR_CONSTEXPR size_type find_first_not_of(const StringLike &str, size_type index = 0, size_type count = npos) const STR_NOEXCEPT
    {
        auto len = getsize_(str);
        if (count == npos || count > len - index)
        {
            count = len;
        }

        return find_first_not_of_(getptr_(str), index, count);
    }

protected:
    STR_CONSTEXPR size_type find_first_not_of_(const value_type ch, size_type index) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i < len; i++)
        {
            if (traits_type::eq(ptr[i], ch) == false)
                return i;
        }

        return npos;
    }

    STR_CONSTEXPR size_type find_first_not_of_(const value_type *s, size_type index, size_type count) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i < len; i++)
        {
            bool matched = false;
            for (size_type j = 0; j < count; j++)
            {
                if (traits_type::eq(ptr[i], s[j]))
                {
                    matched = true;
                    break;
                }
            }

            if (matched == false)
                return i;
        }

        return npos;
    }

public:
    //////////////////////////////////////////////////////////////////////
    /// find_last_of
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR size_type find_last_of(value_type ch, size_type index = npos) const STR_NOEXCEPT
    {
        return find_last_of_(ch, index);
    }

    STR_CONSTEXPR size_type find_last_of(const value_type *s, size_type index = npos) const
    {
        return find_last_of_(s, index, traits_type::length(s));
    }

    STR_CONSTEXPR size_type find_last_of(const value_type *s, size_type index, size_type count) const
    {
        return find_last_of_(s, index, count);
    }

    template <typename StringLike>
    STR_CONSTEXPR size_type find_last_of(const StringLike &str, size_type index = npos, size_type count = npos) const STR_NOEXCEPT
    {
        index = std::min(index, getsize_(str) - 1);

        auto len = getsize_(str);
        if (count == npos || count > len - index)
        {
            count = len;
        }

        return find_last_of_(getptr_(str), index, count);
    }

protected:
    STR_CONSTEXPR size_type find_last_of_(const value_type ch, size_type index) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i >= 0; i--)
        {
            if (traits_type::eq(ptr[i], ch))
                return i;
        }

        return npos;
    }

    STR_CONSTEXPR size_type find_last_of_(const value_type *s, size_type index, size_type count) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i >= 0; i--)
            for (size_type j = 0; j < count; j++)
            {
                if (traits_type::eq(ptr[i], s[j]))
                    return i;
            }

        return npos;
    }

public:
    //////////////////////////////////////////////////////////////////////
    /// find_last_not_of
    //////////////////////////////////////////////////////////////////////

    STR_CONSTEXPR size_type find_last_not_of(value_type ch, size_type index = 0) const STR_NOEXCEPT
    {
        return find_last_not_of_(ch, index);
    }

    STR_CONSTEXPR size_type find_last_not_of(const value_type *s, size_type index = 0) const
    {
        return find_last_not_of_(s, index, traits_type::length(s));
    }

    STR_CONSTEXPR size_type find_last_not_of(const value_type *s, size_type index, size_type count) const
    {
        return find_last_not_of_(s, index, count);
    }

    template <typename StringLike>
    STR_CONSTEXPR size_type find_last_not_of(const StringLike &str, size_type index = 0, size_type count = npos) const STR_NOEXCEPT
    {
        auto len = getsize_(str);
        if (count == npos || count > len - index)
        {
            count = len;
        }

        return find_last_not_of_(getptr_(str), index, count);
    }

protected:
    STR_CONSTEXPR size_type find_last_not_of_(const value_type ch, size_type index) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i >= 0; i--)
        {
            if (traits_type::eq(ptr[i], ch) == false)
                return i;
        }

        return npos;
    }

    STR_CONSTEXPR size_type find_last_not_of_(const value_type *s, size_type index, size_type count) const
    {
        assert_range_(index);

        auto ptr = data();
        auto len = size();
        for (size_type i = index; i >= 0; i--)
        {
            bool matched = false;
            for (size_type j = 0; j < count; j++)
            {
                if (traits_type::eq(ptr[i], s[j]))
                {
                    matched = true;
                    break;
                }
            }

            if (matched == false)
                return i;
        }

        return npos;
    }

protected:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assertions
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename Exception, typename... Args>
    STR_CONSTEXPR void assert_(bool assertion, Args... args) const
    {
        if (!assertion)
        {
            throw Exception(std::forward<Args>(args)...);
        }
    }

    STR_CONSTEXPR void assert_length_(size_type size, const char *msg = nullptr) const
    {
        assert_<std::length_error>(size <= max_size(), msg == nullptr ? "'max_length' reached" : msg);
    }

    STR_CONSTEXPR void assert_range_(size_type index, size_type min, size_type max, const char *msg = nullptr) const
    {
        assert_<std::out_of_range>(index >= min && index <= max, msg == nullptr ? "'index' was out of range" : msg);
    }

    STR_CONSTEXPR void assert_range_(size_type index, const char *msg = nullptr) const
    {
        assert_<std::out_of_range>(index >= 0 && index <= size(), msg == nullptr ? "'index' was out of range" : msg);
    }

    STR_CONSTEXPR void assert_space_(size_type space, const char *msg = nullptr) const
    {
        assert_<std::length_error>(space <= capacity() - size(), msg == nullptr ? "not enough space" : msg);
    }

    STR_CONSTEXPR void assert_null_(const void *ptr, const char *msg = nullptr) const
    {
        assert_<std::invalid_argument>(ptr != nullptr, msg == nullptr ? "null argument passed" : msg);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// strtraits
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename StringLike>
    const_pointer getptr_(const StringLike &str)
    {
        using thistraits = strtraits<basic_str<Char, CharTraits, Allocator>>;
        using othertraits = strtraits<StringLike>;

        static_assert(std::is_same_v<thistraits::char_type, othertraits::char_type>,
                      "char_type must be same for both string types");

        static_assert(std::is_same_v<thistraits::char_traits, othertraits::char_traits>,
                      "char_traits must be same for both string types");

        static_assert(std::is_same_v<thistraits::allocator_type, othertraits::allocator_type>,
                      "allocator_type must be same for both string types");

        return othertraits::data(str);
    }

    template <typename StringLike>
    size_type getsize_(const StringLike &str)
    {
        using thistraits = strtraits<basic_str<Char, CharTraits, Allocator>>;
        using othertraits = strtraits<StringLike>;

        static_assert(std::is_same_v<thistraits::char_type, othertraits::char_type>,
                      "char_type must be same for both string types");

        static_assert(std::is_same_v<thistraits::char_traits, othertraits::char_traits>,
                      "char_traits must be same for both string types");

        static_assert(std::is_same_v<thistraits::allocator_type, othertraits::allocator_type>,
                      "allocator_type must be same for both string types");

        return othertraits::size(str);
    }

    template <typename StringLike>
    std::tuple<const_pointer, size_type> getdata_(const StringLike &str)
    {
        using thistraits = strtraits<basic_str<Char, CharTraits, Allocator>>;
        using othertraits = strtraits<StringLike>;

        static_assert(std::is_same_v<thistraits::char_type, othertraits::char_type>,
                      "char_type must be same for both string types");

        static_assert(std::is_same_v<thistraits::char_traits, othertraits::char_traits>,
                      "char_traits must be same for both string types");

        static_assert(std::is_same_v<thistraits::allocator_type, othertraits::allocator_type>,
                      "allocator_type must be same for both string types");

        return { othertraits::data(str), othertraits::size(str) };
    }
};

template <typename Char, typename CharTraits, typename Allocator>
class basic_str<Char, CharTraits, Allocator>::const_iterator
{
    using this_t = const_iterator;
    using source_t = basic_str<Char, CharTraits, Allocator>;

public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename source_t::value_type;
    using difference_type = typename source_t::difference_type;
    using pointer = typename source_t::const_pointer;
    using reference = typename source_t::const_reference;

public:
    STR_CONSTEXPR const_iterator() STR_NOEXCEPT = default;
    STR_CONSTEXPR const_iterator(const value_type *ptr) STR_NOEXCEPT : ptr_{ptr} {}
    STR_CONSTEXPR ~const_iterator() STR_NOEXCEPT = default;

    STR_NODISCARD STR_CONSTEXPR reference operator*() const STR_NOEXCEPT
    {
        return *ptr_;
    }
    STR_NODISCARD STR_CONSTEXPR pointer operator->() const STR_NOEXCEPT
    {
        return ptr_;
    }

    STR_CONSTEXPR this_t &operator++() STR_NOEXCEPT
    {
        ptr_++;
        return *this;
    }

    STR_CONSTEXPR this_t operator++(int) STR_NOEXCEPT
    {
        this_t tmp(ptr_);
        ++ptr_;
        return tmp;
    }

    STR_CONSTEXPR this_t &operator--() STR_NOEXCEPT
    {
        ptr_--;
        return *this;
    }

    STR_CONSTEXPR this_t operator--(int) STR_NOEXCEPT
    {
        this_t tmp(ptr_);
        --ptr_;
        return tmp;
    }

    STR_CONSTEXPR this_t &operator+=(const difference_type offset) STR_NOEXCEPT
    {
        ptr_ += offset;
        return *this;
    }

    STR_CONSTEXPR this_t &operator-=(const difference_type offset) STR_NOEXCEPT
    {
        ptr_ -= offset;
        return *this;
    }

    STR_NODISCARD STR_CONSTEXPR this_t operator+(const difference_type offset) const STR_NOEXCEPT
    {
        return this_t(ptr_ + offset);
    }

    STR_NODISCARD STR_CONSTEXPR this_t operator-(const difference_type offset) const STR_NOEXCEPT
    {
        return this_t(ptr_ - offset);
    }

    STR_NODISCARD STR_CONSTEXPR difference_type operator+(const this_t &right) const STR_NOEXCEPT
    {
        return static_cast<difference_type>(ptr_ + right.ptr_);
    }

    STR_NODISCARD STR_CONSTEXPR difference_type operator-(const this_t &right) const STR_NOEXCEPT
    {
        return static_cast<difference_type>(ptr_ - right.ptr_);
    }

    STR_NODISCARD STR_CONSTEXPR reference operator[](const difference_type offset) const STR_NOEXCEPT
    {
        return *(ptr_ + offset);
    }

    STR_NODISCARD STR_CONSTEXPR bool operator==(const this_t &right) const STR_NOEXCEPT
    {
        return ptr_ == right.ptr_;
    }

#if _HAS_CXX20
    STR_NODISCARD STR_CONSTEXPR strong_ordering operator<=>(const this_t &right) const STR_NOEXCEPT;
#else
    STR_NODISCARD bool operator!=(const this_t &right) const STR_NOEXCEPT
    {
        return ptr_ != right.ptr_;
    }
    STR_NODISCARD bool operator<(const this_t &right) const STR_NOEXCEPT
    {
        return ptr_ < right.ptr_;
    }
    STR_NODISCARD bool operator>(const this_t &right) const STR_NOEXCEPT
    {
        return ptr_ > right.ptr_;
    }
    STR_NODISCARD bool operator<=(const this_t &right) const STR_NOEXCEPT
    {
        return ptr_ <= right.ptr_;
    }
    STR_NODISCARD bool operator>=(const this_t &right) const STR_NOEXCEPT
    {
        return ptr_ >= right.ptr_;
    }
#endif

protected:
    const value_type *ptr_ = nullptr;
};

template <typename Char, typename CharTraits, typename Allocator>
class basic_str<Char, CharTraits, Allocator>::iterator : public const_iterator
{
    using this_t = iterator;
    using base_t = const_iterator;
    using source_t = basic_str<Char, CharTraits, Allocator>;

public:
    using iterator_category = typename base_t::iterator_category;
    using value_type = typename base_t::value_type;
    using difference_type = typename base_t::difference_type;
    using pointer = typename source_t::pointer;
    using reference = typename source_t::reference;

public:
    STR_CONSTEXPR iterator() STR_NOEXCEPT = default;

    STR_CONSTEXPR iterator(value_type *ptr) STR_NOEXCEPT
        : const_iterator{ptr} {}

    STR_CONSTEXPR ~iterator() STR_NOEXCEPT = default;

    STR_NODISCARD STR_CONSTEXPR reference operator*() const STR_NOEXCEPT
    {
        return const_cast<reference>(base_t::operator*());
    }
    STR_NODISCARD STR_CONSTEXPR pointer operator->() const STR_NOEXCEPT
    {
        return const_cast<pointer>(base_t::operator->());
    }

    STR_CONSTEXPR this_t &operator++() STR_NOEXCEPT
    {
        base_t::operator++();
        return *this;
    }

    STR_CONSTEXPR this_t operator++(int) STR_NOEXCEPT
    {
        this_t tmp = *this;
        base_t::operator++(0);
        return tmp;
    }

    STR_CONSTEXPR this_t &operator--() STR_NOEXCEPT
    {
        base_t::operator--();
        return *this;
    }

    STR_CONSTEXPR this_t operator--(int) STR_NOEXCEPT
    {
        this_t tmp = *this;
        base_t::operator--();
        return tmp;
    }

    STR_CONSTEXPR this_t &operator+=(const difference_type offset) STR_NOEXCEPT
    {
        base_t::operator+=(offset);
        return *this;
    }

    STR_CONSTEXPR this_t &operator-=(const difference_type offset) STR_NOEXCEPT
    {
        base_t::operator-=(offset);
        return *this;
    }

    STR_NODISCARD STR_CONSTEXPR this_t operator+(const difference_type offset) const STR_NOEXCEPT
    {
        return this_t(operator->() + offset);
    }

    STR_NODISCARD STR_CONSTEXPR this_t operator-(const difference_type offset) const STR_NOEXCEPT
    {
        return this_t(operator->() - offset);
    }

    STR_NODISCARD STR_CONSTEXPR difference_type operator+(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator+(right);
    }

    STR_NODISCARD STR_CONSTEXPR difference_type operator-(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator-(right);
    }

    STR_NODISCARD STR_CONSTEXPR reference operator[](const difference_type offset) const STR_NOEXCEPT
    {
        return const_cast<reference>(base_t::operator[offset]);
    }

    STR_NODISCARD STR_CONSTEXPR bool operator==(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator==(right);
    }

#if _HAS_CXX20
    STR_NODISCARD STR_CONSTEXPR strong_ordering operator<=>(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator<=>(right);
    }
#else
    STR_NODISCARD bool operator!=(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator!=(right);
    }
    STR_NODISCARD bool operator<(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator<(right);
    }
    STR_NODISCARD bool operator>(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator>(right);
    }
    STR_NODISCARD bool operator<=(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator<=(right);
    }
    STR_NODISCARD bool operator>=(const this_t &right) const STR_NOEXCEPT
    {
        return base_t::operator>=(right);
    }
#endif
};

//////////////////////////////////////////////////////////////////////
// OStream Operator
//////////////////////////////////////////////////////////////////////

template <typename Char, typename CharTraits, typename Allocator>
std::basic_ostream<Char, CharTraits> &
operator<<(std::basic_ostream<Char, CharTraits> &os,
           const basic_str<Char, CharTraits, Allocator> &str)
{
    using size_type = basic_str<Char, CharTraits, Allocator>::size_type;

    size_type size = str.size();
    auto ptr = str.data();

    for (size_type i = 0; i < size; i++)
    {
        os << ptr[i];
    }

    return os;
}

//////////////////////////////////////////////////////////////////////
// IStream Operator
//////////////////////////////////////////////////////////////////////

template <typename Char, typename CharTraits, typename Allocator>
std::basic_istream<Char, CharTraits> &
operator>>(std::basic_istream<Char, CharTraits> &is,
           basic_str<Char, CharTraits, Allocator> &str)
{
    using size_type = basic_str<Char, CharTraits, Allocator>::size_type;

    size_type size = str.size();
    auto ptr = str.data();

    for (size_type i = 0; i < size; i++)
    {
        is >> ptr[i];
    }

    return is;
}

//////////////////////////////////////////////////////////////////////
// TypeDefs
//////////////////////////////////////////////////////////////////////

using str = basic_str<char>;
using wstr = basic_str<wchar_t>;
using u8str = basic_str<char8_t>;
using u16str = basic_str<char16_t>;
using u32str = basic_str<char32_t>;

//////////////////////////////////////////////////////////////////////
// Numeric Conversions
//////////////////////////////////////////////////////////////////////

// converts a string to a signed integer
int stoi(const str &str, size_t *pos = nullptr, int base = 10)
{
    str::pointer ptr;
    int result = static_cast<int>(
        std::strtol(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
int stoi(const wstr &str, size_t *pos = nullptr, int base = 10)
{
    wstr::pointer ptr;
    int result = static_cast<int>(
        std::wcstol(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

// converts a string to a signed long
long stol(const str &str, size_t *pos = nullptr, int base = 10)
{
    str::pointer ptr;
    long result = static_cast<long>(
        std::strtol(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
long stol(const wstr &str, size_t *pos = nullptr, int base = 10)
{
    wstr::pointer ptr;
    long result = static_cast<long>(
        std::wcstol(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

// converts a string to a signed long long
long long stoll(const str &str, size_t *pos = nullptr, int base = 10)
{
    str::pointer ptr;
    long long result = static_cast<long long>(
        std::strtoll(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
long long stoll(const wstr &str, size_t *pos = nullptr, int base = 10)
{
    wstr::pointer ptr;
    long long result = static_cast<long long>(
        std::wcstoll(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

// converts a string to a unsigned long
unsigned long stoul(const str &str, size_t *pos = nullptr, int base = 10)
{
    str::pointer ptr;
    unsigned long result = static_cast<unsigned long>(
        std::strtoul(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
unsigned long stoul(const wstr &str, size_t *pos = nullptr, int base = 10)
{
    wstr::pointer ptr;
    unsigned long result = static_cast<unsigned long>(
        std::wcstoul(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

// converts a string to a unsigned long long
unsigned long long stoull(const str &str, size_t *pos = nullptr, int base = 10)
{
    str::pointer ptr;
    unsigned long long result = static_cast<unsigned long long>(
        std::strtoull(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
unsigned long long stoull(const wstr &str, size_t *pos = nullptr, int base = 10)
{
    wstr::pointer ptr;
    unsigned long long result = static_cast<unsigned long long>(
        std::wcstoull(str.c_str(), &ptr, base));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

// converts a string to a signed integer
float stof(const str &str, size_t *pos = nullptr)
{
    str::pointer ptr;
    float result = static_cast<float>(
        std::strtof(str.c_str(), &ptr));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
float stof(const wstr &str, size_t *pos = nullptr)
{
    wstr::pointer ptr;
    float result = static_cast<float>(
        std::wcstof(str.c_str(), &ptr));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

// converts a string to a signed long
long stod(const str &str, size_t *pos = nullptr)
{
    str::pointer ptr;
    long result = static_cast<long>(
        std::strtof(str.c_str(), &ptr));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
long stod(const wstr &str, size_t *pos = nullptr)
{
    wstr::pointer ptr;
    long result = static_cast<long>(
        std::wcstof(str.c_str(), &ptr));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

// converts a string to a signed long long
long long stold(const str &str, size_t *pos = nullptr)
{
    str::pointer ptr;
    long long result = static_cast<long long>(
        std::strtold(str.c_str(), &ptr));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}
long long stold(const wstr &str, size_t *pos = nullptr)
{
    wstr::pointer ptr;
    long long result = static_cast<long long>(
        std::wcstold(str.c_str(), &ptr));

    if (pos != nullptr)
    {
        *pos = str.c_str() - ptr;
    }

    return result;
}

STR_NAMESPACE_MAIN_END