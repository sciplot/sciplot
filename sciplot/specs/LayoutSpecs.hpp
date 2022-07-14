// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2022 Allan Leal, Bim Overbohm
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
#include <sciplot/specs/Specs.hpp>

namespace sciplot
{

/// The class used to attach layout options to a type.
template <typename DerivedSpecs>
class LayoutSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Set the origin of the figure relative to the canvas (0,0 is bottom left and 1,1 is top right).
    auto origin(double x, double y) -> DerivedSpecs&;

    /// Set the size factor of the figure relative to the canvas (a value of 1 will fill the entire canvas, < 1 will fill only a part, > 1 will make the figure not fit the canvas).
    auto size(double sx, double sy) -> DerivedSpecs&;

    /// Set the absolute margins of the figure to the canvas. A value of -1 will let gnuplot autocalculate the value.
    auto marginsAbsolute(double left = -1, double right = -1, double top = -1, double bottom = -1) -> DerivedSpecs&;

    /// Set the relative margins of the figure to the canvas as a fraction of the canvas.
    /// Note that size() and origin() will get ignored if you set this.
    /// @note This does not seem to work for me with gnuplot 5.4 patchlevel 2
    // auto marginsRelative(double left = -1, double right = -1, double top = -1, double bottom = -1) -> DerivedSpecs&;

    /// Convert this LayoutSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// Horizontal origin of figure inside canvas
    double m_originX = 0.0;
    /// Vertical origin of figure inside canvas
    double m_originY = 0.0;
    /// True if the origin has been set
    bool m_originSet = false;

    /// The size of the plot in x relative to the canvas
    double m_sizeX = 0;
    /// The size of the plot in y relative to the canvas
    double m_sizeY = 0;
    /// True if the size has been set
    bool m_sizeSet = false;

    /// Left margin of figure inside canvas
    double m_marginsLeft = 0.0;
    /// Right margin of figure inside canvas
    double m_marginsRight = 0.0;
    /// Top margin of figure inside canvas
    double m_marginsTop = 0.0;
    /// Bottom margin of figure inside canvas
    double m_marginsBottom = 0.0;
    /// If true margins inside canvas are absolute values, else relative
    double m_marginsAbsolute = false;
    /// True if the margins have been set
    bool m_marginsSet = false;
};

/// The class used to specify layout options.
class LayoutSpecs : public LayoutSpecsOf<LayoutSpecs>
{
};

template <typename DerivedSpecs>
auto LayoutSpecsOf<DerivedSpecs>::origin(double x, double y) -> DerivedSpecs&
{
    m_originX = x;
    m_originY = y;
    m_originSet = true;
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto LayoutSpecsOf<DerivedSpecs>::size(double sx, double sy) -> DerivedSpecs&
{
    m_sizeX = sx;
    m_sizeY = sy;
    m_sizeSet = true;
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto LayoutSpecsOf<DerivedSpecs>::marginsAbsolute(double left, double right, double top, double bottom) -> DerivedSpecs&
{
    m_marginsLeft = left;
    m_marginsRight = right;
    m_marginsTop = top;
    m_marginsBottom = bottom;
    m_marginsAbsolute = true;
    m_marginsSet = true;
    return static_cast<DerivedSpecs&>(*this);
}

/*
// This does not seem to work for me with gnuplot 5.4 patchlevel 2
template <typename DerivedSpecs>
auto LayoutSpecsOf<DerivedSpecs>::marginsRelative(double left, double right, double top, double bottom) -> DerivedSpecs&
{
    m_marginsLeft = left;
    m_marginsRight = right;
    m_marginsTop = top;
    m_marginsBottom = bottom;
    m_marginsAbsolute = false;
    m_marginsSet = true;
    return static_cast<DerivedSpecs&>(*this);
}*/

template <typename DerivedSpecs>
auto LayoutSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream script;
    if (m_originSet)
    {
        script << "set origin " << m_originX << "," << m_originY << std::endl;
    }
    if (m_sizeSet)
    {
        script << "set size " << m_sizeX << "," << m_sizeY << std::endl;
    }
    if (m_marginsSet)
    {
        script << "set lmargin " << (m_marginsAbsolute ? "" : "at screen ") << m_marginsLeft << std::endl;
        script << "set rmargin " << (m_marginsAbsolute ? "" : "at screen ") << m_marginsRight << std::endl;
        script << "set tmargin " << (m_marginsAbsolute ? "" : "at screen ") << m_marginsTop << std::endl;
        script << "set bmargin " << (m_marginsAbsolute ? "" : "at screen ") << m_marginsBottom << std::endl;
    }
    return script.str();
}

} // namespace sciplot
