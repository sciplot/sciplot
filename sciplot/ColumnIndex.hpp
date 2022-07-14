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
#include <string>

namespace sciplot {

/// An auxiliary type used to represent a data column index.
struct ColumnIndex
{
    /// Construct a default ColumnIndex object.
    ColumnIndex() : ColumnIndex(0) {}

    /// Construct a ColumnIndex object with given integer.
    ColumnIndex(int col) : value(std::to_string(col)) {} // 1 => "1"

    /// Construct a ColumnIndex object with given string (the header of the column).
    ColumnIndex(std::string col) : value("'" + col + "'") {} // "Name" => "'Name'"

    /// Construct a ColumnIndex object with given string.
    ColumnIndex(const char* col) : ColumnIndex(std::string(col)) {}

    /// The column index value.
    std::string value;
};

} // namespace sciplot
