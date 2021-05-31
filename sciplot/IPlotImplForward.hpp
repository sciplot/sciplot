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

// sciplot includes
#include <sciplot/PlotBase.hpp>

namespace sciplot
{

namespace internal
{

/// This class implements the IPLot methods and forwards them through the pimpl pointer
template <typename IMPL_CLASS>
class IPlotImplForward : public IPlot
{
  public:
    /// Construct a forwarder object
    IPlotImplForward()
        : m_impl(std::make_shared<IMPL_CLASS>())
    {
    }

    /// Set the palette of colors for the plot.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto palette(const std::string& name) -> void override { m_impl->palette(name); }

    /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
    auto size(std::size_t width, std::size_t height) -> void override { m_impl->size(width, height); }

    /// Set the font name for the plot (e.g., Helvetica, Georgia, Times).
    auto fontName(const std::string& name) -> void override { m_impl->fontName(name); }

    /// Set the font size for the plot (e.g., 10, 12, 16).
    auto fontSize(std::size_t size) -> void override { m_impl->fontSize(size); }

    /// Set the border of the plot and return a reference to the corresponding specs object.
    auto border() -> BorderSpecs& override { return m_impl->border(); }

    /// Set the grid of the plot and return a reference to the corresponding specs object.
    auto grid() -> GridSpecs& override { return m_impl->grid(); }

    /// Set the label of the x-axis and return a reference to the corresponding specs object.
    auto xlabel(const std::string& label) -> AxisLabelSpecs& override { return m_impl->xlabel(label); }

    /// Set the label of the y-axis and return a reference to the corresponding specs object.
    auto ylabel(const std::string& label) -> AxisLabelSpecs& override { return m_impl->ylabel(label); }

    /// Set the x-range of the plot (also possible with empty values or autoscale options (e.g. "", "*")).
    auto xrange(const StringOrDouble& min, const StringOrDouble& max) -> void override { m_impl->xrange(min, max); }

    /// Set the y-range of the plot (also possible with empty values or autoscale options (e.g. "", "*")).
    auto yrange(const StringOrDouble& min, const StringOrDouble& max) -> void override { m_impl->yrange(min, max); }

    /// Set the default width of boxes in plots containing boxes (in absolute mode).
    /// In absolute mode, a unit width is equivalent to one unit of length along the *x* axis.
    auto boxWidthAbsolute(double val) -> void override { m_impl->boxWidthAbsolute(val); }

    /// Set the default width of boxes in plots containing boxes (in relative mode).
    /// In relative mode, a unit width is equivalent to setting the boxes side by side.
    auto boxWidthRelative(double val) -> void override { m_impl->boxWidthRelative(val); }

    //======================================================================
    // METHODS FOR CUSTOMIZATION OF TICS
    //======================================================================

    /// Set the tics of the plot and return a reference to the corresponding specs object.
    auto tics() -> TicsSpecs& override { return m_impl->tics(); }

    /// Return the specifications of the grid lines along major xtics on the bottom axis.
    auto xtics() -> TicsSpecsMajor& override { return m_impl->xticsMajorBottom(); }

    /// Return the specifications of the grid lines along major ytics on the left axis.
    auto ytics() -> TicsSpecsMajor& override { return m_impl->yticsMajorLeft(); }

    /// Return the specifications of the grid lines along major ztics.
    auto ztics() -> TicsSpecsMajor& override { return m_impl->zticsMajor(); }

    /// Return the specifications of the grid lines along major rtics.
    auto rtics() -> TicsSpecsMajor& override { return m_impl->rticsMajor(); }

    /// Return the specifications of the grid lines along major xtics on the bottom axis.
    auto xticsMajorBottom() -> TicsSpecsMajor& override { return m_impl->xticsMajorBottom(); }

    /// Return the specifications of the grid lines along major xtics on the top axis.
    auto xticsMajorTop() -> TicsSpecsMajor& override { return m_impl->xticsMajorTop(); }

    /// Return the specifications of the grid lines along minor xtics on the bottom axis.
    auto xticsMinorBottom() -> TicsSpecsMinor& override { return m_impl->xticsMinorBottom(); }

