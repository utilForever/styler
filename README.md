# styler

<img src="./media/logo.png" width=256 height=256 />

[![License](https://img.shields.io/badge/Licence-MIT-blue.svg)](./LICENSE)

styler is a header only Modern C++ library for styling output text in Terminal based on [styler](https://github.com/agauniyal/styler) that was created by [Abhinav Gauniyal](https://github.com/agauniyal).
The code is built on C++17 and can be compiled with commonly available compilers such as g++, clang++, or Microsoft Visual Studio. styler currently supports macOS (10.12.6 or later), Ubuntu (17.04 or later), Windows (Visual Studio 2017 or later), and Windows Subsystem for Linux (WSL). Other untested platforms that support C++17 also should be able to build styler.

## Example usage

```c++
#include "styler.hpp"

using namespace styler;

int main()
{
    std::cout << "Plain old text"
              << Style::Bold << "styler-applied text!!"
              << Style::Reset << std::endl;
}
```

## Dependencies

*styler* only depends on [C++ Standard Library](http://en.cppreference.com/w/cpp/header), `unistd.h` system header on Unix and `Windows.h` & `io.h` system headers on Windows based systems. In other words, you don't need any 3rd party dependencies.

## Installation

*styler* is a single header-only library. Put `styler.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## How to use

*styler* uses iostream objects - `cout`/`clog`/`cerr` to apply attributes to output text. Since *styler* aims to support both Windows and Unix like systems, it takes care of the os specific details and tries to provide a uniform interface. Due to incompatiblities b/w different OS versions, not all kinds of attributes are supported on every system so styler will try to skip the ones which might produce garbage(instead of pushing random ANSI escape codes on your streams). Detection of tty is also handled internally so you don't need to check if application user might redirect output to a file.

Apart from setting text attributes, you can also ask styler to override its default behaviour through these methods -

```cpp
void styler::SetControlMode(styler::Control);
```
where `styler::Control` takes
 - `Control::Auto` - Automatically detects whether terminal supports color or not (**Default**)
 - `Control::Off` - Turn off colors completely
 - `Control::Force` - Force colors even if terminal doesn't supports them or output is redirected to non-terminal

```cpp
void styler::SetWinTermMode(styler::WinTerm);
```
where `styler::WinTerm` takes
 - `WinTerm::Auto` - Checks for newer Windows and picks Ansi otherwise falls back to Native (**Default**)
 - `WinTerm::Native` - This method is supported in all versions of Windows but supports less attributes
 - `WinTerm::Ansi` - This method is supported in newer versions of Windows and supports rich variety of attributes


Supported attributes with their compatiblity are listed below -

### Text Styles

| Code | Linux/Windows/Others | Old Windows
| :----: | :---------: | :------: |
| `styler::Style::Bold`       | Yes   | Yes |
| `styler::Style::Faint`      | Yes   | No  |
| `styler::Style::Italic`     | Yes   | No  |
| `styler::Style::Underline`  | Yes   | No  |
| `styler::Style::SlowBlink`  | No    | No  |
| `styler::Style::RapidBlink` | No    | No  |
| `styler::Style::Reverse`    | Yes   | Yes |
| `styler::Style::Conceal`    | Maybe | Yes |
| `styler::Style::Crossed`    | Yes   | No  |

### Text Color

| Code | Linux/Windows/Others | Old Windows
| :----: | :---------: | :------: |
| `styler::Foreground::Black`   | Yes | Yes |
| `styler::Foreground::Red`     | Yes | Yes |
| `styler::Foreground::Green`   | Yes | Yes |
| `styler::Foreground::Yellow`  | Yes | Yes |
| `styler::Foreground::Blue`    | Yes | Yes |
| `styler::Foreground::Magenta` | Yes | Yes |
| `styler::Foreground::Cyan`    | Yes | Yes |
| `styler::Foreground::White`   | Yes | Yes |

### Background Color

| Code | Linux/Windows/Others | Old Windows
| :----: | :---------: | :------: |
| `styler::Background::Black`   | Yes | Yes |
| `styler::Background::Red`     | Yes | Yes |
| `styler::Background::Green`   | Yes | Yes |
| `styler::Background::Yellow`  | Yes | Yes |
| `styler::Background::Blue`    | Yes | Yes |
| `styler::Background::Magenta` | Yes | Yes |
| `styler::Background::Cyan`    | Yes | Yes |
| `styler::Background::White`   | Yes | Yes |

### Foreground Color - High Intensity

| Code | Linux/Windows/Others | Old Windows
| :----: | :---------: | :------: |
| `styler::ForegroundHI::Black`   | Yes | Yes |
| `styler::ForegroundHI::Red`     | Yes | Yes |
| `styler::ForegroundHI::Green`   | Yes | Yes |
| `styler::ForegroundHI::Yellow`  | Yes | Yes |
| `styler::ForegroundHI::Blue`    | Yes | Yes |
| `styler::ForegroundHI::Magenta` | Yes | Yes |
| `styler::ForegroundHI::Cyan`    | Yes | Yes |
| `styler::ForegroundHI::White`   | Yes | Yes |

### Background Color - High Intensity

| Code | Linux/Windows/Others | Old Windows
| :----: | :---------: | :------: |
| `styler::BackgroundHI::Black`   | Yes | Yes |
| `styler::BackgroundHI::Red`     | Yes | Yes |
| `styler::BackgroundHI::Green`   | Yes | Yes |
| `styler::BackgroundHI::Yellow`  | Yes | Yes |
| `styler::BackgroundHI::Blue`    | Yes | Yes |
| `styler::BackgroundHI::Magenta` | Yes | Yes |
| `styler::BackgroundHI::Cyan`    | Yes | Yes |
| `styler::BackgroundHI::White`   | Yes | Yes |

### Reset Styles/Colors

| Code | Linux/Windows/Others | Old Windows
| :----: | :---------: | :------: |
| `styler::Style::Reset`      | Yes | Yes |
| `styler::Foreground::Reset` | Yes | Yes |
| `styler::Background::Reset` | Yes | Yes |

## Documentation

TBA

## How To Contribute

Contributions are always welcome, either reporting issues/bugs or forking the repository and then issuing pull requests when you have completed some additional coding that you feel will be beneficial to the main project. If you are interested in contributing in a more dedicated capacity, then please contact me.

## Contact

You can contact me via e-mail (utilForever at gmail.com). I am always happy to answer questions or help with any issues you might have, and please be sure to share any additional work or your creations with me, I love seeing what other people are making.

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2020 [Chris Ohk](http://www.github.com/utilForever).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.