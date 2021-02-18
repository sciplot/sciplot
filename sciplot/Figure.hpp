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

// C++ includes
#include <sstream>
#include <vector>

// sciplot includes
#include <sciplot/Constants.hpp>
#include <sciplot/Default.hpp>
#include <sciplot/Enums.hpp>
#include <sciplot/Palettes.hpp>
#include <sciplot/specs/AxisLabelSpecs.hpp>
#include <sciplot/specs/BorderSpecs.hpp>
#include <sciplot/specs/DrawSpecs.hpp>
#include <sciplot/specs/FillStyleSpecs.hpp>
#include <sciplot/specs/GridSpecs.hpp>
#include <sciplot/specs/HistogramStyleSpecs.hpp>
#include <sciplot/specs/LegendSpecs.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/DrawSpecs.hpp>
#include <sciplot/specs/TicsSpecs.hpp>
#include <sciplot/specs/TicsSpecsMajor.hpp>
#include <sciplot/specs/TicsSpecsMajor.hpp>
#include <sciplot/specs/TicsSpecsMinor.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to create figures containing plots and other graphical elements.
class Figure
{
  public:
    /// Construct a default Figure object
    Figure();

    /// Set the palette of colors for the plot.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto palette(std::string name) -> void;

    /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
    auto size(std::size_t width, std::size_t height) -> void;

    /// Set the label of the x-axis and return a reference to the corresponding specs object.
    auto xlabel(std::string label) -> AxisLabelSpecs&;

    /// Set the label of the y-axis and return a reference to the corresponding specs object.
    auto ylabel(std::string label) -> AxisLabelSpecs&;

    /// Set the x-range of the plot.
    auto xrange(double min, double max) -> void;

    /// Set the y-range of the plot.
    auto yrange(double min, double max) -> void;

    /// Set the default width of boxes in plots containing boxes (in absolute mode).
    /// In absolute mode, a unit width is equivalent to one unit of length along the *x* axis.
    auto boxWidthAbsolute(double val) -> void;

    /// Set the default width of boxes in plots containing boxes (in relative mode).
    /// In relative mode, a unit width is equivalent to setting the boxes side by side.
    auto boxWidthRelative(double val) -> void;

    /// Set the border of the plot and return a reference to the corresponding specs object.
    auto border() -> BorderSpecs& { return m_border; }

    /// Set the grid of the plot and return a reference to the corresponding specs object.
    auto grid() -> GridSpecs& { return m_grid; }

    //======================================================================
    // METHODS FOR CUSTOMIZATION OF STYLES
    //======================================================================

    /// Return an object that permits fill style to be customized.
    auto styleFill() -> FillStyleSpecs& { return m_style_fill; }

    /// Return an object that permits histogram style to be customized.
    auto styleHistogram() -> HistogramStyleSpecs& { return m_style_histogram; }

    //======================================================================
    // METHODS FOR CUSTOMIZATION OF TICS
    //======================================================================

    /// Set the tics of the plot and return a reference to the corresponding specs object.
    auto tics() -> TicsSpecs& { return m_tics; }

    /// Return the specifications of the grid lines along major xtics on the bottom axis.
    auto xtics() -> TicsSpecsMajor& { return xticsMajorBottom(); }

    /// Return the specifications of the grid lines along major ytics on the left axis.
    auto ytics() -> TicsSpecsMajor& { return yticsMajorLeft(); }

    /// Return the specifications of the grid lines along major ztics.
    auto ztics() -> TicsSpecsMajor& { return zticsMajor(); }

    /// Return the specifications of the grid lines along major rtics.
    auto rtics() -> TicsSpecsMajor& { return rticsMajor(); }

    /// Return the specifications of the grid lines along major xtics on the bottom axis.
    auto xticsMajorBottom() -> TicsSpecsMajor& { return m_xtics_major_bottom; }

    /// Return the specifications of the grid lines along major xtics on the top axis.
    auto xticsMajorTop() -> TicsSpecsMajor& { return m_xtics_major_top; }

    /// Return the specifications of the grid lines along minor xtics on the bottom axis.
    auto xticsMinorBottom() -> TicsSpecsMinor& { return m_xtics_minor_bottom; }

    /// Return the specifications of the grid lines along minor xtics on the top axis.
    auto xticsMinorTop() -> TicsSpecsMinor& { return m_xtics_minor_top; }

