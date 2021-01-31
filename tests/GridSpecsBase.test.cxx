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

// Catch includes
#include <tests/catch.hpp>

// sciplot includes
#include <sciplot/specs/GridSpecsBase.hpp>
using namespace sciplot;

TEST_CASE("GridSpecsBase", "[specs]")
{
    auto defaultgrid = GridSpecsBase();
    defaultgrid.show(true);
    defaultgrid.back();
    defaultgrid.lineColor(internal::DEFAULT_GRID_LINECOLOR);
    defaultgrid.lineWidth(internal::DEFAULT_GRID_LINEWIDTH);
    defaultgrid.lineType(internal::DEFAULT_GRID_LINETYPE);
    defaultgrid.dashType(internal::DEFAULT_GRID_DASHTYPE);

    SECTION("Using constructor GridSpecsBase()")
    {
        auto grid = GridSpecsBase();

        CHECK( grid.repr() == defaultgrid.repr() );

        grid.show(true);
        grid.front();
        grid.lineStyle(7);
        grid.lineType(4);
        grid.lineWidth(5);
        grid.lineColor("red");
        grid.dashType(9);

        CHECK( grid.repr() == "set grid front linestyle 7 linetype 4 linewidth 5 linecolor 'red' dashtype 9" );
    }

    const auto majortics = true;
    const auto minortics = false;

    SECTION("Using constructor GridSpecsBase(ticsname, true===majortics)")
    {
        auto xtics_major_grid = GridSpecsBase("xtics", majortics);
        xtics_major_grid.show(true);
        xtics_major_grid.front();
        xtics_major_grid.lineStyle(2);
        xtics_major_grid.lineType(6);
        xtics_major_grid.lineWidth(1);
        xtics_major_grid.lineColor("black");
        xtics_major_grid.dashType(3);

        CHECK( xtics_major_grid.repr() == "set grid xtics front linestyle 2 linetype 6 linewidth 1 linecolor 'black' dashtype 3" );

        xtics_major_grid.show(false);

        CHECK( xtics_major_grid.repr() == "set grid noxtics" );
    }

    SECTION("Using constructor GridSpecsBase(ticsname, false===minortics)")
    {
        auto ytics_minor_grid = GridSpecsBase("mytics", minortics);
        ytics_minor_grid.show(true);
        ytics_minor_grid.back();
        ytics_minor_grid.lineStyle(6);
        ytics_minor_grid.lineType(2);
        ytics_minor_grid.lineWidth(11);
        ytics_minor_grid.lineColor("purple");
        ytics_minor_grid.dashType(13);

        // Note the comma below. This is because the line properties correspond to grid lines of minor tics. See documentation of `set grid` in Gnuplot manual.
        CHECK( ytics_minor_grid.repr() == "set grid mytics back , linestyle 6 linetype 2 linewidth 11 linecolor 'purple' dashtype 13" );

        ytics_minor_grid.show(false);

        CHECK( ytics_minor_grid.repr() == "set grid nomytics" );
    }
}
