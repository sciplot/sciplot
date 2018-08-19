// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
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
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Ensure appropriate popen or pclose calls when compiling with MSVC
#ifdef _MSC_VER
#define popen _popen
#define pclose _pclose
#endif

namespace Capim {
namespace internal {

/// Return a string for a given index
template<typename T>
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

/// Return the correct gnuplot string command for given rgb color (e.g., "#FF00FF")
auto rgb(std::string color) -> std::string { return "rgb '" + color + "'"; }

/// Return the correct gnuplot string command for given rgb color as hex number (e.g., 0xFF00FF)
auto rgb(int hexcolor) -> std::string { return "rgb " + str(hexcolor); }

/// Auxiliary function that returns the size of the vector argument with least size (for a single vector case)
template<typename VectorType>
auto minsize(const VectorType& v) -> std::size_t
{
    return v.size();
}

/// Auxiliary function that returns the size of the vector argument with least size
template<typename VectorType, typename... Args>
auto minsize(const VectorType& v, const Args&... args) -> std::size_t
{
    return std::min(v.size(), minsize(args...));
}

/// Auxiliary function to write a vector into a line of an ostream object
template<typename VectorType>
auto writeline(std::ostream& out, std::size_t i, const VectorType& v) -> std::ostream&
{
    out << v[i] << "\n";
    return out;
}

/// Auxiliary function to write many vector arguments into a line of an ostream object
template<typename VectorType, typename... Args>
auto writeline(std::ostream& out, std::size_t i, const VectorType& v, const Args&... args) -> std::ostream&
{
    out << v[i] << " ";
    writeline(out, i, args...);
}

/// Auxiliary function to write many vector arguments into an ostream object
template<typename... Args>
auto write(std::ostream& out, const Args&... args) -> std::ostream&
{
    const auto size = minsize(args...);
    for(auto i = 0; i < size; ++i)
        writeline(out, i, args...);
    return out;
}

/// Auxiliary function to create a data set in an ostream object that is understood by gnuplot
template<typename... Args>
auto gnuplotdataset(std::ostream& out, std::size_t index, const Args&... args) -> std::ostream&
{
    // Save the given vectors x and y in a new data set of the data file
    out << "#==============================================================================" << std::endl;
    out << "# DATASET #" << index << std::endl;
    out << "#==============================================================================" << std::endl;

    // White the vector arguments to the ostream object
    write(out, args...);

    // Ensure two blank lines are added here so that gnuplot understands a new data set has been added
    out << "\n\n";

    // Flush the file data to ensure its correct state when gnuplot is called
    out.flush();

    return out;
}

/// The struct where static angle methods are defined.
struct angle
{
    /// Return the angle in degree units.
    static auto deg(long val) -> std::string { return str(val) + "deg"; }

    /// Return the angle in radian units.
    static auto rad(double val) -> std::string { return str(val); }

    /// Return the angle in radian units as a multiple of number pi.
    static auto pi(double val) -> std::string { return str(val) + "pi"; }
};

} // namespace internal
} // namespace Capim
