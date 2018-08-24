// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
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
#include <vector>

// Capim includes
#include <Capim/palletes.hpp>
#include <Capim/specs/axislabelspecs.hpp>
#include <Capim/specs/borderspecs.hpp>
#include <Capim/specs/gridspecs.hpp>
#include <Capim/specs/legendspecs.hpp>
#include <Capim/specs/linespecs.hpp>
#include <Capim/specs/plotspecs.hpp>
#include <Capim/specs/ticspecs.hpp>
#include <Capim/util.hpp>

namespace Capim {

using namespace internal;

/// The class used to define the plots, show in a pop-up window and save to a file.
class Plot
{
public:
    /// Construct a default Plot object
    Plot();

    /// Destroy this plot object
    ~Plot();

    /// Set the pallete of colors for the plot.
    /// @param name Any pallete name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto pallete(std::string name) -> void { m_pallete = name; }

    /// Set the size of the figure.
    auto size(std::size_t width, std::size_t height) -> void { m_size = str(width) + "," + str(height); }

    /// Set the label of the x-axis and return a reference to the corresponding specs object.
    auto xlabel(std::string label) -> axislabelspecs& { m_xlabel.text(label); return m_xlabel; }

    /// Set the label of the y-axis and return a reference to the corresponding specs object.
    auto ylabel(std::string label) -> axislabelspecs& { m_ylabel.text(label); return m_ylabel; }

    /// Set the x-range of the plot.
    auto xrange(double min, double max) -> void { m_xrange = "[" + str(min) + ":" + str(max) + "]"; }

    /// Set the y-range of the plot.
    auto yrange(double min, double max) -> void { m_yrange = "[" + str(min) + ":" + str(max) + "]"; }

    /// Set the border of the plot and return a reference to the corresponding specs object.
    auto border() -> borderspecs& { return m_border; }

    /// Set the grid of the plot and return a reference to the corresponding specs object.
    auto grid() -> gridspecs& { return m_gridspecs; }

    /// Set the tics of the plot and return a reference to the corresponding specs object.
    auto tics() -> ticspecs& { return m_tics; }

    /// Set the legend of the plot and return a reference to the corresponding specs object.
    auto legend() -> legendspecs& { return m_legend; }

    /// Set the number of sample points for analytical plots.
    auto samples(std::size_t value) -> void { m_samples = str(value); }

    /// Plot using a gnuplot command string and return a reference to the corresponding specs object.
    auto plot(std::string what) -> plotspecs&;

    /// Plot two vectors of data and return a reference to the corresponding specs object.
    template<typename X, typename Y>
    auto plot(const X& x, const Y& y) -> plotspecs&;

    /// Show the plot in a pop-up window.
    auto show() -> void;

    /// Save the plot in a file, with its extension defining the figure format.
    /// The extension of the file name determines the format of the figure.
    /// The supported figure formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
    /// Thus, to save a plot in `png` format, choose a file name with a `.png`
    /// file extension as in `fig.png`.
    auto save(std::string filename) -> void;

    /// Use this method to provide gnuplot commands to be executed before the plotting calls.
    auto gnuplot(std::string command) -> void { m_gnuplot << command << std::endl; }

private:
    /// The size of the plot as a gnuplot formatted string (e.g., "size 400,300")
    std::string m_size;

    /// The x-range of the plot as a gnuplot formatted string (e.g., "set xrange [0:1]")
    std::string m_xrange;

    /// The y-range of the plot as a gnuplot formatted string (e.g., "set yrange [0:1]")
    std::string m_yrange;

    /// The name of the data file where the given data to plot are saved
    std::string m_filename;

    /// The multi data set file where data given to plot (e.g., vectors) are saved
    std::ofstream m_filedata;

    /// The current number of data sets in the data file
    std::size_t m_numdatasets = 0;

    /// The name of the gnuplot pallete to be used
    std::string m_pallete;

    /// The border style of the plot
    borderspecs m_border;

    /// The vector of grid specs for the major and minor grid lines in the plot (for xtics, ytics, mxtics, etc.).
    gridspecs m_gridspecs;

    /// The specs of the tics of the plot
    ticspecs m_tics;

    /// The legend specs of the plot
    legendspecs m_legend;

    /// The number of sample points for functions
    std::string m_samples;

    /// The label of the x-axis
    axislabelspecs m_xlabel;

    /// The label of the y-axis
    axislabelspecs m_ylabel;

    /// The label of the z-axis
    axislabelspecs m_zlabel;

    /// The plot specs for each call to gnuplot plot function
    std::vector<plotspecs> m_plotspecs;

    /// The string stream containing gnuplot custom commands
    std::stringstream m_gnuplot;

    /// The pointer to the pipe connecting to Gnuplot
    FILE* pipe = nullptr;

