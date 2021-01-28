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
#include <sciplot/enums.hpp>
#include <sciplot/specs/Specs.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The specifications for a line plot.
template <typename DerivedSpecs>
class LineSpecsOf : virtual public internal::specs<DerivedSpecs>
{
  public:
    /// Construct a default LineSpecsOf instance.
    LineSpecsOf();

    /// Convert this LineSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the line style of the plot.
    auto lineStyle(std::size_t value) -> DerivedSpecs&
    {
        m_linestyle = internal::str(value);
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the line type of the plot.
    auto lineType(std::size_t value) -> DerivedSpecs&
    {
        m_linetype = internal::str(value);
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the line width of the plot.
    auto lineWidth(std::size_t value) -> DerivedSpecs&
    {
        m_linewidth = internal::str(value);
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the line color of the plot.
    auto lineColor(std::string value) -> DerivedSpecs&
    {
        m_linecolor = "'" + value + "'";
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the dash type of the plot.
    auto dashType(std::size_t value) -> DerivedSpecs&
    {
        m_dashtype = internal::str(value);
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the dash type of the plot.
    /// The density parameter only works for the "solid" fill mode and must be in [0,1].
    auto fillStyle(fillstyle value, float density = 1.0F) -> DerivedSpecs&  // TODO: This fillStyle method should not belong to LineSpecsOf.
    {
        m_fillstyle = gnuplot::fillstylestr(value);
        if (value == fillstyle::solid)
        {
            density = density < 0.0F ? 0.0F : (density > 1.0F ? 1.0F : density);
            m_fillstyle += " " + internal::str(density);
        }
        return static_cast<DerivedSpecs&>(*this);
    }

  private:
    /// The line style of the plot (e.g., "ls 2").
    std::string m_linestyle;

    /// The line type of the plot (e.g., "lt 3").
    std::string m_linetype;

    /// The line width of the plot (e.g., "lw 2").
    std::string m_linewidth;

    /// The line color of the plot (e.g., "lc rgb '#FF00FF'").
    std::string m_linecolor;

    /// The dash type of the plot (e.g., "dt 2").
    std::string m_dashtype;

    /// The fill style of the plot (e.g., "fs solid 0.5").
    std::string m_fillstyle;
};

template <typename DerivedSpecs>
LineSpecsOf<DerivedSpecs>::LineSpecsOf()
{
    lineWidth(internal::DEFAULT_LINEWIDTH);
}

template <typename DerivedSpecs>
auto LineSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream ss;
    ss << gnuplot::optionvaluestr("linestyle", m_linestyle);
    ss << gnuplot::optionvaluestr("linetype", m_linetype);
    ss << gnuplot::optionvaluestr("linewidth", m_linewidth);
    ss << gnuplot::optionvaluestr("linecolor", m_linecolor);
    ss << gnuplot::optionvaluestr("dashtype", m_dashtype);
    ss << gnuplot::optionvaluestr("fillstyle", m_fillstyle);
    return ss.str();
}

} // namespace sciplot
