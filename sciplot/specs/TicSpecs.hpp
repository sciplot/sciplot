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
#include <sciplot/specs/TextSpecsOf.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// The class used to specify options for tics.
class TicSpecs : public TextSpecsOf<TicSpecs>
{
  public:
    /// Construct a default TicSpecs instance.
    TicSpecs(ticaxis axis = ticaxis::all);

    /// Convert this TicSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the tics to be mirrored on the oposing axes if `true`.
    auto mirror(bool value = true) -> TicSpecs&
    {
        m_mirror = value ? "mirror" : "nomirror";
        return *this;
    }

    /// Set the tics to be rotated 90 degrees if `true`.
    auto rotate(bool value = true) -> TicSpecs&
    {
        m_rotate = value ? "rotate" : "norotate";
        return *this;
    }

    /// Set the tics to be rotated angle degrees if `true`.
    auto rotateby(double angle) -> TicSpecs&
    {
        m_rotate = "rotate by " + std::to_string(angle);
        return *this;
    }

    /// Set the tics to be displayed on the front of all plot elements.
    auto front() -> TicSpecs&
    {
        m_depth = "front";
        return *this;
    }

    /// Set the tics to be displayed on the back of all plot elements.
    auto back() -> TicSpecs&
    {
        m_depth = "back";
        return *this;
    }

    /// Set the tics to be displayed inside the graph.
    auto inside() -> TicSpecs&
    {
        m_inout = "in";
        return *this;
    }

    /// Set the tics to be displayed outside the graph.
    auto outside() -> TicSpecs&
    {
        m_inout = "out";
        return *this;
    }

    /// Set the scale for the major tics (identical to method scalemajor).
    auto scale(double value) -> TicSpecs& { return scalemajor(value); }

    /// Set the scale for the major tics.
    auto scalemajor(double value) -> TicSpecs&
    {
        m_scalemajor = value;
        return *this;
    }

    /// Set the scale for the minor tics.
    auto scaleminor(double value) -> TicSpecs&
    {
        m_scaleminor = value;
        return *this;
    }

  private:
    /// The axis the tic options will be applied to.
    ticaxis m_axis = ticaxis::all;

    /// The mirror option of the tics.
    std::string m_mirror;

    /// The rotate option for the tics.
    std::string m_rotate;

    /// The depth where the tics are displayed (back or front).
    std::string m_depth;

    /// The place where the tics are displayed (in or out).
    std::string m_inout;

    /// The scale of the major tics.
    double m_scalemajor;

    /// The scale of the minor tics.
    double m_scaleminor;
};

TicSpecs::TicSpecs(ticaxis axis)
    : m_axis(axis)
{
    front();
    outside();
    mirror(false);
    rotate(false);
    scalemajor(0.50);
    scaleminor(0.25);
}

auto TicSpecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << "set " << gnuplot::ticaxisstr(m_axis) << " " << m_mirror << " ";
    // only "tics" support the front / back parameters
    if (m_axis == ticaxis::all)
    {
        ss << m_depth << " ";
    }
    ss << m_inout << " ";
    ss << "scale " << m_scalemajor << "," << m_scaleminor << " ";
    ss << m_rotate << " ";
    ss << TextSpecsOf<TicSpecs>::repr();
    return ss.str();
}

} // namespace sciplot
