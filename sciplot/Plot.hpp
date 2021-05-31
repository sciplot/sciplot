// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2021 Allan Leal, Bim Overbohm
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
#include <memory>
#include <sstream>
#include <vector>

// sciplot includes
#include <sciplot/Constants.hpp>
#include <sciplot/Default.hpp>
#include <sciplot/Enums.hpp>
#include <sciplot/IPlotImplForward.hpp>
#include <sciplot/Palettes.hpp>
#include <sciplot/PlotImpl.hpp>
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
class Plot : public internal::IPlotImplForward<internal::PlotImpl>
{
  public:
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
    // MISCELLANEOUS METHODS
    //======================================================================

    /// Convert this plot object into a gnuplot formatted string.
    auto repr() const -> std::string override;
};

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS
//======================================================================

template <typename X, typename... Vecs>
inline auto Plot::drawWithVecs(const std::string& with, const X& x, const Vecs&... vecs) -> DrawSpecs&
{
    return m_impl->drawWithVecs(with, x, vecs...);
}

template <typename X, typename... Vecs>
inline auto Plot::drawWithVecsContainingNaN(std::string with, const X& x, const Vecs&... vecs) -> DrawSpecs&
{
    return m_impl->drawWithVecsContainingNaN(with, x, vecs...);
}

template <typename X, typename Y>
inline auto Plot::drawCurve(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("lines", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawCurveWithPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("linespoints", x, y);
}

template <typename X, typename Y, typename XD>
inline auto Plot::drawCurveWithErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xerrorlines", x, y, xdelta);
}

template <typename X, typename Y, typename XL, typename XH>
inline auto Plot::drawCurveWithErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xerrorlines", x, y, xlow, xhigh);
}

template <typename X, typename Y, typename YD>
inline auto Plot::drawCurveWithErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&
{
    return m_impl->drawWithVecs("yerrorlines", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
inline auto Plot::drawCurveWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return m_impl->drawWithVecs("yerrorlines", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD, typename YD>
inline auto Plot::drawCurveWithErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xyerrorlines", x, y, xdelta, ydelta);
}

template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
inline auto Plot::drawCurveWithErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xyerrorlines", x, y, xlow, xhigh, ylow, yhigh);
}

template <typename X, typename Y>
inline auto Plot::drawBrokenCurve(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecsContainingNaN("lines", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawBrokenCurveWithPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecsContainingNaN("linespoints", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawCurveFilled(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("filledcurves", x, y);
}

template <typename X, typename Y1, typename Y2>
inline auto Plot::drawCurvesFilled(const X& x, const Y1& y1, const Y2& y2) -> DrawSpecs&
{
    return m_impl->drawWithVecs("filledcurves", x, y1, y2);
}

template <typename X, typename Y>
inline auto Plot::drawBoxes(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("boxes", x, y);
}

template <typename X, typename Y, typename XW>
inline auto Plot::drawBoxes(const X& x, const Y& y, const XW& xwidth) -> DrawSpecs&
{
    return m_impl->drawWithVecs("boxes", x, y, xwidth);
}

template <typename X, typename Y, typename YD>
inline auto Plot::drawBoxesWithErrorBarsY(const X& x, const Y& y, const Y& ydelta) -> DrawSpecs&
{
    return m_impl->drawWithVecs("boxerrorbars", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
inline auto Plot::drawBoxesWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return m_impl->drawWithVecs("boxerrorbars", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD>
inline auto Plot::drawErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xerrorbars", x, y, xdelta);
}

template <typename X, typename Y, typename XL, typename XH>
inline auto Plot::drawErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xerrorbars", x, y, xlow, xhigh);
}

template <typename X, typename Y, typename YD>
inline auto Plot::drawErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&
{
    return m_impl->drawWithVecs("yerrorbars", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
inline auto Plot::drawErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return m_impl->drawWithVecs("yerrorbars", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD, typename YD>
inline auto Plot::drawErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xyerrorbars", x, y, xdelta, ydelta);
}

template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
inline auto Plot::drawErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return m_impl->drawWithVecs("xyerrorbars", x, y, xlow, xhigh, ylow, yhigh);
}

template <typename X, typename Y>
inline auto Plot::drawSteps(const X& x, const Y& y) -> DrawSpecs&
{
    return drawStepsChangeFirstX(x, y);
}

template <typename X, typename Y>
inline auto Plot::drawStepsChangeFirstX(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("steps", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawStepsChangeFirstY(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("fsteps", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawStepsHistogram(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("histeps", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawStepsFilled(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("fillsteps", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawDots(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("dots", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("points", x, y);
}

template <typename X, typename Y>
inline auto Plot::drawImpulses(const X& x, const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("impulses", x, y);
}

template <typename Y>
inline auto Plot::drawHistogram(const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("", y); // empty string because we rely on `set style data histograms` since relying `with histograms` is not working very well (e.g., empty key/lenged appearing in columnstacked mode).
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS USING DATA FROM LOCAL FILES
//======================================================================

inline auto Plot::drawWithCols(const std::string& fname, const std::string& with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, with, cols);
}

inline auto Plot::drawCurve(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "lines", {xcol, ycol});
}

inline auto Plot::drawCurveWithPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "linespoints", {xcol, ycol});
}

inline auto Plot::drawCurveWithErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xerrorlines", {xcol, ycol, xdeltacol});
}

inline auto Plot::drawCurveWithErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xerrorlines", {xcol, ycol, xlowcol, xhighcol});
}

inline auto Plot::drawCurveWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "yerrorlines", {xcol, ycol, ydeltacol});
}

inline auto Plot::drawCurveWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "yerrorlines", {xcol, ycol, ylowcol, yhighcol});
}

inline auto Plot::drawCurveWithErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xyerrorlines", {xcol, ycol, xdeltacol, ydeltacol});
}

inline auto Plot::drawCurveWithErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xyerrorlines", {xcol, ycol, xlowcol, xhighcol, ylowcol, yhighcol});
}

inline auto Plot::drawBoxes(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "boxes", {xcol, ycol});
}

inline auto Plot::drawBoxes(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xwidthcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "boxes", {xcol, ycol, xwidthcol});
}

inline auto Plot::drawBoxesWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "boxerrorbars", {xcol, ycol, ydeltacol});
}

