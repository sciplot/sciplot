// A modern C++ interface for plotting using gnuplot
// https://github.com/allanleal/plot
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

// C++ includes
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// plot includes
#include "palletes.hpp"

// Ensure appropriate popen or pclose calls when compiling with MSVC
#ifdef _MSC_VER
#define popen _popen
#define pclose _pclose
#endif

namespace gnuplot {

/// All gnuplot style options for plotting data
enum class style
{
    lines,
    points,
    linespoints,
    impulses,
    dots,
    steps,
    fsteps,
    histeps,
    errorbars,
    labels,
    xerrorbars,
    yerrorbars,
    xyerrorbars,
    errorlines,
    xerrorlines,
    yerrorlines,
    xyerrorlines,
    boxes,
    histograms,
    filledcurves,
    boxerrorbars,
    boxxyerrorbars,
    financebars,
    candlesticks,
    vectors,
    image,
    rgbimage,
    pm3d,
};


namespace internal {

const auto GOLDEN_RATIO = 1.618034;

const auto DEFAULT_PALLETE = "dark2";
const auto DEFAULT_TEXTCOLOR = "'#404040'";
const auto DEFAULT_GRIDCOLOR = "'#d6d7d9'";
const auto DEFAULT_FONTNAME = "Georgia";
const auto DEFAULT_FONTSIZE = 12;
const auto DEFAULT_LINEWIDTH = 2;
const auto DEFAULT_HEIGHT = 300;
const auto DEFAULT_WIDTH = GOLDEN_RATIO * DEFAULT_HEIGHT;

/// Return a string for a given enum value of type `with`
inline auto str(style value) -> std::string
{
    switch(value) {
    case style::lines: return "lines";
    case style::points: return "points";
    case style::linespoints: return "linespoints";
    case style::impulses: return "impulses";
    case style::dots: return "dots";
    case style::steps: return "steps";
    case style::fsteps: return "fsteps";
    case style::histeps: return "histeps";
    case style::errorbars: return "errorbars";
    case style::labels: return "labels";
    case style::xerrorbars: return "xerrorbars";
    case style::yerrorbars: return "yerrorbars";
    case style::xyerrorbars: return "xyerrorbars";
    case style::errorlines: return "errorlines";
    case style::xerrorlines: return "xerrorlines";
    case style::yerrorlines: return "yerrorlines";
    case style::xyerrorlines: return "xyerrorlines";
    case style::boxes: return "boxes";
    case style::histograms: return "histograms";
    case style::filledcurves: return "filledcurves";
    case style::boxerrorbars: return "boxerrorbars";
    case style::boxxyerrorbars: return "boxxyerrorbars";
    case style::financebars: return "financebars";
    case style::candlesticks: return "candlesticks";
    case style::vectors: return "vectors";
    case style::image: return "image";
    case style::rgbimage: return "rgbimage";
    case style::pm3d: return "pm3d";
    default: return "lines";
    }
}

/// Return a string for a given index
template<typename T>
auto str(const T& i) -> std::string
{
    return std::to_string(i);
}

/// Return a string for a given char array
inline auto str(const char* word) -> std::string
{
    return word;
}

/// Return an empty string
inline auto str() -> std::string
{
    return {};
}

/// The class where options for the draw function is specified.
class drawing
{
public:
    /// Construct a drawing instance.
    /// @param what A string representing what to be plot (e.g., "'filename' u 1:2", "sin(x)", etc.)
    drawing(std::string what) : m_data(new Data(what)) {}

    /// Set the title of the drawing.
    auto title(std::string value) -> drawing& { m_data->title = value == "columnheader" ? value : "'" + value + "'"; return *this; }

    /// Set the format of the drawing (lines, points, linespoints).
    auto with(style value) -> drawing& { m_data->with = str(value); return *this; }

    /// Return the format of the drawing (lines, points, linespoints).
    auto with() const -> std::string { return m_data->with; }

    /// Set the line style of the drawing.
    auto linestyle(std::size_t value) -> drawing& { m_data->linestyle = str(value); return *this; }

    /// Return the line style of the drawing.
    auto linestyle() const -> std::string { return m_data->linestyle; }

    /// Set the line type of the drawing.
    auto linetype(std::size_t value) -> drawing& { m_data->linetype = str(value); return *this; }

    /// Return the line type of the drawing.
    auto linetype() const -> std::string { return m_data->linetype; }

    /// Set the line width of the drawing.
    auto linewidth(std::size_t value) -> drawing& { m_data->linewidth = str(value); return *this; }