    /// Return the specifications of the grid lines along major ytics on the left axis.
    auto yticsMajorLeft() -> TicsSpecsMajor& { return m_ytics_major_left; }

    /// Return the specifications of the grid lines along major ytics on the right axis.
    auto yticsMajorRight() -> TicsSpecsMajor& { return m_ytics_major_right; }

    /// Return the specifications of the grid lines along minor ytics on the left axis.
    auto yticsMinorLeft() -> TicsSpecsMinor& { return m_ytics_minor_left; }

    /// Return the specifications of the grid lines along minor ytics on the right axis.
    auto yticsMinorRight() -> TicsSpecsMinor& { return m_ytics_minor_right; }

    /// Return the specifications of the grid lines along major ztics.
    auto zticsMajor() -> TicsSpecsMajor& { return m_ztics_major; }

    /// Return the specifications of the grid lines along minor ztics.
    auto zticsMinor() -> TicsSpecsMinor& { return m_ztics_minor; }

    /// Return the specifications of the grid lines along minor rtics.
    auto rticsMajor() -> TicsSpecsMajor& { return m_rtics_major; }

    /// Return the specifications of the grid lines along minor rtics.
    auto rticsMinor() -> TicsSpecsMinor& { return m_rtics_minor; }

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS
    //======================================================================

    /// Draw plot object with given `what`, `using` and `with` expressions (e.g., `fig.draw("sin(x)*cos(x)", "", "linespoints")`,  (e.g., `fig.draw("file.dat", "1:2", "points")`)).
    auto draw(std::string what, std::string use, std::string with) -> DrawSpecs&;

    /// Draw plot object with given style and given vectors (e.g., `fig.draw("lines", x, y)`).
    template <typename X, typename... Vecs>
    auto drawWithVecs(std::string with, const X&, const Vecs&... vecs) -> DrawSpecs&;

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

