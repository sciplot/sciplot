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

// Catch includes
#include <tests/catch.hpp>

// sciplot includes
#include <sciplot/specs/LegendSpecs.hpp>
using namespace sciplot;

TEST_CASE("LegendSpecs", "[specs]")
{
    auto legend = LegendSpecs();

    CHECK( legend.repr() ==
        "set key inside right top noopaque nobox vertical Left "
        "noinvert reverse width 0 height 0 samplen 4 spacing 1 "
        "enhanced textcolor '#404040' font 'Georgia,10' title '' "
        "enhanced textcolor '#404040' font 'Georgia,10' maxrows auto maxcols auto" );

    legend.atOutsideBottomRight();
    legend.opaque();
    legend.border().show().lineColor("purple").lineType(3).lineWidth(4);
    legend.horizontalDisplay();
    legend.horizontalMaxCols(5);
    legend.symbolLength(7);
    legend.incrementHeight(11);
    legend.incrementWidth(13);
    legend.startFromLast();
    legend.labelsAfterSymbols();
    legend.labelsRightJustify();
    legend.header("Hello").fontName("Arial").fontSize(17).textColor("blue");
    legend.textColor("red").fontName("Times").fontSize(19);

    CHECK( legend.repr() ==
        "set key bmargin right opaque box linetype 3 linewidth 4 linecolor 'purple' "
        "horizontal Right invert reverse width 13 height 11 samplen 7 spacing 1 "
        "enhanced textcolor 'red' font 'Times,19' title 'Hello' enhanced "
        "textcolor 'blue' font 'Arial,17' maxrows auto maxcols 5" );
}
