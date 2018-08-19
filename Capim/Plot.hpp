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
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Capim includes
#include <Capim/palletes.hpp>
#include <Capim/specs/axislabelspecs.hpp>
#include <Capim/specs/linespecs.hpp>
#include <Capim/specs/plotspecs.hpp>

// Ensure appropriate popen or pclose calls when compiling with MSVC
#ifdef _MSC_VER
#define popen _popen
#define pclose _pclose
#endif

namespace Capim {

using namespace internal;

class Plot
{
public:
    /// Construct a default plot object
    Plot()
    : m_filename("plot" + str(m_counter) + ".dat")
    {
        // Increment the counter
        ++m_counter;

        m_filedata.open(m_filename);

        // Set default values (not exactly the same as official gnuplot for aesthetics reasons)
        size(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        pallete(DEFAULT_PALLETE);

        /// The default border style of the plot
        border("3 front lc rgb " + str(DEFAULT_TEXTCOLOR) + " lt 1 lw 1");

        /// The default grid style of the plot
        grid(str("lc rgb ") + DEFAULT_GRIDCOLOR + " lt 1 dt 2 lw 1");

        /// The border style of the plot
        tics("nomirror front out scale 0.25");

        /// The boolean flag name of the gnuplot pallete to be used
        key(str("opaque tc rgb ") + DEFAULT_TEXTCOLOR + " box lc rgb " + DEFAULT_GRIDCOLOR);

    }

    /// Destroy this plot object
    ~Plot()
    {
        if(pipe != nullptr)
        {
            pclose(pipe);
            pipe = nullptr;
        }
    }

    auto size(std::size_t width, std::size_t height) -> void { m_size = str(width) + "," + str(height); }

    auto xlabel(std::string label) -> axislabelspecs& { m_xlabel.label(label); return m_xlabel; }

    auto ylabel(std::string label) -> axislabelspecs& { m_ylabel.label(label); return m_ylabel; }

    auto xrange(double min, double max) -> void { m_xrange = "[" + str(min) + ":" + str(max) + "]"; }

    auto yrange(double min, double max) -> void { m_yrange = "[" + str(min) + ":" + str(max) + "]"; }

    auto border(std::string options) -> void { m_border = options; }

    auto grid(std::string options) -> void { m_grid = options; }

    auto tics(std::string options) -> void { m_tics = options; }

    auto key(std::string options) -> void { m_key = options; }

    auto pallete(std::string name) -> void { m_pallete = name; }

    auto samples(std::size_t value) -> void { m_samples = str(value); }

    auto plot(std::string what) -> plotspecs&
    {
        // Save the draw arguments for this x,y data
        m_drawings.emplace_back(what);

        // Set the default line style specification for this drawing
        // Desired behavior is 1, 2, 3 (incrementing as new drawings are plotted)
        m_drawings.back().linestyle(m_drawings.size());

        // Return the just created drawing object in case the user wants to customize it
        return m_drawings.back();
    }

    template<typename X, typename Y>
    auto plot(const X& x, const Y& y) -> plotspecs&
    {
        // Save the given vectors x and y as a new data set in the data file
        gnuplotdataset(m_filedata, m_numdatasets, x, y);

        // Update the number of data sets in the file
        ++m_numdatasets;

        // Draw the x,y data now saved in the data file in a data set with index `m_numdatasets - 1`
        return plot("'" + m_filename + "' index " + str(m_numdatasets - 1));
    }

    auto show() -> void
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
        script << "set terminal qt size " << m_size << " enhanced font 'Georgia,10' persist" << std::endl;

        script << "#==============================================================================" << std::endl;
        script << "# SETUP COMMANDS" << std::endl;
        script << "#==============================================================================" << std::endl;
        script << commandvaluestr("set xrange", m_xrange);
        script << commandvaluestr("set yrange", m_yrange);
        script << commandvaluestr("set xlabel", m_xlabel.repr());
        script << commandvaluestr("set ylabel", m_ylabel.repr());
        script << commandvaluestr("set border", m_border);
        script << commandvaluestr("set grid", m_grid);
        script << commandvaluestr("set tics", m_tics);
        script << commandvaluestr("set key", m_key);
        script << commandvaluestr("set samples", m_samples);

        script << "#==============================================================================" << std::endl;
        script << "# PLOT COMMANDS" << std::endl;
        script << "#==============================================================================" << std::endl;
        script << "plot ";

        // The number of things to draw in the plot
        const auto n = m_drawings.size();

        // Plot in the same figure all those given drawing specs
        for(auto i = 0; i < n; ++i)
            script << m_drawings[i] << (i < n - 1 ? ", " : "");

        // Add an empty line at the end
        script << std::endl;

        // Flush the script file to avoid crashes with gnuplot
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

        script << "#==============================================================================" << std::endl;
        script << "# GNUPLOT-PALLETE (" << m_pallete << ")" << std::endl;
        script << "#------------------------------------------------------------------------------" << std::endl;
        script << "# see more at https://github.com/Gnuplotting/gnuplot-palettes" << std::endl;
        script << "#==============================================================================" << std::endl;
        script << palletes.at(m_pallete) << std::endl;

        script << "#==============================================================================" << std::endl;
        script << "# TERMINAL" << std::endl;
        script << "#==============================================================================" << std::endl;
        script << "set terminal " << extension << " size " << m_size << " enhanced rounded font 'Georgia,12'" << std::endl;

        script << "#==============================================================================" << std::endl;
        script << "# OUTPUT" << std::endl;
        script << "#==============================================================================" << std::endl;
        script << "set output '" << filename << "'" << std::endl;

        script << "#==============================================================================" << std::endl;
        script << "# SETUP COMMANDS" << std::endl;
        script << "#==============================================================================" << std::endl;
        script << commandvaluestr("set xrange", m_xrange);
        script << commandvaluestr("set yrange", m_yrange);
        script << commandvaluestr("set xlabel", m_xlabel.repr());
        script << commandvaluestr("set ylabel", m_ylabel.repr());
        script << commandvaluestr("set border", m_border);
        script << commandvaluestr("set grid", m_grid);
        script << commandvaluestr("set tics", m_tics);
        script << commandvaluestr("set key", m_key);
        script << commandvaluestr("set samples", m_samples);

        script << "#==============================================================================" << std::endl;
        script << "# PLOT COMMANDS" << std::endl;
        script << "#==============================================================================" << std::endl;
        script << "plot ";

        // The number of things to draw in the plot
        const auto n = m_drawings.size();

        // Plot in the same figure all those given drawing specs
        for(auto i = 0; i < n; ++i)
            script << m_drawings[i] << (i < n - 1 ? ", " : "");

        // Add an empty line at the end
        script << std::endl;

        // Flush the script file to avoid crashes with gnuplot
        script.flush();

        // std::string command = ("gnuplot " + scriptname + " >> gnuplot.log 2>&1");
        std::string command = ("gnuplot " + scriptname);
        pipe = popen(command.c_str(), "w");
    }

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
    std::string m_border;

    /// The grid style of the plot
    std::string m_grid;

    /// The border style of the plot
    std::string m_tics;

    /// The boolean flag name of the gnuplot pallete to be used
    std::string m_key;

    /// The number of sample points for functions
    std::string m_samples;

    /// The label of the x-axis
    axislabelspecs m_xlabel;

    /// The label of the y-axis
    axislabelspecs m_ylabel;

    /// The drawing options for each draw call
    std::vector<plotspecs> m_drawings;

    /// The pointer to the pipe connecting to Gnuplot
    FILE* pipe = nullptr;

    /// The counter of how many plot objects
    static int m_counter;
};

// Initialize the counter of plot objects
int Plot::m_counter = 0;

} // namespace Capim
