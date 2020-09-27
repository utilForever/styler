#include "Styler.hpp"

#include <string>

using namespace styler;

void PrintHeading(const std::string& heading)
{
    std::cout << '\n'
              << Style::Reset << heading << Style::Reset << Background::Reset
              << Foreground::Reset << std::endl;
}

void TestFeatures(std::ostream& os, const WinTerm opt)
{
    SetWinTermMode(opt);

    PrintHeading("Text Style Test:");
    os << Style::Bold << " Bold " << Style::Reset;
    os << Style::Faint << " Faint " << Style::Reset;
    os << Style::Italic << " Italic " << Style::Reset;
    os << Style::Underline << " Underline " << Style::Reset;
    os << Style::SlowBlink << " SlowBlink " << Style::Reset;
    os << Style::RapidBlink << " RapidBlink " << Style::Reset;
    os << Style::Reverse << " Reverse " << Style::Reset;
    os << Style::Conceal << " Conceal " << Style::Reset;
    os << Style::Crossed << " Crossed " << Style::Reset << std::endl;

    PrintHeading("Background Test:");
    os << Background::Black << " Black " << Background::Reset;
    os << Background::Red << " Red " << Background::Reset;
    os << Background::Green << " Green " << Background::Reset;
    os << Background::Yellow << " Yellow " << Background::Reset;
    os << Background::Blue << " Blue " << Background::Reset;
    os << Background::Magenta << " Magenta " << Background::Reset;
    os << Background::Cyan << " Cyan " << Background::Reset;
    os << Background::Gray << " Grey " << Background::Reset;
    os << Background::White << " White " << Background::Reset << std::endl;

    PrintHeading("Foreground Test:");
    os << Foreground::Black << " Black " << Foreground::Reset;
    os << Foreground::Red << " Red " << Foreground::Reset;
    os << Foreground::Green << " Green " << Foreground::Reset;
    os << Foreground::Yellow << " Yellow " << Foreground::Reset;
    os << Foreground::Blue << " Blue " << Foreground::Reset;
    os << Foreground::Magenta << " Magenta " << Foreground::Reset;
    os << Foreground::Cyan << " Cyan " << Foreground::Reset;
    os << Foreground::Gray << " Grey " << Foreground::Reset;
    os << Foreground::White << " White " << Foreground::Reset << std::endl;
}

void EnumerateWinTerms()
{
    std::cout << std::endl;
    std::cout
        << "_________________________________________________________________";
    std::cout << "\n\n"
              << Style::Reset << Style::Bold << "Printing for WinTerm = Auto"
              << Style::Reset << Background::Reset << Foreground::Reset << '\n';
    std::cout
        << "_________________________________________________________________";
    TestFeatures(std::cout, WinTerm::Auto);
    TestFeatures(std::clog, WinTerm::Auto);
    TestFeatures(std::cerr, WinTerm::Auto);
    std::cout
        << "-------------------------------------------------------------\n\n";

    std::cout << std::endl;
    std::cout
        << "_________________________________________________________________";
    std::cout << "\n\n"
              << Style::Reset << Style::Bold << "Printing for WinTerm = Ansi"
              << Style::Reset << Background::Reset << Foreground::Reset << '\n';
    std::cout
        << "_________________________________________________________________";
    TestFeatures(std::cout, WinTerm::Ansi);
    TestFeatures(std::clog, WinTerm::Ansi);
    TestFeatures(std::cerr, WinTerm::Ansi);
    std::cout
        << "-------------------------------------------------------------\n\n";

    std::cout << std::endl;
    std::cout
        << "_________________________________________________________________";
    std::cout << "\n\n"
              << Style::Reset << Style::Bold << "Printing for WinTerm = Native"
              << Style::Reset << Background::Reset << Foreground::Reset << '\n';
    std::cout
        << "_________________________________________________________________";
    TestFeatures(std::cout, WinTerm::Native);
    TestFeatures(std::clog, WinTerm::Native);
    TestFeatures(std::cerr, WinTerm::Native);
    std::cout
        << "-------------------------------------------------------------\n\n";
}

int main()
{
    std::cout << "\n\n\n"
              << Style::Reset << Style::Underline << Style::Bold
              << "Control = Auto" << Style::Reset << Background::Reset
              << Foreground::Reset << std::endl;
    SetControlMode(Control::Auto);
    EnumerateWinTerms();

    std::cout << "\n\n\n"
              << Style::Reset << Style::Underline << Style::Bold
              << "Control = Force" << Style::Reset << Background::Reset
              << Foreground::Reset << std::endl;
    SetControlMode(Control::Force);
    EnumerateWinTerms();

    std::cout << "\n\n\n"
              << Style::Reset << Style::Underline << Style::Bold
              << "Control = Off" << Style::Reset << Background::Reset
              << Foreground::Reset << std::endl;
    SetControlMode(Control::Off);
    EnumerateWinTerms();

    return 0;
}