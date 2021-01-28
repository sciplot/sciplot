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

// C++ includes
#include <sstream>
#include <vector>

// sciplot includes
#include <sciplot/constants.hpp>
#include <sciplot/default.hpp>
#include <sciplot/enums.hpp>
#include <sciplot/palettes.hpp>
#include <sciplot/specs/AxisLabelSpecs.hpp>
#include <sciplot/specs/BorderSpecs.hpp>
#include <sciplot/specs/GridSpecs.hpp>
#include <sciplot/specs/LegendSpecs.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/PlotSpecs.hpp>
#include <sciplot/specs/TicSpecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The class used to define the plots and their data, show them in a pop-up window or save them to a file.
class plot
{
  public:
    /// Construct a default plot object
    plot();

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    auto autoclean(bool enable = true) -> void;

    /// Convert this plot object into a gnuplot formatted string.
    /// Note that this will only return the plot commands. Data needs to be writte to a seperate file using draw().
    auto repr() const -> std::string;

    /// Set the palette of colors for the plot.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto palette(const std::string& name) -> plot&;

    /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
    auto size(std::size_t width, std::size_t height) -> plot&;

    /// Set the label of the x-axis and return a reference to the corresponding specs object.
    auto xlabel(const std::string& label) -> AxisLabelSpecs&
    {
        m_xlabel.text(label);
        return m_xlabel;
    }

    /// Set the label of the y-axis and return a reference to the corresponding specs object.
    auto ylabel(const std::string& label) -> AxisLabelSpecs&
    {
        m_ylabel.text(label);
        return m_ylabel;
    }

    /// Set the x-range of the plot.
    auto xrange(double min, double max) -> void { m_xrange = "[" + internal::str(min) + ":" + internal::str(max) + "]"; }

    /// Set the y-range of the plot.
    auto yrange(double min, double max) -> void { m_yrange = "[" + internal::str(min) + ":" + internal::str(max) + "]"; }

    /// Set the border of the plot and return a reference to the corresponding specs object.
    auto border() -> BorderSpecs& { return m_border; }

    /// Set the grid of the plot and return a reference to the corresponding specs object.
    auto grid() -> GridSpecs& { return m_GridSpecs; }

    /// Set the tics of the plot and return a reference to the corresponding specs object.
    auto tics() -> TicSpecs& { return m_tics; }

    /// Set the xtics of the plot and return a reference to the corresponding specs object.
    auto xtics() -> TicSpecs& { return m_xtics; }

    /// Set the ytics of the plot and return a reference to the corresponding specs object.
    auto ytics() -> TicSpecs& { return m_ytics; }

    /// Set the legend of the plot and return a reference to the corresponding specs object.
    auto legend() -> LegendSpecs& { return m_legend; }

    /// Set the width of boxes if plot style / plot::with() is "boxes", "boxerrorbars", "candelsticks" or "histograms".
    /// The default box width type is "automatic", which makes the boxes touch. For "relative", "width" specifies
    /// a fraction of that automatic value. With "absolute", "width" specifies an absolute size on the x-axis.
    /// This setting will be applied to all plot draw() calls after this.
    auto boxwidth(boxwidthtype widthtype = boxwidthtype::automatic, float width = 1.0F) -> void { m_boxwidth = internal::str(width) + " " + gnuplot::boxwidthtypestr(widthtype); }

    /// Set the number of sample points for analytical plots.
    auto samples(std::size_t value) -> void { m_samples = internal::str(value); }

    /// Use this method to provide gnuplot commands to be executed before the plotting calls.
    auto gnuplot(const std::string& command) -> void { m_customcmds.push_back(command); }

    /// Plot using a gnuplot command string and return a reference to the corresponding specs object.
    auto draw(const std::string& what) -> PlotSpecs&;

    /// Plot two vectors of data and return a reference to the corresponding specs object.
    /// Will write all data to a plot<N>.dat file.
    template <typename X, typename Y>
    auto draw(const X& x, const Y& y) -> PlotSpecs&;

    /// Write the current plot data to the data file.
    auto saveplotdata() const -> void;

    /// Show the plot in a pop-up window.
    /// Will remove temporary files after showing if autoclean(true) (default).
    auto show() const -> void;

    /// Save the plot in a file, with its extension defining the figure format.
    /// The extension of the file name determines the format of the figure.
    /// The supported figure formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
    /// Thus, to save a plot in `png` format, choose a file name with a `.png`
    /// file extension as in `fig.png`.
    /// Will remove temporary files after saving if autoclean(true) (default).
    auto save(const std::string& filename) const -> void;

    /// Delete all files used to store plot data or scripts.
    auto cleanup() const -> void;

  private:
    /// Counter of how many plot / singleplot objects have been instanciated in the application
    static std::size_t m_counter;

    /// Plot id derived from m_counter upon construction
    /// Must be the first member due to constructor initialization order!
    std::size_t m_id = 0;

    /// Toggle automatic cleaning of temporary files (enabled by default)
    bool m_autoclean = true;

    /// The name of the gnuplot palette to be used
    std::string m_palette;

    /// The size of the plot in x
    std::size_t m_width = 0;

    /// The size of the plot in y
    std::size_t m_height = 0;

    /// The name of the file where the plot commands are saved
    std::string m_scriptfilename;

    /// The multi data set file where data given to plot (e.g., vectors) are saved
    std::string m_datafilename;

