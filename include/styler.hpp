#ifndef STYLER_HPP
#define STYLER_HPP

#include <iostream>
#include <type_traits>

namespace styler
{
enum class style
{
    reset,
    bold,
    dim,
    italic,
    underline,
    blink,
    rblink,
    reversed,
    conceal,
    crossed
};

enum class foreground
{
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    gray,
    reset
};

enum class background
{
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    gray,
    reset
};

namespace internal
{
template <typename T>
using IsValid =
    typename std::enable_if<std::is_same<T, style>::value ||
                                std::is_same<T, foreground>::value ||
                                std::is_same<T, background>::value,
                            std::ostream&>::type;
}
}  // namespace styler

#endif