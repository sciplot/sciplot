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
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The specifications for an axis label (e.g., xlabel, ylabel, etc.)
class AxisLabelSpecs : public TextSpecsOf<AxisLabelSpecs>
{
  public:
    /// Construct a default AxisLabelSpecs instance.
    AxisLabelSpecs(std::string axis);

    /// Set the text of the axis label.
    auto text(std::string text) -> AxisLabelSpecs&;

    /// Specify that the axis label should be rotated by a given angle in degrees.
    auto rotateBy(int degrees) -> AxisLabelSpecs&;

    /// Specify that the axis label should be rotated to be in parallel to the corresponding axis (for 3D plots).
    auto rotateAxisParallel() -> AxisLabelSpecs&;

    /// Specify that the axis label should not be rotated.
    auto rotateNone() -> AxisLabelSpecs&;

    /// Convert this AxisLabelSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The name of the axis (e.g., `"x"`, `"y"`, `"z"`)
    std::string m_axis;

    /// The axis label text (e.g., "Distance (km)")
    std::string m_text;

    /// The rotation command to rotate the label around.
    std::string m_rotate;
};

inline AxisLabelSpecs::AxisLabelSpecs(std::string axis)
: m_axis(axis)
{
}

inline auto AxisLabelSpecs::text(std::string text) -> AxisLabelSpecs&
{
    m_text = "'" + text + "'";
    return *this;
}

inline auto AxisLabelSpecs::rotateBy(int degrees) -> AxisLabelSpecs&
{
    m_rotate = "rotate by " + std::to_string(degrees);
    return *this;
}

inline auto AxisLabelSpecs::rotateAxisParallel() -> AxisLabelSpecs&
{
    m_rotate = "rotate parallel";
    return *this;
}

inline auto AxisLabelSpecs::rotateNone() -> AxisLabelSpecs&
{
    m_rotate = "norotate";
    return *this;
}

inline auto AxisLabelSpecs::repr() const -> std::string
{
    if(m_text.empty() && m_rotate.empty())
        return "";

    std::stringstream ss;
    ss << "set " + m_axis + "label ";
    ss << m_text << " ";
    ss << TextSpecsOf<AxisLabelSpecs>::repr() + " ";
    ss << gnuplot::optionStr(m_rotate);
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