    /// Draw plot object with given style and given vectors (e.g., `fig.draw("lines", x, y)`).
    auto drawWithCols(std::string fname, std::string with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&;

    /// Draw a curve with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawCurve(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw a curve with points with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawCurveWithPoints(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* with given values at @p xcol, @p ycol, and @p xdeltacol columns in file @p fname.
    auto drawCurveWithErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* with given values at @p xcol, @p ycol, @p xlowcol, and @p xhighcol columns in file @p fname.
    auto drawCurveWithErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&;

    /// Draw a curve with error bars along *y* with given values at @p xcol, @p ycol, and @p ydeltacol columns in file @p fname.
    auto drawCurveWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw a curve with error bars along *y* with given values at @p xcol, @p ycol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawCurveWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xdeltacol, and @p ydeltacol columns in file @p fname.
    auto drawCurveWithErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw a curve with error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xlowcol, @p xhighcol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawCurveWithErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw boxes with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawBoxes(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw boxes with given values at @p xcol and @p ycol columns in file @p fname as well as the box widths @p xwidthcol.
    auto drawBoxes(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xwidthcol) -> DrawSpecs&;

    /// Draw boxes with error bars along *y* with given values at @p xcol, @p ycol, @p ydeltacol columns in file @p fname.
    auto drawBoxesWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw boxes with error bars along *y* with given values at @p xcol, @p ycol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawBoxesWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw error bars along *x* with given values at @p xcol, @p ycol, and @p xdeltacol columns in file @p fname.
    auto drawErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&;

    /// Draw error bars along *x* with given values at @p xcol, @p ycol, @p xlowcol, and @p xhighcol columns in file @p fname.
    auto drawErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&;

    /// Draw error bars along *y* with given values at @p xcol, @p ycol, and @p ydeltacol columns in file @p fname.
    auto drawErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw error bars along *y* with given values at @p xcol, @p ycol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xdeltacol, and @p ydeltacol columns in file @p fname.
    auto drawErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&;

    /// Draw error bars along *x* and *y* with given values at @p xcol, @p ycol, @p xlowcol, @p xhighcol, @p ylowcol, and @p yhighcol columns in file @p fname.
    auto drawErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname. Identical to @ref drawStepsChangeFirstX.
    auto drawSteps(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname with steps along *x* changes first.
    auto drawStepsChangeFirstX(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname with steps along *y* changes first.
    auto drawStepsChangeFirstY(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname in a histogram style
    auto drawStepsHistogram(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw steps with given values at @p xcol and @p ycol columns in file @p fname with filled area below steps.
    auto drawStepsFilled(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw dots with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawDots(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw points with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawPoints(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw impulses with given values at @p xcol and @p ycol columns in file @p fname.
    auto drawImpulses(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&;

    /// Draw a histogram with given values at @p ycol column in file @p fname.
    auto drawHistogram(std::string fname, ColumnIndex ycol) -> DrawSpecs&;

    //======================================================================
    // MISCElLANEOUS METHODS
    //======================================================================

    /// Set the legend of the plot and return a reference to the corresponding specs object.
    auto legend() -> LegendSpecs&;

    /// Set the number of sample points for analytical plots.
    auto samples(std::size_t value) -> void;

    /// Use this method to provide gnuplot commands to be executed before the plotting calls.
    auto gnuplot(std::string command) -> void;

    /// Show the figure in a pop-up window.
    /// Will remove temporary files after showing if autoclean(true) (default).
    auto show() const -> void;

    /// Save the figure in a file, with its extension defining the figure format.
    /// The extension of the file name determines the format of the figure.
    /// The supported figure formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
    /// Thus, to save a plot in `png` format, choose a file name with a `.png`
    /// file extension as in `fig.png`.
    /// Will remove temporary files after saving if autoclean(true) (default).
    auto save(std::string filename) const -> void;

    /// Write the current plot data to the data file.
    auto savePlotData() const -> void;

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    auto autoclean(bool enable = true) -> void;

    /// Delete all files used to store plot data or scripts.
    auto cleanup() const -> void;

    /// Convert this plot object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    static std::size_t m_counter;          ///< Counter of how many plot / singleplot objects have been instanciated in the application
    std::size_t m_id = 0;                  ///< The Figure id derived from m_counter upon construction (must be the first member due to constructor initialization order!)
    bool m_autoclean = true;               ///< Toggle automatic cleaning of temporary files (enabled by default)
    std::string m_palette;                 ///< The name of the gnuplot palette to be used
    std::size_t m_width = 0;               ///< The size of the plot in x
    std::size_t m_height = 0;              ///< The size of the plot in y
    std::string m_scriptfilename;          ///< The name of the file where the plot commands are saved
    std::string m_datafilename;            ///< The multi data set file where data given to plot (e.g., vectors) are saved
    std::string m_data;                    ///< The current plot data as a string
    std::size_t m_numdatasets = 0;         ///< The current number of data sets in the data file
    std::string m_xrange;                  ///< The x-range of the plot as a gnuplot formatted string (e.g., "set xrange [0:1]")
    std::string m_yrange;                  ///< The y-range of the plot as a gnuplot formatted string (e.g., "set yrange [0:1]")
    BorderSpecs m_border;                  ///< The border style of the plot
    GridSpecs m_grid;                      ///< The vector of grid specs for the major and minor grid lines in the plot (for xtics, ytics, mxtics, etc.).
    FillStyleSpecs m_style_fill;           ///< The specs for the fill style of the plot elements in the figure that can be painted.
    HistogramStyleSpecs m_style_histogram; ///< The specs for the histogram style of the figure.
    TicsSpecs m_tics;                      ///< The specs of the tics of the plot
    TicsSpecsMajor m_xtics_major_bottom;   ///< The specs for the major xtics at the bottom.
    TicsSpecsMajor m_xtics_major_top;      ///< The specs for the major xtics at the top.
    TicsSpecsMinor m_xtics_minor_bottom;   ///< The specs for the minor xtics at the bottom.
    TicsSpecsMinor m_xtics_minor_top;      ///< The specs for the minor xtics at the top.
    TicsSpecsMajor m_ytics_major_left;     ///< The specs for the major ytics at the left.
    TicsSpecsMajor m_ytics_major_right;    ///< The specs for the major ytics at the right.
    TicsSpecsMinor m_ytics_minor_left;     ///< The specs for the minor ytics at the left.
    TicsSpecsMinor m_ytics_minor_right;    ///< The specs for the minor ytics at the right.
    TicsSpecsMajor m_ztics_major;          ///< The specs for the major ztics.
    TicsSpecsMinor m_ztics_minor;          ///< The specs for the minor ztics.
    TicsSpecsMajor m_rtics_major;          ///< The specs for the major rtics.
    TicsSpecsMinor m_rtics_minor;          ///< The specs for the minor rtics.
    LegendSpecs m_legend;                  ///< The legend specs of the plot
    std::string m_samples;                 ///< The number of sample points for functions
    AxisLabelSpecs m_xlabel;               ///< The label of the x-axis
    AxisLabelSpecs m_ylabel;               ///< The label of the y-axis
    AxisLabelSpecs m_zlabel;               ///< The label of the z-axis
    AxisLabelSpecs m_rlabel;               ///< The label of the r-axis
    std::string m_boxwidth;                ///< The default width of boxes in plots containing boxes without given widths.
    std::vector<DrawSpecs> m_drawspecs;    ///< The plot specs for each call to gnuplot plot function
    std::vector<std::string> m_customcmds; ///< The strings containing gnuplot custom commands
};

// Initialize the counter of plot objects
std::size_t Figure::m_counter = 0;

Figure::Figure()
: m_id(m_counter++),
  m_scriptfilename("show" + internal::str(m_id) + ".plt"),
  m_datafilename("plot" + internal::str(m_id) + ".dat"),
  m_xtics_major_bottom("x"),
  m_xtics_major_top("x2"),
  m_xtics_minor_bottom("x"),
  m_xtics_minor_top("x2"),
  m_ytics_major_left("y"),
  m_ytics_major_right("y2"),
  m_ytics_minor_left("y"),
  m_ytics_minor_right("y2"),
  m_ztics_major("z"),
  m_ztics_minor("z"),
  m_rtics_major("r"),
  m_rtics_minor("r"),
  m_xlabel("x"),
  m_ylabel("y"),
  m_zlabel("z"),
  m_rlabel("r")
{
    // Show only major and minor xtics and ytics
    xticsMajorBottom().show();
    xticsMinorBottom().show();
    yticsMajorLeft().show();
    yticsMinorLeft().show();

    // Hide all other tics
    xticsMajorTop().hide();
    xticsMinorTop().hide();
    yticsMajorRight().hide();
    yticsMinorRight().hide();
    zticsMajor().hide();
    zticsMinor().hide();
    rticsMajor().hide();
    rticsMinor().hide();

    // Default options for fill style
    styleFill().solid();
    styleFill().borderHide();

    // Set all other default options
    boxWidthRelative(internal::DEFAULT_FIGURE_BOXWIDTH_RELATIVE);

    // This is needed because of how drawHistogram works. Using `with histograms` don't work as well.
    gnuplot("set style data histogram");
}

auto Figure::palette(std::string name) -> void
{
    m_palette = name;
}

auto Figure::size(std::size_t width, std::size_t height) -> void
{
    m_width = width;
    m_height = height;
}

auto Figure::xlabel(std::string label) -> AxisLabelSpecs&
{
    m_xlabel.text(label);
    return m_xlabel;
}

auto Figure::ylabel(std::string label) -> AxisLabelSpecs&
{
    m_ylabel.text(label);
    return m_ylabel;
}

auto Figure::xrange(double min, double max) -> void
{
    m_xrange = "[" + internal::str(min) + ":" + internal::str(max) + "]";
}

auto Figure::yrange(double min, double max) -> void
{
    m_yrange = "[" + internal::str(min) + ":" + internal::str(max) + "]";
}

auto Figure::boxWidthAbsolute(double val) -> void
{
    m_boxwidth = internal::str(val) + " absolute";
}

auto Figure::boxWidthRelative(double val) -> void
{
    m_boxwidth = internal::str(val) + " relative";
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS
//======================================================================

auto Figure::draw(std::string what, std::string use, std::string with) -> DrawSpecs&
{
    // Save the draw arguments for this x,y data
    m_drawspecs.emplace_back(what, use, with);

    // Set the default line style specification for this drawing (desired behavior is 1, 2, 3 (incrementing as new lines are plotted))
    m_drawspecs.back().lineStyle(m_drawspecs.size());

    // Return the just created drawing object in case the user wants to customize it
    return m_drawspecs.back();
}

template <typename X, typename... Vecs>
auto Figure::drawWithVecs(std::string with, const X& x, const Vecs&... vecs) -> DrawSpecs&
{
    // Write the given vectors x and y as a new data set to the stream
    std::ostringstream datastream;
    gnuplot::writedataset(datastream, m_numdatasets, x, vecs...);

    // Set the using string to "" if X is not vector of strings.
    // Otherwise, x contain xtics strings. Set the `using` string
    // so that these are properly used as xtics.
    std::string use;
    if constexpr(internal::isStringVector<X>) {
        const auto nvecs = sizeof...(Vecs);
        use = "0:"; // here, column 0 means the pseudo column with numbers 0, 1, 2, 3...
        for(auto i = 2; i <= nvecs + 1; ++i)
            use += std::to_string(i) + ":"; // this constructs 0:2:3:4:
        use += "xtic(1)"; // this terminates the string with 0:2:3:4:xtic(1), and thus column 1 is used for the xtics
    }

    // Append new data set to existing data
    m_data += datastream.str();

    // Draw the data saved using a data set with index `m_numdatasets`. Increase number of data sets
    return draw("'" + m_datafilename + "' index " + internal::str(m_numdatasets++), use, with);
}

template <typename X, typename Y>
auto Figure::drawCurve(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("lines", x, y);
}

template <typename X, typename Y>
auto Figure::drawCurveWithPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("linespoints", x, y);
}

template <typename X, typename Y, typename XD>
auto Figure::drawCurveWithErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&
{
    return drawWithVecs("xerrorlines", x, y, xdelta);
}

template <typename X, typename Y, typename XL, typename XH>
auto Figure::drawCurveWithErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&
{
    return drawWithVecs("xerrorlines", x, y, xlow, xhigh);
}

template <typename X, typename Y, typename YD>
auto Figure::drawCurveWithErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("yerrorlines", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
auto Figure::drawCurveWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("yerrorlines", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD, typename YD>
auto Figure::drawCurveWithErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("xyerrorlines", x, y, xdelta, ydelta);
}

template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
auto Figure::drawCurveWithErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("xyerrorlines", x, y, xlow, xhigh, ylow, yhigh);
}

template <typename X, typename Y>
auto Figure::drawBoxes(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("boxes", x, y);
}

template <typename X, typename Y, typename XW>
auto Figure::drawBoxes(const X& x, const Y& y, const XW& xwidth) -> DrawSpecs&
{
    return drawWithVecs("boxes", x, y, xwidth);
}

template <typename X, typename Y, typename YD>
auto Figure::drawBoxesWithErrorBarsY(const X& x, const Y& y, const Y& ydelta) -> DrawSpecs&
{
    return drawWithVecs("boxerrorbars", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
auto Figure::drawBoxesWithErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("boxerrorbars", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD>
auto Figure::drawErrorBarsX(const X& x, const Y& y, const XD& xdelta) -> DrawSpecs&
{
    return drawWithVecs("xerrorbars", x, y, xdelta);
}

template <typename X, typename Y, typename XL, typename XH>
auto Figure::drawErrorBarsX(const X& x, const Y& y, const XL& xlow, const XH& xhigh) -> DrawSpecs&
{
    return drawWithVecs("xerrorbars", x, y, xlow, xhigh);
}

template <typename X, typename Y, typename YD>
auto Figure::drawErrorBarsY(const X& x, const Y& y, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("yerrorbars", x, y, ydelta);
}

template <typename X, typename Y, typename YL, typename YH>
auto Figure::drawErrorBarsY(const X& x, const Y& y, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("yerrorbars", x, y, ylow, yhigh);
}

template <typename X, typename Y, typename XD, typename YD>
auto Figure::drawErrorBarsXY(const X& x, const Y& y, const XD& xdelta, const YD& ydelta) -> DrawSpecs&
{
    return drawWithVecs("xyerrorbars", x, y, xdelta, ydelta);
}

template <typename X, typename Y, typename XL, typename XH, typename YL, typename YH>
auto Figure::drawErrorBarsXY(const X& x, const Y& y, const XL& xlow, const XH& xhigh, const YL& ylow, const YH& yhigh) -> DrawSpecs&
{
    return drawWithVecs("xyerrorbars", x, y, xlow, xhigh, ylow, yhigh);
}

template <typename X, typename Y>
auto Figure::drawSteps(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecsStepsChangeFirstX(x, y);
}

template <typename X, typename Y>
auto Figure::drawStepsChangeFirstX(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("steps", x, y);
}

template <typename X, typename Y>
auto Figure::drawStepsChangeFirstY(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("fsteps", x, y);
}

template <typename X, typename Y>
auto Figure::drawStepsHistogram(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("histeps", x, y);
}

template <typename X, typename Y>
auto Figure::drawStepsFilled(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("fillsteps", x, y);
}

template <typename X, typename Y>
auto Figure::drawDots(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("dots", x, y);
}

template <typename X, typename Y>
auto Figure::drawPoints(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("points", x, y);
}

template <typename X, typename Y>
auto Figure::drawImpulses(const X& x, const Y& y) -> DrawSpecs&
{
    return drawWithVecs("impulses", x, y);
}

template <typename Y>
auto Figure::drawHistogram(const Y& y) -> DrawSpecs&
{
    return drawWithVecs("", y); // empty string because we rely on `set style data histograms` since relying `with histograms` is not working very well (e.g., empty key/lenged appearing in columnstacked mode).
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS USING DATA FROM LOCAL FILES
//======================================================================

auto Figure::drawWithCols(std::string fname, std::string with, const std::vector<ColumnIndex>& cols) -> DrawSpecs&
{
    std::string use;
    for(auto col : cols)
        use += col.value + ":"; // e.g., "1:4:5:7:" (where 1 is x, 4 is y, 5 is ylow and 7 is yhigh for a yerrorlines plot)
    use = internal::trimright(use, ':'); // e.g., "1:4:5:7:" => "1:4:5:7"
    std::string what = "'" + fname + "'"; // e.g., "'myfile.dat'"
    return draw(what, use, with); // e.g., draw(what="'myfile.dat'", use="1:2", with="lines");
}

auto Figure::drawCurve(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "lines", {xcol, ycol});
}

auto Figure::drawCurveWithPoints(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "linespoints", {xcol, ycol});
}

auto Figure::drawCurveWithErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorlines", {xcol, ycol, xdeltacol});
}

auto Figure::drawCurveWithErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorlines", {xcol, ycol, xlowcol, xhighcol});
}

auto Figure::drawCurveWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorlines", {xcol, ycol, ydeltacol});
}

auto Figure::drawCurveWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorlines", {xcol, ycol, ylowcol, yhighcol});
}

auto Figure::drawCurveWithErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorlines", {xcol, ycol, xdeltacol, ydeltacol});
}

auto Figure::drawCurveWithErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorlines", {xcol, ycol, xlowcol, xhighcol, ylowcol, yhighcol});
}

auto Figure::drawBoxes(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxes", {xcol, ycol});
}

auto Figure::drawBoxes(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xwidthcol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxes", {xcol, ycol, xwidthcol});
}

auto Figure::drawBoxesWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxerrorbars", {xcol, ycol, ydeltacol});
}

auto Figure::drawBoxesWithErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "boxerrorbars", {xcol, ycol, ylowcol, yhighcol});
}

auto Figure::drawErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorbars", {xcol, ycol, xdeltacol});
}

auto Figure::drawErrorBarsX(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xerrorbars", {xcol, ycol, xlowcol, xhighcol});
}

auto Figure::drawErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorbars", {xcol, ycol, ydeltacol});
}

auto Figure::drawErrorBarsY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "yerrorbars", {xcol, ycol, ylowcol, yhighcol});
}

