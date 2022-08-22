// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2021 Allan Leal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// C++ includes
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <type_traits>
#include <valarray>

// sciplot includes
#include <sciplot/Constants.hpp>
#include <sciplot/Enums.hpp>
#include <sciplot/Palettes.hpp>

namespace sciplot
{
namespace internal
{

/// Return a string for a given value of a generic type.
template <typename T>
auto str(const T& val) -> std::string
{
    std::stringstream ss;
    ss << val;
    return ss.str(); // Note: This is different than std::to_string(i). For example, it works with custom types. Also, std::to_string(2.0) may produce "2.000000", difficulting string comparison in the tests.
}

/// Return a string for a given char array
inline auto str(const char* word) -> std::string
{
    return word;
}

/// Return an empty string
inline auto str() -> std::string
{
    return {};
}

/// Remove from the beginning of the string the given character (by default, space).
inline auto trimleft(std::string str, unsigned char character = ' ') -> std::string
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(),
                                        [&](unsigned char ch)
                                        { return ch != character; }));
    return str;
}

/// Remove from the end of the string the given character (by default, space).
inline auto trimright(std::string str, unsigned char character = ' ') -> std::string
{
    str.erase(std::find_if(str.rbegin(), str.rend(),
                           [&](unsigned char ch)
                           { return ch != character; })
                  .base(),
              str.end());
    return str;
}

/// Trim the string from both ends
inline auto trim(std::string str, unsigned char character = ' ') -> std::string
{
    return trimleft(trimright(str, character), character);
}

/// Remove extra spaces from a string (e.g., `"abc  acb   xy s "` becomes `"abc acb xy s "`).
inline auto collapseWhitespaces(std::string s) -> std::string
{
    s.erase(std::unique(std::begin(s), std::end(s),
                        [](unsigned char a, unsigned char b)
                        { return std::isspace(a) && std::isspace(b); }),
            std::end(s));
    return s;
}

/// Trim and collapse all spaces in a string (e.g., `"  abc  acb   xy s "` becomes `"abc acb xy s"`).
inline auto removeExtraWhitespaces(std::string s) -> std::string
{
    return trim(collapseWhitespaces(s));
}

/// Auxiliary function that returns the size of the vector argument with least size (for a single vector case)
template <typename VectorType>
auto minsize(const VectorType& v) -> std::size_t
{
    return v.size();
}

/// Auxiliary function that returns the size of the vector argument with least size
template <typename VectorType, typename... Args>
auto minsize(const VectorType& v, const Args&... args) -> std::size_t
{
    return std::min<decltype(v.size())>(v.size(), minsize(args...));
}

/// Check if type @p T is `std::string`.
template <typename T>
constexpr auto isString = std::is_same_v<std::decay_t<T>, std::string>;

/// Check if type @p T is `std::string`.
template <typename V>
constexpr auto isStringVector = isString<decltype(std::declval<V>()[0])>;

/// Auxiliary function that returns `" + val + "` if `val` is string, otherwise `val` itself.
template <typename T>
auto escapeIfNeeded(const T& val)
{
    if constexpr (isString<T>)
        return "\"" + val + "\""; // Due bug #102 we escape data using double quotes
    else
        return std::isfinite(static_cast<double>(val)) ? internal::str(val) : MISSING_INDICATOR; // static_cast to avoid MSVC error C2668: 'fpclassify': ambiguous call to overloaded function
}

/// Auxiliary function to write many vector arguments into a line of an ostream object
template <typename VectorType>
auto writeline(std::ostream& out, std::size_t i, const VectorType& v) -> std::ostream&
{
    out << escapeIfNeeded(v[i]) << '\n';
    return out;
}

/// Auxiliary function to write many vector arguments into a line of an ostream object
template <typename VectorType, typename... Args>
auto writeline(std::ostream& out, std::size_t i, const VectorType& v, const Args&... args) -> std::ostream&
{
    out << escapeIfNeeded(v[i]) << " ";
    writeline(out, i, args...);
    return out;
}

/// Auxiliary function to write many vector arguments into an ostream object
template <typename... Args>
auto write(std::ostream& out, const Args&... args) -> std::ostream&
{
    const auto size = minsize(args...);
    for (std::size_t i = 0; i < size; ++i)
        writeline(out, i, args...);
    return out;
}

} // namespace internal

namespace gnuplot
{

/// Return the formatted string for a plot title.
inline auto titlestr(std::string word) -> std::string
{
    return word == "columnheader" ? word : "'" + word + "'";
}

/// Return the formatted string for a `option` with a leading space (e.g., "enhanced ")
/// Note that if option is empty, then an empty string is returned.
inline auto optionStr(std::string option) -> std::string
{
    return option.size() ? (option + " ") : "";
}

/// Return the formatted string for a `option value` pair with a leading space (e.g., "size 400,300 ", "ls 2 ")
/// Note that if value is empty, then the option is not needed and an empty string is returned.
inline auto optionValueStr(std::string option, std::string value) -> std::string
{
    return value.size() ? (option + " " + value + " ") : "";
}

/// Return the formatted string for a `command value` pair (e.g. "cmd value" or "set ab de")
/// Note that if value is empty, then the command is not needed and an empty string is returned.
inline auto cmdValueStr(std::string cmd, std::string value) -> std::string
{
    return value.size() ? (cmd + " " + value + "\n") : "";
}

/// Return the formatted, escaped string for a `command value` pair (e.g. "cmd 'value'", or "set ab 'de'")
/// Note that if value is empty, then the command is not needed and an empty string is returned.
inline auto cmdValueEscapedStr(std::string cmd, std::string value) -> std::string
{
    return value.size() ? (cmd + " '" + value + "'\n") : "";
}

/// Return the formatted string for a size pair (x,y).
inline auto figureSizeStr(double sx, double sy) -> std::string
{
    return internal::str(sx) + "," + internal::str(sy);
}

/// Return the formatted string for a size pair (x,y) in either as pixels or as inches (asinches == true).
inline auto canvasSizeStr(std::size_t width, std::size_t height, bool asinches) -> std::string
{
    return asinches ? (internal::str(width * POINT_TO_INCHES) + "in," + internal::str(height * POINT_TO_INCHES) + "in") : (internal::str(width) + "," + internal::str(height));
}

/// Return the correct gnuplot string command for given rgb color (e.g., "#FF00FF")
inline auto rgb(std::string color) -> std::string { return "rgb '" + color + "'"; }

/// Return the correct gnuplot string command for given rgb color as hex number (e.g., 0xFF00FF)
inline auto rgb(int hexcolor) -> std::string { return "rgb " + internal::str(hexcolor); }

/// The struct where static angle methods are defined.
struct angle
{
    /// Return the angle in degree units.
    static auto deg(long val) -> std::string { return internal::str(val) + "deg"; }

