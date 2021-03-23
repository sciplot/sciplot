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
#include <sciplot/specs/DrawSpecs.hpp>
#include <sciplot/specs/FillStyleSpecs.hpp>
#include <sciplot/specs/FontSpecsOf.hpp>
#include <sciplot/specs/GridSpecs.hpp>
#include <sciplot/specs/HistogramStyleSpecs.hpp>
#include <sciplot/specs/LegendSpecs.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/TicsSpecs.hpp>
#include <sciplot/specs/TicsSpecsMajor.hpp>
#include <sciplot/specs/TicsSpecsMajor.hpp>
#include <sciplot/specs/TicsSpecsMinor.hpp>
#include <sciplot/StringOrDouble.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to create a plot containing graphical elements.
class PlotBase
{
  public:
    /// Construct a default Plot object
    PlotBase();

    /// Virtual destructor to avoid memory leaks
    virtual ~PlotBase() = default;

    /// Set the palette of colors for the plot.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto palette(const std::string &name) -> void;

    /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
    auto size(std::size_t width, std::size_t height) -> void;

    /// Set the font name for the plot (e.g., Helvetica, Georgia, Times).
    auto fontName(const std::string &name) -> void;

    /// Set the font size for the plot (e.g., 10, 12, 16).
    auto fontSize(std::size_t size) -> void;

    /// Set the border of the plot and return a reference to the corresponding specs object.
    auto border() -> BorderSpecs& { return m_border; }

    /// Set the grid of the plot and return a reference to the corresponding specs object.
    auto grid() -> GridSpecs& { return m_grid; }

    //======================================================================
    // METHODS FOR CUSTOMIZATION OF STYLES
    //======================================================================

    /// Return an object that permits fill style to be customized.
    auto styleFill() -> FillStyleSpecs& { return m_style_fill; }

    //======================================================================
    // METHODS FOR DRAWING PLOT ELEMENTS
    //======================================================================

    /// Draw plot object with given `what`, `using` and `with` expressions (e.g., `plot.draw("sin(x)*cos(x)", "", "linespoints")`,  (e.g., `plot.draw("file.dat", "1:2", "points")`)).
    auto draw(const std::string& what, const std::string& use, const std::string& with) -> DrawSpecs&;

    //======================================================================
    // MISCElLANEOUS METHODS
    //======================================================================

    /// Set the legend of the plot and return a reference to the corresponding specs object.
    auto legend() -> LegendSpecs&;

    /// Set the number of sample points for analytical plots.
    auto samples(std::size_t value) -> void;

    /// Use this method to provide gnuplot commands to be executed before the plotting calls.
    auto gnuplot(const std::string &command) -> void;

    /// Show the plot in a pop-up window.
    /// @note This method removes temporary files after saving if `PlotBase::autoclean(true)` (default).
    auto show() const -> void;

    /// Save the plot in a file, with its extension defining the file format.
    /// The extension of the file name determines the file format.
    /// The supported formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
    /// Thus, to save a plot in `pdf` format, choose a file as in `plot.pdf`.
    /// @note This method removes temporary files after saving if `PlotBase::autoclean(true)` (default).
    auto save(const std::string &filename) const -> void;

    /// Write the current plot data to the data file.
    auto savePlotData() const -> void;

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    auto autoclean(bool enable = true) -> void;

    /// Delete all files used to store plot data or scripts.
    auto cleanup() const -> void;

    /// Clear all draw and gnuplot commands.
    /// @note This method leaves all other plot properties untouched.
    auto clear() -> void;

    /// Convert this plot object into a gnuplot formatted string.
    virtual auto repr() const -> std::string = 0;

  protected:
    static std::size_t m_counter;          ///< Counter of how many plot / singleplot objects have been instanciated in the application
    std::size_t m_id = 0;                  ///< The Plot id derived from m_counter upon construction (must be the first member due to constructor initialization order!)
    bool m_autoclean = true;               ///< Toggle automatic cleaning of temporary files (enabled by default)
    std::string m_palette;                 ///< The name of the gnuplot palette to be used
    std::size_t m_width = 0;               ///< The size of the plot in x
    std::size_t m_height = 0;              ///< The size of the plot in y
    std::string m_scriptfilename;          ///< The name of the file where the plot commands are saved
    std::string m_datafilename;            ///< The multi data set file where data given to plot (e.g., vectors) are saved
    std::string m_data;                    ///< The current plot data as a string
    std::size_t m_numdatasets = 0;         ///< The current number of data sets in the data file
    FontSpecs m_font;                      ///< The font name and size in the plot
    BorderSpecs m_border;                  ///< The border style of the plot
    GridSpecs m_grid;                      ///< The vector of grid specs for the major and minor grid lines in the plot (for xtics, ytics, mxtics, etc.).
    FillStyleSpecs m_style_fill;           ///< The specs for the fill style of the plot elements in the plot that can be painted.
    std::string m_samples;                 ///< The number of sample points for functions
    LegendSpecs m_legend;                  ///< The legend specs of the plot
    std::vector<DrawSpecs> m_drawspecs;    ///< The plot specs for each call to gnuplot plot function
    std::vector<std::string> m_customcmds; ///< The strings containing gnuplot custom commands
};