    /// Return the specifications of the grid lines along minor xtics on the top axis.
    auto xticsMinorTop() -> TicsSpecsMinor& override { return m_impl->xticsMinorTop(); }

    /// Return the specifications of the grid lines along major ytics on the left axis.
    auto yticsMajorLeft() -> TicsSpecsMajor& override { return m_impl->yticsMajorLeft(); }

    /// Return the specifications of the grid lines along major ytics on the right axis.
    auto yticsMajorRight() -> TicsSpecsMajor& override { return m_impl->yticsMajorRight(); }

    /// Return the specifications of the grid lines along minor ytics on the left axis.
    auto yticsMinorLeft() -> TicsSpecsMinor& override { return m_impl->yticsMinorLeft(); }

    /// Return the specifications of the grid lines along minor ytics on the right axis.
    auto yticsMinorRight() -> TicsSpecsMinor& override { return m_impl->yticsMinorRight(); }

    /// Return the specifications of the grid lines along major ztics.
    auto zticsMajor() -> TicsSpecsMajor& override { return m_impl->zticsMajor(); }

    /// Return the specifications of the grid lines along minor ztics.
    auto zticsMinor() -> TicsSpecsMinor& override { return m_impl->zticsMinor(); }

    /// Return the specifications of the grid lines along minor rtics.
    auto rticsMajor() -> TicsSpecsMajor& override { return m_impl->rticsMajor(); }

    /// Return the specifications of the grid lines along minor rtics.
    auto rticsMinor() -> TicsSpecsMinor& { return m_impl->rticsMinor(); }

    //======================================================================
    // METHODS FOR CUSTOMIZATION OF STYLES
    //======================================================================

    /// Return an object that permits fill style to be customized.
    auto styleFill() -> FillStyleSpecs& override { return m_impl->styleFill(); }

    /// Return an object that permits histogram style to be customized.
    auto styleHistogram() -> HistogramStyleSpecs& override { return m_impl->styleHistogram(); }

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS
    //======================================================================

    /// Draw plot object with given `what`, `using` and `with` expressions (e.g., `plot.draw("sin(x)*cos(x)", "", "linespoints")`,  (e.g., `plot.draw("file.dat", "1:2", "points")`)).
    auto draw(const std::string& what, const std::string& use, const std::string& with) -> DrawSpecs& override { return m_impl->draw(what, use, with); }

    //======================================================================
    // MISCElLANEOUS METHODS
    //======================================================================

    /// Set the legend of the plot and return a reference to the corresponding specs object.
    auto legend() -> LegendSpecs& override { return m_impl->legend(); }

    /// Set the number of sample points for analytical plots.
    auto samples(std::size_t value) -> void override { m_impl->samples(value); }

    /// Use this method to provide gnuplot commands to be executed before the plotting calls.
    auto gnuplot(const std::string& command) -> void override { m_impl->gnuplot(command); }

    /// Show the plot in a pop-up window.
    /// @note This method removes temporary files after saving if `PlotBase::autoclean(true)` (default).
    auto show() const -> void override { m_impl->show(); }

    /// Save the plot in a file, with its extension defining the file format.
    /// The extension of the file name determines the file format.
    /// The supported formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
    /// Thus, to save a plot in `pdf` format, choose a file as in `plot.pdf`.
    /// @note This method removes temporary files after saving if `PlotBase::autoclean(true)` (default).
    auto save(const std::string& filename) const -> void override { m_impl->save(filename); }

    /// Write the current plot data to the data file.
    auto savePlotData() const -> void override { m_impl->savePlotData(); }

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    auto autoclean(bool enable = true) -> void override { m_impl->autoclean(enable); }

    /// Delete all files used to store plot data or scripts.
    auto cleanup() const -> void override { m_impl->cleanup(); }

    /// Clear all draw and gnuplot commands.
    /// @note This method leaves all other plot properties untouched.
    auto clear() -> void override { m_impl->clear(); }

  protected:
    std::shared_ptr<IMPL_CLASS> m_impl{};
};

} // namespace internal

} // namespace sciplot
