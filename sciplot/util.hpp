// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018 Allan Leal
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
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <valarray>

namespace sciplot
{
namespace internal
{

/// Return a string for a given index
template <typename T>
auto str(const T& i) -> std::string
{
    return std::to_string(i);
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
    return std::min(v.size(), minsize(args...));
}

/// Auxiliary function to write a vector into a line of an ostream object
/// This version is called for std::vector<std::string> and escapes strings
template <typename VectorType>
typename std::enable_if<std::is_same<VectorType, std::vector<std::string>>::value, std::ostream&>::type writeline(std::ostream& out, std::size_t i, const VectorType& v)
{
    out << "\"" << v[i] << "\""
        << "\n";
    return out;
}

/// Auxiliary function to write a vector into a line of an ostream object
template <typename VectorType>
typename std::enable_if<!std::is_same<VectorType, std::vector<std::string>>::value, std::ostream&>::type writeline(std::ostream& out, std::size_t i, const VectorType& v)
{
    out << v[i] << "\n";
    return out;
}

/// Auxiliary function to write many vector arguments into a line of an ostream object
/// This version is called for std::vector<std::string> and escapes strings
template <typename VectorType, typename... Args>
typename std::enable_if<std::is_same<VectorType, std::vector<std::string>>::value, std::ostream&>::type writeline(std::ostream& out, std::size_t i, const VectorType& v, const Args&... args)
{
    out << "\"" << v[i] << "\" ";
    writeline(out, i, args...);
    return out;
}

/// Auxiliary function to write many vector arguments into a line of an ostream object
template <typename VectorType, typename... Args>
typename std::enable_if<!std::is_same<VectorType, std::vector<std::string>>::value, std::ostream&>::type writeline(std::ostream& out, std::size_t i, const VectorType& v, const Args&... args)
{
    out << v[i] << " ";
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
inline auto optionstr(std::string option) -> std::string
{
    return option.size() ? (option + " ") : "";
}

/// Return the formatted string for a `option value` pair with a leading space (e.g., "size 400,300 ", "ls 2 ")
/// Note that if value is empty, then the option is not needed and an empty string is returned.
inline auto optionvaluestr(std::string option, std::string value) -> std::string
{
    return value.size() ? (option + " " + value + " ") : "";
}

/// Return the formatted string for a `command value` pair (e.g., "set xlabel 'Time'")
/// Note that if value is empty, then the command is not needed and an empty string is returned.
inline auto commandvaluestr(std::string cmd, std::string value) -> std::string
{
    return value.size() ? (cmd + " " + value + "\n") : "";
}

/// Return the formatted string for a size pair (x,y) in either as pixels or as inches (asinches == true).
auto sizestr(std::size_t width, std::size_t height, bool asinches) -> std::string
{
    return asinches ? (internal::str(width * POINT_TO_INCHES) + "in," + internal::str(height * POINT_TO_INCHES) + "in") : (internal::str(width) + "," + internal::str(height));
}

/// Return the correct gnuplot string command for given rgb color (e.g., "#FF00FF")
auto rgb(std::string color) -> std::string { return "rgb '" + color + "'"; }

/// Return the correct gnuplot string command for given rgb color as hex number (e.g., 0xFF00FF)
auto rgb(int hexcolor) -> std::string { return "rgb " + internal::str(hexcolor); }

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

    // White the vector arguments to the ostream object
    internal::write(out, args...);

    // Ensure two blank lines are added here so that gnuplot understands a new data set has been added
    out << "\n\n";

    return out;
}

/// Auxiliary function to write palette data for a selected palette ot start of plot script
auto palettecmd(std::ostream& out, const std::string& palette) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# GNUPLOT-palette (" << palette << ")" << std::endl;
    out << "#------------------------------------------------------------------------------" << std::endl;
    out << "# see more at https://github.com/Gnuplotting/gnuplot-palettes" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << palettes.at(palette) << std::endl;
    return out;
}

/// Auxiliary function to write terminal commands for showing a plot from a script file
auto showterminalcmd(std::ostream& out) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# TERMINAL" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << "set termoption enhanced" << std::endl;
    //out << "set termoption font '" << DEFAULT_FONTNAME << "," << DEFAULT_FONTSIZE << "'" << std::endl;
    out << "set size ratio " << GOLDEN_RATIO_INVERSE << std::endl;
    return out;
}

/// Auxiliary function to write terminal commands for saving a plot from a script file
auto saveterminalcmd(std::ostream& out, const std::string& extension, const std::string& size) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# TERMINAL" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << "set terminal " << extension << " size " << size << " enhanced rounded" << std::endl; // font '" << DEFAULT_FONTNAME << "," << DEFAULT_FONTSIZE << "'" << std::endl;
    return out;
}

/// Auxiliary function to set the output command to make GNUplot output plots to a file
auto outputcmd(std::ostream& out, const std::string& filename) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# OUTPUT" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << "set output '" << filename << "'" << std::endl;
    return out;
}

/// Auxiliary function to write multiplot commands to a script file
auto multiplotcmd(std::ostream& out, std::size_t rows, std::size_t columns, const std::string& title) -> std::ostream&
{
    out << "#==============================================================================" << std::endl;
    out << "# MULTIPLOT" << std::endl;
    out << "#==============================================================================" << std::endl;
    out << "set multiplot";
    if (rows != 0 || columns != 0)
    {
        out << " layout " << rows << "," << columns;
    }
    if (!title.empty())
    {
        out << " title \"" << title << "\"";
    }
    out << std::endl;
    return out;
}

/// Auxiliary function to run gnuplot to show or save a script file
// persistent == true: for show commands. show the file using GNUplot until the window is closed
// persistent == false: for save commands. close gnuplot immediately
auto runscript(const std::string& scriptfilename, bool persistent) -> bool
{
    std::string command = persistent ? "gnuplot -persistent " : "gnuplot ";
    command += "\"" + scriptfilename + "\"";
    return std::system(command.c_str()) == 0;
}

/// Auxiliary function to escape a output path so it can be used for GNUplot.
/// Removes every character from invalidchars from the path.
auto cleanpath(const std::string& path) -> std::string
{
    const std::string invalidchars = ":*?!\"<>|";
    std::string result = path;
    result.erase(std::remove_if(result.begin(), result.end(), [&invalidchars](char c) { return (std::find(invalidchars.cbegin(), invalidchars.cend(), c) != invalidchars.cend()); }), result.end());
    return result;
}

} // namespace gnuplot

} // namespace sciplot
