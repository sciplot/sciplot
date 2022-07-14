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
#include <typeinfo>
#include <variant>
#include <vector>

// sciplot includes
#include <sciplot/Plot2D.hpp>
#include <sciplot/Plot3D.hpp>
#include <sciplot/specs/FontSpecsOf.hpp>
#include <sciplot/specs/LayoutSpecs.hpp>

namespace sciplot
{

/// The auxiliary type to represent either a 2D or 3D plot.
using PlotVariant = std::variant<Plot2D, Plot3D>;

template <typename... Ts>
struct Overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

static constexpr auto SavePlotVisitor = Overload{
    [](const Plot2D& p)
    { p.savePlotData(); },
    [](const Plot3D& p)
    { p.savePlotData(); }};

static constexpr auto ReprPlotVisitor = Overload{
    [](const Plot2D& p)
    { return p.repr(); },
    [](const Plot3D& p)
    { return p.repr(); }};

static constexpr auto CleanupPlotVisitor = Overload{
    [](const Plot2D& p)
    { p.cleanup(); },
    [](const Plot3D& p)
    { p.cleanup(); }};

/// The class used to create multiple plots in one canvas. A container for plots.
class Figure
{
  public:
    /// Construct a Figure object with given plots.
    Figure(const std::initializer_list<std::initializer_list<PlotVariant>>& plots);

    /// Construct a Figure object with given plots.
    Figure(const std::vector<std::vector<PlotVariant>>& plots);

    /// Get reference to generic plot object in figure
    /// @note Will throw if plot does not exist
    Plot& get(int i, int j);

    /// Get reference to specific plot object (2D / 3D) in figure
    /// @note Will throw if plot does not exist or T is of wrong type
    template <typename T>
    T& get(int i, int j);

    /// Set the palette of colors for all plots in the figure.
    /// @param name Any palette name displayed in https://github.com/Gnuplotting/gnuplot-palettes, such as "viridis", "parula", "jet".
    auto palette(const std::string& name) -> Figure&;

    /// Set the layout of the figure inside the canvas and return a reference to the corresponding specs object.
    auto layout() -> LayoutSpecs&;

    /// Set the font name for all the plots in the figure (e.g., Helvetica, Georgia, Times).
    auto fontName(std::string name) -> Figure&;

    /// Set the font size for all the plots in the figure (e.g., 10, 12, 16).
    auto fontSize(std::size_t size) -> Figure&;

    /// Set the title of the figure.
    auto title(const std::string& title) -> Figure&;

    /// Write the current plot data of all plots to the data file(s).
    auto saveplotdata() const -> void;

    /// Delete all files used to store plot data or scripts.
    auto cleanup() const -> void;

    /// Convert this figure into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// Counter of how many plot / singleplot objects have been instanciated in the application
    static std::size_t m_counter;

    /// Plot id derived from m_counter upon construction
    /// Must be the first member due to constructor initialization order!
    std::size_t m_id = 0;

    /// The layout of the figure inside the canvas
    LayoutSpecs m_layout;

    /// The number of rows in the multiplot layout
    std::size_t m_layoutrows = 0;
    /// The number of columns in the multiplot layout
    std::size_t m_layoutcols = 0;

    /// The title of the figure
    std::string m_title;

    /// All the plots that have been added to the figure
    std::vector<std::vector<PlotVariant>> m_plots;
};

// Initialize the counter of plot objects
inline std::size_t Figure::m_counter = 0;

inline Figure::Figure(const std::initializer_list<std::initializer_list<PlotVariant>>& plots)
    : m_id(m_counter++)
{
    m_layoutrows = plots.size();
    m_layoutcols = 1;
    for (const auto& row : plots)
        m_layoutcols = std::max<decltype(m_layoutcols)>(m_layoutcols, row.size()); // m_layoutcols = max number of columns among all rows

    for (const auto& row : plots)
        m_plots.emplace_back(row.begin(), row.end());
}

inline Figure::Figure(const std::vector<std::vector<PlotVariant>>& plots)
    : m_id(m_counter++), m_plots(plots)
{
    m_layoutrows = plots.size();
    m_layoutcols = 1;
    for (const auto& row : plots)
        m_layoutcols = std::max<decltype(m_layoutcols)>(m_layoutcols, row.size()); // m_layoutcols = max number of columns among all rows
}

inline Plot& Figure::get(int i, int j)
{
    auto& plot = m_plots.at(j).at(i);
    if (std::holds_alternative<Plot2D>(plot))
    {
        return std::get<Plot2D>(plot);
    }
    else if (std::holds_alternative<Plot3D>(plot))
    {
        return std::get<Plot3D>(plot);
    }
    throw std::runtime_error("Unknown plot type / Empty variant");
}

template <>
inline Plot2D& Figure::get(int i, int j)
{
    return std::get<Plot2D>(m_plots.at(j).at(i));
}

template <>
inline Plot3D& Figure::get(int i, int j)
{
    return std::get<Plot3D>(m_plots.at(j).at(i));
}

inline auto Figure::palette(const std::string& name) -> Figure&
{
    for (auto& row : m_plots)
    {
        for (auto& plot : row)
        {
            if (std::holds_alternative<Plot2D>(plot))
            {
                std::get<Plot2D>(plot).palette(name);
            }
            else if (std::holds_alternative<Plot3D>(plot))
            {
                std::get<Plot3D>(plot).palette(name);
            }
        }
    }
    return *this;
}

inline auto Figure::layout() -> LayoutSpecs&
{
    return m_layout;
}

inline auto Figure::title(const std::string& title) -> Figure&
{
    m_title = title;
    return *this;
}

inline auto Figure::repr() const -> std::string
{
    std::stringstream script;
    // Add multiplot commands
    if (m_layoutrows > 1 || m_layoutcols > 1)
    {
        gnuplot::multiplotcmd(script, m_layoutrows, m_layoutcols, m_title);
    }
    script << m_layout << std::endl;
    for (const auto& row : m_plots)
    {
        for (const auto& plot : row)
        {
            script << std::visit(ReprPlotVisitor, plot);
        }
    }
    // Close multiplot
    if (m_layoutrows > 1 || m_layoutcols > 1)
    {
        script << "unset multiplot" << std::endl;
    }
    return script.str();
}

inline auto Figure::saveplotdata() const -> void
{
    for (const auto& row : m_plots)
    {
        for (const auto& plot : row)
        {
            std::visit(SavePlotVisitor, plot);
        }
    }
}

inline auto Figure::cleanup() const -> void
{
    for (const auto& row : m_plots)
    {
        for (const auto& plot : row)
        {
            std::visit(CleanupPlotVisitor, plot);
        }
    }
}

} // namespace sciplot
