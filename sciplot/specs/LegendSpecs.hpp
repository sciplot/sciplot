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

#pragma once

// sciplot includes
#include <sciplot/Default.hpp>
#include <sciplot/specs/FrameSpecsOf.hpp>
#include <sciplot/specs/ShowSpecsOf.hpp>
#include <sciplot/specs/TextSpecsOf.hpp>
#include <sciplot/specs/TitleSpecsOf.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to specify options for legend.
class LegendSpecs : public TextSpecsOf<LegendSpecs>, public ShowSpecsOf<LegendSpecs>, public TitleSpecsOf<LegendSpecs>, public FrameSpecsOf<LegendSpecs>
{
  public:
    /// Construct a default LegendSpecs instance.
    LegendSpecs();

    /// Set the background of the legend box to be opaque.
    auto opaque() -> LegendSpecs&;

    /// Set the background of the legend box to be transparent.
    auto transparent() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its left side.
    auto atLeft() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its right side.
    auto atRight() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its center.
    auto atCenter() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its top side.
    auto atTop() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its top-left corner.
    auto atTopLeft() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its top-right corner.
    auto atTopRight() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its bottom side.
    auto atBottom() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its bottom-left corner.
    auto atBottomLeft() -> LegendSpecs&;

    /// Place the legend on the inside of the plot at its bottom-right corner.
    auto atBottomRight() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its left side.
    auto atOutsideLeft() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its left-top corner.
    auto atOutsideLeftTop() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its left-bottom corner.
    auto atOutsideLeftBottom() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its right side.
    auto atOutsideRight() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its right-top corner.
    auto atOutsideRightTop() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its right-bottom corner.
    auto atOutsideRightBottom() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its bottom side.
    auto atOutsideBottom() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its bottom-left corner.
    auto atOutsideBottomLeft() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its bottom-right corner.
    auto atOutsideBottomRight() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its top side.
    auto atOutsideTop() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its top-left corner.
    auto atOutsideTopLeft() -> LegendSpecs&;

    /// Place the legend on the outside of the plot at its top-right corner.
    auto atOutsideTopRight() -> LegendSpecs&;

    /// Place the legend title on the left.
    auto titleLeft() -> LegendSpecs&;

    /// Place the legend title on the center.
    auto titleCenter() -> LegendSpecs&;

    /// Place the legend title on the right.
    auto titleRight() -> LegendSpecs&;

    /// Set the legend entries to be displayed along the vertical (in columns).
    auto displayVertical() -> LegendSpecs&;

    /// Set the number of rows that trigger a new column to be created in the legend (when using vertical display).
    auto displayVerticalMaxRows(int value) -> LegendSpecs&;

    /// Set the legend entries to be displayed along the horizontal (in rows).
    auto displayHorizontal() -> LegendSpecs&;

    /// Set the number of columns that trigger a new row to be created in the legend (when using horizontal display).
    auto displayHorizontalMaxCols(int value) -> LegendSpecs&;

    /// Set the labels in the legend entries to appear before their corresponding symbols (on the left).
    auto displayLabelsBeforeSymbols() -> LegendSpecs&;

    /// Set the labels in the legend entries to appear after their corresponding symbols (on the right).
    auto displayLabelsAfterSymbols() -> LegendSpecs&;

    /// Set the legend labels to be left justified.
    auto displayJustifyLeft() -> LegendSpecs&;

    /// Set the legend labels to be right justified.
    auto displayJustifyRight() -> LegendSpecs&;

    /// Set the legend entries to be displayed in the order from first to last.
    auto displayStartFromFirst() -> LegendSpecs&;

    /// Set the legend entries to be displayed in the order from last to first.
    auto displayStartFromLast() -> LegendSpecs&;

    /// Set the spacing between the titles in the legend.
    auto displaySpacing(int value) -> LegendSpecs&;

    /// Set the width increment/decrement of the legend frame to either enlarge or reduce its width.
    auto displayExpandWidthBy(int value) -> LegendSpecs&;

    /// Set the height increment/decrement of the legend frame to either enlarge or reduce its height.
    auto displayExpandHeightBy(int value) -> LegendSpecs&;

    /// Set the length of the samples used to generate the symbols in the legend entries.
    auto displaySymbolLength(int value) -> LegendSpecs&;