    /// The counter of how many plot objects
    static std::size_t m_counter;
};

// Initialize the counter of Plot objects
std::size_t Plot::m_counter = 0;

Plot::Plot()
: m_filename("plot" + str(m_counter) + ".dat"),
  m_xlabel("x"),
  m_ylabel("y"),
  m_zlabel("z")
{
    // Increment the counter
    ++m_counter;

    // Open the file where provided data is dumped for plotting
    m_filedata.open(m_filename);

    // Set default values
    size(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    pallete(DEFAULT_PALLETE);
}

Plot::~Plot()
{
    if(pipe != nullptr)
    {
        pclose(pipe);
        pipe = nullptr;
    }
}

auto Plot::plot(std::string what) -> plotspecs&
{
    // Save the draw arguments for this x,y data
    m_plotspecs.emplace_back(what);

    // Set the default line style specification for this drawing (desired behavior is 1, 2, 3 (incrementing as new lines are plotted))
    m_plotspecs.back().linestyle(m_plotspecs.size());

    // Return the just created drawing object in case the user wants to customize it
    return m_plotspecs.back();
}

template<typename X, typename Y>
auto Plot::plot(const X& x, const Y& y) -> plotspecs&
{
    // Save the given vectors x and y as a new data set in the data file
    gnuplotdataset(m_filedata, m_numdatasets, x, y);

    // Update the number of data sets in the file
    ++m_numdatasets;

    // Draw the x,y data now saved in the data file in a data set with index `m_numdatasets - 1`
    return plot("'" + m_filename + "' index " + str(m_numdatasets - 1));
}

auto Plot::show() -> void
{
    std::string scriptname = "show" + str(m_counter) + ".plt";

    std::ofstream script(scriptname);

    script << "#==============================================================================" << std::endl;
    script << "# GNUPLOT-PALLETE (" << m_pallete << ")" << std::endl;
    script << "#------------------------------------------------------------------------------" << std::endl;
    script << "# see more at https://github.com/Gnuplotting/gnuplot-palettes" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << palletes.at(m_pallete) << std::endl;

    script << "#==============================================================================" << std::endl;
    script << "# TERMINAL" << std::endl;
    script << "#==============================================================================" << std::endl;
//    script << "if(strstrt(GPVAL_TERMINALS, 'qt') > 0) {" << std::endl;
//    script << "    set terminal qt size " << m_size << " enhanced font '" << DEFAULT_FONTNAME << "," << DEFAULT_FONTSIZE << "' persist" << std::endl;
//    script << "} else {" << std::endl;
//    script << "    set terminal x11 size " << m_size << " enhanced font '" << DEFAULT_FONTNAME << "," << DEFAULT_FONTSIZE << "' linewidth " << DEFAULT_LINEWIDTH << " raise replotonresize" << std::endl;
//    script << "}" << std::endl;
    script << "set termoption enhanced" << std::endl;
    script << "set termoption font '" << DEFAULT_FONTNAME << "," << DEFAULT_FONTSIZE << "'" << std::endl;
    script << "set size ratio " << 1.0/DEFAULT_WIDTH_HEIGHT_RATIO << std::endl;

    script << "#==============================================================================" << std::endl;
    script << "# SETUP COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << commandvaluestr("set xrange", m_xrange);
    script << commandvaluestr("set yrange", m_yrange);
    script << m_xlabel << std::endl;
    script << m_ylabel << std::endl;
    script << m_border << std::endl;
    script << m_gridspecs << std::endl;
    script << m_tics << std::endl;
    script << m_legend << std::endl;
    script << commandvaluestr("set samples", m_samples);

    script << "#==============================================================================" << std::endl;
    script << "# CUSTOM EXPLICIT GNUPLOT COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << m_gnuplot.str();

    script << "#==============================================================================" << std::endl;
    script << "# PLOT COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << "plot ";

    // The number of things to draw in the plot
    const auto n = m_plotspecs.size();

    // Plot in the same figure all those given drawing specs
    for(auto i = 0; i < n; ++i)
        script << m_plotspecs[i] << (i < n - 1 ? ", " : "");

    // Add an empty line at the end
    script << std::endl;

    // Flush the script file to avoid crashes with gnuplot
    script.flush();

    std::string command = ("gnuplot -persistent " + scriptname);
    pipe = popen(command.c_str(), "w");

    // Remove the no longer needed show{#}.plt file
//        std::remove(scriptname.c_str());
}

auto Plot::save(std::string filename) -> void
{
    std::string extension = filename.substr(filename.rfind(".") + 1);

    std::string scriptname = filename + ".plt";

    std::ofstream script(scriptname);

    script << "#==============================================================================" << std::endl;
    script << "# GNUPLOT-PALLETE (" << m_pallete << ")" << std::endl;
    script << "#------------------------------------------------------------------------------" << std::endl;
    script << "# see more at https://github.com/Gnuplotting/gnuplot-palettes" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << palletes.at(m_pallete) << std::endl;

    script << "#==============================================================================" << std::endl;
    script << "# TERMINAL" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << "set terminal " << extension << " size " << m_size << " enhanced rounded font '" << DEFAULT_FONTNAME << "," << DEFAULT_FONTSIZE << "'" << std::endl;

    script << "#==============================================================================" << std::endl;
    script << "# OUTPUT" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << "set output '" << filename << "'" << std::endl;

    script << "#==============================================================================" << std::endl;
    script << "# SETUP COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << commandvaluestr("set xrange", m_xrange);
    script << commandvaluestr("set yrange", m_yrange);
    script << m_xlabel << std::endl;
    script << m_ylabel << std::endl;
    script << m_border << std::endl;
    script << m_gridspecs << std::endl;
    script << m_tics << std::endl;
    script << m_legend << std::endl;
    script << commandvaluestr("set samples", m_samples);

    script << "#==============================================================================" << std::endl;
    script << "# CUSTOM EXPLICIT GNUPLOT COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << m_gnuplot.str();

    script << "#==============================================================================" << std::endl;
    script << "# PLOT COMMANDS" << std::endl;
    script << "#==============================================================================" << std::endl;
    script << "plot ";

    // The number of things to draw in the plot
    const auto n = m_plotspecs.size();

    // Plot in the same figure all those given drawing specs
    for(auto i = 0; i < n; ++i)
        script << m_plotspecs[i] << (i < n - 1 ? ", " : "");

    // Add an empty line at the end
    script << std::endl;

    // Flush the script file to avoid crashes with gnuplot
    script.flush();

    // std::string command = ("gnuplot " + scriptname + " >> gnuplot.log 2>&1");
    std::string command = ("gnuplot " + scriptname);
    pipe = popen(command.c_str(), "w");
}

} // namespace Capim
