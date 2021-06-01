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

auto createHelixPlot()
{
    // Create a vector with values from 0 to 100 divived into 2000 uniform intervals for the z-axis
    Vec z = linspace(0.0, 100.0, 2000);

    // Construct x and y for each z so that a helix curve is defined
    std::vector<double> x, y;
    double c = 2;
    double r = 1;

    for (auto val : z)
    {
        x.push_back(r * cos(val / c));
        y.push_back(r * sin(val / c));
    }

    // Create the 3D plot for the helix
    Plot3D plot;

    // Draw the helix curve and set the label displayed in the legend
    plot.drawCurve(x, y, z);

    // Disable legend for this plot
    plot.legend().hide();

    // Set the x, y, z labels
    plot.xlabel("x");
    plot.ylabel("y");
    plot.zlabel("z");

    // Clear all borders and set the visible ones
    plot.border().clear();
    plot.border().bottomLeftFront();
    plot.border().bottomRightFront();
    plot.border().leftVertical();

    return plot;
}

int main(int argc, char** argv)
{
    // Create a vector with values from 0 to 5 divived into 200 uniform intervals for the x-axis
    Vec x = linspace(0.0, 5.0, 200);

    // Create 4 different plots
    Plot2D plot0;
    plot0.drawCurve(x, std::sin(x)).label("sin(x)");
    plot0.drawCurve(x, std::cos(x)).label("cos(x)");

    Plot2D plot1;
    plot1.drawCurve(x, std::cos(x)).label("cos(x)");

    Plot2D plot2;
    plot2.drawCurve(x, std::tan(x)).label("tan(x)");

    Plot3D plot3 = createHelixPlot();

    // Use the previous plots as sub-figures in a larger 2x2 figure.
    Figure fig = {{plot0, plot1},
                  {plot2, plot3}};

    fig.size(600, 600);
    fig.title("Mixing 2D and 3D plots");
    fig.palette("dark2");
    fig.show();

    // Save the figure to a PDF file
    fig.save("example-multiplot-mixed.pdf");
}
