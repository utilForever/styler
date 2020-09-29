#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "styler.hpp"

#include <fstream>
#include <string>

using namespace std;
using namespace styler;

#if defined(__unix__) || defined(__unix) || defined(__linux__)
#define OS_LINUX
#elif defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#define OS_WIN
#elif defined(__APPLE__) || defined(__MACH__)
#define OS_MAC
#else
#error Unknown Platform
#endif

TEST_CASE("styler printing with Control::Off and cout")
{
    const string s = "Hello World";
    const string fileName = "out.txt";

    SetControlMode(Control::Off);

    SUBCASE("WinTerm = Native")
    {
        SetWinTermMode(WinTerm::Native);

        ofstream out{ fileName };
        streambuf* coutBuf = cout.rdbuf();

        cout.rdbuf(out.rdbuf());
        cout << Foreground::Blue << s << Style::Reset;
        cout.rdbuf(coutBuf);

        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        SetWinTermMode(WinTerm::Auto);

        ofstream out{ fileName };
        streambuf* coutBuf = cout.rdbuf();

        cout.rdbuf(out.rdbuf());
        cout << Foreground::Blue << s << Style::Reset;
        cout.rdbuf(coutBuf);

        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        SetWinTermMode(WinTerm::Ansi);

        ofstream out{ fileName };
        streambuf* coutBuf = cout.rdbuf();

        cout.rdbuf(out.rdbuf());
        cout << Foreground::Blue << s << Style::Reset;
        cout.rdbuf(coutBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }
}

TEST_CASE("styler printing with Control::Force and cout")
{
    const string s = "Hello World";
    const string fileName = "out.txt";

    SetControlMode(Control::Force);

    SUBCASE("WinTerm = Native")
    {
        SetWinTermMode(WinTerm::Native);

        ofstream out{ fileName };
        streambuf* coutBuf = cout.rdbuf();

        cout.rdbuf(out.rdbuf());
        cout << Foreground::Blue << s << Style::Reset;
        cout.rdbuf(coutBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

#if defined(STYLER_LINUX) || defined(STYLER_MACOSX)
        REQUIRE(s != output);
        REQUIRE(s.size() < output.size());
#elif defined(STYLER_WINDOWS)
        REQUIRE(s == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        SetWinTermMode(WinTerm::Ansi);

        ofstream out{ fileName };
        streambuf* coutBuf = cout.rdbuf();

        cout.rdbuf(out.rdbuf());
        cout << Foreground::Blue << s << Style::Reset;
        cout.rdbuf(coutBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s != output);
        REQUIRE(s.size() < output.size());
    }
}

TEST_CASE("styler printing with Control::Off and cerr")
{
    const string s = "Hello World";
    const string fileName = "out.txt";

    SetControlMode(Control::Off);

    SUBCASE("WinTerm = Native")
    {
        SetWinTermMode(WinTerm::Native);

        ofstream out{ fileName };
        streambuf* cerrBuf = cerr.rdbuf();

        cerr.rdbuf(out.rdbuf());
        cerr << Foreground::Blue << s << Style::Reset;
        cerr.rdbuf(cerrBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        SetWinTermMode(WinTerm::Auto);

        ofstream out{ fileName };
        streambuf* cerrBuf = cerr.rdbuf();

        cerr.rdbuf(out.rdbuf());
        cerr << Foreground::Blue << s << Style::Reset;
        cerr.rdbuf(cerrBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        SetWinTermMode(WinTerm::Ansi);

        ofstream out{ fileName };
        streambuf* cerrBuf = cerr.rdbuf();

        cerr.rdbuf(out.rdbuf());
        cerr << Foreground::Blue << s << Style::Reset;
        cerr.rdbuf(cerrBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }
}

TEST_CASE("styler printing with Control::Force and cerr")
{
    const string s = "Hello World";
    const string fileName = "out.txt";

    SetControlMode(Control::Force);

    SUBCASE("WinTerm = Native")
    {
        SetWinTermMode(WinTerm::Native);

        ofstream out{ fileName };
        streambuf* cerrBuf = cerr.rdbuf();

        cerr.rdbuf(out.rdbuf());
        cerr << Foreground::Blue << s << Style::Reset;
        cerr.rdbuf(cerrBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

#if defined(STYLER_LINUX) || defined(STYLER_MACOSX)
        REQUIRE(s != output);
        REQUIRE(s.size() < output.size());
#elif defined(STYLER_WINDOWS)
        REQUIRE(s == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        SetWinTermMode(WinTerm::Ansi);

        ofstream out{ fileName };
        streambuf* cerrBuf = cerr.rdbuf();

        cerr.rdbuf(out.rdbuf());
        cerr << Foreground::Blue << s << Style::Reset;
        cerr.rdbuf(cerrBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s != output);
        REQUIRE(s.size() < output.size());
    }
}

TEST_CASE("styler printing with Control::Off and clog")
{
    const string s = "Hello World";
    const string fileName = "out.txt";

    SetControlMode(Control::Off);

    SUBCASE("WinTerm = Native")
    {
        SetWinTermMode(WinTerm::Native);

        ofstream out{ fileName };
        streambuf* clogBuf = clog.rdbuf();

        clog.rdbuf(out.rdbuf());
        clog << Foreground::Blue << s << Style::Reset;
        clog.rdbuf(clogBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        SetWinTermMode(WinTerm::Auto);

        ofstream out{ fileName };
        streambuf* clogBuf = clog.rdbuf();

        clog.rdbuf(out.rdbuf());
        clog << Foreground::Blue << s << Style::Reset;
        clog.rdbuf(clogBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        SetWinTermMode(WinTerm::Ansi);

        ofstream out{ fileName };
        streambuf* clogBuf = clog.rdbuf();

        clog.rdbuf(out.rdbuf());
        clog << Foreground::Blue << s << Style::Reset;
        clog.rdbuf(clogBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s == output);
    }
}

TEST_CASE("styler printing with Control::Force and clog")
{
    const string s = "Hello World";
    const string fileName = "out.txt";

    SetControlMode(Control::Force);

    SUBCASE("WinTerm = Native")
    {
        SetWinTermMode(WinTerm::Native);

        ofstream out{ fileName };
        streambuf* clogBuf = clog.rdbuf();

        clog.rdbuf(out.rdbuf());
        clog << Foreground::Blue << s << Style::Reset;
        clog.rdbuf(clogBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

#if defined(OS_LINUX) || defined(OS_MAC)
        REQUIRE(s != output);
        REQUIRE(s.size() < output.size());
#elif defined(OS_WIN)
        REQUIRE(s == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        SetWinTermMode(WinTerm::Ansi);

        ofstream out{ fileName };
        streambuf* clogBuf = clog.rdbuf();

        clog.rdbuf(out.rdbuf());
        clog << Foreground::Blue << s << Style::Reset;
        clog.rdbuf(clogBuf);
        out.close();

        ifstream in{ fileName };
        string output;
        getline(in, output);

        REQUIRE(s != output);
        REQUIRE(s.size() < output.size());
    }
}