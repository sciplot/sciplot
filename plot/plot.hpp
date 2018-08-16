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
#include <sstream>
#include <string>
#include <vector>

// Ensure appropriate popen or pclose calls when compiling with MSVC
#ifdef _MSC_VER
#define popen _popen
#define pclose _pclose
#endif

namespace gnuplot {

enum class with
{
    lines, points, linepoints
};

namespace internal {

/// Return a string for a given enum value of type `with`
inline auto str(with with) -> std::string
{
    switch(with) {
        case with::points: return "points";
        case with::linepoints: return "linepoints";
        default: return "lines";
    }
}

/// Return a string for a given index
inline auto str(int i) -> std::string
{
    return std::to_string(i);
}

// plot(x, y, "with lines title notitle ls 1 lw 1, "filename, u("1", 2));
/// The arguments for each plot call.
struct plotargs
{
    /// The titles of each curve displayed in the key (legend) of the plot
    std::string title;

    /// The type of plot
    std::string with;

    /// The number of the line style
    int linestyle;

    /// The width of the line
    int linewidth; // todo maybe use enum class like linewidth::one, linewidth::two
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

    inline auto xlabel(std::string label) -> void { m_xlabel = label; }
    inline auto ylabel(std::string label) -> void { m_ylabel = label; }

    inline auto xlabel() const -> std::string { return m_xlabel; }
    inline auto ylabel() const -> std::string { return m_ylabel; }


    template<typename X, typename Y>
    auto draw(const X& x, const Y& y, std::string options = "") -> void
    {
        // The minimum size of the arrays x and y (they should actually have equal lengths)
        const auto size = std::min(x.size(), y.size());

        // The string with the every command (e.g., every ::5::15 for rows from 5 to 15)
        const std::string every = std::string("every") + "::" + str(m_numdatarows) + "::" + str(m_numdatarows + size - 1);

        // Save the draw arguments for this x,y data
        m_plotargs.push_back("'" + m_filename + "'" + " using 1:2 " + every + " " + options);

        // Save the x,y data to the open file
        for(auto i = 0; i < size; ++i)
            m_filedata << x[i] << " " << y[i] << '\n';

        // Flush the file data to ensure its correct state when gnuplot is called
        m_filedata.flush();

        // Update the number of rows in the data file
        m_numdatarows += size;
    }

    // template<typename X, typename Y>
    // auto draw(const X& x, const Y& y, std::string title, with plotwith = with::lines, int linestyle = -1, int linewidth = -1) -> void
    // {
    //     // Save the draw arguments for this x,y data
    //     m_plotargs.push_back({ title, str(plotwith), linestyle, linewidth });

    //     // Save the x,y data to the open file
    //     const auto size = std::min(x.size(), y.size());
    //     for(auto i = 0; i < size; ++i)
    //         m_filedata << x[i] << " " << y[i] << '\n';

    //     // Add a new row index to mark the end of a new range of rows
    //     m_ranges.push_back(m_ranges.back() + size);
    // }

    auto show() -> void
    {
        std::string scriptname = "show" + str(m_counter) + ".plt";

        std::ofstream script(scriptname);

        script << "plot ";

        const auto n = m_plotargs.size();
        for(auto i = 0; i < n; ++i)
            script << m_plotargs[i] << (i < n - 1 ? ", " : "");

        script.flush();

        std::string command = ("gnuplot -persistent " + scriptname);
        pipe = popen(command.c_str(), "w");
    }

    auto saveSVG(std::string filename) -> void
    {
        std::string scriptname = filename + ".plt";

        std::ofstream script(scriptname);

        script << "set terminal svg size " << m_size.first << "," << m_size.second << std::endl;
        script << "set output '" << filename << "'" << std::endl;
        script << "plot ";

        const auto n = m_plotargs.size();
        for(auto i = 0; i < n; ++i)
            script << m_plotargs[i] << (i < n - 1 ? ", " : "");

        script.flush();

        // std::string command = ("gnuplot " + scriptname + " >> gnuplot.log 2>&1");
        std::string command = ("gnuplot " + scriptname);
        pipe = popen(command.c_str(), "w");
    }

private:

    auto execute() -> void
    {
    }

private:
    /// The size of the plot
    std::pair<int, int> m_size = {400, 300};

    /// The file output stream where the plot data is saved
    std::ofstream m_filedata;

    /// The name of the file to which the plot data is saved
    std::string m_filename;

    /// The current number of rows in the data file
    std::size_t m_numdatarows = 0;

    /// The label of the x-axis
    std::string m_xlabel;

    /// The label of the y-axis
    std::string m_ylabel;

    /// The arguments in each plot call
    std::vector<std::string> m_plotargs;

    /// The pointer to the pipe connecting to Gnuplot
    FILE* pipe = nullptr;

    /// The counter of how many plot objects
    static int m_counter;
};

// Initialize the counter of plot objects
int plot::m_counter = 0;

} // namespace gnuplot