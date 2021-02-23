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
#include <sciplot/specs/TicsSpecsMajor.hpp>
using namespace sciplot;

TEST_CASE("TicsSpecsMajor", "[specs]")
{
    auto default_xtics = TicsSpecsMajor("x");
    default_xtics.alongBorder();
    default_xtics.mirror(internal::DEFAULT_TICS_MIRROR);
    default_xtics.outsideGraph();
    default_xtics.rotate(internal::DEFAULT_TICS_ROTATE);
    default_xtics.scaleMajorBy(internal::DEFAULT_TICS_SCALE_MAJOR_BY);
    default_xtics.scaleMinorBy(internal::DEFAULT_TICS_SCALE_MINOR_BY);

    auto xtics = TicsSpecsMajor("x");
    CHECK( xtics.repr() == default_xtics.repr() );

    xtics.alongAxis();
    CHECK( xtics.repr() == "set xtics axis nomirror out scale 0.5,0.25 norotate enhanced textcolor '#404040'");

    xtics.alongBorder();
    CHECK( xtics.repr() == "set xtics border nomirror out scale 0.5,0.25 norotate enhanced textcolor '#404040'");

    xtics.mirror();
    CHECK( xtics.repr() == "set xtics border mirror out scale 0.5,0.25 norotate enhanced textcolor '#404040'");

    xtics.insideGraph();
    CHECK( xtics.repr() == "set xtics border mirror in scale 0.5,0.25 norotate enhanced textcolor '#404040'");

    xtics.outsideGraph();
    CHECK( xtics.repr() == "set xtics border mirror out scale 0.5,0.25 norotate enhanced textcolor '#404040'");

    xtics.rotate();
    CHECK( xtics.repr() == "set xtics border mirror out scale 0.5,0.25 rotate enhanced textcolor '#404040'");

    xtics.rotateBy(42);
    CHECK( xtics.repr() == "set xtics border mirror out scale 0.5,0.25 rotate by 42 enhanced textcolor '#404040'");

    xtics.scaleBy(1.2);
    CHECK( xtics.repr() == "set xtics border mirror out scale 1.2,0.25 rotate by 42 enhanced textcolor '#404040'");

    xtics.scaleMajorBy(5.6);
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,0.25 rotate by 42 enhanced textcolor '#404040'");

    xtics.scaleMinorBy(7.9);
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040'");

    xtics.format("%4.2f");
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f'");

    xtics.increment(1.2345);
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' 1.2345");

    xtics.start(0.345);
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' 0.345, 1.2345");

    xtics.end(5.652);
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' 0.345, 1.2345, 5.652");

    xtics.interval(0.234, 0.899, 3.45);
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' 0.234, 0.899, 3.45");

    xtics.at({ 0.1, 0.2, 0.3, 0.4 });
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' (0.1, 0.2, 0.3, 0.4)");

    xtics.at({ 0.1, 0.2, 0.3, 0.4 }, { "A", "", "C", "F" });
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' ('A' 0.1, '' 0.2, 'C' 0.3, 'F' 0.4)");

    xtics.add({ 1.1, 1.2, 1.3, 1.4 });
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' ('A' 0.1, '' 0.2, 'C' 0.3, 'F' 0.4) add (1.1, 1.2, 1.3, 1.4)");

    xtics.add({ 2.1, 2.2, 2.3, 2.4 }, { "Z", "U", "V", "X" });
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' ('A' 0.1, '' 0.2, 'C' 0.3, 'F' 0.4) add ('Z' 2.1, 'U' 2.2, 'V' 2.3, 'X' 2.4)");

    xtics.logscale();
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' ('A' 0.1, '' 0.2, 'C' 0.3, 'F' 0.4) add ('Z' 2.1, 'U' 2.2, 'V' 2.3, 'X' 2.4) logscale");

    xtics.automatic();
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' '%4.2f' add ('Z' 2.1, 'U' 2.2, 'V' 2.3, 'X' 2.4) logscale");

    xtics.fontName("Arial");
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' font 'Arial,' '%4.2f' add ('Z' 2.1, 'U' 2.2, 'V' 2.3, 'X' 2.4) logscale");

    xtics.fontSize(16);
    CHECK( xtics.repr() == "set xtics border mirror out scale 5.6,7.9 rotate by 42 enhanced textcolor '#404040' font 'Arial,16' '%4.2f' add ('Z' 2.1, 'U' 2.2, 'V' 2.3, 'X' 2.4) logscale");

    xtics.automatic();
    xtics.start(1.0);
    CHECK_THROWS( xtics.repr() ); // method start has been called, but not method increment

    xtics.automatic();
    xtics.end(2.0);
    CHECK_THROWS( xtics.repr() ); // method end has been called, but not methods start and increment

    xtics.automatic();
    xtics.start(1.0);
    xtics.end(2.0);
    CHECK_THROWS( xtics.repr() ); // method end has been called, but not method increment

    xtics.automatic();
    xtics.start(1.0);
    xtics.end(2.0);
    xtics.increment(0.1);
    CHECK_NOTHROW( xtics.repr() ); // methods start, increment and end have been called - OK!

    CHECK_THROWS( TicsSpecsMajor("") ); // constructor TicsSpecsMajor has been called with empty string

    xtics.hide();
    CHECK( xtics.repr() == "unset xtics" );
}