    /// Return the angle in radian units.
    static auto rad(double val) -> std::string { return internal::str(val); }

    /// Return the angle in radian units as a multiple of number pi.
    static auto pi(double val) -> std::string { return internal::str(val) + "pi"; }
};

/// Auxiliary function to create a data set in an ostream object that is understood by gnuplot
template <typename... Args>
auto writedataset(std::ostream& out, std::size_t index, const Args&... args) -> std::ostream&
{
    // Save the given vectors x and y in a new data set of the data file
    out << "#==============================================================================" << std::endl;
    out << "# DATASET #" << index << std::endl;
    out << "#==============================================================================" << std::endl;
    // Write the vector arguments to the ostream object
    internal::write(out, args...);
    // Ensure two blank lines are added here so that gnuplot understands a new data set has been added
    out << "\n\n";
    return out;
}

/// Auxiliary function to write palette data for a selected palette to start of plot script
inline auto palettecmd(std::ostream& out, std::string palette) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# GNUPLOT-palette (" << palette << ")" << std::endl;
    out << "#------------------------------------------------------------------------------" << std::endl;
    out << "# see more at https://github.com/Gnuplotting/gnuplot-palettes" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << palettes.at(palette) << std::endl;
    return out;
}

/// Auxiliary function to unset palette in plot script
inline auto unsetpalettecmd(std::ostream& out) -> std::ostream&
{
    out << "do for [i=1:20] { unset style line i }" << std::endl;
    return out;
}

/// Auxiliary function to write terminal commands for showing a plot from a script file
inline auto showterminalcmd(std::ostream& out, std::string size, std::string font, std::string title) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# TERMINAL" << std::endl;
    out << "#==============================================================================" << std::endl;
    // We set a terminal here to make sure we can also set a size. This is necessary, because the
    // canvas size can ONLY be set using "set terminal <TERMINAL> size W, H".
    // See: http://www.bersch.net/gnuplot-doc/canvas-size.html#set-term-size
    // The GNUTERM variable contains the default terminal, which we're using for the show command.
    // See: http://www.bersch.net/gnuplot-doc/unset.html
    out << "set termoption enhanced" << std::endl;
    if (font.size()) out << "set termoption " << font << std::endl;
    out << "set terminal GNUTERM size " << size << (!title.empty() ? " title '" + title + "' " : "") << std::endl;
    out << "set encoding utf8" << std::endl;
    return out;
}

/// Auxiliary function to write terminal commands for saving a plot from a script file
inline auto saveterminalcmd(std::ostream& out, std::string extension, std::string size, std::string font) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# TERMINAL" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << "set terminal " << extension << " size " << size << " enhanced rounded " << font << std::endl;
    out << "set encoding utf8" << std::endl;
    return out;
}

/// Auxiliary function to set the output command to make GNUplot output plots to a file
inline auto outputcmd(std::ostream& out, std::string filename) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# OUTPUT" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << "set output '" << filename << "'" << std::endl;
    out << "set encoding utf8" << std::endl;
    return out;
}

/// Auxiliary function to write multiplot commands to a script file
inline auto multiplotcmd(std::ostream& out, std::size_t rows, std::size_t columns, std::string title) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# MULTIPLOT" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << "set multiplot";
    if (rows != 0 || columns != 0)
    {
        out << " layout " << rows << "," << columns;
    }
    out << " "
        << "rowsfirst";
    out << " "
        << "downwards";
    if (!title.empty())
    {
        out << " title '" << title << "'";
    }
    out << std::endl;
    return out;
}

/// Auxiliary function to run gnuplot to show or save a script file
// persistent == true: for show commands. show the file using GNUplot until the window is closed
// persistent == false: for save commands. close gnuplot immediately
inline auto runscript(std::string scriptfilename, bool persistent) -> bool
{
    std::string command = persistent ? "gnuplot -persistent " : "gnuplot ";
    command += "\"" + scriptfilename + "\"";
    return std::system(command.c_str()) == 0;
}

/// Auxiliary function to escape a output path so it can be used for GNUplot.
/// Removes every character from invalidchars from the path.
inline auto cleanpath(std::string path) -> std::string
{
    const std::string invalidchars = ":*?!\"<>|";
    std::string result = path;
    result.erase(std::remove_if(result.begin(), result.end(), [&invalidchars](char c)
                                { return (std::find(invalidchars.cbegin(), invalidchars.cend(), c) != invalidchars.cend()); }),
                 result.end());
    return result;
}

} // namespace gnuplot

} // namespace sciplot
