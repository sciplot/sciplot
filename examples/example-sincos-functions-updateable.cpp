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

// time and thread includes for the delay
#include <thread>
#include <chrono>

// sciplot includes
#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main(int argc, char** argv)
{
    // Create a vector with values from 0 to 5 divived into 200 uniform intervals for the x-axis
    Vec x = linspace(0.0, 5.0, 50);

    // Create a Plot object
    Plot plot;

    // Set autoscaling and hide the legend as we're plotting single points (will clutter the plot window)
    plot.xrange("*", "*");
    plot.yrange("*", "*");
    plot.legend().hide();
 
    // This disables the deletion of the created gnuplot script and data file.
    plot.autoclean(false);

    // Change its palette
    plot.palette("dark2");

    // Plot two functions
    for (auto i: x){
        plot.drawPoints(Vec({i}), Vec({std::sin(i)})).pointType(0);
        plot.drawPoints(Vec({i}), Vec({std::cos(i)})).pointType(1);
        
        // show plot window and update its contents 
        plot.show(true);

        // the delay is only to showcase the dynamic updates
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

}
