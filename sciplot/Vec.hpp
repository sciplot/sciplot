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
#include <functional>
#include <string>
#include <valarray>
#include <vector>

namespace sciplot {

/// A convenient type alias for std::valarray<double>
using Vec = std::valarray<double>;

/// A convenient type alias for std::vector<std::string>
using Strings = std::vector<std::string>;

/// Return an array with uniform increments from a given initial value to a final one
template <typename T0, typename T1, typename U = double>
auto linspace(T0 x0, T1 x1, std::size_t numintervals) -> std::valarray<U>
{
    std::valarray<U> result(numintervals + 1);
    for(std::size_t i = 0; i <= numintervals; ++i)
        result[i] = x0 + i * (x1 - x0) / static_cast<U>(numintervals);
    return result;
}

/// Return an array with unit increment from a given initial value to a final one
template <typename U = double>
auto range(int x0, int x1) -> Vec
{
    const auto incr = (x1 > x0) ? +1 : -1;
    std::valarray<U> result(x1 - x0 + 1);
    for(std::size_t i = 0; i < result.size(); ++i)
        result[i] = x0 + i * incr;
    return result;
}

} // namespace sciplot
