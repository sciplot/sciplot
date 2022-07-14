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
#include <sciplot/specs/DepthSpecsOf.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/ShowSpecsOf.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to specify options for grid lines along axis tics (major or minor).
class GridSpecsBase : public LineSpecsOf<GridSpecsBase>, public DepthSpecsOf<GridSpecsBase>, public ShowSpecsOf<GridSpecsBase>
{
  public:
    /// Construct a default GridSpecsBase instance.
    GridSpecsBase(std::string tics = "", bool majortics = true);

    /// Convert this GridSpecsBase object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The names of the tics for which the grid is affected.
    std::string m_tics;

    /// The boolean flag that indicates if the grid lines are along major tics, if true, or minor tics otherwise.
    bool m_majortics;
};

inline GridSpecsBase::GridSpecsBase(std::string tics, bool majortics)
: m_tics(tics), m_majortics(majortics)
{
    show(true);
    back();
    lineColor(internal::DEFAULT_GRID_LINECOLOR);
    lineWidth(internal::DEFAULT_GRID_LINEWIDTH);
    lineType(internal::DEFAULT_GRID_LINETYPE);
    dashType(internal::DEFAULT_GRID_DASHTYPE);
}

inline auto GridSpecsBase::repr() const -> std::string
{
    const auto show = ShowSpecsOf<GridSpecsBase>::repr();
    const auto visible = show != "no";

    if(m_tics.empty() && !visible)
        return "unset grid";

    if(m_tics.size() && !visible)
        return "set grid no" + m_tics;

    std::stringstream ss;
    ss << "set grid " << m_tics << " ";
    ss << DepthSpecsOf<GridSpecsBase>::repr() << " ";
    if(m_majortics)
        ss << LineSpecsOf<GridSpecsBase>::repr();
    else
        ss << ", " + LineSpecsOf<GridSpecsBase>::repr(); // For minor tics, the preceding comma is needed
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
