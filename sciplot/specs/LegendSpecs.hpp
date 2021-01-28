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
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/ShowSpecsOf.hpp>
#include <sciplot/specs/TextSpecsOf.hpp>
#include <sciplot/specs/TitleSpecsOf.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The class used to setup the specs of the legend header title.
class LegendHeaderSpecs : public TitleSpecsOf<LegendHeaderSpecs>
{
  public:
    /// Construct a default LegendHeaderSpecs object.
    LegendHeaderSpecs();
};

/// The class used to setup the specs of the legend border lines.
class LegendBorderSpecs : public LineSpecsOf<LegendBorderSpecs>, public ShowSpecsOf<LegendBorderSpecs>
{
  public:
    /// Construct a default LegendBorderSpecs object.
    LegendBorderSpecs();

    /// Convert this LegendBorderSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;
};

/// The class used to specify options for legend.
class LegendSpecs : public TextSpecsOf<LegendSpecs>, public ShowSpecsOf<LegendSpecs>
{
  public:
    /// Construct a default LegendSpecs instance.
    LegendSpecs();

    /// Set the background of the legend box to be opaque.
    auto opaque() -> LegendSpecs&;

    /// Set the background of the legend box to be transparent.
    auto transparent() -> LegendSpecs&;

    /// Enable or disable the border surrounding the legend and return a specs object for its further setup.
    auto border() -> LegendBorderSpecs&;

    /// Set the header title of the legend and return a specs object for its further setup.
    auto header(std::string text) -> LegendHeaderSpecs&;

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

    /// Set the width increment/decrement of the legend frame to either enlarge or reduce its width.
    auto incrementWidth(int value) -> LegendSpecs&;

    /// Set the height increment/decrement of the legend frame to either enlarge or reduce its height.
    auto incrementHeight(int value) -> LegendSpecs&;

    /// Set the length of the samples used to generate the symbols in the legend entries.
    auto symbolLength(int value) -> LegendSpecs&;

    /// Set the legend entries to be displayed along the vertical (in columns).
    auto verticalDisplay() -> LegendSpecs&;

    /// Set the number of rows that trigger a new column to be created in the legend (when using vertical display).
    auto verticalMaxRows(int value) -> LegendSpecs&;

    /// Set the legend entries to be displayed along the horizontal (in rows).
    auto horizontalDisplay() -> LegendSpecs&;

    /// Set the number of columns that trigger a new row to be created in the legend (when using horizontal display).
    auto horizontalMaxCols(int value) -> LegendSpecs&;

    /// Set the labels in the legend entries to appear before their corresponding symbols (on the left).
    auto labelsBeforeSymbols() -> LegendSpecs&;

    /// Set the labels in the legend entries to appear after their corresponding symbols (on the right).
    auto labelsAfterSymbols() -> LegendSpecs&;

    /// Set the legend labels to be left justified.
    auto labelsLeftJustify() -> LegendSpecs&;

    /// Set the legend labels to be right justified.
    auto labelsRightJustify() -> LegendSpecs&;

    /// Set the legend entries to be displayed in the order from first to last.
    auto startFromFirst() -> LegendSpecs&;

    /// Set the legend entries to be displayed in the order from last to first.
    auto startFromLast() -> LegendSpecs&;

    /// Set the spacing between the titles in the legend.
    auto spacing(int value) -> LegendSpecs&;

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

    /// The specs of the surrounding border of the legend.
    LegendBorderSpecs m_border;

