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
    const Vec x = linspace(0.0, PI, 200);

    // Create a Figure object
    Figure fig;

    // Set the x and y labels
    fig.xlabel("x");
    fig.ylabel("y");

    // Set the x and y ranges
    fig.xrange(0.0, PI);
    fig.yrange(0.0, 6.0);

    // Plot i*sin(x) from i = 1 to i = 6
    for (auto i = 1; i <= 6; ++i)
        fig.drawCurve(x, i * std::sin(x)).label(std::to_string(i) + "⋅sin(x)");

    // Show the figure in a pop-up window
    fig.show();

    // Save the figure to a PDF file
    fig.save("example-sine-functions.pdf");
}
