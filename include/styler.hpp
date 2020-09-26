#ifndef STYLER_HPP
#define STYLER_HPP

#include <iostream>
#include <type_traits>

namespace styler
{
enum class Style
{
    Reset,
    Bold,
    Dim,
    Italic,
    Underline,
    Blink,
    RBlink,
    Reversed,
    Conceal,
    Crossed
};

enum class Foreground
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    Gray,
    Reset
};

enum class Background
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    Gray,
    Reset
};

namespace internal
{
template <typename T>
using IsValid =
    typename std::enable_if<std::is_same<T, Style>::value ||
                                std::is_same<T, Foreground>::value ||
                                std::is_same<T, Background>::value,
                            std::ostream&>::type;
}  // namespace internal
}  // namespace styler

#endif