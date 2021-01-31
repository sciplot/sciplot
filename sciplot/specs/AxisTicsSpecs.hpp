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

// C++ includes
#include <vector>

// sciplot includes
#include <sciplot/default.hpp>
#include <sciplot/specs/OffsetSpecsOf.hpp>
#include <sciplot/specs/ShowSpecsOf.hpp>
#include <sciplot/specs/TextSpecsOf.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// The class used to specify options for tics.
class AxisTicsSpecs : public TextSpecsOf<AxisTicsSpecs>, public OffsetSpecsOf<AxisTicsSpecs>, public ShowSpecsOf<AxisTicsSpecs>
{
  public:
    /// Construct a default AxisTicsSpecs instance.
    AxisTicsSpecs(std::string axis);

    /// Set the tics to be displayed along the axis.
    auto alongAxis() -> AxisTicsSpecs&;

    /// Set the tics to be displayed along the border.
    auto alongBorder() -> AxisTicsSpecs&;

    /// Set the tics to be mirrored on the opposite border if `true`.
    auto mirror(bool value=true) -> AxisTicsSpecs&;

    /// Set the tics to be displayed inside the graph.
    auto insideGraph() -> AxisTicsSpecs&;

    /// Set the tics to be displayed outside the graph.
    auto outsideGraph() -> AxisTicsSpecs&;

    /// Set the tics to be rotated by 90 degrees if `true`.
    auto rotate(bool value=true) -> AxisTicsSpecs&;

    /// Set the tics to be rotated by given degrees.
    auto rotateBy(double degrees) -> AxisTicsSpecs&;

    /// Set the tics to be displayed on the front of all plot elements.
    auto stackFront() -> AxisTicsSpecs&;

    /// Set the tics to be displayed on the back of all plot elements.
    auto stackBack() -> AxisTicsSpecs&;

    /// Set the scale for the major tics (identical to method scaleMajorBy).
    auto scaleBy(double value) -> AxisTicsSpecs&;

    /// Set the scale for the major tics.
    auto scaleMajorBy(double value) -> AxisTicsSpecs&;

    /// Set the scale for the minor tics.
    auto scaleMinorBy(double value) -> AxisTicsSpecs&;

    /// Set the format of the tics using a format expression (`"%.2f"`)
    auto format(std::string fmt) -> AxisTicsSpecs&;

    /// Set the values of the tics to be identified automatically or not.
    auto automatic() -> AxisTicsSpecs&;

    /// Set the start value for the tics (you must also call method @ref increment).
    auto start(double value) -> AxisTicsSpecs&;

    /// Set the increment for the tics (start and end values determined automatically).
    auto increment(double value) -> AxisTicsSpecs&;

    /// Set the end value for the tics (you must also call methods @ref start and  @ref increment).
    auto end(double value) -> AxisTicsSpecs&;

    /// Set the start, increment and end values of the tics.
    auto interval(double start, double increment, double end) -> AxisTicsSpecs&;

    /// Set the values of the tics that should be displayed.
    auto at(const std::vector<double>& values) -> AxisTicsSpecs&;

    /// Set the labels that should be displayed on given tic values.
    auto at(const std::vector<double>& values, const std::vector<std::string>& labels) -> AxisTicsSpecs&;

    /// Add more tics to be displayed with given tic values.
    auto add(const std::vector<double>& values) -> AxisTicsSpecs&;

    /// Add more tics to be displayed with given tic values and corresponding labels.
    auto add(const std::vector<double>& values, const std::vector<std::string>& labels) -> AxisTicsSpecs&;

    /// Convert this AxisTicsSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The name of the axis associated with these tics.
    std::string m_axis;

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

    /// The start value for the tics.
    std::string m_start;

    /// The increment for the tics.
    std::string m_increment;

    /// The end value for the tics.
    std::string m_end;

    /// The values/labels of the tics that should be displayed.
    std::string m_at;

    /// The extra values/labels of the tics to be displayed.
    std::string m_add;

    /// The scale of the major tics.
    double m_scalemajor = 1.0;

    /// The scale of the minor tics.
    double m_scaleminor = 1.0;
};

AxisTicsSpecs::AxisTicsSpecs(std::string axis)
: m_axis(axis)
{
    alongBorder();
    mirror(internal::DEFAULT_TICS_MIRROR);
    outsideGraph();
    rotate(internal::DEFAULT_TICS_ROTATE);
    stackFront();
    scaleMajorBy(internal::DEFAULT_TICS_SCALE_MAJOR_BY);
    scaleMinorBy(internal::DEFAULT_TICS_SCALE_MINOR_BY);
}

auto AxisTicsSpecs::alongAxis() -> AxisTicsSpecs&
{
    m_along = "axis";
    return *this;
}

auto AxisTicsSpecs::alongBorder() -> AxisTicsSpecs&
{
    m_along = "border";
    return *this;
}

auto AxisTicsSpecs::mirror(bool value) -> AxisTicsSpecs&
{
    m_mirror = value ? "mirror" : "nomirror";
    return *this;
}

