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

    using namespace internal;

    /// The class used to define multipleplots in one canvas, show them in a pop-up window or save them to a file.
    class multiplot
    {
    public:
        /// Construct a default multiplot object
        multiplot();

        /// Set the palette of colors for the plot.
        /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
        auto palette(const std::string &name) -> multiplot &;

        /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
        auto size(std::size_t width, std::size_t height) -> multiplot &;

        /// Set the layout of the multiplot in x- and y-direction.
        auto layout(std::size_t rows, std::size_t columns) -> multiplot &;

        /// Set the title of the multiplot.
        auto title(const std::string &title) -> multiplot &;

        /// Add a plot to the multiplot.
        /// Note that if you're changing the plot afterwards, changes will NOT be recorded in the multiplot.
        auto add(const plot &p) -> multiplot &;

        /// Show the plot in a pop-up window.
        auto show() -> void;

        /// Save the plot in a file, with its extension defining the figure format.
        /// The extension of the file name determines the format of the figure.
        /// The supported figure formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
        /// Thus, to save a plot in `png` format, choose a file name with a `.png`
        /// file extension as in `fig.png`.
        auto save(const std::string &filename) -> void;

    protected:
        /// Plot id derived from m_counter upon construction
        auto id() const -> std::size_t;

        /// Counter of how many plot / singleplot objects have been instanciated in the application
        static std::size_t m_counter;

    private:
        /// Plot id derived from m_counter upon construction
        std::size_t m_id = 0;

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
        : m_id(m_counter++), m_scriptfilename("multishow" + str(id()) + ".plt")
    {
    }

    auto multiplot::id() const -> std::size_t
    {
        return m_id;
    }

    auto multiplot::palette(const std::string &name) -> multiplot &
    {
        m_palette = name;
        return *this;
    }

    auto multiplot::size(std::size_t width, std::size_t height) -> multiplot &
    {
        m_width = width;
        m_height = height;
        return *this;
    }

    auto multiplot::layout(std::size_t rows, std::size_t columns) -> multiplot &
    {
        m_layoutrows = rows;
        m_layoutcols = columns;
        return *this;
    }

    auto multiplot::title(const std::string &title) -> multiplot &
    {
        m_title = title;
        return *this;
    }

    auto multiplot::add(const plot &p) -> multiplot &
    {
        m_plots.push_back(p);
        return *this;
    }

    auto multiplot::show() -> void
    {
        // Open script file and truncate it
        std::ofstream script(m_scriptfilename);
        // Add palette info. Use default palette if the user hasn't set one
        gnuplotpalettecmd(script, m_palette.empty() ? DEFAULT_PALETTE : m_palette);
        // Add terminal info
        gnuplotshowterminalcmd(script);
        // Add multiplot commands
        gnuplotmultiplotcmd(script, m_layoutrows, m_layoutcols, m_title);
        // Add the plot commands
        for (const auto &p : m_plots)
        {
            script << p.repr();
        }
        // Add an empty line at the end and close the script to avoid crashes with gnuplot
        script << std::endl;
        script.close();
        // Show the plot
        gnuplotrunscript(m_scriptfilename, true);
        // Remove the no longer needed show{#}.plt file
        //        std::remove(m_scriptfilename.c_str());
    }

    auto multiplot::save(const std::string &filename) -> void
    {
        // Clean the file name to prevent errors
        auto cleanedfilename = gnuplotcleanpath(filename);
        // Get extension from file name
        auto extension = cleanedfilename.substr(cleanedfilename.rfind(".") + 1);
        // Open script file
        std::string scriptfilename = cleanedfilename + ".plt";
        std::ofstream script(scriptfilename);
        // Add palette info. Use default palette if the user hasn't set one
        gnuplotpalettecmd(script, m_palette.empty() ? DEFAULT_PALETTE : m_palette);
        // Add terminal info
        auto width = m_width == 0 ? DEFAULT_FIGURE_WIDTH : m_width;
        auto height = m_height == 0 ? DEFAULT_FIGURE_HEIGHT : m_height;
        std::string size = extension == "pdf" ? gnuplotsizeinches(width, height) : gnuplotsize(width, height);
        gnuplotsaveterminalcmd(script, extension, size);
        // Add output command
        gnuplotoutputcmd(script, cleanedfilename);
        // Add multiplot commands
        gnuplotmultiplotcmd(script, m_layoutrows, m_layoutcols, m_title);
        // Add the plot commands
        for (const auto &p : m_plots)
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
        // Save the plot as a file
        gnuplotrunscript(scriptfilename, false);
    }

} // namespace sciplot