// Initialize the counter of plot objects
inline std::size_t PlotBase::m_counter = 0;

inline PlotBase::PlotBase()
: m_id(m_counter++),
  m_scriptfilename("show" + internal::str(m_id) + ".plt"),
  m_datafilename("plot" + internal::str(m_id) + ".dat")
{
    // Show only major and minor xtics and ytics

    // Default options for fill style
    styleFill().solid();
    styleFill().borderHide();
}

inline auto PlotBase::palette(const std::string &name) -> void
{
    m_palette = name;
}

inline auto PlotBase::size(std::size_t width, std::size_t height) -> void
{
    m_width = width;
    m_height = height;
}

inline auto PlotBase::fontName(const std::string &name) -> void
{
    m_font.fontName(name);
    m_legend.fontName(name);
}

inline auto PlotBase::fontSize(std::size_t size) -> void
{
    m_font.fontSize(size);
    m_legend.fontSize(size);
}

//======================================================================
// METHODS FOR DRAWING PLOT ELEMENTS
//======================================================================

inline auto PlotBase::draw(const std::string& what, const std::string& use, const std::string& with) -> DrawSpecs&
{
    // Save the draw arguments for this x,y data
    m_drawspecs.emplace_back(what, use, with);

    // Return the just created drawing object in case the user wants to customize it
    return m_drawspecs.back();
}

//======================================================================
// MISCELLANEOUS METHODS
//======================================================================

inline auto PlotBase::legend() -> LegendSpecs&
{
    return m_legend;
}

inline auto PlotBase::samples(std::size_t value) -> void
{
    m_samples = internal::str(value);
}

inline auto PlotBase::gnuplot(const std::string &command) -> void
{
    m_customcmds.push_back(command);
}

inline auto PlotBase::show() const -> void
{
    // Open script file and truncate it
    std::ofstream script(m_scriptfilename);

    // Add palette info. Use default palette if the user hasn't set one
    gnuplot::palettecmd(script, m_palette.empty() ? internal::DEFAULT_PALETTE : m_palette);

    // Add terminal info
    auto width = m_width == 0 ? internal::DEFAULT_FIGURE_WIDTH : m_width;
    auto height = m_height == 0 ? internal::DEFAULT_FIGURE_HEIGHT : m_height;
    std::string size = gnuplot::sizestr(width, height, false);
    gnuplot::showterminalcmd(script, size, m_font);

    // Add the plot commands
    script << repr();

    // Add an empty line at the end and close the script to avoid crashes with gnuplot
    script << std::endl;
    script.close();

    // save plot data to a file
    savePlotData();

    // Show the plot
    gnuplot::runscript(m_scriptfilename, true);

    // remove the temporary files if user wants to
    if(m_autoclean)
    {
        cleanup();
    }
}

inline auto PlotBase::save(const std::string &filename) const -> void
{
    // Clean the file name to prevent errors
    auto cleanedfilename = gnuplot::cleanpath(filename);

    // Get extension from file name
    auto extension = cleanedfilename.substr(cleanedfilename.rfind('.') + 1);

    // Open script file
    std::ofstream script(m_scriptfilename);

    // Add palette info. Use default palette if the user hasn't set one
    gnuplot::palettecmd(script, m_palette.empty() ? internal::DEFAULT_PALETTE : m_palette);

    // Add terminal info
    auto width = m_width == 0 ? internal::DEFAULT_FIGURE_WIDTH : m_width;
    auto height = m_height == 0 ? internal::DEFAULT_FIGURE_HEIGHT : m_height;
    std::string size = gnuplot::sizestr(width, height, extension == "pdf");
    gnuplot::saveterminalcmd(script, extension, size, m_font);

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

    // Save the plot as a file
    gnuplot::runscript(m_scriptfilename, false);

    // remove the temporary files if user wants to
    if (m_autoclean)
    {
        cleanup();
    }
}

inline auto PlotBase::savePlotData() const -> void
{
    // Open data file, truncate it and write all current plot data to it
    if(!m_data.empty())
    {
        std::ofstream data(m_datafilename);
        data << m_data;
    }
}

inline auto PlotBase::autoclean(bool enable) -> void
{
    m_autoclean = enable;
}

inline auto PlotBase::cleanup() const -> void
{
    std::remove(m_scriptfilename.c_str());
    std::remove(m_datafilename.c_str());
}

inline auto PlotBase::clear() -> void
{
    m_drawspecs.clear();
    m_customcmds.clear();
}

} // namespace sciplot
