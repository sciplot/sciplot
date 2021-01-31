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
#include <sciplot/specs/GridSpecs.hpp>
using namespace sciplot;

TEST_CASE("GridSpecs", "[specs]")
{
    auto grid = GridSpecs();

    CHECK( grid.repr() == "unset grid" );

    grid.show();
    grid.front();
    grid.lineColor("ocean");
    grid.lineWidth(1);
    grid.lineType(3);
    grid.dashType(5);

    CHECK( grid.repr() == "set grid front linetype 3 linewidth 1 linecolor 'ocean' dashtype 5" );

    grid.xticsMajorBottom().front().lineColor("red");
    grid.xticsMajorTop().back().lineColor("black");
    grid.yticsMajorLeft().front().lineColor("purple");
    grid.yticsMajorRight().back().lineColor("green");
    grid.xticsMinorBottom().front().lineColor("white");
    grid.xticsMinorTop().back().lineColor("gray");
    grid.yticsMinorLeft().front().lineColor("orange");
    grid.yticsMinorRight().back().lineColor("lime");

    CHECK( grid.repr() == "set grid front linetype 3 linewidth 1 linecolor 'ocean' dashtype 5\n"
                          "set grid xtics front linetype 1 linewidth 1 linecolor 'red' dashtype 0\n"
                          "set grid x2tics back linetype 1 linewidth 1 linecolor 'black' dashtype 0\n"
                          "set grid ytics front linetype 1 linewidth 1 linecolor 'purple' dashtype 0\n"
                          "set grid y2tics back linetype 1 linewidth 1 linecolor 'green' dashtype 0\n"
                          "set grid mxtics front , linetype 1 linewidth 1 linecolor 'white' dashtype 0\n"
                          "set grid mx2tics back , linetype 1 linewidth 1 linecolor 'gray' dashtype 0\n"
                          "set grid mytics front , linetype 1 linewidth 1 linecolor 'orange' dashtype 0\n"
                          "set grid my2tics back , linetype 1 linewidth 1 linecolor 'lime' dashtype 0");
}
