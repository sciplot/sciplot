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

// sciplot includes
#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main(int argc, char** argv)
{
    // Create three vectors, each one for x and y values, and a third one containing the color code for each point
    Vec x = linspace(0, 9, 9);
    Vec y = {1, 1, 2, 2, 3, 3, 2, 1, 1, 1};
    Vec c = {0, 0, 1, 1, 2, 2, 1, 0, 0, 0};

    // Create the data file
    std::string plotDataFile = "custom_plot_data.dat";
    std::ofstream p(plotDataFile);

    // Fill the data file with the values from the vectors
    for (size_t i = 0; i < x.size(); i++)
        p << x[i] << " " << y[i] << " " << y[i] + 2 << " " << c[i] << std::endl;

    // Create the plot
    Plot plot;

    // Enable the use of custom draw commands
    plot.useCustomDrawCmds();

    // Some extra settings for this example (no legend, no colorbox, custom palette)
    plot.legend().hide();
    plot.gnuplot("unset colorbox");
    plot.gnuplot("set palette defined (0 'green', 1 'yellow', 2 'red')");

    // Create the custom draw commands
    plot.drawCustom("'" + plotDataFile + "' using 1:2:4 with points pointsize 2 pointtype 5 palette");
    plot.drawCustom("'" + plotDataFile + "' using 1:3:4 with points pointsize 2 pointtype 7 palette");

    // Show the plot in a pop-up window
    plot.show();

    // OPTIONAL: If any non-custom commands are to be plotted, the custom ones have to be disabled
    plot.useCustomDrawCmds(false);

    // This plot does not include the custom plot commands
    plot.drawCurveWithPoints(x, y);

    plot.show();
}
