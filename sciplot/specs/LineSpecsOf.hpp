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

// sciplot includes
#include <sciplot/Default.hpp>
#include <sciplot/specs/Specs.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to attach line options to a type.
template <typename DerivedSpecs>
class LineSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default LineSpecsOf instance.
    LineSpecsOf();

    /// Set the line style of the underlying line object.
    auto lineStyle(int value) -> DerivedSpecs&;

    /// Set the line type of the underlying line object.
    auto lineType(int value) -> DerivedSpecs&;

    /// Set the line width of the underlying line object.
    auto lineWidth(int value) -> DerivedSpecs&;

    /// Set the line color of the underlying line object.
    auto lineColor(std::string value) -> DerivedSpecs&;

    /// Set the dash type of the underlying line object.
    auto dashType(int value) -> DerivedSpecs&;

    /// Convert this LineSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The line style of the underlying line object (e.g., "ls 2").
    std::string m_linestyle;

    /// The line type of the underlying line object (e.g., "lt 3").
    std::string m_linetype;

    /// The line width of the underlying line object (e.g., "lw 2").
    std::string m_linewidth;

    /// The line color of the underlying line object (e.g., "lc rgb '#FF00FF'").
    std::string m_linecolor;

    /// The dash type of the underlying line object (e.g., "dt 2").
    std::string m_dashtype;
};

/// The class used to specify line options.
class LineSpecs : public LineSpecsOf<LineSpecs> {};

template <typename DerivedSpecs>
LineSpecsOf<DerivedSpecs>::LineSpecsOf()
{
}

template <typename DerivedSpecs>
auto LineSpecsOf<DerivedSpecs>::lineStyle(int value) -> DerivedSpecs&
{
    m_linestyle = "linestyle " + internal::str(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto LineSpecsOf<DerivedSpecs>::lineType(int value) -> DerivedSpecs&
{
    m_linetype = "linetype " + internal::str(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto LineSpecsOf<DerivedSpecs>::lineWidth(int value) -> DerivedSpecs&
{
    m_linewidth = "linewidth " + internal::str(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto LineSpecsOf<DerivedSpecs>::lineColor(std::string value) -> DerivedSpecs&
{
    m_linecolor = "linecolor '" + value + "'";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto LineSpecsOf<DerivedSpecs>::dashType(int value) -> DerivedSpecs&
{
    m_dashtype = "dashtype " + internal::str(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto LineSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream ss; // ensure it remains empty if no line style option has been given!
    ss << m_linestyle << " ";
    ss << m_linetype << " ";
    ss << m_linewidth << " ";
    ss << m_linecolor << " ";
    ss << m_dashtype << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
