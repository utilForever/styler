#ifndef STYLER_HPP
#define STYLER_HPP

#if defined(__unix__) || defined(__unix) || defined(__linux__)
#define STYLER_LINUX
#elif defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#define STYLER_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#define STYLER_MACOSX
#else
#error Unknown Platform
#endif

#if defined(STYLER_LINUX) || defined(STYLER_MACOSX)
#elif defined(STYLER_WINDOWS)
#include <Windows.h>
#include <io.h>
#endif

#include <algorithm>
#include <atomic>
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

inline bool IsSupportColor() noexcept
{
#if defined(STYLER_LINUX) || defined(STYLER_MACOSX)
    const char* terms[] = { "ansi",    "color",  "console", "cygwin", "gnome",
                            "konsole", "kterm",  "linux",   "msys",   "putty",
                            "rxvt",    "screen", "vt100",   "xterm" };

    const char* envParam = std::getenv("TERM");
    if (!envParam)
    {
        return false;
    }

    return std::any_of(std::begin(terms), std::end(terms),
                       [&](const char* term) {
                           return std::strstr(envParam, term) != nullptr;
                       });
#elif defined(STYLER_WINDOWS)
    // All windows versions support colors through native console methods
    return true;
#endif
}

#if defined(STYLER_WINDOWS)
inline bool IsMSYSPty(int fd) noexcept
{
    // Dynamic load for binary compatibility with old Windows
    const auto ptrFileInfo =
        reinterpret_cast<decltype(&GetFileInformationByHandleEx)>(
            GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")),
                           "GetFileInformationByHandleEx"));
    if (!ptrFileInfo)
    {
        return false;
    }

    const auto handle = reinterpret_cast<HANDLE>(_get_osfhandle(fd));
    if (handle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    // Check that it's a pipe:
    if (GetFileType(handle) != FILE_TYPE_PIPE)
    {
        return false;
    }

    // POD type is binary compatible with FILE_NAME_INFO from WinBase.h
    // It have the same alignment and used to avoid UB in caller code
    struct MY_FILE_NAME_INFO
    {
        DWORD FileNameLength;
        WCHAR FileName[MAX_PATH];
    };

    auto pNameInfo = std::make_unique<MY_FILE_NAME_INFO>();
    if (!pNameInfo)
    {
        return false;
    }

    // Check pipe name is template of
    // {"cygwin-","msys-"}XXXXXXXXXXXXXXX-ptyX-XX
    if (!ptrFileInfo(handle, FileNameInfo, pNameInfo.get(),
                     sizeof(MY_FILE_NAME_INFO)))
    {
        return false;
    }

    const std::wstring name(pNameInfo->FileName,
                            pNameInfo->FileNameLength / sizeof(WCHAR));
    if ((name.find(L"msys-") == std::wstring::npos &&
         name.find(L"cygwin-") == std::wstring::npos) ||
        name.find(L"-pty") == std::wstring::npos)
    {
        return false;
    }

    return true;
}
#endif

inline bool IsTerminal(const std::streambuf* osbuf) noexcept
{
#if defined(STYLER_LINUX) || defined(STYLER_MACOSX)
    if (osbuf == std::cout.rdbuf())
    {
        const static bool coutTerm = isatty(fileno(stdout)) != 0;
        return coutTerm;
    }
    else if (osbuf == std::cerr.rdbuf() || osbuf == std::clog.rdbuf())
    {
        const static bool cerrTerm = isatty(fileno(stderr)) != 0;
        return cerrTerm;
    }
#elif defined(STYLER_WINDOWS)
    if (osbuf == std::cout.rdbuf())
    {
        const static bool coutTerm =
            _isatty(_fileno(stdout)) || IsMSYSPty(_fileno(stdout));
        return coutTerm;
    }
    else if (osbuf == std::cerr.rdbuf() || osbuf == std::clog.rdbuf())
    {
        const static bool cerrTerm =
            _isatty(_fileno(stderr)) || IsMSYSPty(_fileno(stderr));
        return cerrTerm;
    }
#endif

    return false;
}

template <typename T>
using IsValid =
    typename std::enable_if<std::is_same<T, Style>::value ||
                                std::is_same<T, Foreground>::value ||
                                std::is_same<T, Background>::value,
                            std::ostream&>::type;

#if defined(STYLER_WINDOWS)
template <typename T>
IsValid<T> SetColor(std::ostream& os, const T value)
{
    (void)value;

    return os;
}
#else
template <typename T>
IsValid<T> SetColor(std::ostream& os, const T value)
{
    return os << "\033[" << static_cast<int>(value) << "m";
}
#endif
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