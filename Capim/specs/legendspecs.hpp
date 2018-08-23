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

/// The class used to setup the specs of the legend title.
class legendtitlespecs : public titlespecs<legendtitlespecs>
{};

/// The class used to setup the specs of the legend border lines.
class legendborderspecs : public linespecs<legendborderspecs>, public showspecs<legendborderspecs>
{
public:
    /// Construct a default legendborderspecs object.
    legendborderspecs()
    {
        linecolor(DEFAULT_KEY_LINECOLOR);
        linetype(DEFAULT_KEY_LINETYPE);
        linewidth(DEFAULT_KEY_LINEWIDTH);
        linecolor(DEFAULT_KEY_LINECOLOR);
    }

    /// Convert this legendborderspecs object into a gnuplot formatted string.
    auto repr() const -> std::string
    {
        if(showspecs<legendborderspecs>::repr() == "no")
            return "nobox";

        std::stringstream ss;
        ss << "box " << linespecs<legendborderspecs>::repr();
        return ss.str();
    }
};

/// The class used to specify options for legend (legend).
class legendspecs : public textspecs<legendspecs>, public showspecs<legendspecs>
{
public:
    /// Construct a default legendspecs instance.
    legendspecs();

    /// Convert this legendspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the legend to be displayed inside the graph's border.
    auto inside() -> legendspecs& { m_placement = "inside"; return *this; }

    /// Set the legend to be displayed outside the graph's border.
    auto outside() -> legendspecs& { m_placement = "outside"; return *this; }

    /// Set the legend fram to be opaque or not, so that no plot element obstructs it.
    auto opaque(bool value = true) -> legendspecs& { m_opaque = value ? "opaque" : "noopaque"; return *this; }

    /// Set the titles to be displayed one on top of each other (along the vertical).
    auto vertical() -> legendspecs& { m_alignment = "vertical"; return *this; }

    /// Set the titles to be displayed one next to each other (along the horizontal).
    auto horizontal() -> legendspecs& { m_alignment = "horizontal"; return *this; }

    /// Set the titles displayed in the legend to be left justified.
    auto leftjustified() -> legendspecs& { m_justification = "Left"; return *this; }

    /// Set the titles displayed in the legend to be right justified.
    auto rightjustified() -> legendspecs& { m_justification = "Right"; return *this; }

    /// Enable or disable the border surrounding the legend and return a specs object for its further setup.
    auto border() -> legendborderspecs& { return m_border; }

    /// Set the title of the legend and return a specs object for its further setup.
    auto title(std::string text) -> legendtitlespecs& { m_title.text(text); return m_title; }

private:
    /// The place where the legend is displayed (inside or outside the graph).
    std::string m_placement;

    /// The alignment of the titles (either along the horizontal or vertical).
    std::string m_alignment;

    /// The alignment of the titles (either along the horizontal or vertical).
    std::string m_opaque;

    /// The justification mode of the titles in the legend (Left or Right gnuplot options).
    std::string m_justification;

    /// The specs of the surrounding border of the legend.
    legendborderspecs m_border;

    /// The title of the label.
    legendtitlespecs m_title;
};

legendspecs::legendspecs()
{
    inside();
    vertical();
    opaque();
    rightjustified();
    fontname(DEFAULT_KEY_FONTNAME);
    fontsize(DEFAULT_KEY_FONTSIZE);
    border().show(false);
    title("").fontsize(DEFAULT_KEY_FONTSIZE);
}

auto legendspecs::repr() const -> std::string
{
    if(showspecs<legendspecs>::repr() == "no")
        return "unset legend";

    std::stringstream ss;
    ss << "set key " << m_placement << " " << m_alignment << " " << m_justification << " ";
    ss << textspecs<legendspecs>::repr() << " ";
    ss << m_opaque << " ";
    ss << m_border << " ";
    ss << "title " << m_title << " ";
    return ss.str();
}

} // namespace internal
} // namespace Capim
