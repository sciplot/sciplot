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
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace plot {

enum class with
{
    lines, points, linepoints
};

namespace internal {

inline auto toString(with with) -> std::string
{
    switch(with) {
        case with::points: return "points";
        case with::linepoints: return "linepoints";
        default: return "lines";
    }
}

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

inline auto plotCommandString(std::string filename, plotargs args) -> std::string
{
    std::stringstream cmd;
    if(args.linestyle < 0) args.linestyle = 1;
    cmd << "'" << filename << "' using 1:2 ";
    cmd << "title " << args.title << " ";
    cmd << "with " << args.with << " ";
    cmd << "linestyle " << args.linestyle << " ";
    return cmd.str();
}

} // namespace internal

using namespace internal;

class plot
{
public:
    /// Construct a default plot object
    plot()
    {
    }

    inline auto xlabel(std::string label) -> void { m_xlabel = label; }
    inline auto ylabel(std::string label) -> void { m_ylabel = label; }

    inline auto xlabel() const -> std::string { return m_xlabel; }
    inline auto ylabel() const -> std::string { return m_ylabel; }

    template<typename X, typename Y>
    auto plot(const X& x, const Y& y, std::string title, with plotwith = with::lines, int linestyle = -1) -> void
    {
        m_args.push_back({ title, plotwith, linestyle });
        m_filenames.push_back(title + ".plot" + std::to_string(m_counter) + ".dat");
        std::ostream out(m_filenames.back());
        const auto size = std::min(x.size(), y.size());
        out << "x" << " " << "y" << '\n';
        for(auto i = 0; i < size; ++i)
            out << x[i] << " " << y[i] << '\n';
        out.flush();
        out.close();
    }

    auto show() -> void
    {

    }

    auto savePNG(std::string filename) -> void
    {
        std::ostream script(filename + ".plt");

        script << "set terminal png size " << m_size.first << "," << m_size.second << std::endl;
        script << "set output '" << filename << "'";
        script << "plot ";

        const auto n = m_filenames.size();
        for(auto i = 0; i < n; ++i)
            script << plotCommandString(m_filenames[i], m_args[i]) << (i < n - 1 ? ", " : "");

        execute(filename + '.plt');
    }

private:

    auto execute() -> void
    {
        std::stringstream 
    }

private:
    /// The size of the plot
    std::pair<int, int> m_size = {400, 300};

    /// The names of the files to which the plot data have been temporarily saved
    std::vector<std::string> m_filenames;

    /// The label of the x-axis
    std::string m_xlabel;

    /// The label of the y-axis
    std::string m_ylabel;

    /// The arguments in each plot call
    std::vector<plotargs> m_args;

    /// The counter of how many plot objects
    static int m_counter;
};

// Initialize the counter of plot objects
int plot::m_counter = 0;

} // namespace plot