auto AxisTicsSpecs::rotate(bool value) -> AxisTicsSpecs&
{
    m_rotate = value ? "rotate" : "norotate";
    return *this;
}

auto AxisTicsSpecs::rotateBy(double degrees) -> AxisTicsSpecs&
{
    m_rotate = "rotate by " + internal::str(degrees);
    return *this;
}

auto AxisTicsSpecs::stackFront() -> AxisTicsSpecs&
{
    m_depth = "front";
    return *this;
}

auto AxisTicsSpecs::stackBack() -> AxisTicsSpecs&
{
    m_depth = "back";
    return *this;
}

auto AxisTicsSpecs::insideGraph() -> AxisTicsSpecs&
{
    m_inout = "in";
    return *this;
}

auto AxisTicsSpecs::outsideGraph() -> AxisTicsSpecs&
{
    m_inout = "out";
    return *this;
}

auto AxisTicsSpecs::scaleBy(double value) -> AxisTicsSpecs&
{
    return scaleMajorBy(value);
}

auto AxisTicsSpecs::scaleMajorBy(double value) -> AxisTicsSpecs&
{
    m_scalemajor = value;
    return *this;
}

auto AxisTicsSpecs::scaleMinorBy(double value) -> AxisTicsSpecs&
{
    m_scaleminor = value;
    return *this;
}

auto AxisTicsSpecs::format(std::string fmt) -> AxisTicsSpecs&
{
    m_format = "'" + fmt + "'";
    return *this;
}

auto AxisTicsSpecs::automatic() -> AxisTicsSpecs&
{
    // clear strings related to tics values/labels
    m_start = "";
    m_end = "";
    m_increment = "";
    m_at = "";
    return *this;
}

auto AxisTicsSpecs::start(double value) -> AxisTicsSpecs&
{
    m_start = internal::str(value) + ", ";
    m_at = m_start + m_increment + m_end;
    return *this;
}

auto AxisTicsSpecs::increment(double value) -> AxisTicsSpecs&
{
    m_increment = internal::str(value);
    m_at = m_start + m_increment + m_end;
    return *this;
}

auto AxisTicsSpecs::end(double value) -> AxisTicsSpecs&
{
    m_end = ", " + internal::str(value);
    m_at = m_start + m_increment + m_end;
    return *this;
}

auto AxisTicsSpecs::interval(double start, double increment, double end) -> AxisTicsSpecs&
{
    if(increment <= 0.0) throw std::runtime_error("The `increment` argument in method AxisTicsSpecs::interval must be positive.");
    if(end <= start) throw std::runtime_error("The `end` argument in method AxisTicsSpecs::interval must be greater than `start`.");
    std::stringstream ss;
    ss << start << ", " << increment << ", " << end;
    m_at = ss.str();
    return *this;
}

auto AxisTicsSpecs::at(const std::vector<double>& values) -> AxisTicsSpecs&
{
    std::stringstream ss;
    ss << "(";
    for(auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << values[i];
    ss << ")";
    m_at = ss.str();
    return *this;
}

auto AxisTicsSpecs::at(const std::vector<double>& values, const std::vector<std::string>& labels) -> AxisTicsSpecs&
{
    std::stringstream ss;
    ss << "(";
    for(auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << "'" << labels[i] << "' " << values[i];
    ss << ")";
    m_at = ss.str();
    return *this;
}

auto AxisTicsSpecs::add(const std::vector<double>& values) -> AxisTicsSpecs&
{
    std::stringstream ss;
    ss << "add (";
    for(auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << values[i];
    ss << ")";
    m_add = ss.str();
    return *this;
}

auto AxisTicsSpecs::add(const std::vector<double>& values, const std::vector<std::string>& labels) -> AxisTicsSpecs&
{
    std::stringstream ss;
    ss << "add (";
    for(auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << "'" << labels[i] << "' " << values[i];
    ss << ")";
    m_add = ss.str();
    return *this;
}

auto AxisTicsSpecs::repr() const -> std::string
{
    const auto show = ShowSpecsOf<AxisTicsSpecs>::repr();
    if(show == "no")
        return "unset " + m_axis + "tics";

    if(m_start.size() && m_increment.empty())
        throw std::runtime_error("You have called method AxisTicsSpecs::start but not AxisTicsSpecs::increment.");
    if(m_end.size() && m_increment.empty())
        throw std::runtime_error("You have called method AxisTicsSpecs::end but not AxisTicsSpecs::increment.");
    if(m_end.size() && m_start.empty())
        throw std::runtime_error("You have called method AxisTicsSpecs::end but not AxisTicsSpecs::start.");

    std::stringstream ss;
    ss << "set " << m_axis << "tics" << " ";
    ss << m_along << " ";
    ss << m_mirror << " ";
    ss << m_depth << " ";
    ss << m_inout << " ";
    ss << "scale " << m_scalemajor << "," << m_scaleminor << " ";
    ss << m_rotate << " ";
    ss << OffsetSpecsOf<AxisTicsSpecs>::repr() << " ";
    ss << TextSpecsOf<AxisTicsSpecs>::repr() << " ";
    ss << m_format << " ";
    ss << m_at << " ";
    ss << m_add << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
