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
#include <sciplot/specs/OffsetSpecsOf.hpp>
#include <sciplot/specs/ShowSpecsOf.hpp>
#include <sciplot/specs/TextSpecsOf.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// The class used to specify options for tics.
class TicsSpecs : public TextSpecsOf<TicsSpecs>, public OffsetSpecsOf<TicsSpecs>, public ShowSpecsOf<TicsSpecs>
{
  public:
    /// Construct a default TicsSpecs instance.
    TicsSpecs();

    /// Set the tics to be displayed along the axis.
    auto alongAxis() -> TicsSpecs&;

    /// Set the tics to be displayed along the border.
    auto alongBorder() -> TicsSpecs&;

    /// Set the tics to be mirrored on the opposite border if `true`.
    auto mirror(bool value=true) -> TicsSpecs&;

    /// Set the tics to be displayed inside the graph.
    auto insideGraph() -> TicsSpecs&;

    /// Set the tics to be displayed outside the graph.
    auto outsideGraph() -> TicsSpecs&;

    /// Set the tics to be rotated by 90 degrees if `true`.
    auto rotate(bool value=true) -> TicsSpecs&;

    /// Set the tics to be rotated by given degrees.
    auto rotateBy(double degrees) -> TicsSpecs&;

    /// Set the tics to be displayed on the front of all plot elements.
    auto stackFront() -> TicsSpecs&;

    /// Set the tics to be displayed on the back of all plot elements.
    auto stackBack() -> TicsSpecs&;

    /// Set the scale for the major tics (identical to method scaleMajorBy).
    auto scaleBy(double value) -> TicsSpecs&;

    /// Set the scale for the major tics.
    auto scaleMajorBy(double value) -> TicsSpecs&;

    /// Set the scale for the minor tics.
    auto scaleMinorBy(double value) -> TicsSpecs&;

    /// Set the format of the tics using a format expression (`"%.2f"`)
    auto format(std::string fmt) -> TicsSpecs&;

    /// Convert this TicsSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Convert this TicsSpecs object into a gnuplot formatted string.
    auto repr(std::string axis) const -> std::string;

  private:
    /// The option indicating if tics are displayed along axis or border.
    std::string m_along;

    /// The mirror option of the tics.
    std::string m_mirror;

    /// The rotate option for the tics.
    std::string m_rotate;

    /// The depth where the tics are displayed (back or front).
    std::string m_depth;

    /// The place where the tics are displayed (in or out).
    std::string m_inout;

    /// The format expression for formatting the display of the tics.
    std::string m_format;

    /// The scale of the major tics.
    double m_scalemajor = 1.0;

    /// The scale of the minor tics.
    double m_scaleminor = 1.0;
};

TicsSpecs::TicsSpecs()
{
    alongBorder();
    mirror(internal::DEFAULT_TICS_MIRROR);
    outsideGraph();
    rotate(internal::DEFAULT_TICS_ROTATE);
    stackFront();
    scaleMajorBy(internal::DEFAULT_TICS_SCALE_MAJOR_BY);
    scaleMinorBy(internal::DEFAULT_TICS_SCALE_MINOR_BY);
}

auto TicsSpecs::alongAxis() -> TicsSpecs&
{
    m_along = "axis";
    return *this;
}

auto TicsSpecs::alongBorder() -> TicsSpecs&
{
    m_along = "border";
    return *this;
}

auto TicsSpecs::mirror(bool value) -> TicsSpecs&
{
    m_mirror = value ? "mirror" : "nomirror";
    return *this;
}

auto TicsSpecs::rotate(bool value) -> TicsSpecs&
{
    m_rotate = value ? "rotate" : "norotate";
    return *this;
}

auto TicsSpecs::rotateBy(double degrees) -> TicsSpecs&
{
    m_rotate = "rotate by " + internal::str(degrees);
    return *this;
}

auto TicsSpecs::stackFront() -> TicsSpecs&
{
    m_depth = "front";
    return *this;
}

auto TicsSpecs::stackBack() -> TicsSpecs&
{
    m_depth = "back";
    return *this;
}

auto TicsSpecs::insideGraph() -> TicsSpecs&
{
    m_inout = "in";
    return *this;
}

auto TicsSpecs::outsideGraph() -> TicsSpecs&
{
    m_inout = "out";
    return *this;
}

auto TicsSpecs::scaleBy(double value) -> TicsSpecs&
{
    return scaleMajorBy(value);
}

auto TicsSpecs::scaleMajorBy(double value) -> TicsSpecs&
{
    m_scalemajor = value;
    return *this;
}

auto TicsSpecs::scaleMinorBy(double value) -> TicsSpecs&
{
    m_scaleminor = value;
    return *this;
}

auto TicsSpecs::format(std::string fmt) -> TicsSpecs&
{
    m_format = "'" + fmt + "'";
    return *this;
}

auto TicsSpecs::repr() const -> std::string
{
    return repr("");
}

auto TicsSpecs::repr(std::string axis) const -> std::string
{
    const auto show = ShowSpecsOf<TicsSpecs>::repr();
    if(show == "no")
        return "unset tics";

    std::stringstream ss;
    ss << "set " + axis + "tics" << " ";
    ss << m_along << " ";
    ss << m_mirror << " ";
    ss << m_depth << " ";
    ss << m_inout << " ";
    ss << "scale " << m_scalemajor << "," << m_scaleminor << " ";
    ss << m_rotate << " ";
    ss << OffsetSpecsOf<TicsSpecs>::repr() << " ";
    ss << TextSpecsOf<TicsSpecs>::repr() << " ";
    ss << m_format;
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
