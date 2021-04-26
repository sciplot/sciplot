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
#include <sciplot/specs/OffsetSpecsOf.hpp>
#include <sciplot/specs/ShowSpecsOf.hpp>
#include <sciplot/specs/TextSpecsOf.hpp>

namespace sciplot
{

/// The class used to attach common tic options to a type that also specifies tic options.
template <typename DerivedSpecs>
class TicsSpecsBaseOf : public TextSpecsOf<DerivedSpecs>, public OffsetSpecsOf<DerivedSpecs>, public ShowSpecsOf<DerivedSpecs>
{
  public:
    /// Construct a default TicsSpecsBaseOf instance.
    TicsSpecsBaseOf();

    /// Set the tics to be displayed along the axis.
    auto alongAxis() -> DerivedSpecs&;

    /// Set the tics to be displayed along the border.
    auto alongBorder() -> DerivedSpecs&;

    /// Set the tics to be mirrored on the opposite border if `true`.
    auto mirror(bool value = true) -> DerivedSpecs&;

    /// Set the tics to be displayed inside the graph.
    auto insideGraph() -> DerivedSpecs&;

    /// Set the tics to be displayed outside the graph.
    auto outsideGraph() -> DerivedSpecs&;

    /// Set the tics to be rotated by 90 degrees if `true`.
    auto rotate(bool value = true) -> DerivedSpecs&;

    /// Set the tics to be rotated by given degrees.
    auto rotateBy(double degrees) -> DerivedSpecs&;

    /// Set the scale for the major tics (identical to method scaleMajorBy).
    auto scaleBy(double value) -> DerivedSpecs&;

    /// Set the scale for the major tics.
    auto scaleMajorBy(double value) -> DerivedSpecs&;

    /// Set the scale for the minor tics.
    auto scaleMinorBy(double value) -> DerivedSpecs&;

    /// Set the format of the tics using a format expression (`"%.2f"`)
    auto format(std::string fmt) -> DerivedSpecs&;

    /// Set logarithmic scale with base for an axis.
    auto logscale(int base = 10) -> DerivedSpecs&;

    /// Convert this TicsSpecsBaseOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Convert this TicsSpecsBaseOf object into a gnuplot formatted string.
    auto repr(std::string axis) const -> std::string;

  private:
    /// The option indicating if tics are displayed along axis or border.
    std::string m_along;

    /// The mirror option of the tics.
    std::string m_mirror;

    /// The rotate option for the tics.
    std::string m_rotate;

    /// The place where the tics are displayed (in or out).
    std::string m_inout;

    /// The format expression for formatting the display of the tics.
    std::string m_format;

    /// The scale of the major tics.
    double m_scalemajor = 1.0;

    /// The scale of the minor tics.
    double m_scaleminor = 1.0;

    /// Logarithmic scaling base settings for the axis.
    std::string m_logscaleBase;
};

template <typename DerivedSpecs>
TicsSpecsBaseOf<DerivedSpecs>::TicsSpecsBaseOf()
{
    alongBorder();
    mirror(internal::DEFAULT_TICS_MIRROR);
    outsideGraph();
    rotate(internal::DEFAULT_TICS_ROTATE);
    scaleMajorBy(internal::DEFAULT_TICS_SCALE_MAJOR_BY);
    scaleMinorBy(internal::DEFAULT_TICS_SCALE_MINOR_BY);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::alongAxis() -> DerivedSpecs&
{
    m_along = "axis";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::alongBorder() -> DerivedSpecs&
{
    m_along = "border";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::mirror(bool value) -> DerivedSpecs&
{
    m_mirror = value ? "mirror" : "nomirror";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::rotate(bool value) -> DerivedSpecs&
{
    m_rotate = value ? "rotate" : "norotate";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::rotateBy(double degrees) -> DerivedSpecs&
{
    m_rotate = "rotate by " + internal::str(degrees);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::insideGraph() -> DerivedSpecs&
{
    m_inout = "in";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::outsideGraph() -> DerivedSpecs&
{
    m_inout = "out";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::scaleBy(double value) -> DerivedSpecs&
{
    return scaleMajorBy(value);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::scaleMajorBy(double value) -> DerivedSpecs&
{
    m_scalemajor = value;
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::scaleMinorBy(double value) -> DerivedSpecs&
{
    m_scaleminor = value;
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::format(std::string fmt) -> DerivedSpecs&
{
    m_format = "'" + fmt + "'";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::logscale(int base) -> DerivedSpecs&
{
    m_logscaleBase = std::to_string(base);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::repr() const -> std::string
{
    return repr("");
}

template <typename DerivedSpecs>
auto TicsSpecsBaseOf<DerivedSpecs>::repr(std::string axis) const -> std::string
{
    const auto show = ShowSpecsOf<DerivedSpecs>::repr();
    if (show == "no")
        return "unset " + axis + "tics";

    std::stringstream ss;
    if (!m_logscaleBase.empty())
    {
        ss << "set logscale " + axis + " " + m_logscaleBase + "\n";
    }
    ss << "set " + axis + "tics"
       << " ";
    ss << m_along << " ";
    ss << m_mirror << " ";
    ss << m_inout << " ";
    ss << "scale " << m_scalemajor << "," << m_scaleminor << " ";
    ss << m_rotate << " ";
    ss << OffsetSpecsOf<DerivedSpecs>::repr() << " ";
    ss << TextSpecsOf<DerivedSpecs>::repr() << " ";
    ss << m_format;
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
