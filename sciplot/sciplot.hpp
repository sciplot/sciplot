// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2022 Allan Leal, Bim Overbohm
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

#pragma once

// We check if windows.h. is already included, as this might break compilation. See: https://sciplot.github.io/known_issues/
#ifdef _WINDOWS_
#ifdef _MSC_VER
#pragma message(__FILE__ "(): warning: You might run into compiler errors if windows.h is included before sciplot.hpp! See: https://sciplot.github.io/known_issues/")
#else
#warning You might run into compiler errors if windows.h is included before sciplot.hpp! See: https://sciplot.github.io/known_issues/
#endif // _MSC_VER
#endif // _WINDOWS_

// sciplot includes
#include <sciplot/Canvas.hpp>
#include <sciplot/Constants.hpp>
#include <sciplot/Default.hpp>
#include <sciplot/Enums.hpp>
#include <sciplot/Figure.hpp>
#include <sciplot/Palettes.hpp>
#include <sciplot/Plot.hpp>
#include <sciplot/Plot2D.hpp>
#include <sciplot/Plot3D.hpp>
#include <sciplot/StringOrDouble.hpp>
#include <sciplot/Utils.hpp>
#include <sciplot/Vec.hpp>