    /// The current plot data as a string
    std::string m_data;

    /// The current number of data sets in the data file
    std::size_t m_numdatasets = 0;

    /// The x-range of the plot as a gnuplot formatted string (e.g., "set xrange [0:1]")
    std::string m_xrange;

    /// The y-range of the plot as a gnuplot formatted string (e.g., "set yrange [0:1]")
    std::string m_yrange;

    /// The border style of the plot
    BorderSpecs m_border;

    /// The vector of grid specs for the major and minor grid lines in the plot (for xtics, ytics, mxtics, etc.).
    GridSpecs m_GridSpecs;

    /// The specs of the tics of the plot
    TicSpecs m_tics;

    /// The specs of the xtics of the plot
    TicSpecs m_xtics = TicSpecs(ticaxis::x);

    /// The specs of the ytics of the plot
    TicSpecs m_ytics = TicSpecs(ticaxis::y);

    /// The legend specs of the plot
    LegendSpecs m_legend;

    /// The number of sample points for functions
    std::string m_samples;

    /// The label of the x-axis
    AxisLabelSpecs m_xlabel;

    /// The label of the y-axis
    AxisLabelSpecs m_ylabel;

    /// The label of the z-axis
    AxisLabelSpecs m_zlabel;

    /// Boxes width type if plot style is "boxes", "boxerrorbars", "candelsticks" or "histograms and
    /// relative or absolute box width value
    std::string m_boxwidth;

    /// The plot specs for each call to gnuplot plot function
    std::vector<PlotSpecs> m_PlotSpecs;

    /// The strings containing gnuplot custom commands
    std::vector<std::string> m_customcmds;
};

// Initialize the counter of plot objects
std::size_t plot::m_counter = 0;

plot::plot()
    : m_id(m_counter++), m_scriptfilename("show" + internal::str(m_id) + ".plt"), m_datafilename("plot" + internal::str(m_id) + ".dat"), m_xlabel("x"), m_ylabel("y"), m_zlabel("z")
{
}

auto plot::autoclean(bool enable) -> void
{
    m_autoclean = enable;
}

auto plot::palette(const std::string& name) -> plot&
{
    m_palette = name;
    return *this;
}

auto plot::size(std::size_t width, std::size_t height) -> plot&
{
    m_width = width;
    m_height = height;
    return *this;
}

auto plot::draw(const std::string& what) -> PlotSpecs&
{
    // Save the draw arguments for this x,y data
    m_PlotSpecs.emplace_back(what);

    // Set the default line style specification for this drawing (desired behavior is 1, 2, 3 (incrementing as new lines are plotted))
    m_PlotSpecs.back().linestyle(m_PlotSpecs.size());

    // Return the just created drawing object in case the user wants to customize it
    return m_PlotSpecs.back();
}

template <typename X, typename Y>
auto plot::draw(const X& x, const Y& y) -> PlotSpecs&
{
    // Write the given vectors x and y as a new data set to the stream
    std::ostringstream datastream;
    gnuplot::writedataset(datastream, m_numdatasets, x, y);

    // Append new data set to existing data
    m_data += datastream.str();

    // Draw the data saved using a data set with index `m_numdatasets`. Increase number of data sets
    return draw("'" + m_datafilename + "' index " + internal::str(m_numdatasets++));
}

auto plot::repr() const -> std::string
{
    std::stringstream script;

    // Add plot setup commands
    script << "#==============================================================================" << std::endl;
    script << "# SETUP COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << gnuplot::commandvaluestr("set xrange", m_xrange);
    script << gnuplot::commandvaluestr("set yrange", m_yrange);
    script << m_xlabel << std::endl;
    script << m_ylabel << std::endl;
    script << m_border << std::endl;
    script << m_GridSpecs << std::endl;
    script << m_tics << std::endl;
    script << m_xtics << std::endl;
    script << m_ytics << std::endl;
    script << m_legend << std::endl;
    script << gnuplot::commandvaluestr("set boxwidth", m_boxwidth);
    script << gnuplot::commandvaluestr("set samples", m_samples);

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

    // Add the actual plot commands for all figures from the draw() calls
    script << "#==============================================================================" << std::endl;
    script << "# PLOT COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << "plot ";

    // Write plot commands and style per plot
    const auto n = m_PlotSpecs.size();
    for (std::size_t i = 0; i < n; ++i)
        script << m_PlotSpecs[i] << (i < n - 1 ? ", " : "");

    // Add an empty line at the end
    script << std::endl;
    return script.str();
}

auto plot::saveplotdata() const -> void
{
    // Open data file, truncate it and write all current plot data to it
    if (!m_data.empty())
    {
        std::ofstream data(m_datafilename);
        data << m_data;
    }
}

auto plot::show() const -> void
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
    saveplotdata();

    // Show the plot
    gnuplot::runscript(m_scriptfilename, true);

    // remove the temporary files if user wants to
    if (m_autoclean)
    {
        cleanup();
    }
}

auto plot::save(const std::string& filename) const -> void
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
    saveplotdata();

    // Save the plot as a file
    gnuplot::runscript(m_scriptfilename, false);

    // remove the temporary files if user wants to
    if (m_autoclean)
    {
        cleanup();
    }
}

auto plot::cleanup() const -> void
{
    std::remove(m_scriptfilename.c_str());
    std::remove(m_datafilename.c_str());
}

} // namespace sciplot
