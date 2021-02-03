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
#include <sciplot/specs/HistogramSpecs.hpp>
using namespace sciplot;

TEST_CASE("HistogramSpecsWithLineProps", "[specs]")
{
    auto specs = HistogramSpecs();

    CHECK( specs.repr() == "set style histogram" );

    specs.clustered();
    CHECK( specs.repr() == "set style histogram clustered" );

    specs.clusteredWithGap(0.92);
    CHECK( specs.repr() == "set style histogram clustered gap 0.92" );

    specs.errorBars();
    CHECK( specs.repr() == "set style histogram errorbars" );

    specs.errorBarsWithGap(0.56);
    CHECK( specs.repr() == "set style histogram errorbars gap 0.56" );

    specs.errorBarsWithLineWidth(1.6);
    CHECK( specs.repr() == "set style histogram errorbars gap 0.56 linewidth 1.6" );

    specs.rowStacked();
    CHECK( specs.repr() == "set style histogram rowstacked" );

    specs.columnStacked();
    CHECK( specs.repr() == "set style histogram columnstacked" );
}
