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
#include <sciplot/ColumnIndex.hpp>
#include <sciplot/Utils.hpp>
#include <sciplot/specs/FillSpecsOf.hpp>
#include <sciplot/specs/FilledCurvesSpecsOf.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/PointSpecsOf.hpp>

namespace sciplot
{

/// The class where options for the plotted element can be specified.
class DrawSpecs : public LineSpecsOf<DrawSpecs>, public PointSpecsOf<DrawSpecs>, public FillSpecsOf<DrawSpecs>, public FilledCurvesSpecsOf<DrawSpecs>
{
  public:
    /// Construct a DrawSpecs instance.
    /// @param what The string representing `what` to be plot (e.g., "'filename'", "sin(x)")
    /// @param use The string representing the `using` expression (e.g., "using 1:2", "using 4:6:8:9")
    /// @param with The string representing the `with plotstyle` expression (e.g., "lines", "linespoints", "dots")
    DrawSpecs(std::string what, std::string use, std::string with);

    /// Set the legend label of the plotted element.
    auto label(std::string text) -> DrawSpecs&;

    /// Set the legend label of the plotted element to be retrieved from the header of column.
    auto labelFromColumnHeader() -> DrawSpecs&;

    /// Set the legend label of the plotted element to be retrieved from the header of a column with given index.
    auto labelFromColumnHeader(int icolumn) -> DrawSpecs&;

    /// Set the legend label of the plotted element to be ignored.
    auto labelNone() -> DrawSpecs&;

    /// Set the legend label to be determined automatically from the plot expression.
    auto labelDefault() -> DrawSpecs&;

    /// Set the column in the data file containing the tic labels for *x* axis.
    auto xtics(ColumnIndex icol) -> DrawSpecs&;

    /// Set the column in the data file containing the tic labels for *y* axis.
    auto ytics(ColumnIndex icol) -> DrawSpecs&;

    /// Convert this DrawSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The string representing `what` to be plot (e.g., "'filename'", "sin(x)").
    std::string m_what;

    /// The string representing the `using` expression (e.g., "using 1:2", "using 4:6:8:9").
    std::string m_using;

    /// The string representing the `with plotstyle` expression (e.g., "lines", "linespoints", "dots").
    std::string m_with;

    /// The title of the plot as a gnuplot formatted string (e.g., "title 'sin(x)'").
    std::string m_title;

    /// The column in the data file containing the x tic labels.
    std::string m_xtic;

    /// The column in the data file containing the y tic labels.
    std::string m_ytic;
};

inline DrawSpecs::DrawSpecs(std::string what, std::string use, std::string with)
    : m_what(what), m_using(use), m_with(with)
{
    lineWidth(internal::DEFAULT_LINEWIDTH);
}

inline auto DrawSpecs::label(std::string text) -> DrawSpecs&
{
    m_title = "title '" + text + "'";
    return *this;
}

inline auto DrawSpecs::labelFromColumnHeader() -> DrawSpecs&
{
    m_title = "title columnheader";
    return *this;
}

inline auto DrawSpecs::labelFromColumnHeader(int icolumn) -> DrawSpecs&
{
    m_title = "title columnheader(" + std::to_string(icolumn) + ")";
    return *this;
}

inline auto DrawSpecs::labelNone() -> DrawSpecs&
{
    m_title = "notitle";
    return *this;
}

inline auto DrawSpecs::labelDefault() -> DrawSpecs&
{
    m_title = "";
    return *this;
}

inline auto DrawSpecs::xtics(ColumnIndex icol) -> DrawSpecs&
{
    m_xtic = "xtic(stringcolumn(" + icol.value + "))"; // xtic(stringcolumn(1)) or xtic(stringcolumn('Name'))
    return *this;
}

inline auto DrawSpecs::ytics(ColumnIndex icol) -> DrawSpecs&
{
    m_ytic = "ytic(stringcolumn(" + icol.value + "))"; // ytic(stringcolumn(1)) or ytic(stringcolumn('Name'))
    return *this;
}

inline auto DrawSpecs::repr() const -> std::string
{
    std::string use = m_using;
    if (m_xtic.size()) use += ":" + m_xtic;
    if (m_ytic.size()) use += ":" + m_ytic;

    std::stringstream ss;
    ss << m_what << " ";
    ss << gnuplot::optionValueStr("using", use);
    ss << m_title << " ";
    ss << gnuplot::optionValueStr("with", m_with);
    ss << FilledCurvesSpecsOf<DrawSpecs>::repr() << " ";
    ss << LineSpecsOf<DrawSpecs>::repr() << " ";
    ss << PointSpecsOf<DrawSpecs>::repr() << " ";
    ss << FillSpecsOf<DrawSpecs>::repr() << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
