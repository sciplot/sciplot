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
#include <vector>

// sciplot includes
#include <sciplot/Figure.hpp>

namespace sciplot {

/// The class used to define multipleplots in one canvas, show them in a pop-up window or save them to a file.
class Figures
{
  public:
    /// Construct a Figures object with given figures.
    Figures(const std::initializer_list<std::initializer_list<Figure>>& figs);

    /// Construct a Figures object with given figures.
    Figures(const std::vector<std::vector<Figure>>& figs);

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    auto autoclean(bool enable = true) -> void;

    /// Set the palette of colors for the plot.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto palette(const std::string& name) -> Figures&;

    /// Set the size of the plot (in unit of points, with 1 inch = 72 points).
    auto size(std::size_t width, std::size_t height) -> Figures&;

    /// Set the title of the final figure.
    auto title(const std::string& title) -> Figures&;

    /// Write the current plot data of all plots to the data file(s).
    auto saveplotdata() const -> void;

    /// Show the figure in a pop-up window.
    /// Will remove temporary files after showing if autoclean(true) (default).
    auto show() const -> void;

    /// Save the figure in a file, with its extension defining the figure format.
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

    /// The number of rows in the figures layout
    std::size_t m_layoutrows = 0;

    /// The number of columns in the figures layout
    std::size_t m_layoutcols = 0;

    /// The title of the plot
    std::string m_title;

    /// The name of the file where the plot commands are saved
    std::string m_scriptfilename;

    /// All the plots that have been added to the figures
    std::vector<std::vector<Figure>> m_figures;
};

// Initialize the counter of plot objects
inline std::size_t Figures::m_counter = 0;

inline Figures::Figures(const std::initializer_list<std::initializer_list<Figure>>& figs)
: m_id(m_counter++),
  m_scriptfilename("multishow" + internal::str(m_id) + ".plt")
{
    m_layoutrows = figs.size();
    m_layoutcols = 1;
    for(const auto& row : figs)
        m_layoutcols = std::max(m_layoutcols, row.size()); // m_layoutcols = max number of columns among all rows

    for(const auto& row : figs)
        m_figures.emplace_back(row.begin(), row.end());
}

inline Figures::Figures(const std::vector<std::vector<Figure>>& figs)
: m_id(m_counter++),
  m_scriptfilename("multishow" + internal::str(m_id) + ".plt"),
  m_figures(figs)
{
    m_layoutrows = figs.size();
    m_layoutcols = 1;
    for(const auto& row : figs)
        m_layoutcols = std::max(m_layoutcols, row.size()); // m_layoutcols = max number of columns among all rows
}

inline auto Figures::autoclean(bool enable) -> void
{
    m_autoclean = enable;
}

inline auto Figures::palette(const std::string& name) -> Figures&
{
    m_palette = name;
    return *this;
}

inline auto Figures::size(std::size_t width, std::size_t height) -> Figures&
{
    m_width = width;
    m_height = height;
    return *this;
}

inline auto Figures::title(const std::string& title) -> Figures&
{
    m_title = title;
    return *this;
}

inline auto Figures::saveplotdata() const -> void
{
    for(const auto& row : m_figures)
        for(const auto& fig : row)
            fig.savePlotData();
}

inline auto Figures::show() const -> void
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

    // Add multiplot commands
    gnuplot::multiplotcmd(script, m_layoutrows, m_layoutcols, m_title);

    // // Add the plot commands
    // for(const auto& p : m_figures)
    // {
    //     script << p.repr();
    // }

    // Add the plot commands
    for(const auto& row : m_figures)
        for(const auto& fig : row)
            script << fig.repr();

    // Add an empty line at the end and close the script to avoid crashes with gnuplot
    script << std::endl;
    script.close();

    // save plot data to file(s)
    saveplotdata();

    // Show the figure
    gnuplot::runscript(m_scriptfilename, true);

    // remove the temporary files if user wants to
    if(m_autoclean)
    {
        cleanup();
    }
}

inline auto Figures::save(const std::string& filename) const -> void
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

    // // Add the plot commands
    // for(const auto& p : m_figures)
    // {
    //     script << p.repr();
    // }

    // Add the plot commands
    for(const auto& row : m_figures)
        for(const auto& fig : row)
            script << fig.repr();

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

    // Save the figure as a file
    gnuplot::runscript(m_scriptfilename, false);

    // remove the temporary files if user wants to
    if(m_autoclean)
    {
        cleanup();
    }
}

inline auto Figures::cleanup() const -> void
{
    std::remove(m_scriptfilename.c_str());
    for(const auto& row : m_figures)
        for(const auto& fig : row)
            fig.cleanup();
}

} // namespace sciplot
