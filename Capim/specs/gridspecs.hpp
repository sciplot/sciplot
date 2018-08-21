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

#pragma once

// Capim includes
#include <Capim/default.hpp>
#include <Capim/specs/linespecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The class used to specify options for grid.
class gridspecs : public linespecs<gridspecs>
{
public:
    /// Construct a default gridspecs instance.
    gridspecs(std::string tics, bool majorgrid) : m_tics(tics), m_majorgrid(majorgrid)
    {
        back();
    }

    /// Set the grid to be plot on the back of other plotting elements.
    auto back() -> gridspecs& { m_depth = "back"; return *this; }

    /// Set the grid to be plot on the front of other plotting elements.
    auto front() -> gridspecs& { m_depth = "back"; return *this; }

    /// Set the grid to be plot on the back of other plotting elements in 2d plots.
    /// In 3d plots, this option splits the grid and the graph box into two layers,
    /// with one behind, and the other in front of the plotted elements.
    auto layerdefault() -> gridspecs& { m_depth = "layerdefault"; return *this; }

    /// Convert this gridspecs object into a gnuplot formatted string.
    virtual auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << optionstr(m_tics);
        ss << optionstr(m_depth);
        if(m_majorgrid) ss << linespecs<gridspecs>::repr();
        else ss << ", " + linespecs<gridspecs>::repr();
        return ss.str();
    }

private:
    /// The names of the tics for which the grid is affected.
    std::string m_tics;

    /// The names of the tics for which the grid is affected.
    bool m_majorgrid;

    /// The placement depth for the grid.
    std::string m_depth;
};

} // namespace internal
} // namespace Capim
