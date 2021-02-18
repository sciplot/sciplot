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
#include <sciplot/specs/TextSpecsOf.hpp>
#include <sciplot/specs/OffsetSpecsOf.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to attach title options to a type.
template <typename DerivedSpecs>
class TitleSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default TitleSpecsOf instance.
    TitleSpecsOf();

    /// Set the text of the title.
    auto title(std::string title) -> DerivedSpecs&;

    /// Shift the title element along the x direction by given number of characters (can be fraction).
    auto titleShiftAlongX(double chars) -> DerivedSpecs&;

    /// Shift the title element along the y direction by given number of characters (can be fraction).
    auto titleShiftAlongY(double chars) -> DerivedSpecs&;

    /// Shift the title element along the x direction within the graph coordinate system.
    auto titleShiftAlongGraphX(double val) -> DerivedSpecs&;

    /// Shift the title element along the y direction within the graph coordinate system.
    auto titleShiftAlongGraphY(double val) -> DerivedSpecs&;

    /// Shift the title element along the x direction within the screen coordinate system.
    auto titleShiftAlongScreenX(double val) -> DerivedSpecs&;

    /// Shift the title element along the y direction within the screen coordinate system.
    auto titleShiftAlongScreenY(double val) -> DerivedSpecs&;

    /// Set the color of the title text (e.g., `"blue"`, `"#404040"`)
    auto titleTextColor(std::string color) -> DerivedSpecs&;

    /// Set the font name of the title text (e.g., Helvetica, Georgia, Times).
    auto titleFontName(std::string name) -> DerivedSpecs&;

    /// Set the font point size of the title text (e.g., 10, 12, 16).
    auto titleFontSize(int size) -> DerivedSpecs&;

    /// Convert this TitleSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The text of the title.
    std::string m_title;

    /// The text options for the title.
    TextSpecs m_text_specs;

    /// The offset options for the title.
    OffsetSpecs m_offset_specs;
};

/// The class used to specify title options.
class TitleSpecs : public TitleSpecsOf<TitleSpecs> {};

template <typename DerivedSpecs>
TitleSpecsOf<DerivedSpecs>::TitleSpecsOf()
{
    title("");
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::title(std::string title) -> DerivedSpecs&
{
    m_title = "'" + title + "'";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleShiftAlongX(double chars) -> DerivedSpecs&
{
    m_offset_specs.shiftAlongX(chars);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleShiftAlongY(double chars) -> DerivedSpecs&
{
    m_offset_specs.shiftAlongY(chars);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleShiftAlongGraphX(double val) -> DerivedSpecs&
{
    m_offset_specs.shiftAlongGraphX(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleShiftAlongGraphY(double val) -> DerivedSpecs&
{
    m_offset_specs.shiftAlongGraphY(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleShiftAlongScreenX(double val) -> DerivedSpecs&
{
    m_offset_specs.shiftAlongScreenX(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleShiftAlongScreenY(double val) -> DerivedSpecs&
{
    m_offset_specs.shiftAlongScreenY(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleTextColor(std::string color) -> DerivedSpecs&
{
    m_text_specs.textColor(color);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleFontName(std::string name) -> DerivedSpecs&
{
    m_text_specs.fontName(name);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::titleFontSize(int size) -> DerivedSpecs&
{
    m_text_specs.fontSize(size);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TitleSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    if(m_title == "''")
        return "";

    std::stringstream ss;
    ss << "title " << m_title << " ";
    ss << m_text_specs.repr() << " ";
    ss << m_offset_specs.repr();
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