    /// Convert this LegendSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The place at which the legend is displayed.
    std::string m_placement;

    /// The opaque option of the legend.
    std::string m_opaque;

    /// The alignment of the labels (either along the horizontal or vertical).
    std::string m_alignment;

    /// The reverse option for the labels (if they printed on the left or right sides within the legend).
    std::string m_reverse;

    /// The invert option of the labels (if they are printed from first to last or the other way around).
    std::string m_invert;

    /// The justification mode of the labels in the legend (Left or Right gnuplot options).
    std::string m_justification;

    /// The location of the legend title (left, center, right).
    std::string m_title_loc = "left";

    /// The width increment of the legend frame.
    int m_width_increment;

    /// The height increment of the legend frame.
    int m_height_increment;

    /// The length of the samples in the legend.
    int m_samplen;

    /// The spacing between the titles in the legend.
    int m_spacing;

    /// The maximum number of rows of titles in the legend.
    std::string m_maxrows = "auto";

    /// The maximum number of rows of titles in the legend.
    std::string m_maxcols = "auto";
};

inline LegendSpecs::LegendSpecs()
{
    atTopRight();
    title("");
    displayExpandWidthBy(internal::DEFAULT_LEGEND_FRAME_EXTRA_WIDTH);
    displayExpandHeightBy(internal::DEFAULT_LEGEND_FRAME_EXTRA_HEIGHT);
    displaySymbolLength(internal::DEFAULT_LEGEND_SAMPLE_LENGTH);
    displaySpacing(internal::DEFAULT_LEGEND_SPACING);
    displayVertical();
    displayLabelsAfterSymbols();
    displayJustifyLeft();
    displayStartFromFirst();
    opaque();
}

inline auto LegendSpecs::opaque() -> LegendSpecs&
{
    m_opaque = "opaque";
    return *this;
}

inline auto LegendSpecs::transparent() -> LegendSpecs&
{
    m_opaque = "noopaque";
    return *this;
}

inline auto LegendSpecs::atLeft() -> LegendSpecs&
{
    m_placement = "inside left";
    return *this;
}

inline auto LegendSpecs::atRight() -> LegendSpecs&
{
    m_placement = "inside right";
    return *this;
}

inline auto LegendSpecs::atCenter() -> LegendSpecs&
{
    m_placement = "inside center";
    return *this;
}

inline auto LegendSpecs::atTop() -> LegendSpecs&
{
    m_placement = "inside center top";
    return *this;
}

inline auto LegendSpecs::atTopLeft() -> LegendSpecs&
{
    m_placement = "inside left top";
    return *this;
}

inline auto LegendSpecs::atTopRight() -> LegendSpecs&
{
    m_placement = "inside right top";
    return *this;
}

inline auto LegendSpecs::atBottom() -> LegendSpecs&
{
    m_placement = "inside center bottom";
    return *this;
}

inline auto LegendSpecs::atBottomLeft() -> LegendSpecs&
{
    m_placement = "inside left bottom";
    return *this;
}

inline auto LegendSpecs::atBottomRight() -> LegendSpecs&
{
    m_placement = "inside right bottom";
    return *this;
}

inline auto LegendSpecs::atOutsideLeft() -> LegendSpecs&
{
    m_placement = "lmargin center";
    return *this;
}

inline auto LegendSpecs::atOutsideLeftTop() -> LegendSpecs&
{
    m_placement = "lmargin top";
    return *this;
}

inline auto LegendSpecs::atOutsideLeftBottom() -> LegendSpecs&
{
    m_placement = "lmargin bottom";
    return *this;
}

inline auto LegendSpecs::atOutsideRight() -> LegendSpecs&
{
    m_placement = "rmargin center";
    return *this;
}

inline auto LegendSpecs::atOutsideRightTop() -> LegendSpecs&
{
    m_placement = "rmargin top";
    return *this;
}

inline auto LegendSpecs::atOutsideRightBottom() -> LegendSpecs&
{
    m_placement = "rmargin bottom";
    return *this;
}

inline auto LegendSpecs::atOutsideBottom() -> LegendSpecs&
{
    m_placement = "bmargin center";
    return *this;
}

