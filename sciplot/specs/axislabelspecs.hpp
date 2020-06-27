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

// sciplot includes
#include <sciplot/default.hpp>
#include <sciplot/specs/fontspecs.hpp>
#include <sciplot/specs/titlespecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The specifications for an axis label (e.g., xlabel, ylabel, etc.)
class axislabelspecs : public titlespecs<axislabelspecs>
{
  public:
    /// Construct a default axislabelspecs instance.
    axislabelspecs(std::string axis);

    /// Convert this axislabelspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the axis label parallel to its corresponding axis.
    auto axisparallel() -> axislabelspecs &
    {
        m_rotate = "parallel";
        return *this;
    }

  private:
    /// The name of the axis (e.g., `"x"`, `"y"`, `"z"`)
    std::string m_axis;

    /// The rotation command to rotate the label around.
    std::string m_rotate;
};

axislabelspecs::axislabelspecs(std::string axis)
    : m_axis(axis)
{
}

auto axislabelspecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << "set " + m_axis + "label ";
    ss << titlespecs<axislabelspecs>::repr();
    ss << gnuplot::optionvaluestr("rotate", m_rotate);
    return ss.str();
}

} // namespace sciplot
