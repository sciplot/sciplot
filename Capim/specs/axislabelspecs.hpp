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

// Capim includes
#include <Capim/default.hpp>
#include <Capim/specs/fontspecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The specifications for an axis label (e.g., xlabel, ylabel, etc.)
class axislabelspecs : public fontspecs<axislabelspecs>
{
public:
    /// Construct a default axislabelspecs instance.
    axislabelspecs();

    /// Convert this axislabelspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the word of the label.
    /// @param word The word of the label (e.g., "Temperature [K]")
    auto label(std::string word) -> axislabelspecs& { m_label = "'" + word + "'"; return *this; }

    /// Set the offset of the label.
    /// @param xval The offset along the x direction
    /// @param yval The offset along the y direction
    auto offset(int xval, int yval) -> axislabelspecs& { m_offset = str(xval) + "," + str(yval); return *this; }

    /// Set the color of the label.
    /// @param color The color of the label (e.g., "blue", "rgb '#404040'")
    auto textcolor(std::string color) -> axislabelspecs& { m_textcolor = color; return *this; }

    /// Set the enhanced mode of the label.
    /// @param value If true, then `enhanced` gnuplot option is used, otherwise, `noenhanced`
    auto enhanced(bool value) -> axislabelspecs& { m_enhanced = value ? "enhanced" : "noenhanced"; return *this; }

    /// Set the rotation angle of the label in degrees.
    auto rotate(double angle) -> axislabelspecs& { m_rotate = "by " + str(angle); return *this; }

    /// Set the axis label parallel to its corresponding axis.
    auto axisparallel() -> axislabelspecs& { m_rotate = "parallel"; return *this; }

private:
    std::string m_label;
    std::string m_offset;
    std::string m_textcolor;
    std::string m_enhanced;
    std::string m_rotate;
};

axislabelspecs::axislabelspecs()
{
    fontname(DEFAULT_FONTNAME);
    fontsize(DEFAULT_FONTSIZE);
    textcolor(DEFAULT_TEXTCOLOR);
}

auto axislabelspecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << m_label << " ";
    ss << optionvaluestr("offset", m_offset);
    ss << fontspecs<axislabelspecs>::repr();
    ss << optionvaluestr("textcolor", m_textcolor);
    ss << optionstr(m_enhanced);
    ss << optionvaluestr("rotate", m_rotate);
    return ss.str();
}

} // namespace internal
} // namespace Capim
