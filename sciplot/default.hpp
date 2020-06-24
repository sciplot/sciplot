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

#pragma once

// sciplot includes
#include <sciplot/constants.hpp>
#include <sciplot/enums.hpp>

namespace sciplot {
namespace internal {

const auto DEFAULT_FIGURE_HEIGHT = 200; // this is equivalent to 6 inches if 1 in = 72 points
const auto DEFAULT_FIGURE_WIDTH = DEFAULT_FIGURE_HEIGHT * GOLDEN_RATIO;

const auto DEFAULT_PALETTE = "dark2";

const auto DEFAULT_FONTNAME = "Georgia";
const auto DEFAULT_FONTSIZE = 12;

const auto DEFAULT_TEXTCOLOR = "#404040";

const auto DEFAULT_PLOTSTYLE = plotstyle::lines;
const auto DEFAULT_LINEWIDTH = 2;

const auto DEFAULT_BORDER_LINECOLOR = "#404040";
const auto DEFAULT_BORDER_LINETYPE = 1;
const auto DEFAULT_BORDER_LINEWIDTH = 2;

const auto DEFAULT_GRID_LINECOLOR = "#d6d7d9";
const auto DEFAULT_GRID_LINEWIDTH = 1;
const auto DEFAULT_GRID_LINETYPE = 1;
const auto DEFAULT_GRID_DASHTYPE = 0;

const auto DEFAULT_LEGEND_TEXTCOLOR = DEFAULT_TEXTCOLOR;
const auto DEFAULT_LEGEND_LINECOLOR = DEFAULT_GRID_LINECOLOR;
const auto DEFAULT_LEGEND_LINEWIDTH = DEFAULT_GRID_LINEWIDTH;
const auto DEFAULT_LEGEND_LINETYPE = 1;
const auto DEFAULT_LEGEND_FONTNAME = DEFAULT_FONTNAME;
const auto DEFAULT_LEGEND_FONTSIZE = 10;
const auto DEFAULT_LEGEND_SPACING = 1;
const auto DEFAULT_LEGEND_SAMPLE_LENGTH = 4;

} // namespace internal
} // namespace sciplot
