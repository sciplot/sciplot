// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
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

// Capim includes
#include <Capim/Plot.hpp>
using namespace Capim;

// Capim example includes
#include <examples/bessel.hpp>
using namespace Capim::bessel;

int main(int argc, char **argv)
{
    Plot plt;

    plt.xlabel("x");
    plt.ylabel("J_v(x)");

    plt.plot(x, j0).title("J_0").dashtype(1);
    plt.plot(x, j1).title("J_1").dashtype(2);
    plt.plot(x, j2).title("J_2").dashtype(3);
    plt.plot(x, j3).title("J_3").dashtype(4);
    plt.plot(x, j4).title("J_4").dashtype(5);
    plt.plot(x, j5).title("J_5").dashtype(6);
    plt.plot(x, j6).title("J_6").dashtype(7);

    plt.show();
}
