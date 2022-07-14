// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2022 Allan Leal, Bim Overbohm
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

    // Create 2 different plots
    Plot2D plot0;
    plot0.drawCurve(x, std::sin(x)).label("sin(x)");
    plot0.drawCurve(x, std::cos(x)).label("cos(x)");

    Plot2D plot1;
    plot1.drawCurve(x, std::cos(x)).label("cos(x)");

    // Use the plots in a 2x1 figure
    Figure fig1 = {{plot0, plot1}};
    fig1.title("1st figure");
    fig1.layout().origin(0.0, 0.5);
    fig1.layout().size(0.5, 0.5);

    // Use the plots in a 2x1 figure
    Figure fig2 = {{plot0, plot1}};
    fig2.title("2nd figure");
    // no margin left and right, default margins top and bottom
    fig2.layout().marginsAbsolute(0, 0, -1, -1);

    // Create canvas to hold figures
    Canvas canvas = {{fig1, fig2}};
    // Set canvas title. this only works for windows atm
    canvas.title("Canvas title");

    // Show the plot in a pop-up window
    // Note that this will only show the last figure
    canvas.show();

    // Save the figure to a PDF file
    // Note that the figures will go to successive pages
    canvas.save("example-figures-layout.pdf");
}
