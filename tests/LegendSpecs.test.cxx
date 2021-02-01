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
#include <sciplot/specs/LegendSpecs.hpp>
using namespace sciplot;

TEST_CASE("LegendSpecs", "[specs]")
{
    auto default_legend = LegendSpecs();
    default_legend.atTopRight();
    default_legend.fontName(internal::DEFAULT_LEGEND_FONTNAME);
    default_legend.fontSize(internal::DEFAULT_LEGEND_FONTSIZE);
    default_legend.title("");
    default_legend.titleFontName(internal::DEFAULT_LEGEND_FONTNAME);
    default_legend.titleFontSize(internal::DEFAULT_LEGEND_FONTSIZE);
    default_legend.displayExpandWidthBy(internal::DEFAULT_LEGEND_FRAME_EXTRA_WIDTH);
    default_legend.displayExpandHeightBy(internal::DEFAULT_LEGEND_FRAME_EXTRA_HEIGHT);
    default_legend.displaySymbolLength(internal::DEFAULT_LEGEND_SAMPLE_LENGTH);
    default_legend.displaySpacing(internal::DEFAULT_LEGEND_SPACING);
    default_legend.displayVertical();
    default_legend.displayLabelsAfterSymbols();
    default_legend.displayJustifyLeft();
    default_legend.displayStartFromFirst();
    default_legend.opaque();

    auto legend = LegendSpecs();

    CHECK( legend.repr() == default_legend.repr() );

    legend.atOutsideBottomRight();
    legend.transparent();

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
        "set key bmargin right noopaque horizontal Right invert "
        "reverse width 13 height 11 samplen 7 spacing 1 enhanced "
        "textcolor 'red' font 'Times,19' title 'Hello' enhanced "
        "textcolor 'blue' font 'Arial,17' left box linetype 3 "
        "linewidth 4 linecolor 'purple' maxrows auto maxcols 5");
}
