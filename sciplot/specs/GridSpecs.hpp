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
#include <sciplot/util.hpp>
#include <sciplot/specs/GridSpecsBase.hpp>

namespace sciplot
{

/// The class used to specify options for grid.
class GridSpecs : public GridSpecsBase
{
  public:
    /// Construct a default GridSpecs instance.
    GridSpecs();

    /// Convert this GridSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Return a grid specification object for configuring grid lines along major xtics.
    auto xtics() -> GridSpecsBase& { return _gridmajor("xtics"); }

    /// Return a grid specification object for configuring grid lines along major ytics.
    auto ytics() -> GridSpecsBase& { return _gridmajor("ytics"); }

    /// Return a grid specification object for configuring grid lines along major ztics.
    auto ztics() -> GridSpecsBase& { return _gridmajor("ztics"); }

    /// Return a grid specification object for configuring grid lines along major rtics.
    auto rtics() -> GridSpecsBase& { return _gridmajor("rtics"); }

    /// Return a grid specification object for configuring grid lines along major x2tics.
    auto x2tics() -> GridSpecsBase& { return _gridmajor("x2tics"); }

    /// Return a grid specification object for configuring grid lines along major y2tics.
    auto y2tics() -> GridSpecsBase& { return _gridmajor("y2tics"); }

    /// Return a grid specification object for configuring grid lines along minor xtics.
    auto mxtics() -> GridSpecsBase& { return _gridminor("mxtics"); }

    /// Return a grid specification object for configuring grid lines along minor ytics.
    auto mytics() -> GridSpecsBase& { return _gridminor("mytics"); }

    /// Return a grid specification object for configuring grid lines along minor ztics.
    auto mztics() -> GridSpecsBase& { return _gridminor("mztics"); }

    /// Return a grid specification object for configuring grid lines along minor rtics.
    auto mrtics() -> GridSpecsBase& { return _gridminor("mrtics"); }

    /// Return a grid specification object for configuring grid lines along minor x2tics.
    auto mx2tics() -> GridSpecsBase& { return _gridminor("mx2tics"); }

    /// Return a grid specification object for configuring grid lines along minor y2tics.
    auto my2tics() -> GridSpecsBase& { return _gridminor("my2tics"); }

  private:
    /// Auxiliary private method that adds a new specs object for grid lines along a major tics.
    auto _gridmajor(std::string tics) -> GridSpecsBase&
    {
        m_gridticsspecs.emplace_back(tics, true);
        return m_gridticsspecs.back();
    }

    /// Auxiliary private method that adds a new specs object for grid lines along a minor tics.
    auto _gridminor(std::string tics) -> GridSpecsBase&
    {
        m_gridticsspecs.emplace_back(tics, false);
        return m_gridticsspecs.back();
    }

  private:
    /// The vector of grid specs for the major and minor grid lines in the plot (for xtics, ytics, mxtics, etc.).
    std::vector<GridSpecsBase> m_gridticsspecs;
};

GridSpecs::GridSpecs()
    : GridSpecsBase("", true)
{
    back();
}

auto GridSpecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << GridSpecsBase::repr();
    for (auto specs : m_gridticsspecs)
        ss << '\n'
           << specs.repr();
    return ss.str();
}

} // namespace sciplot
