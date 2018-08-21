// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
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

// Capim includes
#include <Capim/default.hpp>
#include <Capim/specs/linespecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The class used to specify options for grid lines along axis tics (major or minor).
class gridspecsbase : public linespecs<gridspecsbase>
{
public:
    /// Construct a default gridticsspecs instance.
    gridspecsbase(std::string tics = "", bool majortics = true);

    /// Convert this gridticsspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Enable the grid lines along the specified axis tics.
    auto enable() -> gridspecsbase& { m_active = true; return *this; }

    /// Disable the grid lines along the specified axis tics.
    auto disable() -> gridspecsbase& { m_active = false; return *this; }

    /// Set the grid lines to be plot on the back of other plotting elements.
    auto back() -> gridspecsbase& { m_depth = "back"; return *this; }

    /// Set the grid lines to be plot on the front of other plotting elements.
    auto front() -> gridspecsbase& { m_depth = "front"; return *this; }

    /// Set the grid lines to be plot on the back of other plotting elements in 2d plots. In 3d plots, this option splits the grid and the graph box into two layers, with one behind, and the other in front of the plotted elements.
    auto layerdefault() -> gridspecsbase& { m_depth = "layerdefault"; return *this; }

private:
    /// The names of the tics for which the grid is affected.
    std::string m_tics;

    /// The boolean flag that indicates if the grid lines are along major tics, if true, or minor tics otherwise.
    bool m_majortics;

    /// The boolean flag that indicates if the grid lines for the chosen tics are active.
    bool m_active;

    /// The placement depth for the grid.
    std::string m_depth;
};

gridspecsbase::gridspecsbase(std::string tics, bool majortics)
: m_tics(tics), m_majortics(majortics)
{
    enable();
    back();
    linecolor(DEFAULT_GRID_LINECOLOR);
    linewidth(DEFAULT_GRID_LINEWIDTH);
    linetype(DEFAULT_GRID_LINETYPE);
    dashtype(DEFAULT_GRID_DASHTYPE);
}

auto gridspecsbase::repr() const -> std::string
{
    if(m_tics.empty() && !m_active)
        return "unset grid";

    if(m_tics.size() && !m_active)
        return "set grid no" + m_tics;

    std::stringstream ss;
    ss << "set grid ";
    ss << optionstr(m_tics);
    ss << optionstr(m_depth);
    if(m_majortics) ss << linespecs<gridspecsbase>::repr();
    else ss << ", " + linespecs<gridspecsbase>::repr(); // For minor tics, the preceding comma is needed
    return ss.str();
}

} // namespace internal
} // namespace Capim
