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
#include <sciplot/default.hpp>
#include <sciplot/specs/Specs.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// The class used to specify fill style of plot elements in a figure that can be painted.
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
    auto transparent(bool active=true) -> FillStyleSpecs&;

    /// Set the border line color of the underlying object.
    auto borderLineColor(std::string color) -> FillStyleSpecs&;

    /// Set the border line width of the underlying object.
    auto borderLineWidth(int value) -> FillStyleSpecs&;

    /// Set the border of the underlying object to be shown or not.
    auto borderShow(bool value=true) -> FillStyleSpecs&;

    /// Set the border of the underlying object to be hidden.
    auto borderHide() -> FillStyleSpecs&;

    /// Convert this FillStyleSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The fill style of the underlying object (e.g, "empty", "solid", "pattern").
    std::string m_fillstyle;

    /// The fill transparency of the underlying object (active or not).
    bool m_transparent;

    /// The fill intensity of the underlying object with respect to its border color.
    double m_density;

    /// The fill pattern number of the underlying object.
    std::string m_pattern_number;

    /// The border color of the underlying object.
    std::string m_bordercolor;

    /// The border line width of the underlying object.
    std::string m_borderlinewidth;

    /// The border show status of the underlying object.
    bool m_bordershow;
};

FillStyleSpecs::FillStyleSpecs()
{
    solid();
    intensity(internal::DEFAULT_FILL_INTENSITY);
    transparent(internal::DEFAULT_FILL_TRANSPARENCY);
    borderLineWidth(internal::DEFAULT_FILL_BORDER_LINEWIDTH);
    borderHide();
}

auto FillStyleSpecs::empty() -> FillStyleSpecs&
{
    m_fillstyle = "empty";
    return *this;
}

auto FillStyleSpecs::solid() -> FillStyleSpecs&
{
    m_fillstyle = "solid";
    return *this;
}

auto FillStyleSpecs::pattern(int number) -> FillStyleSpecs&
{
    m_fillstyle = "pattern";
    m_pattern_number = internal::str(number);
    return *this;
}

auto FillStyleSpecs::intensity(double value) -> FillStyleSpecs&
{
    m_density = std::min(std::max(0.0, value), 1.0); // value in [0, 1]
    return *this;
}

auto FillStyleSpecs::transparent(bool active) -> FillStyleSpecs&
{
    m_transparent = active;
    return *this;
}

auto FillStyleSpecs::borderLineColor(std::string color) -> FillStyleSpecs&
{
    m_bordercolor = "'" + color + "'";
    return *this;
}

auto FillStyleSpecs::borderLineWidth(int value) -> FillStyleSpecs&
{
    m_borderlinewidth = internal::str(value);
    return *this;
}

auto FillStyleSpecs::borderShow(bool show) -> FillStyleSpecs&
{
    m_bordershow = show;
    return *this;
}

auto FillStyleSpecs::borderHide() -> FillStyleSpecs&
{
    return borderShow(false);
}

auto FillStyleSpecs::repr() const -> std::string
{
    const std::string transparent = m_transparent ? "transparent " : "";

    std::stringstream fs;
    if(m_fillstyle == "solid")
        fs << transparent << "solid " << m_density;
    else if(m_fillstyle == "pattern")
        fs << transparent << "pattern " << m_pattern_number;
    else fs << "empty";

    std::stringstream bs;
    if(m_bordershow == true)
    {
        bs << "border" << " ";
        bs << gnuplot::optionValueStr("linecolor", m_bordercolor);
        bs << gnuplot::optionValueStr("linewidth", m_borderlinewidth);
    }
    else bs << "noborder";

    std::stringstream ss;
    ss << "set style fill" << " ";
    ss << fs.str() << " ";
    ss << bs.str();

    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