auto Figure::drawErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xdeltacol, ColumnIndex ydeltacol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorbars", {xcol, ycol, xdeltacol, ydeltacol});
}

auto Figure::drawErrorBarsXY(std::string fname, ColumnIndex xcol, ColumnIndex ycol, ColumnIndex xlowcol, ColumnIndex xhighcol, ColumnIndex ylowcol, ColumnIndex yhighcol) -> DrawSpecs&
{
    return drawWithCols(fname, "xyerrorbars", {xcol, ycol, xlowcol, xhighcol, ylowcol, yhighcol});
}

auto Figure::drawSteps(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "steps", {xcol, ycol});
}

auto Figure::drawStepsChangeFirstX(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "steps", {xcol, ycol});
}

auto Figure::drawStepsChangeFirstY(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "fsteps", {xcol, ycol});
}

auto Figure::drawStepsHistogram(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "histeps", {xcol, ycol});
}

auto Figure::drawStepsFilled(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "fillsteps", {xcol, ycol});
}

auto Figure::drawDots(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "dots", {xcol, ycol});
}

auto Figure::drawPoints(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "points", {xcol, ycol});
}

auto Figure::drawImpulses(std::string fname, ColumnIndex xcol, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "impulses", {xcol, ycol});
}

auto Figure::drawHistogram(std::string fname, ColumnIndex ycol) -> DrawSpecs&
{
    return drawWithCols(fname, "", {ycol});
}

