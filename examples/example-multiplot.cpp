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

int main(int argc, char** argv)
{
    // Create a vector with values from 0 to 5 divived into 200 uniform intervals for the x-axis
    const vec x = linspace(0.0, 5.0, 200);

    // Create 4 different plots
    plot p0;
    p0.draw(x, std::sin(x)).title("sin(x)");
    p0.draw(x, std::cos(x)).title("cos(x)");
    plot p1;
    p1.draw(x, std::cos(x)).title("cos(x)");
    plot p2;
    p2.draw(x, std::tan(x)).title("tan(x)");
    plot p3;
    p3.draw(x, std::sqrt(x)).title("sqrt(x)");

    // Create multiplot to add the plots, set title, palette and 2x2 layout
    multiplot mp;
    mp.title("Example - Multiplot");
    mp.palette("dark2");
    mp.layout(2, 2);

    // Add plots to multiplot
    mp.add(p0).add(p1).add(p2).add(p3);

    // Show the multiplot in a pop-up window
    mp.show();
    // Save the multiplot to files
    mp.save("example-multiplot.pdf");
    mp.save("example-multiplot.svg");
}
