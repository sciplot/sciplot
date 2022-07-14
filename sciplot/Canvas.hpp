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
#include <variant>
#include <vector>

// sciplot includes
#include <sciplot/Figure.hpp>

namespace sciplot
{

/// The class used to create multiple figures in one canvas. A canvas can be show on screen or output to file.
class Canvas
{
  public:
    /// Construct a Canvas object with given figures.
    Canvas(const std::initializer_list<std::initializer_list<Figure>>& figures);

    /// Construct a Canvas object with given figures.
    Canvas(const std::vector<std::vector<Figure>>& figures);

    /// Get reference to figure object on canvas
    /// @note Will throw if figure does not exist
    Figure& get(int i, int j);

    /// Toggle automatic cleaning of temporary files (enabled by default). Pass false if you want to keep your script / data files.
    /// Call cleanup() to remove those files manually.
    auto autoclean(bool enable = true) -> void;

    /// Set the default palette of colors for all plots that DO NOT have a palette set.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto defaultPalette(const std::string& name) -> Canvas&;

    /// Set the output size of the canvas (in unit of points, with 1 inch = 72 points).
    auto size(std::size_t width, std::size_t height) -> Canvas&;

    /// Set the font name for all the plots on the canvas (e.g., Helvetica, Georgia, Times).
    auto fontName(std::string name) -> Canvas&;

    /// Set the font size for all the plots on the canvas (e.g., 10, 12, 16).
    auto fontSize(std::size_t size) -> Canvas&;

    /// Set the title of the canvas.
    /// @note This only work for show() atm!
    auto title(const std::string& title) -> Canvas&;

    /// Write the current plot data of all figures to the data file(s).
    auto saveplotdata() const -> void;

    /// Show the canvas in a pop-up window.
    /// @note This method removes temporary files after saving if `Canvas::autoclean(true)` (default).
    auto show() const -> void;

    /// Save the canvas to a file, with its extension defining the file format.
    /// The extension of the file name determines the file format.
    /// The supported formats are: `pdf`, `eps`, `svg`, `png`, and `jpeg`.
    /// Thus, to save the canvas in `pdf` format, choose a file name as in `canvas.pdf`.
    /// @note This method removes temporary files after saving if `Canvas::autoclean(true)` (default).
    auto save(const std::string& filename) const -> void;

    /// Delete all files used to store plot data or scripts.
    auto cleanup() const -> void;

  private:
    /// Counter of how many canvas objects have been instanciated in the application
    static std::size_t m_counter;

    /// Canvas id derived from m_counter upon construction
    /// Must be the first member due to constructor initialization order!
    std::size_t m_id = 0;

    /// Toggle automatic cleaning of temporary files (enabled by default)
    bool m_autoclean = true;

    /// The name of the default gnuplot palette to be used
    std::string m_defaultPalette;

    /// The font name and size used in the plots
    FontSpecs m_font;

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

