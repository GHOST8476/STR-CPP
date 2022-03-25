#pragma once
#include "common.hpp"
#include "tweaks.hpp"

STR_NAMESPACE_MAIN_BEGIN

#ifdef STR_TWEAKS_DISABLE_DEFAULT_STRTRAITS_IMPL
template <typename StringLike>
class strtraits;

#else
template <typename StringLike>
class strtraits
{
public:
    using char_type = typename StringLike::value_type;
    using char_traits = typename StringLike::traits_type;
    using allocator_type = typename StringLike::allocator_type;
    using allocator_traits = typename StringLike::allocator_traits;
    using size_type = typename StringLike::size_type;
    using difference_type = typename StringLike::difference_type;
    using reference = typename StringLike::reference;
    using const_reference = typename StringLike::const_reference;
    using pointer = typename StringLike::pointer;
    using const_pointer = typename StringLike::const_pointer;
    using iterator = typename StringLike::iterator;
    using const_iterator = typename StringLike::const_iterator;
    using reverse_iterator = typename StringLike::reverse_iterator;
    using const_reverse_iterator = typename StringLike::const_reverse_iterator;

public:
    STR_CONSTEXPR static size_type size(const StringLike &str)
        STR_NOEXCEPT_IF(STR_NOEXCEPT_IF(str.size()))
    {
        return str.size();
    }

    STR_CONSTEXPR static pointer data(StringLike &str)
        STR_NOEXCEPT_IF(STR_NOEXCEPT_IF(str.data()))
    {
        return str.data();
    }

    STR_CONSTEXPR static pointer data(StringLike &&str)
        STR_NOEXCEPT_IF(STR_NOEXCEPT_IF(str.data()))
    {
        return str.data();
    }

    STR_CONSTEXPR static const_pointer data(const StringLike &str)
        STR_NOEXCEPT_IF(STR_NOEXCEPT_IF(str.data()))
    {
        return str.data();
    }
};

#endif

STR_NAMESPACE_MAIN_END