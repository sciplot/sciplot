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

#pragma once

// sciplot includes
#include <sciplot/default.hpp>
#include <sciplot/specs/textspecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// The class used to specify options for font.
class ticspecs : public textspecs<ticspecs>
{
public:
    /// Construct a default ticspecs instance.
    ticspecs();

    /// Convert this ticspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the tics to be mirrored on the oposing axes if `true`.
    auto mirror(bool value = true) -> ticspecs& { m_mirror = value ? "mirror" : "nomirror"; return *this; }

    /// Set the tics to be displayed on the front of all plot elements.
    auto front() -> ticspecs& { m_depth = "front"; return *this; }

    /// Set the tics to be displayed on the back of all plot elements.
    auto back() -> ticspecs& { m_depth = "back"; return *this; }

    /// Set the tics to be displayed inside the graph.
    auto inside() -> ticspecs& { m_inout = "in"; return *this; }

    /// Set the tics to be displayed outside the graph.
    auto outside() -> ticspecs& { m_inout = "out"; return *this; }

    /// Set the scale for the major tics (identical to method scalemajor).
    auto scale(double value) -> ticspecs& { return scalemajor(value); }

    /// Set the scale for the major tics.
    auto scalemajor(double value) -> ticspecs& { m_scalemajor = value; return *this; }

    /// Set the scale for the minor tics.
    auto scaleminor(double value) -> ticspecs& { m_scaleminor = value; return *this; }

private:
    /// The mirror option of the tics.
    std::string m_mirror;

    /// The depth where the tics are displayed (back or front).
    std::string m_depth;

    /// The place where the tics are displayed (in or out).
    std::string m_inout;

    /// The scale of the major tics.
    double m_scalemajor;

    /// The scale of the minor tics.
    double m_scaleminor;
};

ticspecs::ticspecs()
{
    front();
    outside();
    mirror(false);
    scalemajor(0.50);
    scaleminor(0.25);
}

auto ticspecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << "set tics " << m_mirror << " " << m_depth << " " << m_inout << " ";
    ss << "scale " << m_scalemajor << "," << m_scaleminor << " ";
    ss << textspecs<ticspecs>::repr();
    return ss.str();
}

} // namespace sciplot
