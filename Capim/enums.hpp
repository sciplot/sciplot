// A modern C++ interface for plotting using gnuplot
// https://github.com/allanleal/plot
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

// C++ includes
#include <string>

namespace Capim {

/// All gnuplot style options for plotting data
enum class style
{
    lines,
    points,
    linespoints,
    impulses,
    dots,
    steps,
    fsteps,
    histeps,
    errorbars,
    labels,
    xerrorbars,
    yerrorbars,
    xyerrorbars,
    errorlines,
    xerrorlines,
    yerrorlines,
    xyerrorlines,
    boxes,
    histograms,
    filledcurves,
    boxerrorbars,
    boxxyerrorbars,
    financebars,
    candlesticks,
    vectors,
    image,
    rgbimage,
    pm3d,
};

/// All extension formats supported by Capim when saving a plot to a file.
enum class ext
{
    emf,
    png,
    svg,
    pdf,
    eps
};

namespace internal {

/// Return a string for a given enum value of type `with`
inline auto stylestr(style value) -> std::string
{
    switch(value) {
    case style::lines: return "lines";
    case style::points: return "points";
    case style::linespoints: return "linespoints";
    case style::impulses: return "impulses";
    case style::dots: return "dots";
    case style::steps: return "steps";
    case style::fsteps: return "fsteps";
    case style::histeps: return "histeps";
    case style::errorbars: return "errorbars";
    case style::labels: return "labels";
    case style::xerrorbars: return "xerrorbars";
    case style::yerrorbars: return "yerrorbars";
    case style::xyerrorbars: return "xyerrorbars";
    case style::errorlines: return "errorlines";
    case style::xerrorlines: return "xerrorlines";
    case style::yerrorlines: return "yerrorlines";
    case style::xyerrorlines: return "xyerrorlines";
    case style::boxes: return "boxes";
    case style::histograms: return "histograms";
    case style::filledcurves: return "filledcurves";
    case style::boxerrorbars: return "boxerrorbars";
    case style::boxxyerrorbars: return "boxxyerrorbars";
    case style::financebars: return "financebars";
    case style::candlesticks: return "candlesticks";
    case style::vectors: return "vectors";
    case style::image: return "image";
    case style::rgbimage: return "rgbimage";
    case style::pm3d: return "pm3d";
    default: return "lines";
    }
}

} // namespace internal
} // namespace Capim