    /// The title of the label.
    LegendHeaderSpecs m_header;

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

LegendSpecs::LegendSpecs()
{
    atTopRight();
    transparent();
    fontName(internal::DEFAULT_LEGEND_FONTNAME);
    fontSize(internal::DEFAULT_LEGEND_FONTSIZE);
    incrementWidth(0.0);
    incrementHeight(0.0);
    symbolLength(internal::DEFAULT_LEGEND_SAMPLE_LENGTH);
    spacing(internal::DEFAULT_LEGEND_SPACING);
    verticalDisplay();
    labelsAfterSymbols();
    labelsLeftJustify();
    startFromFirst();
}

auto LegendSpecs::opaque() -> LegendSpecs&
{
    m_opaque = "opaque";
    return *this;
}

auto LegendSpecs::transparent() -> LegendSpecs&
{
    m_opaque = "noopaque";
    return *this;
}

auto LegendSpecs::border() -> LegendBorderSpecs&
{
    return m_border;
}

auto LegendSpecs::header(std::string text) -> LegendHeaderSpecs&
{
    m_header.text(text);
    return m_header;
}

auto LegendSpecs::atLeft() -> LegendSpecs&
{
    m_placement = "inside left";
    return *this;
}

auto LegendSpecs::atRight() -> LegendSpecs&
{
    m_placement = "inside right";
    return *this;
}

auto LegendSpecs::atCenter() -> LegendSpecs&
{
    m_placement = "inside center";
    return *this;
}

auto LegendSpecs::atTop() -> LegendSpecs&
{
    m_placement = "inside center top";
    return *this;
}

auto LegendSpecs::atTopLeft() -> LegendSpecs&
{
    m_placement = "inside left top";
    return *this;
}

auto LegendSpecs::atTopRight() -> LegendSpecs&
{
    m_placement = "inside right top";
    return *this;
}

auto LegendSpecs::atBottom() -> LegendSpecs&
{
    m_placement = "inside center bottom";
    return *this;
}

auto LegendSpecs::atBottomLeft() -> LegendSpecs&
{
    m_placement = "inside left bottom";
    return *this;
}

auto LegendSpecs::atBottomRight() -> LegendSpecs&
{
    m_placement = "inside right bottom";
    return *this;
}

auto LegendSpecs::atOutsideLeft() -> LegendSpecs&
{
    m_placement = "lmargin center";
    return *this;
}

auto LegendSpecs::atOutsideLeftTop() -> LegendSpecs&
{
    m_placement = "lmargin top";
    return *this;
}

auto LegendSpecs::atOutsideLeftBottom() -> LegendSpecs&
{
    m_placement = "lmargin bottom";
    return *this;
}

auto LegendSpecs::atOutsideRight() -> LegendSpecs&
{
    m_placement = "rmargin center";
    return *this;
}

auto LegendSpecs::atOutsideRightTop() -> LegendSpecs&
{
    m_placement = "rmargin top";
    return *this;
}

auto LegendSpecs::atOutsideRightBottom() -> LegendSpecs&
{
    m_placement = "rmargin bottom";
    return *this;
}

auto LegendSpecs::atOutsideBottom() -> LegendSpecs&
{
    m_placement = "bmargin center";
    return *this;
}

auto LegendSpecs::atOutsideBottomLeft() -> LegendSpecs&
{
    m_placement = "bmargin left";
    return *this;
}

auto LegendSpecs::atOutsideBottomRight() -> LegendSpecs&
{
    m_placement = "bmargin right";
    return *this;
}

auto LegendSpecs::atOutsideTop() -> LegendSpecs&
{
    m_placement = "tmargin center";
    return *this;
}

auto LegendSpecs::atOutsideTopLeft() -> LegendSpecs&
{
    m_placement = "tmargin left";
    return *this;
}

auto LegendSpecs::atOutsideTopRight() -> LegendSpecs&
{
    m_placement = "tmargin right";
    return *this;
}

auto LegendSpecs::incrementWidth(int value) -> LegendSpecs&
{
    m_width_increment = value;
    return *this;
}

auto LegendSpecs::incrementHeight(int value) -> LegendSpecs&
{
    m_height_increment = value;
    return *this;
}

auto LegendSpecs::symbolLength(int value) -> LegendSpecs&
{
    m_samplen = value;
    return *this;
}

auto LegendSpecs::verticalDisplay() -> LegendSpecs&
{
    m_alignment = "vertical";
    return *this;
}

auto LegendSpecs::verticalMaxRows(int value) -> LegendSpecs&
{
    m_maxrows = internal::str(value);
    return *this;
}

auto LegendSpecs::horizontalDisplay() -> LegendSpecs&
{
    m_alignment = "horizontal";
    return *this;
}

auto LegendSpecs::horizontalMaxCols(int value) -> LegendSpecs&
{
    m_maxcols = internal::str(value);
    return *this;
}

auto LegendSpecs::labelsBeforeSymbols() -> LegendSpecs&
{
    m_reverse = "noreverse";
    return *this;
}

auto LegendSpecs::labelsAfterSymbols() -> LegendSpecs&
{
    m_reverse = "reverse";
    return *this;
}

auto LegendSpecs::labelsLeftJustify() -> LegendSpecs&
{
    m_justification = "Left";
    return *this;
}

auto LegendSpecs::labelsRightJustify() -> LegendSpecs&
{
    m_justification = "Right";
    return *this;
}

auto LegendSpecs::startFromFirst() -> LegendSpecs&
{
    m_invert = "noinvert";
    return *this;
}

auto LegendSpecs::startFromLast() -> LegendSpecs&
{
    m_invert = "invert";
    return *this;
}

auto LegendSpecs::spacing(int value) -> LegendSpecs&
{
    m_spacing = value;
    return *this;
}

auto LegendSpecs::repr() const -> std::string
{
    if (ShowSpecsOf<LegendSpecs>::repr() == "no")
        return "unset legend";

    std::stringstream ss;
    ss << "set key ";
    ss << m_placement << " " << m_opaque << " ";
    ss << m_border << " ";
    ss << m_alignment << " ";
    ss << m_justification << " ";
    ss << m_invert << " ";
    ss << m_reverse << " ";
    ss << "width " << m_width_increment << " ";
    ss << "height " << m_height_increment << " ";
    ss << "samplen " << m_samplen << " ";
    ss << "spacing " << m_spacing << " ";
    ss << TextSpecsOf<LegendSpecs>::repr() << " ";
    ss << "title " << m_header << " ";
    ss << "maxrows " << m_maxrows << " ";
    ss << "maxcols " << m_maxcols << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

LegendHeaderSpecs::LegendHeaderSpecs()
{
    text("");
    fontName(internal::DEFAULT_LEGEND_FONTNAME);
    fontSize(internal::DEFAULT_LEGEND_FONTSIZE);
}

LegendBorderSpecs::LegendBorderSpecs()
{
    show(internal::DEFAULT_LEGEND_BORDER_SHOW);
    lineColor(internal::DEFAULT_LEGEND_LINECOLOR);
    lineType(internal::DEFAULT_LEGEND_LINETYPE);
    lineWidth(internal::DEFAULT_LEGEND_LINEWIDTH);
    lineColor(internal::DEFAULT_LEGEND_LINECOLOR);
}

auto LegendBorderSpecs::repr() const -> std::string
{
    if (ShowSpecsOf<LegendBorderSpecs>::repr() == "no")
        return "nobox";

    std::stringstream ss;
    ss << "box " << LineSpecsOf<LegendBorderSpecs>::repr();
    return ss.str();
}

} // namespace sciplot