inline auto LegendSpecs::atOutsideBottomLeft() -> LegendSpecs&
{
    m_placement = "bmargin left";
    return *this;
}

inline auto LegendSpecs::atOutsideBottomRight() -> LegendSpecs&
{
    m_placement = "bmargin right";
    return *this;
}

inline auto LegendSpecs::atOutsideTop() -> LegendSpecs&
{
    m_placement = "tmargin center";
    return *this;
}

inline auto LegendSpecs::atOutsideTopLeft() -> LegendSpecs&
{
    m_placement = "tmargin left";
    return *this;
}

inline auto LegendSpecs::atOutsideTopRight() -> LegendSpecs&
{
    m_placement = "tmargin right";
    return *this;
}

inline auto LegendSpecs::titleLeft() -> LegendSpecs&
{
    m_title_loc = "left";
    return *this;
}

inline auto LegendSpecs::titleCenter() -> LegendSpecs&
{
    m_title_loc = "center";
    return *this;
}

inline auto LegendSpecs::titleRight() -> LegendSpecs&
{
    m_title_loc = "right";
    return *this;
}

inline auto LegendSpecs::displayVertical() -> LegendSpecs&
{
    m_alignment = "vertical";
    return *this;
}

inline auto LegendSpecs::displayVerticalMaxRows(int value) -> LegendSpecs&
{
    m_maxrows = internal::str(value);
    return *this;
}

inline auto LegendSpecs::displayHorizontal() -> LegendSpecs&
{
    m_alignment = "horizontal";
    return *this;
}

inline auto LegendSpecs::displayHorizontalMaxCols(int value) -> LegendSpecs&
{
    m_maxcols = internal::str(value);
    return *this;
}

inline auto LegendSpecs::displayLabelsBeforeSymbols() -> LegendSpecs&
{
    m_reverse = "noreverse";
    return *this;
}

inline auto LegendSpecs::displayLabelsAfterSymbols() -> LegendSpecs&
{
    m_reverse = "reverse";
    return *this;
}

inline auto LegendSpecs::displayJustifyLeft() -> LegendSpecs&
{
    m_justification = "Left";
    return *this;
}

inline auto LegendSpecs::displayJustifyRight() -> LegendSpecs&
{
    m_justification = "Right";
    return *this;
}

inline auto LegendSpecs::displayStartFromFirst() -> LegendSpecs&
{
    m_invert = "noinvert";
    return *this;
}

inline auto LegendSpecs::displayStartFromLast() -> LegendSpecs&
{
    m_invert = "invert";
    return *this;
}

inline auto LegendSpecs::displaySpacing(int value) -> LegendSpecs&
{
    m_spacing = value;
    return *this;
}

inline auto LegendSpecs::displayExpandWidthBy(int value) -> LegendSpecs&
{
    m_width_increment = value;
    return *this;
}

inline auto LegendSpecs::displayExpandHeightBy(int value) -> LegendSpecs&
{
    m_height_increment = value;
    return *this;
}

inline auto LegendSpecs::displaySymbolLength(int value) -> LegendSpecs&
{
    m_samplen = value;
    return *this;
}

inline auto LegendSpecs::repr() const -> std::string
{
    const auto show = ShowSpecsOf<LegendSpecs>::repr();
    if(show == "no")
        return "unset key";

    auto titlespecs = TitleSpecsOf<LegendSpecs>::repr();
    if(titlespecs.size())
        titlespecs += " " + m_title_loc; // attach left|center|right to title (e.g. title 'Legend' right)

    std::stringstream ss;
    ss << "set key ";
    ss << m_placement << " " << m_opaque << " ";
    ss << m_alignment << " ";
    ss << m_justification << " ";
    ss << m_invert << " ";
    ss << m_reverse << " ";
    ss << "width " << m_width_increment << " ";
    ss << "height " << m_height_increment << " ";
    ss << "samplen " << m_samplen << " ";
    ss << "spacing " << m_spacing << " ";
    ss << TextSpecsOf<LegendSpecs>::repr() << " ";
    ss << titlespecs << " ";
    ss << FrameSpecsOf<LegendSpecs>::repr() << " ";
    ss << "maxrows " << m_maxrows << " ";
    ss << "maxcols " << m_maxcols << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
