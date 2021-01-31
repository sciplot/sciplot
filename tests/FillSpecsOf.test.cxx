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
    auto default_fillspecs = FillSpecs();
    default_fillspecs.fillSolid();
    default_fillspecs.fillIntensity(internal::DEFAULT_FILL_INTENSITY);
    default_fillspecs.fillTransparent(internal::DEFAULT_FILL_TRANSPARENCY);
    default_fillspecs.borderLineWidth(internal::DEFAULT_FILL_BORDER_LINEWIDTH);
    default_fillspecs.borderHide();

    auto fillspecs = FillSpecs();

    CHECK( fillspecs.repr() == default_fillspecs.repr() );
    CHECK( fillspecs.repr() == "fillstyle solid 1 noborder");

    fillspecs.borderShow();
    fillspecs.borderLineColor("red");

    CHECK( fillspecs.repr() == "fillstyle solid 1 border linecolor 'red' linewidth 2");

    fillspecs.borderLineColor("blue");
    fillspecs.borderLineWidth(7);

    CHECK( fillspecs.repr() == "fillstyle solid 1 border linecolor 'blue' linewidth 7");

    fillspecs.fillColor("pink");

    CHECK( fillspecs.repr() == "fillcolor 'pink' fillstyle solid 1 border linecolor 'blue' linewidth 7");

    fillspecs.fillIntensity(0.7);

    CHECK( fillspecs.repr() == "fillcolor 'pink' fillstyle solid 0.7 border linecolor 'blue' linewidth 7");

    fillspecs.fillIntensity(1.7);

    CHECK( fillspecs.repr() == "fillcolor 'pink' fillstyle solid 1 border linecolor 'blue' linewidth 7");

    fillspecs.fillIntensity(-0.2);

    CHECK( fillspecs.repr() == "fillcolor 'pink' fillstyle solid 0 border linecolor 'blue' linewidth 7");

    fillspecs.fillTransparent();

    CHECK( fillspecs.repr() == "fillcolor 'pink' fillstyle transparent solid 0 border linecolor 'blue' linewidth 7");

    fillspecs.fillPattern(3);

    CHECK( fillspecs.repr() == "fillcolor 'pink' fillstyle transparent pattern 3 border linecolor 'blue' linewidth 7");

    fillspecs.fillTransparent(false);
    fillspecs.borderHide();

    CHECK( fillspecs.repr() == "fillcolor 'pink' fillstyle pattern 3 noborder");
}
