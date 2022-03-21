#pragma once
#include "tweaks.hpp"

///////////////////////////////////////////////////////////////////
// Namespaces
///////////////////////////////////////////////////////////////////
#define STR_NAMESPACE_MAIN str
#define STR_NAMESPACE_MAIN_BEGIN \
    namespace STR_NAMESPACE_MAIN \
    {
#define STR_NAMESPACE_MAIN_END }

///////////////////////////////////////////////////////////////////
// Namespaces
///////////////////////////////////////////////////////////////////
// #define STR_CONSTEXPR constexpr
#define STR_CONSTEXPR
#define STR_CONSTEXPR_20 STR_CONSTEXPR
#define STR_CONSTEXPR_VFUNC STR_CONSTEXPR virtual

#define STR_NOEXCEPT noexcept
#define STR_NOEXCEPT_IF(condition) noexcept(condition)

#define STR_NODISCARD [[nodiscard]]

enum char8_t : unsigned char
{
};

STR_NAMESPACE_MAIN_BEGIN

template <typename Char, typename StringLike>
const Char *getptr(const StringLike &strlike)
{
    return strlike.data();
}

template <typename Size, typename StringLike>
Size getsize(const StringLike &strlike)
{
    return strlike.size();
}

STR_NAMESPACE_MAIN_END