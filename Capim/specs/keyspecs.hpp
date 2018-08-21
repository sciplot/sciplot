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
#include <Capim/specs/fontspecs.hpp>
#include <Capim/specs/linespecs.hpp>
#include <Capim/specs/textspecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The class used to specify options for key (legend).
class keyspecs : public linespecs<keyspecs>, public fontspecs<keyspecs>
{
public:
    /// Construct a default keyspecs instance.
    keyspecs();

    /// Convert this gridticsspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Enable the display of the key.
    auto enable() -> keyspecs& { m_active = "on"; return *this; }

    /// Disable the display of the key.
    auto disable() -> keyspecs& { m_active = "off"; return *this; }

    /// Set the key to be displayed inside the graph's border.
    auto inside() -> keyspecs& { m_placement = "inside"; return *this; }

    /// Set the key to be displayed outside the graph's border.
    auto outside() -> keyspecs& { m_placement = "outside"; return *this; }

    /// Set the titles displayed in the key to be left justified.
    auto leftjustified() -> keyspecs& { m_justification = "Left"; return *this; }

    /// Set the titles displayed in the key to be right justified.
    auto rightjustified() -> keyspecs& { m_justification = "Right"; return *this; }

    /// Set the title of the key and return a specs object for its further setup.
    auto title(std::string text) -> textspecs& { m_title.text(text); return m_title; }

    /// Enable or disable the box surrounding the key and return a specs object for its further setup.
    auto box(bool value = true) -> linespecs& { m_boxed = value; return m_box; }

private:
    /// The string determining if the key is displayed or not (on or off).
    std::string m_active;

    /// The place where the key is displayed (inside or outside the graph).
    std::string m_placement;

    /// The justification mode of the titles in the key (Left or Right gnuplot options).
    std::string m_justification;

    /// The title of the label.
    textspecs m_title;

    /// The placement depth for the grid.
    std::string m_depth;

    std::string
    /// The specs of the surrounding box of the key.
    bool m_boxed;

    /// The specs of the surrounding box of the key.
    linespecs m_box;
};

keyspecs::keyspecs()
{
    righttop();
    inside();
    leftjustified();
    box().linecolor(DEFAULT_GRID_LINECOLOR);
    box().linetype(DEFAULT_GRID_LINETYPE);
    box().linewidth(DEFAULT_LINEWIDTH);
}

} // namespace internal
} // namespace Capim