inline auto Plot::drawBoxesWithErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "boxerrorbars", {xcol, ycol, ylowcol, yhighcol});
}

inline auto Plot::drawErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xerrorbars", {xcol, ycol, xdeltacol});
}

inline auto Plot::drawErrorBarsX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xerrorbars", {xcol, ycol, xlowcol, xhighcol});
}

inline auto Plot::drawErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "yerrorbars", {xcol, ycol, ydeltacol});
}

inline auto Plot::drawErrorBarsY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "yerrorbars", {xcol, ycol, ylowcol, yhighcol});
}

inline auto Plot::drawErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xyerrorbars", {xcol, ycol, xdeltacol, ydeltacol});
}

inline auto Plot::drawErrorBarsXY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "xyerrorbars", {xcol, ycol, xlowcol, xhighcol, ylowcol, yhighcol});
}

inline auto Plot::drawSteps(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "steps", {xcol, ycol});
}

inline auto Plot::drawStepsChangeFirstX(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "steps", {xcol, ycol});
}

inline auto Plot::drawStepsChangeFirstY(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "fsteps", {xcol, ycol});
}

inline auto Plot::drawStepsHistogram(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "histeps", {xcol, ycol});
}

inline auto Plot::drawStepsFilled(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "fillsteps", {xcol, ycol});
}

inline auto Plot::drawDots(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "dots", {xcol, ycol});
}

inline auto Plot::drawPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "points", {xcol, ycol});
}

inline auto Plot::drawImpulses(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "impulses", {xcol, ycol});
}

inline auto Plot::drawHistogram(std::string fname, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "", {ycol});
}

//======================================================================
// MISCELLANEOUS METHODS
//======================================================================

inline auto Plot::repr() const -> std::string
{
    return m_impl->repr();
}

} // namespace sciplot
