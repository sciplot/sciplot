// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018 Allan Leal
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

// sciplot include for Bessel functions
#include "bessel.hpp"

int main(int argc, char** argv)
{
    // Create a sciplot::plot object
    plot plt;

    // Set the x and y labels
    plt.xlabel("x");
    plt.ylabel("J_v(x)");

    // Plot the Bessel functions of first kind and from 0th to 6th order (already evaluated in sciplot/bessel.hpp).
    plt.draw(x, J0).title("J_0");
    plt.draw(x, J1).title("J_1");
    plt.draw(x, J2).title("J_2");
    plt.draw(x, J3).title("J_3");
    plt.draw(x, J4).title("J_4");
    plt.draw(x, J5).title("J_5");
    plt.draw(x, J6).title("J_6");

    // Show the plot in a pop-up window
    plt.show();

    // Save the plot to a pdf file
    plt.save("example-bessel-functions.pdf");
}