    /// All the figures that have been added to the canvas
    std::vector<std::vector<Figure>> m_figures;
};

// Initialize the counter of plot objects
inline std::size_t Canvas::m_counter = 0;

inline Canvas::Canvas(const std::initializer_list<std::initializer_list<Figure>>& figures)
    : m_id(m_counter++), m_scriptfilename("multishow" + internal::str(m_id) + ".plt")
{
    m_layoutrows = figures.size();
    m_layoutcols = 1;
    for (const auto& row : figures)
        m_layoutcols = std::max<decltype(m_layoutcols)>(m_layoutcols, row.size()); // m_layoutcols = max number of columns among all rows

    for (const auto& row : figures)
        m_figures.emplace_back(row.begin(), row.end());
}

inline Canvas::Canvas(const std::vector<std::vector<Figure>>& figures)
    : m_id(m_counter++), m_scriptfilename("multishow" + internal::str(m_id) + ".plt"), m_figures(figures)
{
    m_layoutrows = figures.size();
    m_layoutcols = 1;
    for (const auto& row : figures)
        m_layoutcols = std::max<decltype(m_layoutcols)>(m_layoutcols, row.size()); // m_layoutcols = max number of columns among all rows
}

inline Figure& Canvas::get(int i, int j)
{
    return m_figures.at(j).at(i);
}

inline auto Canvas::autoclean(bool enable) -> void
{
    m_autoclean = enable;
}

inline auto Canvas::defaultPalette(const std::string& name) -> Canvas&
{
    m_defaultPalette = name;
    return *this;
}

inline auto Canvas::size(std::size_t width, std::size_t height) -> Canvas&
{
    m_width = width;
    m_height = height;
    return *this;
}

inline auto Canvas::fontName(std::string name) -> Canvas&
{
    m_font.fontName(name);
    return *this;
}

inline auto Canvas::fontSize(std::size_t size) -> Canvas&
{
    m_font.fontSize(size);
    return *this;
}

inline auto Canvas::title(const std::string& title) -> Canvas&
{
    m_title = title;
    return *this;
}

inline auto Canvas::saveplotdata() const -> void
{
    for (const auto& row : m_figures)
    {
        for (const auto& figure : row)
        {
            figure.saveplotdata();
        }
    }
}

inline auto Canvas::show() const -> void
{
    // Open script file and truncate it
    std::ofstream script(m_scriptfilename);
    // Add palette info. Use default palette if the user hasn't set one
    gnuplot::palettecmd(script, m_defaultPalette.empty() ? internal::SCIPLOT_DEFAULT_PALETTE : m_defaultPalette);
    // Add terminal info
    auto width = m_width == 0 ? internal::DEFAULT_FIGURE_WIDTH : m_width;
    auto height = m_height == 0 ? internal::DEFAULT_FIGURE_HEIGHT : m_height;
    std::string size = gnuplot::canvasSizeStr(width, height, false);
    gnuplot::showterminalcmd(script, size, m_font, m_title);
    // Add the plot commands
    for (const auto& row : m_figures)
    {
        for (const auto& figure : row)
        {
            // Add the plot commands
            script << figure.repr();
        }
    }
    // Add an empty line at the end and close the script to avoid crashes with gnuplot
    script << std::endl;
    script.close();
    // save plot data to file(s)
    saveplotdata();
    // Show the figure
    gnuplot::runscript(m_scriptfilename, true);
    // remove the temporary files if user wants to
    if (m_autoclean)
    {
        cleanup();
    }
}

inline auto Canvas::save(const std::string& filename) const -> void
{
    // Clean the file name to prevent errors
    auto cleanedfilename = gnuplot::cleanpath(filename);
    // Get extension from file name
    auto extension = cleanedfilename.substr(cleanedfilename.rfind(".") + 1);
    // Open script file
    std::ofstream script(m_scriptfilename);
    // Add palette info. Use default palette if the user hasn't set one
    gnuplot::palettecmd(script, m_defaultPalette.empty() ? internal::SCIPLOT_DEFAULT_PALETTE : m_defaultPalette);
    // Add terminal info including output size
    auto width = m_width == 0 ? internal::DEFAULT_FIGURE_WIDTH : m_width;
    auto height = m_height == 0 ? internal::DEFAULT_FIGURE_HEIGHT : m_height;
    std::string size = gnuplot::canvasSizeStr(width, height, extension == "pdf");
    gnuplot::saveterminalcmd(script, extension, size, m_font);
    // Add output command
    gnuplot::outputcmd(script, cleanedfilename);
    // Add the plot commands
    for (const auto& row : m_figures)
    {
        for (const auto& figure : row)
        {
            // Add the plot commands
            script << figure.repr();
        }
    }
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
    if (m_autoclean)
    {
        cleanup();
    }
}

inline auto Canvas::cleanup() const -> void
{
    std::remove(m_scriptfilename.c_str());
    for (const auto& row : m_figures)
    {
        for (const auto& figure : row)
        {
            figure.cleanup();
        }
    }
}

} // namespace sciplot
