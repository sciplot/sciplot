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
    // Create a vector with values from 0 to pi divived into 200 uniform intervals for the x-axis
    Vec x = linspace(0.0, PI, 200);

    // Create a Plot object
    Plot2D plot;

    // Set the x and y labels
    plot.xlabel("x");
    plot.ylabel("y");

    // Set the x and y ranges
    plot.xrange(0.0, PI);
    plot.yrange(0.0, 1.0);

    // Set the legend to be on the bottom along the horizontal
    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);

    // Plot sin(i*x) from i = 1 to i = 6
    plot.drawCurve(x, std::sin(1.0 * x)).label("sin(x)");
    plot.drawCurve(x, std::sin(2.0 * x)).label("sin(2x)");
    plot.drawCurve(x, std::sin(3.0 * x)).label("sin(3x)");
    plot.drawCurve(x, std::sin(4.0 * x)).label("sin(4x)");
    plot.drawCurve(x, std::sin(5.0 * x)).label("sin(5x)");
    plot.drawCurve(x, std::sin(6.0 * x)).label("sin(6x)");

    // Show the plot in a pop-up window
    plot.show();

    // Save the plot to a PDF file
    plot.save("example-sine-functions.pdf");
}
