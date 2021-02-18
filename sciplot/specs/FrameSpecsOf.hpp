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
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to attach frame options to a type.
template <typename DerivedSpecs>
class FrameSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default FrameSpecsOf instance.
    FrameSpecsOf();

    /// Set the visibility of the legend frame to a shown or hidden status.
    auto frameShow(bool value=true) -> DerivedSpecs&;

    /// Set the visibility of the legend frame to a hidden status.
    auto frameHide() -> DerivedSpecs&;

    /// Set the line style of the legend frame.
    auto frameLineStyle(int value) -> DerivedSpecs&;

    /// Set the line type of the legend frame.
    auto frameLineType(int value) -> DerivedSpecs&;

    /// Set the line width of the legend frame.
    auto frameLineWidth(int value) -> DerivedSpecs&;

    /// Set the line color of the legend frame.
    auto frameLineColor(std::string value) -> DerivedSpecs&;

    /// Set the dash type of the legend frame.
    auto frameDashType(int value) -> DerivedSpecs&;

    /// Convert this FrameSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The visibility option for the frame.
    bool m_show;

    /// The line options for the frame.
    LineSpecs m_line_specs;
};

/// The class used to specify frame options.
class FrameSpecs : public FrameSpecsOf<FrameSpecs> {};

template <typename DerivedSpecs>
FrameSpecsOf<DerivedSpecs>::FrameSpecsOf()
{
    frameShow(internal::DEFAULT_LEGEND_FRAME_SHOW);
    frameLineWidth(internal::DEFAULT_LEGEND_FRAME_LINEWIDTH);
    frameLineColor(internal::DEFAULT_LEGEND_FRAME_LINECOLOR);
    frameLineType(internal::DEFAULT_LEGEND_FRAME_LINETYPE);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::frameShow(bool value) -> DerivedSpecs&
{
    m_show = value;
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::frameHide() -> DerivedSpecs&
{
    return frameShow(false);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::frameLineStyle(int value) -> DerivedSpecs&
{
    m_line_specs.lineStyle(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::frameLineType(int value) -> DerivedSpecs&
{
    m_line_specs.lineType(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::frameLineWidth(int value) -> DerivedSpecs&
{
    m_line_specs.lineWidth(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::frameLineColor(std::string value) -> DerivedSpecs&
{
    m_line_specs.lineColor(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::frameDashType(int value) -> DerivedSpecs&
{
    m_line_specs.dashType(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FrameSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    if(m_show == false)
        return "nobox";

    std::stringstream ss;
    ss << "box " << m_line_specs.repr();
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
