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

// Catch includes
#include <tests/catch.hpp>

// sciplot includes
#include <sciplot/specs/TitleSpecsOf.hpp>
using namespace sciplot;

TEST_CASE("TitleSpecs", "[specs]")
{
    auto specs = TitleSpecs();

    specs.title("Hello");
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040'");

    specs.titleShiftAlongX(1);
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' offset 1, 0");

    specs.titleShiftAlongY(2);
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' offset 1, 2");

    specs.titleShiftAlongGraphX(0.3);
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' offset graph 0.3, 2");

    specs.titleShiftAlongGraphY(0.4);
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' offset graph 0.3, graph 0.4");

    specs.titleShiftAlongScreenX(0.5);
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' offset screen 0.5, graph 0.4");

    specs.titleShiftAlongScreenY(0.6);
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' offset screen 0.5, screen 0.6");

    specs.titleFontName("Arial");
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' font 'Arial,' offset screen 0.5, screen 0.6");

    specs.titleFontSize(13);
    CHECK( specs.repr() == "title 'Hello' enhanced textcolor '#404040' font 'Arial,13' offset screen 0.5, screen 0.6");
}
