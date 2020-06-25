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

// Catch includes
#include <tests/catch.hpp>

// sciplot includes
#include <sciplot/plot.hpp>
using namespace sciplot;

TEST_CASE("plotting tests", "[plot]")
{
    SECTION("########## AUXILIARY FUNCTIONS ##########")
    {
        REQUIRE(titlestr("Something") == "'Something'");
        REQUIRE(titlestr("columnheader") == "columnheader");

        REQUIRE(optionvaluestr("title", "'sin(x)'") == "title 'sin(x)' ");
        REQUIRE(optionvaluestr("ls", "") == "");
    }

    plot plt;

    std::vector<double> x = {1,2,3,4,5,6};
    std::vector<double> y = {1,2,2,3,3,4};

    plt.palette("dark2");
    plt.xlabel("Temperature [K]");
    plt.ylabel("Amount [mol]");
//    plt.legend().maxrows(2);
//    plt.legend().maxcols(2);
//    plt.gnuplot("set mxtics 4");
//    plt.legend().box().show(false);
//    plt.legend().title("{/:Bold Legend}").fontsize(10);
//    plt.grid("xtics ytics").linecolor(rgb("#EEEEEE")).linetype(1).dashtype(5);

//    plt.gnuplot("unset grid");

//    plt.border().clear().left().top().behind();

//    plt.legend().titles().leftsiderightjustified();

    plt.xrange(0, 3);
    for(auto i = 1; i <= 7; ++i)
        plt.draw(str(i) + " * sin(x)").title("line_" + str(i)).dashtype(i);

    plt.show();
    plt.save("xy.svg");
}
