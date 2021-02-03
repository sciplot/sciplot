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

TEST_CASE("DrawSpecsWithLineProps", "[specs]")
{
    auto default_specs = DrawSpecsWithLineProps("file.dat", "lines");
    default_specs.lineWidth(internal::DEFAULT_LINEWIDTH);

    auto specs = DrawSpecsWithLineProps("file.dat", "lines");
    CHECK( specs.repr() == default_specs.repr() );

    specs.xcolumn(1);
    specs.ycolumn("City");

    CHECK( specs.repr() ==
        "'file.dat' using 1:'City':xtic(stringcolumn(1)):ytic(stringcolumn('City')) "
        "with lines linewidth 2" );

    specs.lineWidth(3);
    specs.lineColor("orange");

    CHECK( specs.repr() ==
        "'file.dat' using 1:'City':xtic(stringcolumn(1)):ytic(stringcolumn('City')) "
        "with lines linewidth 3 linecolor 'orange'" );

    specs.label("SuperFig");
    specs.xcolumn("State");
    specs.ycolumn(7);
    specs.xtic("Country");
    specs.ytic(9);

    CHECK( specs.repr() ==
        "'file.dat' using 'State':7:xtic(stringcolumn('Country')):ytic(stringcolumn(9)) "
        "title 'SuperFig' with lines linewidth 3 linecolor 'orange'" );
}

TEST_CASE("DrawSpecsWithPointProps", "[specs]")
{
    auto specs = DrawSpecsWithPointProps("file.dat", "points");

    CHECK( specs.repr() == "'file.dat' using 0:1 with points" );

    specs.labelFromColumnHeader();
    specs.pointSize(3);
    specs.pointType(7);
    specs.xcolumn(1);
    specs.ycolumn("City");

    CHECK( specs.repr() ==
        "'file.dat' using 1:'City':xtic(stringcolumn(1)):ytic(stringcolumn('City')) "
        "title columnheader with points pointtype 7 pointsize 3" );

    specs.labelFromColumnHeader(13);
    specs.xcolumn("State");
    specs.ycolumn(7);
    specs.xtic("Country");
    specs.ytic(9);

    CHECK( specs.repr() ==
        "'file.dat' using 'State':7:xtic(stringcolumn('Country')):ytic(stringcolumn(9)) "
        "title columnheader(13) with points pointtype 7 pointsize 3" );
}