//======================================================================
// MISCElLANEOUS METHODS
//======================================================================

auto Figure::legend() -> LegendSpecs&
{
    return m_legend;
}

auto Figure::samples(std::size_t value) -> void
{
    m_samples = internal::str(value);
}

auto Figure::gnuplot(std::string command) -> void
{
    m_customcmds.push_back(command);
}

auto Figure::show() const -> void
{
    // Open script file and truncate it
    std::ofstream script(m_scriptfilename);

    // Add palette info. Use default palette if the user hasn't set one
    gnuplot::palettecmd(script, m_palette.empty() ? internal::DEFAULT_PALETTE : m_palette);

    // Add terminal info
    auto width = m_width == 0 ? internal::DEFAULT_FIGURE_WIDTH : m_width;
    auto height = m_height == 0 ? internal::DEFAULT_FIGURE_HEIGHT : m_height;
    std::string size = gnuplot::sizestr(width, height, false);
    gnuplot::showterminalcmd(script, size);

    // Add the plot commands
    script << repr();

    // Add an empty line at the end and close the script to avoid crashes with gnuplot
    script << std::endl;
    script.close();

    // save plot data to a file
    savePlotData();

    // Show the figure
    gnuplot::runscript(m_scriptfilename, true);

    // remove the temporary files if user wants to
    if(m_autoclean)
    {
        cleanup();
    }
}

