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
class FillStyleSpecs : virtual public Specs<FillStyleSpecs>
{
  public:
    /// Construct a default FillStyleSpecs instance.
    FillStyleSpecs();

    /// Set an empty fill style for the underlying object.
    auto empty() -> FillStyleSpecs&;

    /// Set a solid fill style for the underlying object.
    auto solid() -> FillStyleSpecs&;

    /// Set a pattern fill style for the underlying object.
    auto pattern(int number) -> FillStyleSpecs&;

    /// Set the fill color intensity of the underlying object with respect to its border color (a value between 0.0 and 1.0).
    auto intensity(double value) -> FillStyleSpecs&;

    /// Set the fill of the underlying object to be transparent or not.
    auto transparent(bool active = true) -> FillStyleSpecs&;

    /// Set the border line color of the underlying object.
    auto borderLineColor(std::string color) -> FillStyleSpecs&;

    /// Set the border line width of the underlying object.
    auto borderLineWidth(int value) -> FillStyleSpecs&;

    /// Set the border of the underlying object to be shown or not.
    auto borderShow(bool value = true) -> FillStyleSpecs&;

    /// Set the border of the underlying object to be hidden.
    auto borderHide() -> FillStyleSpecs&;

    /// Convert this FillStyleSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The fill mode for the underlying object (e.g, "empty", "solid", "pattern").
    std::string m_fillmode;

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

inline FillStyleSpecs::FillStyleSpecs()
{
}

inline auto FillStyleSpecs::empty() -> FillStyleSpecs&
{
    m_fillmode = "empty";
    return *this;
}

inline auto FillStyleSpecs::solid() -> FillStyleSpecs&
{
    m_fillmode = "solid";
    return *this;
}

inline auto FillStyleSpecs::pattern(int number) -> FillStyleSpecs&
{
    m_fillmode = "pattern";
    m_pattern_number = internal::str(number);
    return *this;
}

inline auto FillStyleSpecs::intensity(double value) -> FillStyleSpecs&
{
    value = std::min<decltype(value)>(std::max<decltype(value)>(0.0, value), 1.0); // value in [0, 1]
    m_density = internal::str(value);
    m_fillmode = "solid";
    return *this;
}

inline auto FillStyleSpecs::transparent(bool active) -> FillStyleSpecs&
{
    m_transparent = active ? "transparent" : "";
    if (m_fillmode.empty())
        m_fillmode = "solid";
    return *this;
}

inline auto FillStyleSpecs::borderLineColor(std::string color) -> FillStyleSpecs&
{
    m_bordercolor = "'" + color + "'";
    return *this;
}

inline auto FillStyleSpecs::borderLineWidth(int value) -> FillStyleSpecs&
{
    m_borderlinewidth = internal::str(value);
    return *this;
}

inline auto FillStyleSpecs::borderShow(bool show) -> FillStyleSpecs&
{
    m_bordershow = show ? "yes" : "no";
    return *this;
}

inline auto FillStyleSpecs::borderHide() -> FillStyleSpecs&
{
    return borderShow(false);
}

inline auto FillStyleSpecs::repr() const -> std::string
{
    std::string fillstyle; // ensure it remains empty if no fill style option has been given!
    if (m_fillmode == "solid")
        fillstyle = m_transparent + " solid " + m_density;
    else if (m_fillmode == "pattern")
        fillstyle = m_transparent + " pattern " + m_pattern_number;
    else if (m_fillmode == "empty")
        fillstyle = "empty";

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

    if (fillstyle.empty() && borderstyle.empty())
        return "";

    std::string ss = "set style fill " + fillstyle + " " + borderstyle;

    return internal::removeExtraWhitespaces(ss);
}

} // namespace sciplot
