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
#include <sciplot/specs/LineSpecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The class used to specify options for grid lines along axis tics (major or minor).
class GridSpecsbase : public LineSpecs<GridSpecsbase>
{
  public:
    /// Construct a default GridSpecsbase instance.
    GridSpecsbase(std::string tics = "", bool majortics = true);

    /// Convert this GridSpecsbase object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the active state of the grid lines along the specified axis tics.
    auto show(bool value = true) -> GridSpecsbase&
    {
        m_show = value;
        return *this;
    }

    /// Set the grid lines to be plot on the back of other plot elements.
    auto back() -> GridSpecsbase&
    {
        m_depth = "back";
        return *this;
    }

    /// Set the grid lines to be plot on the front of other plot elements.
    auto front() -> GridSpecsbase&
    {
        m_depth = "front";
        return *this;
    }

    /// Set the grid lines to be plot on the back of other plot elements in 2d plots. In 3d plots, this option splits the grid and the graph box into two layers, with one behind, and the other in front of the plotted elements.
    auto layerdefault() -> GridSpecsbase&
    {
        m_depth = "layerdefault";
        return *this;
    }

  private:
    /// The names of the tics for which the grid is affected.
    std::string m_tics;

    /// The boolean flag that indicates if the grid lines are along major tics, if true, or minor tics otherwise.
    bool m_majortics;

    /// The boolean flag that indicates if the grid lines for the chosen tics are shown.
    bool m_show;

    /// The placement depth for the grid.
    std::string m_depth;
};

GridSpecsbase::GridSpecsbase(std::string tics, bool majortics)
    : m_tics(tics), m_majortics(majortics)
{
    show(false);
    back();
    linecolor(internal::DEFAULT_GRID_LINECOLOR);
    linewidth(internal::DEFAULT_GRID_LINEWIDTH);
    linetype(internal::DEFAULT_GRID_LINETYPE);
    dashtype(internal::DEFAULT_GRID_DASHTYPE);
}

auto GridSpecsbase::repr() const -> std::string
{
    if (m_tics.empty() && !m_show)
        return "unset grid";

    if (m_tics.size() && !m_show)
        return "set grid no" + m_tics;

    std::stringstream ss;
    ss << "set grid ";
    ss << gnuplot::optionstr(m_tics);
    ss << gnuplot::optionstr(m_depth);
    if (m_majortics)
        ss << LineSpecs<GridSpecsbase>::repr();
    else
        ss << ", " + LineSpecs<GridSpecsbase>::repr(); // For minor tics, the preceding comma is needed
    return ss.str();
}

} // namespace sciplot
