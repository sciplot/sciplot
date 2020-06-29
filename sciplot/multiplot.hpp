// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2020 Allan Leal
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

// sciplot includes
#include <sciplot/constants.hpp>
#include <sciplot/default.hpp>
#include <sciplot/enums.hpp>
#include <sciplot/palettes.hpp>
#include <sciplot/plot.hpp>
#include <sciplot/specs/axislabelspecs.hpp>
#include <sciplot/specs/borderspecs.hpp>
#include <sciplot/specs/gridspecs.hpp>
#include <sciplot/specs/legendspecs.hpp>
#include <sciplot/specs/linespecs.hpp>
#include <sciplot/specs/plotspecs.hpp>
#include <sciplot/specs/ticspecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The class used to define multipleplots in one canvas, show them in a pop-up window or save them to a file.
class multiplot
{
  public:
    /// Construct a default multiplot object
    multiplot();

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    auto autoclean(bool enable = true) -> void;

    /// Set the palette of colors for the plot.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto palette(const std::string& name) -> multiplot&;

    /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
    auto size(std::size_t width, std::size_t height) -> multiplot&;

    /// Set the layout of the multiplot in x- and y-direction.
    auto layout(std::size_t rows, std::size_t columns) -> multiplot&;

    /// Set the title of the multiplot.
    auto title(const std::string& title) -> multiplot&;

    /// Add a plot to the multiplot.
    /// Note that if you're changing the plot afterwards, changes will NOT be recorded in the multiplot.
    auto add(const plot& p) -> multiplot&;

    /// Write the current plot data of all plots to the data file(s).
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

    /// The number of rows in the multiplot layout
    std::size_t m_layoutrows = 0;

    /// The number of columns in the multiplot layout
    std::size_t m_layoutcols = 0;

    /// The title of the plot
    std::string m_title;

    /// The name of the file where the plot commands are saved
    std::string m_scriptfilename;

    /// All the plots that have been added to the multiplot
    std::vector<plot> m_plots;
};

// Initialize the counter of plot objects
std::size_t multiplot::m_counter = 0;

multiplot::multiplot()
    : m_id(m_counter++), m_scriptfilename("multishow" + internal::str(m_id) + ".plt")
{
}

auto multiplot::autoclean(bool enable) -> void
{
    m_autoclean = enable;
}

auto multiplot::palette(const std::string& name) -> multiplot&
{
    m_palette = name;
    return *this;
}

auto multiplot::size(std::size_t width, std::size_t height) -> multiplot&
{
    m_width = width;
    m_height = height;
    return *this;
}

auto multiplot::layout(std::size_t rows, std::size_t columns) -> multiplot&
{
    m_layoutrows = rows;
    m_layoutcols = columns;
    return *this;
}

auto multiplot::title(const std::string& title) -> multiplot&
{
    m_title = title;
    return *this;
}

auto multiplot::add(const plot& p) -> multiplot&
{
    m_plots.push_back(p);
    return *this;
}

auto multiplot::saveplotdata() const -> void
{
    for (const auto& p : m_plots)
    {
        p.saveplotdata();
    }
}

auto multiplot::show() const -> void
{
    // Open script file and truncate it
    std::ofstream script(m_scriptfilename);

    // Add palette info. Use default palette if the user hasn't set one
    gnuplot::palettecmd(script, m_palette.empty() ? internal::DEFAULT_PALETTE : m_palette);

    // Add terminal info
    gnuplot::showterminalcmd(script);

    // Add multiplot commands
    gnuplot::multiplotcmd(script, m_layoutrows, m_layoutcols, m_title);

    // Add the plot commands
    for (const auto& p : m_plots)
    {
        script << p.repr();
    }

    // Add an empty line at the end and close the script to avoid crashes with gnuplot
    script << std::endl;
    script.close();

    // save plot data to file(s)
    saveplotdata();

    // Show the plot
    gnuplot::runscript(m_scriptfilename, true);

    // remove the temporary files if user wants to
    if (m_autoclean)
    {
        cleanup();
    }
}

auto multiplot::save(const std::string& filename) const -> void
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

    // Add multiplot commands
    gnuplot::multiplotcmd(script, m_layoutrows, m_layoutcols, m_title);

    // Add the plot commands
    for (const auto& p : m_plots)
    {
        script << p.repr();
    }

    // Close multiplot
    script << "unset multiplot" << std::endl;

    // Unset the output
    script << std::endl;
    script << "set output";

    // Add an empty line at the end and close the script to avoid crashes with gnuplot
    script << std::endl;
    script.close();

    // save plot data to file(s)
    saveplotdata();

    // Save the plot as a file
    gnuplot::runscript(m_scriptfilename, false);

    // remove the temporary files if user wants to
    if (m_autoclean)
    {
        cleanup();
    }
}

auto multiplot::cleanup() const -> void
{
    std::remove(m_scriptfilename.c_str());
    for (const auto& p : m_plots)
    {
        p.cleanup();
    }
}

} // namespace sciplot
