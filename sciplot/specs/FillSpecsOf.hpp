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
#include <sciplot/Utils.hpp>
#include <sciplot/specs/Specs.hpp>

namespace sciplot
{

/// The class used to attach color or pattern fill options to a type.
template <typename DerivedSpecs>
class FillSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default FillSpecsOf instance.
    FillSpecsOf();

    /// Set an empty fill style for the underlying object.
    auto fillEmpty() -> DerivedSpecs&;

    /// Set a solid fill style for the underlying object.
    auto fillSolid() -> DerivedSpecs&;

    /// Set a pattern fill style for the underlying object.
    auto fillPattern(int number) -> DerivedSpecs&;

    /// Set the color for the solid or pattern fill of the underlying object.
    auto fillColor(std::string value) -> DerivedSpecs&;

    /// Set the fill color intensity of the underlying object with respect to its border color (a value between 0.0 and 1.0).
    auto fillIntensity(double value) -> DerivedSpecs&;

    /// Set the fill of the underlying object to be transparent or not.
    auto fillTransparent(bool active = true) -> DerivedSpecs&;

    /// Set the border line color of the underlying object.
    auto borderLineColor(std::string color) -> DerivedSpecs&;

    /// Set the border line width of the underlying object.
    auto borderLineWidth(int value) -> DerivedSpecs&;

    /// Set the border of the underlying object to be shown or not.
    auto borderShow(bool value = true) -> DerivedSpecs&;

    /// Set the border of the underlying object to be hidden.
    auto borderHide() -> DerivedSpecs&;

    /// Convert this FillSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The fill mode for the underlying object (e.g, "empty", "solid", "pattern").
    std::string m_fillmode;

    /// The fill color of the underlying object.
    std::string m_fillcolor;

    /// The fill transparency of the underlying object (active or not).
    std::string m_transparent;

    /// The fill intensity of the underlying object with respect to its border color.
    std::string m_density;

    /// The fill pattern number of the underlying object.
    std::string m_pattern_number;

    /// The border color of the underlying object.
    std::string m_bordercolor;

    /// The border line width of the underlying object.
    std::string m_borderlinewidth;

    /// The border show status of the underlying object.
    std::string m_bordershow;
};

/// The class used to specify color or pattern fill options.
class FillSpecs : public FillSpecsOf<FillSpecs>
{
};

template <typename DerivedSpecs>
FillSpecsOf<DerivedSpecs>::FillSpecsOf()
{
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::fillEmpty() -> DerivedSpecs&
{
    m_fillmode = "empty";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::fillSolid() -> DerivedSpecs&
{
    m_fillmode = "solid";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::fillPattern(int number) -> DerivedSpecs&
{
    m_fillmode = "pattern";
    m_pattern_number = internal::str(number);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::fillColor(std::string color) -> DerivedSpecs&
{
    m_fillcolor = "fillcolor '" + color + "'";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::fillIntensity(double value) -> DerivedSpecs&
{
    value = std::min<decltype(value)>(std::max<decltype(value)>(0.0, value), 1.0); // value in [0, 1]
    m_density = internal::str(value);
    m_fillmode = "solid";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::fillTransparent(bool active) -> DerivedSpecs&
{
    m_transparent = active ? "transparent" : "";
    if (m_fillmode.empty())
        m_fillmode = "solid";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::borderLineColor(std::string color) -> DerivedSpecs&
{
    m_bordercolor = "'" + color + "'";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::borderLineWidth(int value) -> DerivedSpecs&
{
    m_borderlinewidth = internal::str(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::borderShow(bool show) -> DerivedSpecs&
{
    m_bordershow = show ? "yes" : "no";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::borderHide() -> DerivedSpecs&
{
    return borderShow(false);
}

template <typename DerivedSpecs>
auto FillSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::string fillstyle; // ensure it remains empty if no fill style option has been given!
    if (m_fillmode == "solid")
        fillstyle = "fillstyle " + m_transparent + " solid " + m_density;
    else if (m_fillmode == "pattern")
        fillstyle = "fillstyle " + m_transparent + " pattern " + m_pattern_number;
    else if (m_fillmode == "empty")
        fillstyle = "fillstyle empty";

    std::string borderstyle; // ensure it remains empty if no border option has been given!
    if (m_bordershow != "")
    {
        if (m_bordershow == "yes")
        {
            borderstyle = "border ";
            borderstyle += gnuplot::optionValueStr("linecolor", m_bordercolor);
            borderstyle += gnuplot::optionValueStr("linewidth", m_borderlinewidth);
        }
        else
            borderstyle = "noborder";
    }

    std::stringstream ss;
    ss << m_fillcolor << " " << fillstyle << " " << borderstyle;

    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
