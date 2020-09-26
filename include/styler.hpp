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

//! Behavior of styler function calls.
enum class Control
{
    Off,   //! Toggle off rang style/color calls
    Auto,  //! (Default) auto-detect terminal and colorize if needed
    Force  //! Force ansi color output to non terminal streams
};

//! Terminal mode of Windows.
enum class WinTerm
{
    Auto,   // (Default) Automatically detects whether ANSI or Native API
    Ansi,   // Force use ANSI API
    Native  // Force use Native API
};

namespace internal
{
inline std::atomic<Control>& GetControlMode() noexcept
{
    static std::atomic<Control> controlMode{ Control::Auto };
    return controlMode;
}

inline std::atomic<WinTerm>& GetWinTermMode() noexcept
{
    static std::atomic<WinTerm> termMode{ WinTerm::Auto };
    return termMode;
}

template <typename T>
using IsValid =
    typename std::enable_if<std::is_same<T, Style>::value ||
                                std::is_same<T, Foreground>::value ||
                                std::is_same<T, Background>::value,
                            std::ostream&>::type;
}  // namespace internal

template <typename T>
internal::IsValid<T> operator<<(std::ostream& os, const T value)
{
    (void)value;

    const Control controlMode = internal::GetControlMode();

    if (controlMode == Control::Auto)
    {
    }

    if (controlMode == Control::Force)
    {
    }

    return os;
}

inline void SetControlMode(Control value) noexcept
{
    internal::GetControlMode() = value;
}

inline void SetWinTermMode(WinTerm value) noexcept
{
    internal::GetWinTermMode() = value;
}

}  // namespace styler

#endif