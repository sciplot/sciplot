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
    // Create a vector with values from 0 to 100 divived into 2000 uniform intervals for the z-axis
    Vec z = linspace(0.0, 100.0, 2000);

    // Construct x and y for each z so that a helix curve is defined
    std::vector<double> x,y;
    double c = 2;
    double r = 1;

    for(auto val : z) {
        x.push_back(r*cos(val/c));
        y.push_back(r*sin(val/c));
    }

    // Create a Plot3D object
    Plot3D plot;

    // Set the x, y, z labels
    plot.xlabel("x");
    plot.ylabel("y");
    plot.zlabel("z");

    // Clear all borders and set the visible ones
    plot.border().clear();
    plot.border().bottomLeftFront();
    plot.border().bottomRightFront();
    plot.border().leftVertical();

    // This disables the deletion of the created gnuplot script and data file.
    plot.autoclean(false);

    // Change its palette
    plot.palette("dark2");

    // Draw the helix curve
    plot.drawCurve(x, y, z).label("helix").lineColor("orange");

    // Show the plot in a pop-up window
    plot.show();

    // Save the plot to a PDF file
    plot.save("example-3d-helix.pdf");
}