    /// Return the line width of the drawing.
    auto linewidth() const -> std::string { return m_data->linewidth; }

    /// Set the line color of the drawing.
    auto linecolor(std::string value) -> drawing& { m_data->linecolor = value; return *this; }

    /// Return the line color of the drawing.
    auto linecolor() const -> std::string { return m_data->linecolor; }

    /// Set the dash type of the drawing.
    auto dashtype(std::size_t value) -> drawing& { m_data->dashtype = str(value); return *this; }

    /// Return the dash type of the drawing.
    auto dashtype() const -> std::string { return m_data->dashtype; }

    /// Return the command string to be used in gnuplot plot command.
    auto command() const -> std::string
    {
        std::string cmd = m_data->what;
        if(m_data->title.size()) cmd = cmd + " title " + m_data->title;
        if(m_data->with.size()) cmd = cmd + " with " + m_data->with;
        if(m_data->linestyle.size()) cmd = cmd + " linestyle " + m_data->linestyle;
        if(m_data->linetype.size()) cmd = cmd + " linetype " + m_data->linetype;
        if(m_data->linewidth.size()) cmd = cmd + " linewidth " + m_data->linewidth;
        if(m_data->linecolor.size()) cmd = cmd + " linecolor " + m_data->linecolor;
        if(m_data->dashtype.size()) cmd = cmd + " dashtype " + m_data->dashtype;

        return cmd;
    }

private:
    struct Data
    {
        Data(std::string what) : what(what) {}
        std::string what;
        std::string title;
        std::string with = "lines";
        std::string linestyle;
        std::string linetype;
        std::string linewidth = str(DEFAULT_LINEWIDTH);
        std::string linecolor;
        std::string dashtype;
    };

    std::shared_ptr<Data> m_data;
};

/// Return the correct gnuplot string command for given rgb color (e.g., "#FF00FF")
auto rgb(std::string color) -> std::string { return "rgb '" + color + "'"; }

/// Return the correct gnuplot string command for given rgb color as hex number (e.g., 0xFF00FF)
auto rgb(int hexcolor) -> std::string { return "rgb " + str(hexcolor); }

/// The options for an axis label (e.g., xlabel, ylabel, etc.)
class axislabel
{
public:
    /// Construct a default axislabel instance.
    axislabel() : m_data(new Data(""))
    {}

    /// Construct a axislabel instance with given label title.
    axislabel(std::string title) : m_data(new Data("'" + title + "'"))
    {}

    /// Set the offset of the label.
    /// @param xval The offset along the x direction
    /// @param yval The offset along the y direction
    auto offset(int xval, int yval) -> axislabel& { m_data->offset = str(xval) + "," + str(yval); return *this; }

    /// Set the font name for the label.
    /// @param name The name of the font (e.g., Helvetica, Georgia, Times)
    auto fontname(std::string name) -> axislabel& { m_data->fontname = name; return *this; }

    /// Set the font size of the label.
    /// @param size The point size of the font (e.g., 10, 12, 16)
    auto fontsize(std::size_t size) -> axislabel& { m_data->fontsize = str(size); }

    /// Set the color of the label.
    /// @param color The color of the label (e.g., "blue", "rgb '#404040'")
    auto textcolor(std::string color) -> axislabel& { m_data->textcolor = color; return *this; }

    /// Set the enhanced mode of the label.
    /// @param value If true, then `enhanced` gnuplot option is used, otherwise, `noenhanced`
    auto enhanced(bool value) -> axislabel& { m_data->enhanced = value ? "enhanced" : "noenhanced"; return *this; }

    /// Set the rotation of the label.
    /// @param degrees The degrees used to rotate the label.
    auto rotate(double degrees) -> axislabel& { m_data->rotate = "rotate by " + str(degrees); return *this; }

    /// Set the label to rotate parallel to the axis.
    auto rotateparallel() -> axislabel& { m_data->rotate = "rotate parallel"; return *this; }

    /// Return the command string to be used in gnuplot label command.
    auto command() const -> std::string
    {
        std::string font = "'" + m_data->fontname;
        if(m_data->fontsize.size()) font = font + "," + m_data->fontsize;
        font = font +  "'";

        std::string cmd = m_data->title;
        if(m_data->offset.size()) cmd = cmd + " offset " + m_data->offset;
        if(m_data->fontname.size() || m_data->fontsize.size()) cmd = cmd + " font '" + m_data->fontname + "," + m_data->fontsize + "'";
        if(m_data->textcolor.size()) cmd = cmd + " textcolor " + m_data->textcolor;
        if(m_data->enhanced.size()) cmd = cmd + m_data->enhanced;
        if(m_data->rotate.size()) cmd = cmd + m_data->rotate;

        return cmd;
    }

private:
    struct Data
    {
        Data(std::string title) : title(title) {}
        std::string title;
        std::string offset;
        std::string fontname = DEFAULT_FONTNAME;
        std::string fontsize = str(DEFAULT_FONTSIZE);
        std::string textcolor = DEFAULT_TEXTCOLOR;
        std::string enhanced;
        std::string rotate;
    };

