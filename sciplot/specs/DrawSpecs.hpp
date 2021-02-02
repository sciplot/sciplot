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
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/PointSpecsOf.hpp>
#include <sciplot/specs/FillSpecsOf.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// Auxiliary type used in methods that accept column index using either integers or strings.
struct ColumnIndex
{
    /// Construct a default ColumnIndex object.
    ColumnIndex() {}

    /// Construct a ColumnIndex object with given integer.
    ColumnIndex(int col) : value(std::to_string(col)) {} // 1 => "1"

    /// Construct a ColumnIndex object with given string.
    ColumnIndex(std::string col) : value("'" + col + "'") {} // "Name" => "'Name'"

    /// Construct a ColumnIndex object with given string.
    ColumnIndex(const char* col) : ColumnIndex(std::string(col)) {}

    /// The column index value.
    std::string value;
};

/// The class used to attach draw options to a plot element being drawn.
template <typename DerivedSpecs>
class DrawSpecsOf : virtual public Specs<DerivedSpecs>
{
public:
    /// Construct a DrawSpecsOf instance.
    /// @param datafile The path to the file containing the data to be plotted.
    /// @param plotstyle The plot style to be used for the draw operation (e.g., "lines", "points", "histograms", "dots", etc.).
    explicit DrawSpecsOf(std::string datafile, std::string plotstyle)
    : m_datafile(datafile), m_plotstyle(plotstyle)
    {}

