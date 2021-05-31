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
#include <sciplot/Plot3DImpl.hpp>
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
class Plot3D : public internal::IPlotImplForward<internal::Plot3DImpl>
{
  public:
    /// Set the label of the z-axis and return a reference to the corresponding specs object.
    auto zlabel(const std::string& label) -> AxisLabelSpecs&;

    /// Set the z-range of the plot (also possible with empty values or autoscale options (e.g. "", "*")).
    auto zrange(StringOrDouble min, StringOrDouble max) -> void;

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS
    //======================================================================
    /// Draw plot object with given style and given vectors (e.g., `plot.draw("lines", x, y)`).

    template <typename X, typename... Vecs>
    auto drawWithVecs(const std::string& with, const X&, const Vecs&... vecs) -> DrawSpecs&;

    /// Draw a curve with given @p x and @p y vectors.
    template <typename X, typename Y, typename Z>
    auto drawCurve(const X& x, const Y& y, const Z& z) -> DrawSpecs&;

    /// Draw a curve with points with given @p x and @p y vectors.
    template <typename X, typename Y, typename Z>
    auto drawCurveWithPoints(const X& x, const Y& y, const Z& z) -> DrawSpecs&;

    /// Draw dots with given @p x and @p y vectors.
    template <typename X, typename Y, typename Z>
    auto drawDots(const X& x, const Y& y, const Z& z) -> DrawSpecs&;

    /// Draw points with given @p x and @p y vectors.
    template <typename X, typename Y, typename Z>
    auto drawPoints(const X& x, const Y& y, const Z& z) -> DrawSpecs&;

    /// Draw impulses with given @p x and @p y vectors.
    template <typename X, typename Y, typename Z>
    auto drawImpulses(const X& x, const Y& y, const Z& z) -> DrawSpecs&;

    /// Draw a histogram for the given @p y vector.
    template <typename Y>
    auto drawHistogram(const Y& y) -> DrawSpecs&;

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS USING DATA FROM LOCAL FILES
    //======================================================================

    /// Draw plot object with given style and given vectors (e.g., `plot.draw("lines", x, y)`).
    auto drawWithCols(const std::string& fname, const std::string& with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&;

    /// Draw a curve with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawCurve(const std::string& fname, const ColumnIndex& col, const ColumnIndex& ycol) -> DrawSpecs&;

    /// Draw a curve with points with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawCurveWithPoints(const std::string& fname, const ColumnIndex& xcol, const ColumnIndex& ycol) -> DrawSpecs&;

    /// Draw dots with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawDots(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw points with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw impulses with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawImpulses(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw a histogram with given values at @p ycol column in file @p fname.
    auto drawHistogram(const std::string& fname, ColumnIndex ycol) -> DrawSpecs&;

    //======================================================================
    // MISCELLANEOUS METHODS
    //======================================================================

    /// Convert this plot object into a gnuplot formatted string.
    auto repr() const -> std::string override;
};

inline auto Plot3D::zlabel(const std::string& label) -> AxisLabelSpecs&
{
    return m_impl->zlabel(label);
}

inline auto Plot3D::zrange(StringOrDouble min, StringOrDouble max) -> void
{
    return m_impl->zrange(min, max);
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS
//======================================================================

template <typename X, typename... Vecs>
inline auto Plot3D::drawWithVecs(const std::string& with, const X& x, const Vecs&... vecs) -> DrawSpecs&
{
    return m_impl->drawWithVecs(with, x, vecs...);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawCurve(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return m_impl->drawWithVecs("lines", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawCurveWithPoints(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{

    return m_impl->drawWithVecs("linespoints", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawDots(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return m_impl->drawWithVecs("dots", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawPoints(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return m_impl->drawWithVecs("points", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawImpulses(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return m_impl->drawWithVecs("impulses", x, y, z);
}

template <typename Y>
inline auto Plot3D::drawHistogram(const Y& y) -> DrawSpecs&
{
    return m_impl->drawWithVecs("", y); // empty string because we rely on `set style data histograms` since relying `with histograms` is not working very well (e.g., empty key/lenged appearing in columnstacked mode).
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS USING DATA FROM LOCAL FILES
//======================================================================

inline auto Plot3D::drawWithCols(const std::string& fname, const std::string& with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, with, cols);
}

inline auto Plot3D::drawCurve(const std::string& fname, const ColumnIndex& xcol, const ColumnIndex& ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "lines", {xcol, ycol});
}

inline auto Plot3D::drawCurveWithPoints(const std::string& fname, const ColumnIndex& xcol, const ColumnIndex& ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "linespoints", {xcol, ycol});
}

inline auto Plot3D::drawDots(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "dots", {xcol, ycol});
}

inline auto Plot3D::drawPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "points", {xcol, ycol});
}

inline auto Plot3D::drawImpulses(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "impulses", {xcol, ycol});
}

inline auto Plot3D::drawHistogram(const std::string& fname, ColumnIndex ycol) -> DrawSpecs&
{
    return m_impl->drawWithCols(fname, "", {ycol});
}

//======================================================================
// MISCELLANEOUS METHODS
//======================================================================

inline auto Plot3D::repr() const -> std::string
{
    return m_impl->repr();
}

} // namespace sciplot
