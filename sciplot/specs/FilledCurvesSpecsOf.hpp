// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2021 Allan Leal, Bim Overbohm
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
#include <sciplot/specs/Specs.hpp>

namespace sciplot
{

/// The class used to set options for the gnuplot filledcurve functionality.
template <typename DerivedSpecs>
class FilledCurvesSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default FilledCurveSpecs instance.
    FilledCurvesSpecsOf();

    /// Limit filled area to above curves.
    auto above() -> DerivedSpecs&;

    /// Limit filled area to below curves.
    auto below() -> DerivedSpecs&;

    /// Convert this FillSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// Fill mode for curve(s)
    std::string m_fillMode;
};

/// The class used to specify color or pattern fill options.
class FilledCurvesSpecs : public FilledCurvesSpecsOf<FilledCurvesSpecs>
{
};

template <typename DerivedSpecs>
FilledCurvesSpecsOf<DerivedSpecs>::FilledCurvesSpecsOf()
{
}

template <typename DerivedSpecs>
auto FilledCurvesSpecsOf<DerivedSpecs>::above() -> DerivedSpecs&
{
    m_fillMode = "above";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FilledCurvesSpecsOf<DerivedSpecs>::below() -> DerivedSpecs&
{
    m_fillMode = "below";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FilledCurvesSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream ss;
    ss << " " << m_fillMode;
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
