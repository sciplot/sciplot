// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/allanleal/sciplot
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
#include <sciplot/specs/fontspecs.hpp>
#include <sciplot/specs/linespecs.hpp>
#include <sciplot/specs/showspecs.hpp>
#include <sciplot/specs/textspecs.hpp>
#include <sciplot/specs/titlespecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot {
namespace internal {

/// The class used to setup the specs of the legend header title.
class legendheaderspecs : public titlespecs<legendheaderspecs>
{
public:
    /// Construct a default legendheaderspecs object.
    legendheaderspecs();
};

/// The class used to setup the specs of the legend border lines.
class legendborderspecs : public linespecs<legendborderspecs>, public showspecs<legendborderspecs>
{
public:
    /// Construct a default legendborderspecs object.
    legendborderspecs();

    /// Convert this legendborderspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;
};

/// The class used to setup the specs of the legend border lines.
class legendtitlesspecs : public virtual specs<legendtitlesspecs>
{
public:
    /// Construct a default legendtitlesspecs object.
    legendtitlesspecs();

    /// Convert this legendborderspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the titles to be displayed along the vertical, one on top of each other.
    auto vertical() -> legendtitlesspecs& { m_alignment = "vertical"; return *this; }

    /// Set the titles to be displayed along the horizontal, one next to each other.
    auto horizontal() -> legendtitlesspecs& { m_alignment = "horizontal"; return *this; }

    /// Set the legend titles to be on the left side of the their corresponding symbols (e.g., line segments, points).
    auto leftside() -> legendtitlesspecs& { m_reverse = "noreverse"; return *this; }

    /// Set the legend titles to be on the right side of the their corresponding symbols (e.g., line segments, points).
    auto rightside() -> legendtitlesspecs& { m_reverse = "reverse"; return *this; }

    /// Set the legend titles to be left justified.
    auto leftjustified() -> legendtitlesspecs& { m_justification = "Left"; return *this; }

    /// Set the legend titles to be right justified.
    auto rightjustified() -> legendtitlesspecs& { m_justification = "Right"; return *this; }

    /// Set the legend titles to be on the left side and right justified.
    auto leftsiderightjustified() -> legendtitlesspecs& { leftside(); rightjustified(); return *this; }

    /// Set the legend titles to be on the right side and left justified.
    auto rightsideleftjustified() -> legendtitlesspecs& { rightside(); leftjustified(); return *this; }

    /// Set the legend titles to be displayed in the order from first to last.
    auto startfromfirst() -> legendtitlesspecs& { m_invert = "noinvert"; return *this; }

    /// Set the legend titles to be displayed in the order from last to first.
    auto startfromlast() -> legendtitlesspecs& { m_invert = "invert"; return *this; }

private:
    /// The alignment of the titles (either along the horizontal or vertical).
    std::string m_alignment;

    /// The reverse option for the titles (if they printed on the left or right sides within the legend).
    std::string m_reverse;

    /// The invert option of the titles (if they are printed from first to last or the other way around).
    std::string m_invert;

    /// The justification mode of the titles in the legend (Left or Right gnuplot options).
    std::string m_justification;
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

    /// Return the specs object for configuring how the titles in the legend are displayed.
    auto titles() -> legendtitlesspecs& { return m_titles; }

    /// Enable or disable the border surrounding the legend and return a specs object for its further setup.
    auto border() -> legendborderspecs& { return m_border; }

    /// Set the header title of the legend and return a specs object for its further setup.
    auto header(std::string text) -> legendheaderspecs& { m_header.text(text); return m_header; }

    /// Set the width increment of the legend frame.
    auto addtowidth(double value) -> legendspecs& { m_width = value; return *this; }

    /// Set the height increment of the legend frame.
    auto addtoheight(double value) -> legendspecs& { m_height = value; return *this; }

    /// Set the length of the samples in the legend.
    auto samplelength(double value) -> legendspecs& { m_samplen = value; return *this; }

    /// Set the spacing between the titles in the legend.
    auto spacing(double value) -> legendspecs& { m_spacing = value; return *this; }

    /// Set the maximum number of rows of titles in the legend.
    auto maxrows(std::size_t value) -> legendspecs& { m_maxrows = str(value); return *this; }

    /// Set the maximum number of rows of titles in the legend.
    auto maxcols(std::size_t value) -> legendspecs& { m_maxcols = str(value); return *this; }

private:
    /// The place where the legend is displayed (inside or outside the graph).
    std::string m_placement;

    /// The alignment of the titles (either along the horizontal or vertical).
    std::string m_opaque;

    /// The specs of the titles of the legend.
    legendtitlesspecs m_titles;

    /// The specs of the surrounding border of the legend.
    legendborderspecs m_border;

    /// The title of the label.
    legendheaderspecs m_header;

    /// The width increment of the legend frame.
    double m_width;

    /// The height increment of the legend frame.
    double m_height;

    /// The length of the samples in the legend.
    double m_samplen;

    /// The spacing between the titles in the legend.
    double m_spacing;

    /// The maximum number of rows of titles in the legend.
    std::string m_maxrows = "auto";

    /// The maximum number of rows of titles in the legend.
    std::string m_maxcols = "auto";
};

legendspecs::legendspecs()
{
    inside();
    opaque();
    fontname(DEFAULT_LEGEND_FONTNAME);
    fontsize(DEFAULT_LEGEND_FONTSIZE);
    addtowidth(0.0);
    addtoheight(0.0);
    samplelength(DEFAULT_LEGEND_SAMPLE_LENGTH);
    spacing(DEFAULT_LEGEND_SPACING);
}

auto legendspecs::repr() const -> std::string
{
    if(showspecs<legendspecs>::repr() == "no")
        return "unset legend";

    std::stringstream ss;
    ss << "set key ";
    ss << m_placement << " " << m_opaque << " ";
    ss << m_border << " " << m_titles << " ";
    ss << "width " << m_width << " ";
    ss << "height " << m_height << " ";
    ss << "samplen " << m_samplen << " ";
    ss << "spacing " << m_spacing << " ";
    ss << textspecs<legendspecs>::repr() << " ";
    ss << "title " << m_header;
    ss << "maxrows " << m_maxrows << " ";
    ss << "maxcols " << m_maxcols << " ";
    return ss.str();
}

legendheaderspecs::legendheaderspecs()
{
    text("");
    fontname(DEFAULT_LEGEND_FONTNAME);
    fontsize(DEFAULT_LEGEND_FONTSIZE);
}

legendborderspecs::legendborderspecs()
{
    show(false);
    linecolor(DEFAULT_LEGEND_LINECOLOR);
    linetype(DEFAULT_LEGEND_LINETYPE);
    linewidth(DEFAULT_LEGEND_LINEWIDTH);
    linecolor(DEFAULT_LEGEND_LINECOLOR);
}

auto legendborderspecs::repr() const -> std::string
{
    if(showspecs<legendborderspecs>::repr() == "no")
        return "nobox";

    std::stringstream ss;
    ss << "box " << linespecs<legendborderspecs>::repr();
    return ss.str();
}

legendtitlesspecs::legendtitlesspecs()
{
    vertical();
    rightsideleftjustified();
    startfromfirst();
}

auto legendtitlesspecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << m_alignment << " " << m_justification << " " << m_invert << " " << m_reverse;
    return ss.str();
}

} // namespace internal
} // namespace sciplot
