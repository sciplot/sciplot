// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2021 Allan Leal, Bim Overbohm
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

// sciplot includes
#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main(int argc, char** argv)
{
    // Create a vector with values from 0 to 5 divived into 200 uniform intervals for the x-axis
    Vec x = linspace(0.0, 5.0, 200);

    // Create some plots and draw curves
    Plot2D plot0;
    plot0.drawCurve(x, std::sin(x)).label("sin(x)");
    Plot2D plot1;
    plot1.drawCurve(x, std::cos(x)).label("cos(x)");

    // Use the previous plots as sub-figures in a larger figure. Note that
    // plot0 and plot1 will be deep-copied into fig
    Figure fig = {{plot0, plot1}};

    // This will NOT change the plot in fig, only plot0
    plot0.drawCurve(x, std::tan(x)).label("tan(x)");

    // Get a reference to the copy of plot1 in fig. This gets the generic base
    // class Plot supports methods common to Plot2D and Plot3D
    auto& plotref = fig.get(1, 0);
    // This will modify the plot in fig, but NOT plot1
    plotref.grid().show();

    // Get a reference to the copy of plot0 in fig. This gets the Plot2D
    // version to provide 2D-specific drawing functions
    auto& plot2dref = fig.get<Plot2D>(0, 0);
    // This will modify the plot in fig, but NOT plot0
    plot2dref.drawCurve(x, std::sqrt(x)).label("sqrt(x)");

    // Set figure title and palette
    fig.title("Getting plots from figures");
    fig.palette("dark2");

    // Create canvas to hold figure
    Canvas canvas = {{fig}};
    // Set output canvas size to 750x750 pixels
    canvas.size(750, 750);

    // Show the plot in a pop-up window
    canvas.show();

    // Save the figure to a svg file
    canvas.save("example-plot-get.svg");
}
