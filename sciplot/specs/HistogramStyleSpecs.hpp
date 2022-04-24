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
#include <sciplot/specs/Specs.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to specify histogram style options.
class HistogramStyleSpecs : virtual public Specs<HistogramStyleSpecs>
{
  public:
    /// Construct a default HistogramStyleSpecs instance.
    HistogramStyleSpecs();

    /// Set the histogram style to be clustered.
    auto clustered() -> HistogramStyleSpecs&;

    /// Set the histogram style to be clustered with a given gap size.
    auto clusteredWithGap(double value) -> HistogramStyleSpecs&;

    /// Set the histogram style to be stacked with groups formed using data along rows.
    auto rowStacked() -> HistogramStyleSpecs&;

    /// Set the histogram style to be stacked with groups formed using data along columns.
    auto columnStacked() -> HistogramStyleSpecs&;

    /// Set the histogram style to be with error bars.
    auto errorBars() -> HistogramStyleSpecs&;

    /// Set the histogram style to be with error bars and also set its gap size.
    auto errorBarsWithGap(double value) -> HistogramStyleSpecs&;

    /// Set the histogram style to be with error bars and also set its line width.
    auto errorBarsWithLineWidth(double value) -> HistogramStyleSpecs&;

    /// Convert this HistogramStyleSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The type of the histogram (clustered, errorbars, rowstacked, columnstacked).
    std::string m_type;

    /// The gap size (for clustered).
    std::string m_gap_clustered;

    /// The gap size (for errorbars).
    std::string m_gap_errorbars;

    /// The line width (applicable only to errorbars).
    std::string m_linewidth;
};

inline HistogramStyleSpecs::HistogramStyleSpecs()
{
}

inline auto HistogramStyleSpecs::clustered() -> HistogramStyleSpecs&
{
    m_type = "clustered";
    return *this;
}

inline auto HistogramStyleSpecs::clusteredWithGap(double value) -> HistogramStyleSpecs&
{
    m_type = "clustered";
    m_gap_clustered = "gap " + internal::str(value);
    return *this;
}

inline auto HistogramStyleSpecs::rowStacked() -> HistogramStyleSpecs&
{
    m_type = "rowstacked";
    return *this;
}

inline auto HistogramStyleSpecs::columnStacked() -> HistogramStyleSpecs&
{
    m_type = "columnstacked";
    return *this;
}

inline auto HistogramStyleSpecs::errorBars() -> HistogramStyleSpecs&
{
    m_type = "errorbars";
    return *this;
}

inline auto HistogramStyleSpecs::errorBarsWithGap(double value) -> HistogramStyleSpecs&
{
    m_type = "errorbars";
    m_gap_errorbars = "gap " + internal::str(value);
    return *this;
}

inline auto HistogramStyleSpecs::errorBarsWithLineWidth(double value) -> HistogramStyleSpecs&
{
    m_type = "errorbars";
    m_linewidth = "linewidth " + internal::str(value);
    return *this;
}

inline auto HistogramStyleSpecs::repr() const -> std::string
{
    [[maybe_unused]] const auto supports_gap = (m_type == "clustered" || m_type == "errorbars");
    [[maybe_unused]] const auto supports_linewidth = (m_type == "errorbars");

    std::stringstream ss;
    ss << "set style histogram" << " ";
    ss << m_type << " ";
    if(m_type == "clustered") ss << m_gap_clustered << " ";
    if(m_type == "errorbars") ss << m_gap_errorbars << " ";
    if(m_type == "errorbars") ss << m_linewidth << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