    std::shared_ptr<Data> m_data;
};

} // namespace internal

using namespace internal;

class plot
{
public:
    /// Construct a default plot object
    plot()
    : m_filename("plot" + str(m_counter) + ".dat")
    {
        // Increment the counter
        ++m_counter;

        m_filedata.open(m_filename);
    }

    /// Destroy this plot object
    ~plot()
    {
        if(pipe != nullptr)
        {
            pclose(pipe);
            pipe = nullptr;
        }
    }

    inline auto xlabel(std::string title) -> axislabel& { m_xlabel = axislabel(title); return m_xlabel; }
    inline auto xlabel() const -> axislabel { return m_xlabel; }

    inline auto ylabel(std::string label) -> axislabel& { m_ylabel = axislabel(label); return m_ylabel; }
    inline auto ylabel() const -> axislabel { return m_ylabel; }

    inline auto xrange(double min, double max) -> void { m_xrange = { min, max }; }
    inline auto xrange() const -> std::pair<double, double> { return m_xrange; }

    inline auto yrange(double min, double max) -> void { m_yrange = { min, max }; }
    inline auto yrange() const -> std::pair<double, double> { return m_yrange; }

    inline auto border(std::string options) -> void { m_border = options; }
    inline auto border() const -> std::string { return m_border; }

    inline auto grid(std::string options) -> void { m_grid = options; }
    inline auto grid() const -> std::string { return m_grid; }

    inline auto tics(std::string options) -> void { m_tics = options; }
    inline auto tics() const -> std::string { return m_tics; }

    inline auto key(std::string options) -> void { m_key = options; }
    inline auto key() const -> std::string { return m_key; }

    inline auto pallete(std::string name) -> void { m_pallete = name; }
    inline auto pallete() const -> std::string { return m_pallete; }

    inline auto samples(std::size_t value) -> void { m_samples = value; }
    inline auto samples() const -> std::size_t { return m_samples; }

    auto draw(std::string what) -> drawing&
    {
        // Save the draw arguments for this x,y data
        m_drawings.emplace_back(what);

        // Return the just created drawing object in case the user wants to customize it
        return m_drawings.back();
    }

    template<typename X, typename Y>
    auto draw(const X& x, const Y& y) -> drawing&
    {
        // The minimum size of the arrays x and y (they should actually have equal lengths)
        const auto size = std::min(x.size(), y.size());

        // The string with the every command (e.g., every ::5::15 for rows from 5 to 15)
        const std::string every = std::string("every") + "::" + str(m_numdatarows) + "::" + str(m_numdatarows + size - 1);

        // Save the x,y values to the data file
        for(auto i = 0; i < size; ++i)
            m_filedata << x[i] << " " << y[i] << '\n';

        // Flush the file data to ensure its correct state when gnuplot is called
        m_filedata.flush();

        // Update the number of rows in the data file
        m_numdatarows += size;

        // Save the plot command to draw the x,y data now saved in the data file
        m_drawings.emplace_back("'" + m_filename + "'" + " using 1:2 " + every);

        // Return the just created drawing object in case the user wants to customize it
        return m_drawings.back();
    }

