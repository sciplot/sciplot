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
        "set key inside right top noopaque vertical Left "
        "noinvert reverse width 0 height 0 samplen 4 spacing 1 "
        "enhanced textcolor '#404040' font 'Georgia,10' "
        "nobox maxrows auto maxcols auto");

    legend.atOutsideBottomRight();
    legend.opaque();

    // Customize frame
    legend.frameShow();
    legend.frameLineColor("purple");
    legend.frameLineType(3);
    legend.frameLineWidth(4);

    // Customize display of labels and symbols
    legend.displayHorizontal();
    legend.displayHorizontalMaxCols(5);
    legend.displaySymbolLength(7);
    legend.displayExpandHeightBy(11);
    legend.displayExpandWidthBy(13);
    legend.displayStartFromLast();
    legend.displayLabelsAfterSymbols();
    legend.displayJustifyRight();

    // Customize title
    legend.title("Hello");
    legend.titleFontName("Arial");
    legend.titleFontSize(17);
    legend.titleTextColor("blue");
    legend.titleLeft();
    legend.textColor("red").fontName("Times").fontSize(19);

    CHECK( legend.repr() ==
        "set key bmargin right opaque horizontal Right invert "
        "reverse width 13 height 11 samplen 7 spacing 1 enhanced "
        "textcolor 'red' font 'Times,19' title 'Hello' enhanced "
        "textcolor 'blue' font 'Arial,17' left box linetype 3 "
        "linewidth 4 linecolor 'purple' maxrows auto maxcols 5");
}
