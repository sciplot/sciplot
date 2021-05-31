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
#include <sstream>
#include <vector>

// sciplot includes
#include <sciplot/Constants.hpp>
#include <sciplot/Default.hpp>
#include <sciplot/Enums.hpp>
#include <sciplot/Palettes.hpp>
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

/// Interface for a plot containing graphical elements.
class IPlot
{
  public:
    /// Virtual destructor to avoid memory leaks
    virtual ~IPlot() = default;

    /// Set the palette of colors for the plot.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    virtual auto palette(const std::string& name) -> void = 0;

    /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
    virtual auto size(std::size_t width, std::size_t height) -> void = 0;

    /// Set the font name for the plot (e.g., Helvetica, Georgia, Times).
    virtual auto fontName(const std::string& name) -> void = 0;

    /// Set the font size for the plot (e.g., 10, 12, 16).
    virtual auto fontSize(std::size_t size) -> void = 0;

    /// Set the border of the plot and return a reference to the corresponding specs object.
    virtual auto border() -> BorderSpecs& = 0;

    /// Set the grid of the plot and return a reference to the corresponding specs object.
    virtual auto grid() -> GridSpecs& = 0;

    /// Set the label of the x-axis and return a reference to the corresponding specs object.
    virtual auto xlabel(const std::string& label) -> AxisLabelSpecs& = 0;

    /// Set the label of the y-axis and return a reference to the corresponding specs object.
    virtual auto ylabel(const std::string& label) -> AxisLabelSpecs& = 0;

    /// Set the x-range of the plot (also possible with empty values or autoscale options (e.g. "", "*")).
    virtual auto xrange(const StringOrDouble& min, const StringOrDouble& max) -> void = 0;

    /// Set the y-range of the plot (also possible with empty values or autoscale options (e.g. "", "*")).
    virtual auto yrange(const StringOrDouble& min, const StringOrDouble& max) -> void = 0;

    /// Set the default width of boxes in plots containing boxes (in absolute mode).
    /// In absolute mode, a unit width is equivalent to one unit of length along the *x* axis.
    virtual auto boxWidthAbsolute(double val) -> void = 0;

    /// Set the default width of boxes in plots containing boxes (in relative mode).
    /// In relative mode, a unit width is equivalent to setting the boxes side by side.
    virtual auto boxWidthRelative(double val) -> void = 0;

    //======================================================================
    // METHODS FOR CUSTOMIZATION OF TICS
    //======================================================================

    /// Set the tics of the plot and return a reference to the corresponding specs object.
    virtual auto tics() -> TicsSpecs& = 0;

    /// Return the specifications of the grid lines along major xtics on the bottom axis.
    virtual auto xtics() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along major ytics on the left axis.
    virtual auto ytics() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along major ztics.
    virtual auto ztics() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along major rtics.
    virtual auto rtics() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along major xtics on the bottom axis.
    virtual auto xticsMajorBottom() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along major xtics on the top axis.
    virtual auto xticsMajorTop() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along minor xtics on the bottom axis.
    virtual auto xticsMinorBottom() -> TicsSpecsMinor& = 0;

    /// Return the specifications of the grid lines along minor xtics on the top axis.
    virtual auto xticsMinorTop() -> TicsSpecsMinor& = 0;

    /// Return the specifications of the grid lines along major ytics on the left axis.
    virtual auto yticsMajorLeft() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along major ytics on the right axis.
    virtual auto yticsMajorRight() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along minor ytics on the left axis.
    virtual auto yticsMinorLeft() -> TicsSpecsMinor& = 0;

    /// Return the specifications of the grid lines along minor ytics on the right axis.
    virtual auto yticsMinorRight() -> TicsSpecsMinor& = 0;

    /// Return the specifications of the grid lines along major ztics.
    virtual auto zticsMajor() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along minor ztics.
    virtual auto zticsMinor() -> TicsSpecsMinor& = 0;

    /// Return the specifications of the grid lines along minor rtics.
    virtual auto rticsMajor() -> TicsSpecsMajor& = 0;

    /// Return the specifications of the grid lines along minor rtics.
    virtual auto rticsMinor() -> TicsSpecsMinor& = 0;

    //======================================================================
    // METHODS FOR CUSTOMIZATION OF STYLES
    //======================================================================

    /// Return an object that permits fill style to be customized.
    virtual auto styleFill() -> FillStyleSpecs& = 0;

    /// Return an object that permits histogram style to be customized.
    virtual auto styleHistogram() -> HistogramStyleSpecs& = 0;

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS
    //======================================================================

    /// Draw plot object with given `what`, `using` and `with` expressions (e.g., `plot.draw("sin(x)*cos(x)", "", "linespoints")`,  (e.g., `plot.draw("file.dat", "1:2", "points")`)).
    virtual auto draw(const std::string& what, const std::string& use, const std::string& with) -> DrawSpecs& = 0;

    //======================================================================
    // MISCElLANEOUS METHODS
    //======================================================================

    /// Set the legend of the plot and return a reference to the corresponding specs object.
    virtual auto legend() -> LegendSpecs& = 0;

    /// Set the number of sample points for analytical plots.
    virtual auto samples(std::size_t value) -> void = 0;

    /// Use this method to provide gnuplot commands to be executed before the plotting calls.
    virtual auto gnuplot(const std::string& command) -> void = 0;

    /// Show the plot in a pop-up window.
    /// @note This method removes temporary files after saving if `PlotBase::autoclean(true)` (default).
    virtual auto show() const -> void = 0;

    /// Save the plot in a file, with its extension defining the file format.
    /// The extension of the file name determines the file format.
    /// The supported formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
    /// Thus, to save a plot in `pdf` format, choose a file as in `plot.pdf`.
    /// @note This method removes temporary files after saving if `PlotBase::autoclean(true)` (default).
    virtual auto save(const std::string& filename) const -> void = 0;

    /// Write the current plot data to the data file.
    virtual auto savePlotData() const -> void = 0;

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    virtual auto autoclean(bool enable = true) -> void = 0;

    /// Delete all files used to store plot data or scripts.
    virtual auto cleanup() const -> void = 0;

    /// Clear all draw and gnuplot commands.
    /// @note This method leaves all other plot properties untouched.
    virtual auto clear() -> void = 0;

    /// Convert this plot object into a gnuplot formatted string.
    virtual auto repr() const -> std::string = 0;
};

} // namespace sciplot
