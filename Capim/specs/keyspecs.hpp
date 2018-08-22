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
#include <Capim/specs/showspecs.hpp>
#include <Capim/specs/textspecs.hpp>
#include <Capim/specs/titlespecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The class used to setup the specs of the key title.
class keytitlespecs : public titlespecs<keytitlespecs>
{};

/// The class used to setup the specs of the key box lines.
class keyboxspecs : public linespecs<keyboxspecs>, public showspecs<keyboxspecs>
{
    auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << showspecs<keyboxspecs>::repr() << "box " << linespecs<keyboxspecs>::repr();
        return ss.str();
    }
};

/// The class used to specify options for key (legend).
class keyspecs : public textspecs<keyspecs>, public showspecs<keyspecs>
{
public:
    /// Construct a default keyspecs instance.
    keyspecs();

    /// Convert this gridticsspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the key to be displayed inside the graph's border.
    auto inside() -> keyspecs& { m_placement = "inside"; return *this; }

    /// Set the key to be displayed outside the graph's border.
    auto outside() -> keyspecs& { m_placement = "outside"; return *this; }

    /// Set the key fram to be opaque or not, so that no plot element obstructs it.
    auto opaque(bool value = true) -> keyspecs& { m_opaque = value ? "opaque" : "noopaque"; return *this; }

    /// Set the titles to be displayed one on top of each other (along the vertical).
    auto vertical() -> keyspecs& { m_alignment = "vertical"; return *this; }

    /// Set the titles to be displayed one next to each other (along the horizontal).
    auto horizontal() -> keyspecs& { m_alignment = "horizontal"; return *this; }

    /// Set the titles displayed in the key to be left justified.
    auto leftjustified() -> keyspecs& { m_justification = "Left"; return *this; }

    /// Set the titles displayed in the key to be right justified.
    auto rightjustified() -> keyspecs& { m_justification = "Right"; return *this; }

    /// Enable or disable the box surrounding the key and return a specs object for its further setup.
    auto box() -> keyboxspecs& { return m_box; }

    /// Set the title of the key and return a specs object for its further setup.
    auto title(std::string text) -> keytitlespecs& { m_title.text(text); return m_title; }

private:
    /// The place where the key is displayed (inside or outside the graph).
    std::string m_placement;

    /// The alignment of the titles (either along the horizontal or vertical).
    std::string m_alignment;

    /// The alignment of the titles (either along the horizontal or vertical).
    std::string m_opaque;

    /// The justification mode of the titles in the key (Left or Right gnuplot options).
    std::string m_justification;

    /// The specs of the surrounding box of the key.
    keyboxspecs m_box;

    /// The title of the label.
    keytitlespecs m_title;
};

keyspecs::keyspecs()
{
    inside();
    vertical();
    opaque();
    rightjustified();
    fontname(DEFAULT_KEY_FONTNAME);
    fontsize(DEFAULT_KEY_FONTSIZE);
    box().show();
    box().linecolor(DEFAULT_KEY_LINECOLOR);
    box().linetype(DEFAULT_KEY_LINETYPE);
    box().linewidth(DEFAULT_KEY_LINEWIDTH);
    box().linecolor(DEFAULT_KEY_LINECOLOR);
    title("").fontsize(DEFAULT_KEY_FONTSIZE);
}

auto keyspecs::repr() const -> std::string
{
    if(showspecs<keyspecs>::repr() == "no")
        return "unset key";

    std::stringstream ss;
    ss << "set key " << m_placement << " " << m_alignment << " " << m_justification << " ";
    ss << textspecs<keyspecs>::repr() << " ";
    ss << m_opaque << " ";
    ss << m_box << " ";
    ss << "title " << m_title << " ";
    return ss.str();
}

} // namespace internal
} // namespace Capim
