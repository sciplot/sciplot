// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2022 Allan Leal, Bim Overbohm
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

// C++ includes
#include <sstream>
#include <vector>

// sciplot includes
#include <sciplot/Constants.hpp>
#include <sciplot/Default.hpp>
#include <sciplot/Enums.hpp>
#include <sciplot/Palettes.hpp>
#include <sciplot/Plot.hpp>
#include <sciplot/StringOrDouble.hpp>
#include <sciplot/Utils.hpp>
#include <sciplot/specs/AxisLabelSpecs.hpp>
#include <sciplot/specs/BorderSpecs.hpp>
#include <sciplot/specs/DrawSpecs.hpp>
#include <sciplot/specs/FillStyleSpecs.hpp>
#include <sciplot/specs/FontSpecsOf.hpp>
#include <sciplot/specs/GridSpecs.hpp>
#include <sciplot/specs/HistogramStyleSpecs.hpp>
#include <sciplot/specs/LegendSpecs.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/TicsSpecs.hpp>
#include <sciplot/specs/TicsSpecsMajor.hpp>
#include <sciplot/specs/TicsSpecsMinor.hpp>

namespace sciplot
{

/// The class used to create a plot containing graphical elements.
class Plot2D : public Plot
{
  public:
    /// Construct a default Plot object
    Plot2D();

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS
    //======================================================================
    /// Draw plot object with given style and given vectors (e.g., `plot.draw("lines", x, y)`).
    template <typename X, typename... Vecs>
    auto drawWithVecs(const std::string& with, const X&, const Vecs&... vecs) -> DrawSpecs&;

    /// Draw plot object with given style and given vectors (e.g., `plot.draw("lines", x, y)`) that may contain NaN values.
    template <typename X, typename... Vecs>
    auto drawWithVecsContainingNaN(std::string with, const X&, const Vecs&... vecs) -> DrawSpecs&;

