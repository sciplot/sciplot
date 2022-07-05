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
#include <sciplot/specs/DrawSpecs.hpp>
using namespace sciplot;

TEST_CASE("DrawSpecs", "[specs]")
{
    auto specs = DrawSpecs("'file.dat'", "1:2", "lines");

    CHECK( specs.repr() == "'file.dat' using 1:2 with lines linewidth 2" );

    specs.label("SuperData");
    CHECK( specs.repr() == "'file.dat' using 1:2 title 'SuperData' with lines linewidth 2" );

    specs.labelDefault();
    CHECK( specs.repr() == "'file.dat' using 1:2 with lines linewidth 2" );

    specs.labelFromColumnHeader();
    CHECK( specs.repr() == "'file.dat' using 1:2 title columnheader with lines linewidth 2" );

    specs.labelFromColumnHeader(3);
    CHECK( specs.repr() == "'file.dat' using 1:2 title columnheader(3) with lines linewidth 2" );

    specs.label("OnlyData");
    CHECK( specs.repr() == "'file.dat' using 1:2 title 'OnlyData' with lines linewidth 2" );

    specs.lineWidth(3);
    specs.lineColor("orange");
    CHECK( specs.repr() == "'file.dat' using 1:2 title 'OnlyData' with lines linewidth 3 linecolor 'orange'" );

    specs.ytics(9);
    CHECK( specs.repr() == "'file.dat' using 1:2:ytic(stringcolumn(9)) title 'OnlyData' with lines linewidth 3 linecolor 'orange'" );

    specs.xtics("Country");
    CHECK( specs.repr() == "'file.dat' using 1:2:xtic(stringcolumn('Country')):ytic(stringcolumn(9)) title 'OnlyData' with lines linewidth 3 linecolor 'orange'" );
}
