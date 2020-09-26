#include "styler.hpp"

using namespace styler;

int main()
{
    std::cout << "\n\n\n"
              << Style::Reset << Style::Underline << Style::Bold
              << "Control = Auto" << Style::Reset << Background::Reset
              << Foreground::Reset << std::endl;

    return 0;
}