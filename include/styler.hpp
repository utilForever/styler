#ifndef STYLER_HPP
#define STYLER_HPP

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
}
}  // namespace styler

#endif