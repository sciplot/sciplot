// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2020 Allan Leal
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

int main(int argc, char **argv)
{
    // Create a vector with x values
    std::vector<std::string> x = {"strings", "as", "tick", "labels"};

    // Create a vector with y values
    std::vector<float> y = {4, 2, 5, 1};

    // Create a sciplot::plot object
    plot plt;

    // Set a plot legend
    plt.legend().header("Example - Plotting boxes");

    // Set the x and y labels
    plt.xlabel("x");
    plt.ylabel("y");

    // Add values to plot
    auto &specs = plt.draw(x, y);
    // plot y values from data column 2, and the x-axis ticks from column 1
    specs.use(plotspecs::USE_AUTO, 2, plotspecs::USE_AUTO, 1);
    // makes sure we plot boxes
    specs.with(sciplot::plotstyle::boxes);
    // and set the the fill style to a solid fill
    specs.fillstyle(sciplot::fillstyle::solid);
    // Set a proper title for the plot
    specs.title("Plot title");

    // Adjust the relative width of the boxes
    plt.boxwidth(sciplot::boxwidthtype::relative, 0.75F);

    // Show the plot in a pop-up window
    plt.show();

    // Save the plot to a pdf file
    plt.save("example-boxes.pdf");
}
