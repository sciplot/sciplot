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

// C++ includes
#include <vector>

// sciplot includes
#include <sciplot/Utils.hpp>
#include <sciplot/specs/TicsSpecsBaseOf.hpp>

namespace sciplot
{

/// The class used to specify options for major tics of a specific axis.
class TicsSpecsMajor : public TicsSpecsBaseOf<TicsSpecsMajor>
{
  public:
    /// Construct a default TicsSpecsMajor instance.
    TicsSpecsMajor(std::string axis);

    /// Set the values of the tics to be identified automatically.
    auto automatic() -> TicsSpecsMajor&;

    /// Set the start value for the tics (you must also call method @ref increment).
    auto start(double value) -> TicsSpecsMajor&;

    /// Set the increment for the tics (start and end values determined automatically).
    auto increment(double value) -> TicsSpecsMajor&;

    /// Set the end value for the tics (you must also call methods @ref start and  @ref increment).
    auto end(double value) -> TicsSpecsMajor&;

    /// Set the start, increment and end values of the tics.
    auto interval(double start, double increment, double end) -> TicsSpecsMajor&;

    /// Set the values of the tics that should be displayed.
    auto at(const std::vector<double>& values) -> TicsSpecsMajor&;

    /// Set the labels that should be displayed on given tic values.
    auto at(const std::vector<double>& values, const std::vector<std::string>& labels) -> TicsSpecsMajor&;

    /// Add more tics to be displayed with given tic values.
    auto add(const std::vector<double>& values) -> TicsSpecsMajor&;

    /// Add more tics to be displayed with given tic values and corresponding labels.
    auto add(const std::vector<double>& values, const std::vector<std::string>& labels) -> TicsSpecsMajor&;

    /// Convert this TicsSpecsMajor object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The name of the axis associated with these tics.
    const std::string m_axis;

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
};

inline TicsSpecsMajor::TicsSpecsMajor(std::string axis)
    : TicsSpecsBaseOf<TicsSpecsMajor>(), m_axis(axis)
{
    if (axis.empty())
        throw std::runtime_error(
            "You have provided an empty string "
            "in `axis` argument of constructor TicsSpecsMajor(axis).");
}

inline auto TicsSpecsMajor::automatic() -> TicsSpecsMajor&
{
    // clear strings related to tics values/labels
    m_start = "";
    m_end = "";
    m_increment = "";
    m_at = "";
    return *this;
}

inline auto TicsSpecsMajor::start(double value) -> TicsSpecsMajor&
{
    m_start = internal::str(value) + ", ";
    m_at = m_start + m_increment + m_end;
    return *this;
}

inline auto TicsSpecsMajor::increment(double value) -> TicsSpecsMajor&
{
    m_increment = internal::str(value);
    m_at = m_start + m_increment + m_end;
    return *this;
}

inline auto TicsSpecsMajor::end(double value) -> TicsSpecsMajor&
{
    m_end = ", " + internal::str(value);
    m_at = m_start + m_increment + m_end;
    return *this;
}

inline auto TicsSpecsMajor::interval(double start, double increment, double end) -> TicsSpecsMajor&
{
    if (increment <= 0.0) throw std::runtime_error("The `increment` argument in method TicsSpecsMajor::interval must be positive.");
    if (end <= start) throw std::runtime_error("The `end` argument in method TicsSpecsMajor::interval must be greater than `start`.");
    std::stringstream ss;
    ss << start << ", " << increment << ", " << end;
    m_at = ss.str();
    return *this;
}

inline auto TicsSpecsMajor::at(const std::vector<double>& values) -> TicsSpecsMajor&
{
    std::stringstream ss;
    ss << "(";
    for (auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << values[i];
    ss << ")";
    m_at = ss.str();
    return *this;
}

inline auto TicsSpecsMajor::at(const std::vector<double>& values, const std::vector<std::string>& labels) -> TicsSpecsMajor&
{
    std::stringstream ss;
    ss << "(";
    for (auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << "'" << labels[i] << "' " << values[i];
    ss << ")";
    m_at = ss.str();
    return *this;
}

inline auto TicsSpecsMajor::add(const std::vector<double>& values) -> TicsSpecsMajor&
{
    std::stringstream ss;
    ss << "add (";
    for (auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << values[i];
    ss << ")";
    m_add = ss.str();
    return *this;
}

inline auto TicsSpecsMajor::add(const std::vector<double>& values, const std::vector<std::string>& labels) -> TicsSpecsMajor&
{
    std::stringstream ss;
    ss << "add (";
    for (auto i = 0; i < values.size(); ++i)
        ss << (i == 0 ? "" : ", ") << "'" << labels[i] << "' " << values[i];
    ss << ")";
    m_add = ss.str();
    return *this;
}

inline auto TicsSpecsMajor::repr() const -> std::string
{
    const auto baserepr = TicsSpecsBaseOf<TicsSpecsMajor>::repr(m_axis);

    if (isHidden())
        return baserepr;

    if (m_start.size() && m_increment.empty())
        throw std::runtime_error("You have called method TicsSpecsMajor::start but not TicsSpecsMajor::increment.");
    if (m_end.size() && m_increment.empty())
        throw std::runtime_error("You have called method TicsSpecsMajor::end but not TicsSpecsMajor::increment.");
    if (m_end.size() && m_start.empty())
        throw std::runtime_error("You have called method TicsSpecsMajor::end but not TicsSpecsMajor::start.");

    std::stringstream ss;
    ss << baserepr << " ";
    ss << m_at << " ";
    ss << m_add << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