    auto show() -> void
    {
        std::string scriptname = "show" + str(m_counter) + ".plt";

        std::ofstream script(scriptname);

        // Ensure a ls option is provided in options
//        if(options.find("ls") == std::string::npos)
//            options = " ls " + str(m_drawings.size() + 1) + " " + options;

        script << palletes.at(m_pallete) << std::endl;

        script << "# Set the terminal" << std::endl;
        script << "set terminal qt size " << m_size.first << "," << m_size.second << " enhanced font 'Georgia,10' persist" << std::endl;

        script << "# Configuration of the plot details" << std::endl;
        if(m_xrange.first != m_xrange.second) script << "set xrange [" << m_xrange.first << ":" << m_xrange.second << "]" << std::endl;
        if(m_yrange.first != m_yrange.second) script << "set yrange [" << m_xrange.first << ":" << m_xrange.second << "]" << std::endl;
        script << "set xlabel " << m_xlabel.command() << std::endl;
        script << "set ylabel " << m_ylabel.command() << std::endl;
        script << "set border " << m_border << std::endl;
        script << "set grid " << m_grid << std::endl;
        script << "set tics " << m_tics << std::endl;
        script << "set key " << m_key << std::endl;
        script << "set samples " << m_samples << std::endl;

        script << "# Set the plots" << std::endl;
        script << "plot ";

        // The number of things to draw in the plot
        const auto n = m_drawings.size();

        // Add the strings to plot each drawing
        for(auto i = 0; i < n; ++i)
        {
            // Ensure linestyle is explicitly set to avoid use of default gnuplot colors
            if(m_drawings[i].linestyle().empty())
                m_drawings[i].linestyle(i + 1);

            // Add the plot command for the current drawing
            script << m_drawings[i].command() << (i < n - 1 ? ", " : "");
        }

        script.flush();

        std::string command = ("gnuplot " + scriptname);
        pipe = popen(command.c_str(), "w");

        // Remove the no longer needed show{#}.plt file
//        std::remove(scriptname.c_str());
    }

    auto save(std::string filename) -> void
    {
        std::string extension = filename.substr(filename.rfind(".") + 1);

        std::string scriptname = filename + ".plt";

        std::ofstream script(scriptname);

        script << palletes.at(m_pallete) << std::endl;

        script << "set terminal " << extension << " size " << m_size.first << "," << m_size.second << " enhanced rounded font 'Georgia,12'" << std::endl;

        script << "# Set the output" << std::endl;
        script << "set output '" << filename << "'" << std::endl;

        script << "# Configuration of the plot details" << std::endl;
        if(m_xrange.first != m_xrange.second) script << "set xrange [" << m_xrange.first << ":" << m_xrange.second << "]" << std::endl;
        if(m_yrange.first != m_yrange.second) script << "set yrange [" << m_xrange.first << ":" << m_xrange.second << "]" << std::endl;
        script << "set xlabel " << m_xlabel.command() << std::endl;
        script << "set ylabel " << m_ylabel.command() << std::endl;
        script << "set border " << m_border << std::endl;
        script << "set grid " << m_grid << std::endl;
        script << "set tics " << m_tics << std::endl;
        script << "set key " << m_key << std::endl;
        script << "set samples " << m_samples << std::endl;

        script << "plot ";

        const auto n = m_drawings.size();
        for(auto i = 0; i < n; ++i)
            script << m_drawings[i].command() << (i < n - 1 ? ", " : "");

        script.flush();

        // std::string command = ("gnuplot " + scriptname + " >> gnuplot.log 2>&1");
        std::string command = ("gnuplot " + scriptname);
        pipe = popen(command.c_str(), "w");
    }

private:
    /// The size of the plot
    std::pair<int, int> m_size = { DEFAULT_WIDTH, DEFAULT_HEIGHT };

    /// The x range of the plot
    std::pair<double, double> m_xrange = {0, 0};

    /// The y range of the plot
    std::pair<double, double> m_yrange = {0, 0};

    /// The file output stream where the plot data is saved
    std::ofstream m_filedata;

    /// The name of the file to which the plot data is saved
    std::string m_filename;

    /// The name of the gnuplot pallete to be used
    std::string m_pallete = DEFAULT_PALLETE;

    /// The border style of the plot
    std::string m_border = str() + "3 front lc rgb " + DEFAULT_TEXTCOLOR + " lt 1 lw 1";

    /// The grid style of the plot
    std::string m_grid = str() + "lc rgb " + DEFAULT_GRIDCOLOR + " lt 1 dt 2 lw 1";

    /// The border style of the plot
    std::string m_tics = "nomirror front out scale 0.25";

    /// The boolean flag name of the gnuplot pallete to be used
    std::string m_key = str() + "opaque tc rgb " + DEFAULT_TEXTCOLOR + " box lc rgb " + DEFAULT_GRIDCOLOR;

    /// The number of sample points for functions
    std::size_t m_samples = 250;

    /// The current number of rows in the data file
    std::size_t m_numdatarows = 0;

    /// The label of the x-axis
    axislabel m_xlabel;

    /// The label of the y-axis
    axislabel m_ylabel;

    /// The drawing options for each draw call
    std::vector<drawing> m_drawings;

    /// The pointer to the pipe connecting to Gnuplot
    FILE* pipe = nullptr;

    /// The counter of how many plot objects
    static int m_counter;
};

// Initialize the counter of plot objects
int plot::m_counter = 0;

} // namespace gnuplot
