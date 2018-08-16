import sys, os

# Auxiliary commands
up = os.path.dirname
join = os.path.join

# Download the git submodule gnuplot-palettes
os.system('git submodule update --init')

# The root directory of the plot project
rootdir = up(up(sys.argv[0]))

# The directory where gnuplot-palettes are downloaded
palletesdir = join(rootdir, 'gnuplot-palettes')

# The directory of the library plot (source dir)
plotdir = join(rootdir, 'plot')

# The sorted list of pallete file names (that ends with .pal)
filenames = [filename for filename in os.listdir(palletesdir) if filename.endswith('.pal')]
filenames.sort()

# The list of pairs (pallete name, pallete .pal file contents)
palletes = []

for filename in filenames:
    file = open(join(palletesdir, filename), 'r')
    palletes.append((filename[:-4], file.read()))

# Open the plot/palletes.hpp file
palletes_hpp = open(join(plotdir, 'palletes.hpp'), 'w')

# Print the header part of the palletes.hpp file
print >>palletes_hpp, \
"""// A modern C++ interface for plotting using gnuplot
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
#include <map>
#include <string>

namespace plot {

/// Color palettes for gnuplot taken from https://github.com/Gnuplotting/gnuplot-palettes"""

# Print the std::map with keys equal to pallete names and values as the pal file contents
print >>palletes_hpp, 'const std::map<std::string, std::string> palletes = {'

for (key, value) in palletes:
    key = repr(key).replace("'", '"')
    value = repr(value).replace('"', '')
    value = 'R"({0})"'.format(value)
    print >>palletes_hpp, "    {{ {0}, {1} }},".format(key, value)

print >>palletes_hpp, '};'

# Print the closing brace of namespace plot
print >>palletes_hpp
print >>palletes_hpp, '} // namespace plot'
