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
    // Create a vector with the xtic labels for the boxes
    Strings names = {"John", "Peter", "Thomas", "Marta"};

    // Create a vector with the y values for the boxes
    Vec ages = {44, 27, 35, 20};

    // Create a vector with the xwidth values for the boxes
    Vec experiences = {0.8, 0.4, 0.7, 0.9};

    // Create a Plot object
    Plot plot;

    // Set the legend to the top left corner of the plot
    plot.legend().atTopLeft();

    // Set the y label and its range
    plot.ylabel("Age");
    plot.yrange(0.0, 50);

    // Plot the boxes using y values.
    plot.drawBoxes(names, ages, experiences)
        .fillSolid()
        .fillColor("pink")
        .fillIntensity(0.5)
        .borderShow()
        .labelNone();

    // Adjust the relative width of the boxes
    plot.boxWidthRelative(0.75);

    plot.autoclean(false);

    // Show the plot in a pop-up window
    plot.show();

    // Save the plot to a PDF file
    plot.save("example-boxes-ticklabels.pdf");
}