auto Figure::save(std::string filename) const -> void
{
    // Clean the file name to prevent errors
    auto cleanedfilename = gnuplot::cleanpath(filename);

    // Get extension from file name
    auto extension = cleanedfilename.substr(cleanedfilename.rfind(".") + 1);

    // Open script file
    std::ofstream script(m_scriptfilename);

    // Add palette info. Use default palette if the user hasn't set one
    gnuplot::palettecmd(script, m_palette.empty() ? internal::DEFAULT_PALETTE : m_palette);

    // Add terminal info
    auto width = m_width == 0 ? internal::DEFAULT_FIGURE_WIDTH : m_width;
    auto height = m_height == 0 ? internal::DEFAULT_FIGURE_HEIGHT : m_height;
    std::string size = gnuplot::sizestr(width, height, extension == "pdf");
    gnuplot::saveterminalcmd(script, extension, size);

    // Add output command
    gnuplot::outputcmd(script, cleanedfilename);

    // Add the plot commands
    script << repr();

    // Unset the output
    script << std::endl;
    script << "set output";

    // Add an empty line at the end and close the script to avoid crashes with gnuplot
    script << std::endl;
    script.close();

    // save plot data to a file
    savePlotData();

    // Save the figure as a file
    gnuplot::runscript(m_scriptfilename, false);

    // remove the temporary files if user wants to
    if (m_autoclean)
    {
        cleanup();
    }
}