    /// Draw a curve with given @p x and @p y vectors.
    template <typename X, typename Y>
    auto drawCurve(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw a curve with points with given @p x and @p y vectors.
    template <typename X, typename Y>
    auto drawCurveWithPoints(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* with given @p x, @p y, and @p xdelta vectors.
    template <typename X, typename Y, typename XD>
    auto drawCurveWithErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* with given @p x, @p y, @p xlow, and @p xhigh vectors.
    template <typename X, typename Y, typename XL, typename XH>
    auto drawCurveWithErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&;

    /// Draw a curve with error bars along *y* with given @p x, @p y, and @p ydelta vectors.
    template <typename X, typename Y, typename YD>
    auto drawCurveWithErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&;

    /// Draw a curve with error bars along *y* with given @p x, @p y, @p ylow, and @p yhigh vectors.
    template <typename X, typename Y, typename YL, typename YH>
    auto drawCurveWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* and *y* with given @p x, @p y, @p xdelta, and @p ydelta vectors.
    template <typename X, typename Y, typename XD, typename YD>
    auto drawCurveWithErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* and *y* with given @p x, @p y, @p xlow, @p xhigh, @p ylow, and @p yhigh vectors.
    template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
    auto drawCurveWithErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&;

    /// Draw a curve with given @p x and @p y vectors, breaking this curve whenever NaN is found in @p x or @p y.
    template <typename X, typename Y>
    auto drawBrokenCurve(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw a curve with points with given @p x and @p y vectors, breaking this curve whenever NaN is found in @p x or @p y.
    template <typename X, typename Y>
    auto drawBrokenCurveWithPoints(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw curves with given @p x and @p y vectors with filled areas above / below axes.
    template <typename X, typename Y>
    auto drawCurveFilled(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw curves with given @p x, @p y1 and @p y2 vectors with filled areas above / below / between curves.
    template <typename X, typename Y1, typename Y2>
    auto drawCurvesFilled(const X& x, const Y1& y1, const Y2& y2) -> DrawSpecs&;

    /// Draw boxes with given @p x and @p y vectors.
    template <typename X, typename Y>
    auto drawBoxes(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw boxes with given @p x and @p y vectors as well as the box widths @p xwidth.
    template <typename X, typename Y, typename XW>
    auto drawBoxes(const X& x, const Y& y, const XW& xwidth) -> DrawSpecs&;

    /// Draw boxes with error bars along *y* with given @p x, @p y, @p ydelta vectors.
    template <typename X, typename Y, typename YD>
    auto drawBoxesWithErrorBarsY(const X& x, const Y& y, const Y& ydelta) -> DrawSpecs&;

    /// Draw boxes with error bars along *y* with given @p x, @p y, @p ylow, and @p yhigh vectors.
    template <typename X, typename Y, typename YL, typename YH>
    auto drawBoxesWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&;

    /// Draw error bars along *x* with given @p x, @p y, and @p xdelta vectors.
    template <typename X, typename Y, typename XD>
    auto drawErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&;

    /// Draw error bars along *x* with given @p x, @p y, @p xlow, and @p xhigh vectors.
    template <typename X, typename Y, typename XL, typename XH>
    auto drawErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&;

    /// Draw error bars along *y* with given @p x, @p y, and @p ydelta vectors.
    template <typename X, typename Y, typename YD>
    auto drawErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&;

    /// Draw error bars along *y* with given @p x, @p y, @p ylow, and @p yhigh vectors.
    template <typename X, typename Y, typename YL, typename YH>
    auto drawErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&;

    /// Draw error bars along *x* and *y* with given @p x, @p y, @p xdelta, and @p ydelta vectors.
    template <typename X, typename Y, typename XD, typename YD>
    auto drawErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&;

    /// Draw error bars along *x* and *y* with given @p x, @p y, @p xlow, @p xhigh, @p ylow, and @p yhigh vectors.
    template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
    auto drawErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&;

    /// Draw steps with given @p x and @p y vectors. Identical to @ref drawStepsChangeFirstX.
    template <typename X, typename Y>
    auto drawSteps(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw steps with given @p x and @p y vectors with steps along *x* changes first.
    template <typename X, typename Y>
    auto drawStepsChangeFirstX(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw steps with given @p x and @p y vectors with steps along *y* changes first.
    template <typename X, typename Y>
    auto drawStepsChangeFirstY(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw steps with given @p x and @p y vectors in a histogram style
    template <typename X, typename Y>
    auto drawStepsHistogram(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw steps with given @p x and @p y vectors with filled area below steps.
    template <typename X, typename Y>
    auto drawStepsFilled(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw dots with given @p x and @p y vectors.
    template <typename X, typename Y>
    auto drawDots(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw points with given @p x and @p y vectors.
    template <typename X, typename Y>
    auto drawPoints(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw impulses with given @p x and @p y vectors.
    template <typename X, typename Y>
    auto drawImpulses(const X& x, const Y& y) -> DrawSpecs&;

    /// Draw a histogram for the given @p y vector.
    template <typename Y>
    auto drawHistogram(const Y& y) -> DrawSpecs&;

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS USING DATA FROM LOCAL FILES
    //======================================================================

    /// Draw plot object with given style and given vectors (e.g., `plot.draw("lines", x, y)`).
    auto drawWithCols(const std::string& fname, const std::string& with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&;

    /// Draw a curve with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawCurve(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw a curve with points with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawCurveWithPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* with given values at @p xcol, @p ycol, and @p xdeltacol columns in file @p fname.
    auto drawCurveWithErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* with given values at @p xcol, @p ycol, @p xlowcol, and @p xhighcol columns in file @p fname.
    auto drawCurveWithErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&;

    /// Draw a curve with error bars along *y* with given values at @p xcol, @p ycol, and @p ydeltacol columns in file @p fname.
    auto drawCurveWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw a curve with error bars along *y* with given values at @p xcol, @p ycol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawCurveWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xdeltacol, and @p ydeltacol columns in file @p fname.
    auto drawCurveWithErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xlowcol, @p xhighcol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawCurveWithErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw boxes with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawBoxes(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw boxes with given values at @p xcol and @p ycol columns in file @p fname as well as the box widths @p xwidthcol.
    auto drawBoxes(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xwidthcol) -> DrawSpecs&;

    /// Draw boxes with error bars along *y* with given values at @p xcol, @p ycol, @p ydeltacol columns in file @p fname.
    auto drawBoxesWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw boxes with error bars along *y* with given values at @p xcol, @p ycol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawBoxesWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw error bars along *x* with given values at @p xcol, @p ycol, and @p xdeltacol columns in file @p fname.
    auto drawErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&;

    /// Draw error bars along *x* with given values at @p xcol, @p ycol, @p xlowcol, and @p xhighcol columns in file @p fname.
    auto drawErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&;

    /// Draw error bars along *y* with given values at @p xcol, @p ycol, and @p ydeltacol columns in file @p fname.
    auto drawErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw error bars along *y* with given values at @p xcol, @p ycol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xdeltacol, and @p ydeltacol columns in file @p fname.
    auto drawErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xlowcol, @p xhighcol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname. Identical to @ref drawStepsChangeFirstX.
    auto drawSteps(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname with steps along *x* changes first.
    auto drawStepsChangeFirstX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname with steps along *y* changes first.
    auto drawStepsChangeFirstY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname in a histogram style
    auto drawStepsHistogram(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname with filled area below steps.
    auto drawStepsFilled(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw dots with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawDots(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw points with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw impulses with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawImpulses(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw a histogram with given values at @p ycol column in file @p fname.
    auto drawHistogram(std::string fname, ColumnIndex ycol) -> DrawSpecs&;

    //======================================================================
    // MISCElLANEOUS METHODS
    //======================================================================

    /// Convert this plot object into a gnuplot formatted string.
    auto repr() const -> std::string override;
};

inline Plot2D::Plot2D()
    : Plot()
{
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS
//======================================================================

template <typename X, typename... Vecs>
inline auto Plot2D::drawWithVecs(const std::string& with, const X& x, const Vecs&... vecs) -> DrawSpecs&
{
    // Write the given vectors x and y as a new data set to the stream
    std::ostringstream datastream;
    gnuplot::writedataset(datastream, m_numdatasets, x, vecs...);

    // Set the using string to "" if X is not vector of strings.
    // Otherwise, x contain xtics strings. Set the `using` string
    // so that these are properly used as xtics.
    std::string use;
    if constexpr (internal::isStringVector<X>)
    {
        const auto nvecs = sizeof...(Vecs);
        use = "0:"; // here, column 0 means the pseudo column with numbers 0, 1, 2, 3...
        for (auto i = 2; i <= nvecs + 1; ++i)
            use += std::to_string(i) + ":"; // this constructs 0:2:3:4:
        use += "xtic(1)"; // this terminates the string with 0:2:3:4:xtic(1), and thus column 1 is used for the xtics
    }

    // Append new data set to existing data
    m_data += datastream.str();

    // Draw the data saved using a data set with index `m_numdatasets`. Increase number of data sets and set the line style specification (desired behavior is 1, 2, 3 (incrementing as new lines are plotted)).
    return draw("'" + m_datafilename + "' index " + internal::str(m_numdatasets++), use, with).lineStyle(static_cast<int>(m_drawspecs.size()));
}

template <typename X, typename... Vecs>
inline auto Plot2D::drawWithVecsContainingNaN(std::string with, const X& x, const Vecs&... vecs) -> DrawSpecs&
{
    // Write the given vectors x and y as a new data set to the stream
    std::ostringstream datastream;
    gnuplot::writedataset(datastream, m_numdatasets, x, vecs...);

    std::string use;
    const auto nvecs = sizeof...(Vecs);
    use = "0:"; // here, column 0 means the pseudo column with numbers 0, 1, 2, 3...
    for (auto i = 2; i <= nvecs + 1; ++i)
        use += "($" + std::to_string(i) + "):"; // this constructs 0:$(2):$(3):$(4):
    use += "xtic(1)"; // this terminates the string with 0:$(2):$(3):$(4):xtic(1), and thus column 1 is used for the xtics

    // Append new data set to existing data
    m_data += datastream.str();

    // Draw the data saved using a data set with index `m_numdatasets`. Increase number of data sets and set the line style specification (desired behavior is 1, 2, 3 (incrementing as new lines are plotted)).
    return draw("'" + m_datafilename + "' index " + internal::str(m_numdatasets++), use, with).lineStyle(static_cast<int>(m_drawspecs.size()));
}

template <typename X, typename Y>
inline auto Plot2D::drawCurve(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("lines", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawCurveWithPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("linespoints", x, y);
}

template <typename X, typename Y, typename XD>
inline auto Plot2D::drawCurveWithErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&
{
    return drawWithVecs("xerrorlines", x, y, xdelta);
}

template <typename X, typename Y, typename XL, typename XH>
inline auto Plot2D::drawCurveWithErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&
{
    return drawWithVecs("xerrorlines", x, y, xlow, xhigh);
}

template <typename X, typename Y, typename YD>
inline auto Plot2D::drawCurveWithErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("yerrorlines", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
inline auto Plot2D::drawCurveWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("yerrorlines", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD, typename YD>
inline auto Plot2D::drawCurveWithErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("xyerrorlines", x, y, xdelta, ydelta);
}

template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
inline auto Plot2D::drawCurveWithErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("xyerrorlines", x, y, xlow, xhigh, ylow, yhigh);
}

template <typename X, typename Y>
inline auto Plot2D::drawBrokenCurve(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecsContainingNaN("lines", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawBrokenCurveWithPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecsContainingNaN("linespoints", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawCurveFilled(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("filledcurves", x, y);
}

template <typename X, typename Y1, typename Y2>
inline auto Plot2D::drawCurvesFilled(const X& x, const Y1& y1, const Y2& y2) -> DrawSpecs&
{
    return drawWithVecs("filledcurves", x, y1, y2);
}

template <typename X, typename Y>
inline auto Plot2D::drawBoxes(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("boxes", x, y);
}

template <typename X, typename Y, typename XW>
inline auto Plot2D::drawBoxes(const X& x, const Y& y, const XW& xwidth) -> DrawSpecs&
{
    return drawWithVecs("boxes", x, y, xwidth);
}

template <typename X, typename Y, typename YD>
inline auto Plot2D::drawBoxesWithErrorBarsY(const X& x, const Y& y, const Y& ydelta) -> DrawSpecs&
{
    return drawWithVecs("boxerrorbars", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
inline auto Plot2D::drawBoxesWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("boxerrorbars", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD>
inline auto Plot2D::drawErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&
{
    return drawWithVecs("xerrorbars", x, y, xdelta);
}

template <typename X, typename Y, typename XL, typename XH>
inline auto Plot2D::drawErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&
{
    return drawWithVecs("xerrorbars", x, y, xlow, xhigh);
}

template <typename X, typename Y, typename YD>
inline auto Plot2D::drawErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("yerrorbars", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
inline auto Plot2D::drawErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("yerrorbars", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD, typename YD>
inline auto Plot2D::drawErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("xyerrorbars", x, y, xdelta, ydelta);
}

template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
inline auto Plot2D::drawErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("xyerrorbars", x, y, xlow, xhigh, ylow, yhigh);
}

template <typename X, typename Y>
inline auto Plot2D::drawSteps(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecsStepsChangeFirstX(x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawStepsChangeFirstX(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("steps", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawStepsChangeFirstY(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("fsteps", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawStepsHistogram(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("histeps", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawStepsFilled(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("fillsteps", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawDots(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("dots", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("points", x, y);
}

template <typename X, typename Y>
inline auto Plot2D::drawImpulses(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("impulses", x, y);
}

template <typename Y>
inline auto Plot2D::drawHistogram(const Y& y) -> DrawSpecs&
{
    return drawWithVecs("", y); // empty string because we rely on `set style data histograms` since relying `with histograms` is not working very well (e.g., empty key/lenged appearing in columnstacked mode).
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS USING DATA FROM LOCAL FILES
//======================================================================

inline auto Plot2D::drawWithCols(const std::string& fname, const std::string& with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&
{
    std::string use;
    for (const auto& col : cols)
        use += col.value + ":"; // e.g., "1:4:5:7:" (where 1 is x, 4 is y, 5 is ylow and 7 is yhigh for a yerrorlines plot)
    use = internal::trimright(use, ':'); // e.g., "1:4:5:7:" => "1:4:5:7"
    std::string what = "'" + fname + "'"; // e.g., "'myfile.dat'"
    return draw(what, use, with).lineStyle(static_cast<int>(m_drawspecs.size())); // e.g., draw(what="'myfile.dat'", use="1:2", with="lines");
}

inline auto Plot2D::drawCurve(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "lines", {xcol, ycol});
}

inline auto Plot2D::drawCurveWithPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "linespoints", {xcol, ycol});
}

inline auto Plot2D::drawCurveWithErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorlines", {xcol, ycol, xdeltacol});
}

inline auto Plot2D::drawCurveWithErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorlines", {xcol, ycol, xlowcol, xhighcol});
}

inline auto Plot2D::drawCurveWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorlines", {xcol, ycol, ydeltacol});
}

inline auto Plot2D::drawCurveWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorlines", {xcol, ycol, ylowcol, yhighcol});
}

inline auto Plot2D::drawCurveWithErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorlines", {xcol, ycol, xdeltacol, ydeltacol});
}

inline auto Plot2D::drawCurveWithErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorlines", {xcol, ycol, xlowcol, xhighcol, ylowcol, yhighcol});
}

inline auto Plot2D::drawBoxes(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxes", {xcol, ycol});
}

inline auto Plot2D::drawBoxes(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xwidthcol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxes", {xcol, ycol, xwidthcol});
}

inline auto Plot2D::drawBoxesWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxerrorbars", {xcol, ycol, ydeltacol});
}

inline auto Plot2D::drawBoxesWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxerrorbars", {xcol, ycol, ylowcol, yhighcol});
}

inline auto Plot2D::drawErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorbars", {xcol, ycol, xdeltacol});
}

inline auto Plot2D::drawErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorbars", {xcol, ycol, xlowcol, xhighcol});
}

inline auto Plot2D::drawErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorbars", {xcol, ycol, ydeltacol});
}

inline auto Plot2D::drawErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorbars", {xcol, ycol, ylowcol, yhighcol});
}

inline auto Plot2D::drawErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorbars", {xcol, ycol, xdeltacol, ydeltacol});
}

inline auto Plot2D::drawErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorbars", {xcol, ycol, xlowcol, xhighcol, ylowcol, yhighcol});
}

inline auto Plot2D::drawSteps(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "steps", {xcol, ycol});
}

inline auto Plot2D::drawStepsChangeFirstX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "steps", {xcol, ycol});
}

inline auto Plot2D::drawStepsChangeFirstY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "fsteps", {xcol, ycol});
}

inline auto Plot2D::drawStepsHistogram(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "histeps", {xcol, ycol});
}

inline auto Plot2D::drawStepsFilled(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "fillsteps", {xcol, ycol});
}

inline auto Plot2D::drawDots(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "dots", {xcol, ycol});
}

inline auto Plot2D::drawPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "points", {xcol, ycol});
}

inline auto Plot2D::drawImpulses(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "impulses", {xcol, ycol});
}

inline auto Plot2D::drawHistogram(std::string fname, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "", {ycol});
}

//======================================================================
// MISCElLANEOUS METHODS
//======================================================================

inline auto Plot2D::repr() const -> std::string
{
    std::stringstream script;
    // Add plot setup commands
    script << "#==============================================================================" << std::endl;
    script << "# SETUP COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    // Add palette info if a palette was set
    if (!m_palette.empty())
    {
        gnuplot::palettecmd(script, m_palette);
    }
    script << gnuplot::cmdValueStr("set xrange", m_xrange);
    script << gnuplot::cmdValueStr("set yrange", m_yrange);
    script << m_xlabel << std::endl;
    script << m_ylabel << std::endl;
    script << m_rlabel << std::endl;
    script << m_border << std::endl;
    script << m_grid << std::endl;
    script << m_style_fill << std::endl;
    script << m_style_histogram << std::endl;
    script << m_tics << std::endl;
    script << m_xtics_major_bottom << std::endl;
    script << m_xtics_major_top << std::endl;
    script << m_xtics_minor_bottom << std::endl;
    script << m_xtics_minor_top << std::endl;
    script << m_ytics_major_left << std::endl;
    script << m_ytics_major_right << std::endl;
    script << m_ytics_minor_left << std::endl;
    script << m_ytics_minor_right << std::endl;
    script << m_ztics_major << std::endl;
    script << m_ztics_minor << std::endl;
    script << m_rtics_major << std::endl;
    script << m_rtics_minor << std::endl;
    script << m_legend << std::endl;
    script << gnuplot::cmdValueStr("set boxwidth", m_boxwidth);
    script << gnuplot::cmdValueStr("set samples", m_samples);
    script << gnuplot::cmdValueStr("set datafile missing", MISSING_INDICATOR);
    // Add custom gnuplot commands
    if (!m_customcmds.empty())
    {
        script << "#==============================================================================" << std::endl;
        script << "# CUSTOM EXPLICIT GNUPLOT COMMANDS" << std::endl;
        script << "#==============================================================================" << std::endl;
        for (const auto& c : m_customcmds)
        {
            script << c << std::endl;
        }
    }
    // Add the actual plot commands for all drawXYZ() calls
    script << "#==============================================================================" << std::endl;
    script << "# PLOT COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << "plot \\\n"; // use `\` to have a plot command in each individual line!
    // Write plot commands and style per plot
    const auto n = m_drawspecs.size();
    for (std::size_t i = 0; i < n; ++i)
    {
        script << "    " << m_drawspecs[i] << (i < n - 1 ? ", \\\n" : ""); // consider indentation with 4 spaces!
    }
    // Add an empty line after plots
    script << std::endl;
    // unset palette info if a palette was set
    if (!m_palette.empty())
    {
        gnuplot::unsetpalettecmd(script);
    }
    // Add an empty line at the end
    script << std::endl;
    return script.str();
}

} // namespace sciplot
