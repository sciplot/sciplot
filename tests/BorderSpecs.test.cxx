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
#include <sciplot/specs/BorderSpecs.hpp>
using namespace sciplot;

TEST_CASE("BorderSpecs", "[specs]")
{
    auto defaultborder = BorderSpecs();
    defaultborder.left();
    defaultborder.bottom();
    defaultborder.linetype(internal::DEFAULT_BORDER_LINETYPE);
    defaultborder.linewidth(internal::DEFAULT_BORDER_LINEWIDTH);
    defaultborder.linecolor(internal::DEFAULT_BORDER_LINECOLOR);
    defaultborder.front();

    auto border = BorderSpecs();

    CHECK( border.repr() == defaultborder.repr() );

    border.right();
    border.top();
    border.linetype(5);
    border.linewidth(7);
    border.linecolor("red");
    border.back();

    CHECK( border.repr() == "set border 15 back linetype 5 linewidth 7 linecolor 'red'" );

    border.behind();

    CHECK( border.repr() == "set border 15 behind linetype 5 linewidth 7 linecolor 'red'" );
}
