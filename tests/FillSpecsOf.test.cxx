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
#include <sciplot/specs/FillSpecsOf.hpp>
using namespace sciplot;

TEST_CASE("FillSpecs", "[specs]")
{
    auto specs = FillSpecs();

    CHECK( specs.repr() == "" );

    specs.fillEmpty();
    CHECK( specs.repr() == "fillstyle empty");

    specs.fillSolid();
    CHECK( specs.repr() == "fillstyle solid");

    specs.fillIntensity(0.83);
    CHECK( specs.repr() == "fillstyle solid 0.83");

    specs.fillTransparent();
    CHECK( specs.repr() == "fillstyle transparent solid 0.83");

    specs.fillEmpty();
    specs.fillIntensity(0.24);
    CHECK( specs.repr() == "fillstyle transparent solid 0.24");

    specs.fillEmpty();
    specs.fillTransparent();
    CHECK( specs.repr() == "fillstyle empty");

    specs.fillPattern(23);
    CHECK( specs.repr() == "fillstyle transparent pattern 23");

    specs.fillTransparent(false);
    CHECK( specs.repr() == "fillstyle pattern 23");

    specs.fillColor("white");
    CHECK( specs.repr() == "fillcolor 'white' fillstyle pattern 23");

    specs.borderShow();
    CHECK( specs.repr() == "fillcolor 'white' fillstyle pattern 23 border");

    specs.borderLineColor("red");
    CHECK( specs.repr() == "fillcolor 'white' fillstyle pattern 23 border linecolor 'red'");

    specs.borderLineWidth(2);
    CHECK( specs.repr() == "fillcolor 'white' fillstyle pattern 23 border linecolor 'red' linewidth 2");

    specs.borderHide();
    CHECK( specs.repr() == "fillcolor 'white' fillstyle pattern 23 noborder");

    specs.fillEmpty();
    specs.fillIntensity(0.7);
    CHECK( specs.repr() == "fillcolor 'white' fillstyle solid 0.7 noborder");

    specs.fillIntensity(1.7);
    CHECK( specs.repr() == "fillcolor 'white' fillstyle solid 1 noborder");

    specs.fillIntensity(-0.2);
    CHECK( specs.repr() == "fillcolor 'white' fillstyle solid 0 noborder");
}
