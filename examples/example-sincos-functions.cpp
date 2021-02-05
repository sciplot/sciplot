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
    // Create a vector with values from 0 to 5 divived into 200 uniform intervals for the x-axis
    const vec x = linspace(0.0, 5.0, 8);

    // Create a figure
    Figure fig;
    fig.autoclean(false);

    // Change its palette
    fig.palette("dark2");

    fig.samples(200);

    // fig.styleFill().borderHide();

    // Plot two functions
    // fig.draw("exp(-x)*sin(x*10)", "").label("exp(-x)·sin(x*10)").lineColor("gold");
    // fig.draw("'+' using ($1):(sin($1)):(sin($1)**2)", "filledcurves").label("exp(-x)·sin(x*10)").lineColor("gold");
    // fig.drawCurve(x, std::sin(x)).label("sin(x)");
    // fig.drawHistogram(std::cos(x)).label("cos(x)");
    // fig.drawHistogram(std::sin(x)).label("sin(x)");
    fig.drawCurve("test2.dat", 1, 2).label("A");
    // fig.drawCurveWithErrorBarsXY("test2.dat", 1, 2, 7, 8, 5, 6).label("B");
    // fig.drawCurveWithErrorBarsXY("test2.dat", "x", "y", "xlow", "xhigh", "ylow", "yhigh").label("B").xtics("name");

    // Show the plot in a pop-up window
    // fig.show();

    // Save the plot to a PDF file
    fig.save("example-sincos-functions.pdf");
}


// // sciplot includes
// #include <sciplot/sciplot.hpp>
// using namespace sciplot;

// int main(int argc, char** argv)
// {
//     // Create a vector with values from 0 to 5 divived into 200 uniform intervals for the x-axis
//     const vec x = linspace(0.0, 5.0, 200);

//     // Create a plot object
//     plot plt;

//     plt.autoclean(false);

//     // Change its palette
//     plt.palette("dark2");

//     // Plot two functions
//     plt.draw(x, std::sin(x)).label("sin(x)");
//     plt.draw(x, std::cos(x)).label("cos(x)");

//     // Show the plot in a pop-up window
//     plt.show();

//     // Save the plot to a PDF file
//     plt.save("example-sincos-functions.pdf");
// }
