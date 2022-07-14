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
#include <sciplot/Default.hpp>
#include <sciplot/Utils.hpp>
#include <sciplot/specs/ShowSpecsOf.hpp>

namespace sciplot
{

/// The class used to specify options for minor tics of a specific axis.
class TicsSpecsMinor : public ShowSpecsOf<TicsSpecsMinor>
{
  public:
    /// Construct a default TicsSpecsMinor instance.
    TicsSpecsMinor(std::string axis);

    /// Set the number of minor tics between major tics to be identified automatically.
    auto automatic() -> TicsSpecsMinor&;

    /// Set the number of minor tics between major tics.
    auto number(int value) -> TicsSpecsMinor&;

    /// Convert this TicsSpecsMinor object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The name of the axis associated with these tics.
    const std::string m_axis;

    /// The frequency of minor tics between major tics (number of minor tics = frequency - 1).
    std::string m_frequency;
};

inline TicsSpecsMinor::TicsSpecsMinor(std::string axis)
    : m_axis(axis)
{
    if (axis.empty())
        throw std::runtime_error(
            "You have provided an empty string "
            "in `axis` argument of constructor TicsSpecsMinor(axis).");
}

inline auto TicsSpecsMinor::automatic() -> TicsSpecsMinor&
{
    m_frequency = "";
    return *this;
}

inline auto TicsSpecsMinor::number(int value) -> TicsSpecsMinor&
{
    value = std::max<decltype(value)>(value, 0);
    m_frequency = internal::str(value + 1);
    return *this;
}

inline auto TicsSpecsMinor::repr() const -> std::string
{
    if (isHidden())
        return "unset m" + m_axis + "tics";

    std::stringstream ss;
    ss << "set m" << m_axis << "tics"
       << " ";
    ss << m_frequency;
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