auto Figure::savePlotData() const -> void
{
    // Open data file, truncate it and write all current plot data to it
    if(!m_data.empty())
    {
        std::ofstream data(m_datafilename);
        data << m_data;
    }
}

auto Figure::autoclean(bool enable) -> void
{
    m_autoclean = enable;
}

auto Figure::cleanup() const -> void
{
    std::remove(m_scriptfilename.c_str());
    std::remove(m_datafilename.c_str());
}

auto Figure::repr() const -> std::string
{
    std::stringstream script;

    // Add plot setup commands
    script << "#==============================================================================" << std::endl;
    script << "# SETUP COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << gnuplot::commandValueStr("set xrange", m_xrange);
    script << gnuplot::commandValueStr("set yrange", m_yrange);
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
    script << gnuplot::commandValueStr("set boxwidth", m_boxwidth);
    script << gnuplot::commandValueStr("set samples", m_samples);

    // Add custom gnuplot commands
    if (!m_customcmds.empty())
    {
        script << "#==============================================================================" << std::endl;
        script << "# CUSTOM EXPLICIT GNUPLOT COMMANDS" << std::endl;
        script << "#==============================================================================" << std::endl;
        for(const auto& c : m_customcmds)
        {
            script << c << std::endl;
        }
    }

    // Add the actual plot commands for all figures from the draw() calls
    script << "#==============================================================================" << std::endl;
    script << "# PLOT COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << "plot \\\n"; // use `\` to have a plot command in each individual line!

    // Write plot commands and style per plot
    const auto n = m_drawspecs.size();
    for(std::size_t i = 0; i < n; ++i)
        script << "    " << m_drawspecs[i] << (i < n - 1 ? ", \\\n" : ""); // consider indentation with 4 spaces!

    // Add an empty line at the end
    script << std::endl;
    return script.str();
}

} // namespace sciplot
