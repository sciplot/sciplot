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
class Plot3D : public Plot
{
  public:
    /// Construct a default Plot object
    Plot3D();

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
    // MISCElLANEOUS METHODS
    //======================================================================

    /// Convert this plot object into a gnuplot formatted string.
    auto repr() const -> std::string override;

  private:
    std::string m_zrange; ///< The z-range of the plot as a gnuplot formatted string (e.g., "set yrange [0:1]")
    AxisLabelSpecs m_zlabel; ///< The label of the z-axis
};

inline Plot3D::Plot3D()
    : Plot(), m_zlabel("z")
{
}

inline auto Plot3D::zlabel(const std::string& label) -> AxisLabelSpecs&
{
    m_zlabel.text(label);
    return m_zlabel;
}

inline auto Plot3D::zrange(StringOrDouble min, StringOrDouble max) -> void
{
    m_zrange = "[" + min.value + ":" + max.value + "]";
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS
//======================================================================

template <typename X, typename... Vecs>
inline auto Plot3D::drawWithVecs(const std::string& with, const X& x, const Vecs&... vecs) -> DrawSpecs&
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

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawCurve(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return drawWithVecs("lines", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawCurveWithPoints(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{

    return drawWithVecs("linespoints", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawDots(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return drawWithVecs("dots", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawPoints(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return drawWithVecs("points", x, y, z);
}

template <typename X, typename Y, typename Z>
inline auto Plot3D::drawImpulses(const X& x, const Y& y, const Z& z) -> DrawSpecs&
{
    return drawWithVecs("impulses", x, y, z);
}

template <typename Y>
inline auto Plot3D::drawHistogram(const Y& y) -> DrawSpecs&
{
    return drawWithVecs("", y); // empty string because we rely on `set style data histograms` since relying `with histograms` is not working very well (e.g., empty key/lenged appearing in columnstacked mode).
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS USING DATA FROM LOCAL FILES
//======================================================================

inline auto Plot3D::drawWithCols(const std::string& fname, const std::string& with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&
{
    std::string use;
    for (const auto& col : cols)
        use += col.value + ":"; // e.g., "1:4:5:7:" (where 1 is x, 4 is y, 5 is ylow and 7 is yhigh for a yerrorlines plot)
    use = internal::trimright(use, ':'); // e.g., "1:4:5:7:" => "1:4:5:7"
    std::string what = "'" + fname + "'"; // e.g., "'myfile.dat'"
    return draw(what, use, with).lineStyle(static_cast<int>(m_drawspecs.size())); // e.g., draw(what="'myfile.dat'", use="1:2", with="lines");
}

inline auto Plot3D::drawCurve(const std::string& fname, const ColumnIndex& xcol, const ColumnIndex& ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "lines", {xcol, ycol});
}

inline auto Plot3D::drawCurveWithPoints(const std::string& fname, const ColumnIndex& xcol, const ColumnIndex& ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "linespoints", {xcol, ycol});
}

inline auto Plot3D::drawDots(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "dots", {xcol, ycol});
}

inline auto Plot3D::drawPoints(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "points", {xcol, ycol});
}

inline auto Plot3D::drawImpulses(const std::string& fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "impulses", {xcol, ycol});
}

inline auto Plot3D::drawHistogram(const std::string& fname, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "", {ycol});
}

//======================================================================
// MISCElLANEOUS METHODS
//======================================================================

inline auto Plot3D::repr() const -> std::string
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
    script << gnuplot::cmdValueStr("set zrange", m_zrange);
    script << m_xlabel << std::endl;
    script << m_ylabel << std::endl;
    script << m_zlabel << std::endl;
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
    // unset palette info if a palette was set
    if (!m_palette.empty())
    {
        gnuplot::unsetpalettecmd(script);
    }
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
    script << "splot \\\n"; // use `\` to have a plot command in each individual line!
    // Write plot commands and style per plot
    const auto n = m_drawspecs.size();
    for (std::size_t i = 0; i < n; ++i)
    {
        script << "    " << m_drawspecs[i] << (i < n - 1 ? ", \\\n" : ""); // consider indentation with 4 spaces!
    }
    // Add an empty line at the end
    script << std::endl;
    return script.str();
}

} // namespace sciplot
