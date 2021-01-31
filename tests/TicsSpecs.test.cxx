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
#include <sciplot/specs/GridSpecs.hpp>
#include <sciplot/specs/TicsSpecs.hpp>
using namespace sciplot;

TEST_CASE("TicsSpecs", "[specs]")
{
    auto default_tics = TicsSpecs();
    default_tics.alongBorder();
    default_tics.mirror(internal::DEFAULT_TICS_MIRROR);
    default_tics.outsideGraph();
    default_tics.rotate(internal::DEFAULT_TICS_ROTATE);
    default_tics.stackFront();
    default_tics.scaleMajorBy(internal::DEFAULT_TICS_SCALE_MAJOR_BY);
    default_tics.scaleMinorBy(internal::DEFAULT_TICS_SCALE_MINOR_BY);

    auto tics = TicsSpecs();
    CHECK( tics.repr() == default_tics.repr() );

    tics.alongAxis();
    CHECK( tics.repr() == "set tics axis nomirror front out scale 0.5,0.25 norotate enhanced textcolor '#404040' font 'Georgia,12'");

    tics.alongBorder();
    CHECK( tics.repr() == "set tics border nomirror front out scale 0.5,0.25 norotate enhanced textcolor '#404040' font 'Georgia,12'");

    tics.mirror();
    CHECK( tics.repr() == "set tics border mirror front out scale 0.5,0.25 norotate enhanced textcolor '#404040' font 'Georgia,12'");

    tics.insideGraph();
    CHECK( tics.repr() == "set tics border mirror front in scale 0.5,0.25 norotate enhanced textcolor '#404040' font 'Georgia,12'");

    tics.outsideGraph();
    CHECK( tics.repr() == "set tics border mirror front out scale 0.5,0.25 norotate enhanced textcolor '#404040' font 'Georgia,12'");

    tics.rotate();
    CHECK( tics.repr() == "set tics border mirror front out scale 0.5,0.25 rotate enhanced textcolor '#404040' font 'Georgia,12'");

    tics.rotateBy(42);
    CHECK( tics.repr() == "set tics border mirror front out scale 0.5,0.25 rotate by 42 enhanced textcolor '#404040' font 'Georgia,12'");

    tics.stackFront();
    CHECK( tics.repr() == "set tics border mirror front out scale 0.5,0.25 rotate by 42 enhanced textcolor '#404040' font 'Georgia,12'");

    tics.stackBack();
    CHECK( tics.repr() == "set tics border mirror back out scale 0.5,0.25 rotate by 42 enhanced textcolor '#404040' font 'Georgia,12'");

    tics.scaleBy(1.2);
    CHECK( tics.repr() == "set tics border mirror back out scale 1.2,0.25 rotate by 42 enhanced textcolor '#404040' font 'Georgia,12'");

    tics.scaleMajorBy(5.6);
    CHECK( tics.repr() == "set tics border mirror back out scale 5.6,0.25 rotate by 42 enhanced textcolor '#404040' font 'Georgia,12'");

    tics.scaleMinorBy(7.9);
    CHECK( tics.repr() == "set tics border mirror back out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' font 'Georgia,12'");
}
