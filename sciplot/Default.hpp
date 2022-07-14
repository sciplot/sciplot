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

#pragma once

// C++ includes
#include <cmath>

// sciplot includes
#include <sciplot/Constants.hpp>
#include <sciplot/Enums.hpp>

namespace sciplot
{
namespace internal
{

const auto DEFAULT_FIGURE_HEIGHT = 200; // this is equivalent to 6 inches if 1 in = 72 points
const auto DEFAULT_FIGURE_WIDTH = static_cast<size_t>(std::round(DEFAULT_FIGURE_HEIGHT * GOLDEN_RATIO));
const auto DEFAULT_FIGURE_BOXWIDTH_RELATIVE = 0.9;

const auto SCIPLOT_DEFAULT_PALETTE = "dark2";

const auto DEFAULT_TEXTCOLOR = "#404040";

const auto DEFAULT_LINEWIDTH = 2;
const auto DEFAULT_POINTSIZE = 2;

const auto DEFAULT_FILL_INTENSITY = 1.0;
const auto DEFAULT_FILL_TRANSPARENCY = false;
const auto DEFAULT_FILL_BORDER_LINEWIDTH = 2;

const auto DEFAULT_BORDER_LINECOLOR = "#404040";
const auto DEFAULT_BORDER_LINETYPE = 1;
const auto DEFAULT_BORDER_LINEWIDTH = 2;

const auto DEFAULT_GRID_LINECOLOR = "#d6d7d9";
const auto DEFAULT_GRID_LINEWIDTH = 1;
const auto DEFAULT_GRID_LINETYPE = 1;
const auto DEFAULT_GRID_DASHTYPE = 0;

const auto DEFAULT_LEGEND_TEXTCOLOR = DEFAULT_TEXTCOLOR;
const auto DEFAULT_LEGEND_FRAME_SHOW = false;
const auto DEFAULT_LEGEND_FRAME_LINECOLOR = DEFAULT_GRID_LINECOLOR;
const auto DEFAULT_LEGEND_FRAME_LINEWIDTH = DEFAULT_GRID_LINEWIDTH;
const auto DEFAULT_LEGEND_FRAME_LINETYPE = 1;
const auto DEFAULT_LEGEND_FRAME_EXTRA_WIDTH = 0;
const auto DEFAULT_LEGEND_FRAME_EXTRA_HEIGHT = 1;
const auto DEFAULT_LEGEND_SPACING = 1;
const auto DEFAULT_LEGEND_SAMPLE_LENGTH = 4;

const auto DEFAULT_TICS_MIRROR = false;
const auto DEFAULT_TICS_ROTATE = false;
const auto DEFAULT_TICS_SCALE_MAJOR_BY = 0.50;
const auto DEFAULT_TICS_SCALE_MINOR_BY = 0.25;
const auto DEFAULT_TICS_MINOR_SHOW = false;

} // namespace internal
} // namespace sciplot