    /// Set the legend label of the plotted element.
    auto legendLabel(std::string text) -> DrawSpecsOf&
    {
        m_title = "title '" + text + "'";
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the legend label of the plotted element to be retrieved from the header of column.
    auto legendLabelFromColumnHeader() -> DrawSpecsOf&
    {
        m_title = "title columnheader";
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the legend label of the plotted element to be retrieved from the header of a column with given index.
    auto legendLabelFromColumnHeader(int icolumn) -> DrawSpecsOf&
    {
        m_title = "title columnheader(" + std::to_string(icolumn) + ")";
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the legend label of the plotted element to be ignored.
    auto legendLabelNone() -> DrawSpecsOf&
    {
        m_title = "title notitle";
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the legend label to be determined automatically from the plot expression.
    auto legendLabelDefault() -> DrawSpecsOf&
    {
        m_title = "";
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the format of the plot (lines, points, linespoints).
    auto with(std::string value) -> DrawSpecsOf&
    {
        m_with = value;
        return static_cast<DerivedSpecs&>(*this);
    }

    /// The column in the data file containing the x values.
    auto xcolumn(ColumnIndex icol) -> DerivedSpecs&
    {
        m_xcol = icol.value; // an integer string such as "1" or a column name such as "'Name'"
        if(m_xtic.empty())
            xtic(icol);
        return static_cast<DerivedSpecs&>(*this);
    }

    /// The column in the data file containing the y values.
    auto ycolumn(ColumnIndex icol) -> DerivedSpecs&
    {
        m_ycol = icol.value; // an integer string such as "1" or a column name such as "'Name'"
        if(m_ytic.empty())
            ytic(icol);
        return static_cast<DerivedSpecs&>(*this);
    }

    /// The column in the data file containing the x tic labels.
    auto xtic(ColumnIndex icol) -> DerivedSpecs&
    {
        m_xtic = "xtic(stringcolumn(" + icol.value + "))"; // xtic(stringcolumn(1)) or xtic(stringcolumn('Name'))
        return static_cast<DerivedSpecs&>(*this);
    }

    /// The column in the data file containing the y tic labels.
    auto ytic(ColumnIndex icol) -> DerivedSpecs&
    {
        m_ytic = "ytic(stringcolumn(" + icol.value + "))"; // ytic(stringcolumn(1)) or ytic(stringcolumn('Name'))
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Convert this DrawSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string
    {
        std::string using_expr = "using " +
            m_xcol + ":" + m_ycol + ":" + m_xtic + ":" + m_ytic;

        using_expr = internal::trimright(using_expr, ':'); // remove any leading `:` in string `using_expr`

        std::stringstream ss;
        ss << "'" << m_datafile << "'" << " ";
        ss << using_expr << " ";
        ss << m_title << " ";
        ss << "with " << m_plotstyle << " ";
        return internal::removeExtraWhitespaces(ss.str());
    }

protected:
    /// The path to the file containing the data to be plotted.
    std::string m_datafile;

    /// The plot style to be used for the draw operation (e.g., "lines", "points", "histograms", "dots", etc.).
    std::string m_plotstyle;

    /// The title (i.e., legend label) of the plotted element as a gnuplot formatted string (e.g., "title 'sin(x)'").
    std::string m_title;

    /// The style of the plot (lines, points, linespoints) as a gnuplot formatted string (e.g., "with linespoints").
    std::string m_with;

    /// Select which columns from the data file to use for plot data or tick labels (e.g. "using 1:xtic(2)").
    std::string m_using;

    /// The column in the data file containing the x values.
    std::string m_xcol = "0";

    /// The column in the data file containing the y values.
    std::string m_ycol = "1";

    /// The column in the data file containing the x tic labels.
    std::string m_xtic = "";

    /// The column in the data file containing the y tic labels.
    std::string m_ytic = "";
};

/// The class used to specify options to a plot element being drawn that has line properties.
class DrawSpecsWithLineProps : public DrawSpecsOf<DrawSpecsWithLineProps>, public LineSpecsOf<DrawSpecsWithLineProps>
{
public:
    /// Construct a DrawSpecsWithLineProps instance.
    explicit DrawSpecsWithLineProps(std::string datafile, std::string plotstyle)
    : DrawSpecsOf<DrawSpecsWithLineProps>(datafile, plotstyle)
    {}

    /// Convert this DrawSpecsWithLineProps object into a gnuplot formatted string.
    auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << DrawSpecsOf<DrawSpecsWithLineProps>::repr() << " ";
        ss << LineSpecsOf<DrawSpecsWithLineProps>::repr();
        return internal::removeExtraWhitespaces(ss.str());
    }
};

/// The class used to specify options to a plot element being drawn that has point properties.
class DrawSpecsWithPointProps : public DrawSpecsOf<DrawSpecsWithPointProps>, public PointSpecsOf<DrawSpecsWithPointProps>
{
public:
    /// Construct a DrawSpecsWithPointProps instance.
    explicit DrawSpecsWithPointProps(std::string datafile, std::string plotstyle)
    : DrawSpecsOf<DrawSpecsWithPointProps>(datafile, plotstyle)
    {}

    /// Convert this DrawSpecsWithPointProps object into a gnuplot formatted string.
    auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << DrawSpecsOf<DrawSpecsWithPointProps>::repr() << " ";
        ss << PointSpecsOf<DrawSpecsWithPointProps>::repr();
        return internal::removeExtraWhitespaces(ss.str());
    }
};

/// The class used to specify options to a plot element being drawn that has line and point properties.
class DrawSpecsWithLinePointProps : public DrawSpecsOf<DrawSpecsWithLinePointProps>, public LineSpecsOf<DrawSpecsWithLinePointProps>, public PointSpecsOf<DrawSpecsWithLinePointProps>
{
public:
    /// Construct a DrawSpecsWithLinePointProps instance.
    explicit DrawSpecsWithLinePointProps(std::string datafile, std::string plotstyle)
    : DrawSpecsOf<DrawSpecsWithLinePointProps>(datafile, plotstyle)
    {}

    /// Convert this DrawSpecsWithLinePointProps object into a gnuplot formatted string.
    auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << DrawSpecsOf<DrawSpecsWithLinePointProps>::repr() << " ";
        ss << LineSpecsOf<DrawSpecsWithLinePointProps>::repr() << " ";
        ss << PointSpecsOf<DrawSpecsWithLinePointProps>::repr();
        return internal::removeExtraWhitespaces(ss.str());
    }
};

/// The class used to specify options to a plot element being drawn that has line and fill properties.
class DrawSpecsWithLineFillProps : public DrawSpecsOf<DrawSpecsWithLineFillProps>, public LineSpecsOf<DrawSpecsWithLineFillProps>, public FillSpecsOf<DrawSpecsWithLineFillProps>
{
public:
    /// Construct a DrawSpecsWithLineFillProps instance.
    explicit DrawSpecsWithLineFillProps(std::string datafile, std::string plotstyle)
    : DrawSpecsOf<DrawSpecsWithLineFillProps>(datafile, plotstyle)
    {}

    /// Convert this DrawSpecsWithLineFillProps object into a gnuplot formatted string.
    auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << DrawSpecsOf<DrawSpecsWithLineFillProps>::repr() << " ";
        ss << LineSpecsOf<DrawSpecsWithLineFillProps>::repr() << " ";
        ss << FillSpecsOf<DrawSpecsWithLineFillProps>::repr();
        return internal::removeExtraWhitespaces(ss.str());
    }
};

} // namespace sciplot
