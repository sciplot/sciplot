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
#include <Capim/specs/specs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The specifications for an axis label (e.g., xlabel, ylabel, etc.)
class axislabelspecs : public specs
{
public:
    /// Construct a default axislabelspecs instance.
    axislabelspecs() : axislabelspecs("")
    {
    }

    /// Construct a axislabelspecs instance with given label title.
    axislabelspecs(std::string title) : m_title("'" + title + "'")
    {
        // Set default values (not exactly the same as official gnuplot for aesthetics reasons)
        fontname(DEFAULT_FONTNAME);
        fontsize(DEFAULT_FONTSIZE);
        textcolor(DEFAULT_TEXTCOLOR);
    }

    /// Set the offset of the label.
    /// @param xval The offset along the x direction
    /// @param yval The offset along the y direction
    auto offset(int xval, int yval) -> axislabelspecs& { m_offset = str(xval) + "," + str(yval); return *this; }

    /// Set the font name for the label.
    /// @param name The name of the font (e.g., Helvetica, Georgia, Times)
    auto fontname(std::string name) -> axislabelspecs& { m_fontname = name; return *this; }

    /// Set the font size of the label.
    /// @param size The point size of the font (e.g., 10, 12, 16)
    auto fontsize(std::size_t size) -> axislabelspecs& { m_fontsize = str(size); return *this; }

    /// Set the color of the label.
    /// @param color The color of the label (e.g., "blue", "rgb '#404040'")
    auto textcolor(std::string color) -> axislabelspecs& { m_textcolor = color; return *this; }

    /// Set the enhanced mode of the label.
    /// @param value If true, then `enhanced` gnuplot option is used, otherwise, `noenhanced`
    auto enhanced(bool value) -> axislabelspecs& { m_enhanced = value ? "enhanced" : "noenhanced"; return *this; }

    /// Set the rotation of the label.
    /// @param angle The angle used to rotate the label.
    /// @param units The units of the angle ("" is radians, "pi" as multiple of pi number, "deg" in degrees).
    auto rotateby(double angle, std::string units = "") -> axislabelspecs& { m_rotate = "rotate by " + str(angle) + units; return *this; }

    /// Set the label to rotate parallel to the axis.
    auto rotateparallel() -> axislabelspecs& { m_rotate = "rotate parallel"; return *this; }

    /// Set the label to a no rotate state.
    auto norotate() -> axislabelspecs& { m_rotate = "norotate"; return *this; }

    /// Convert this axislabelspecs object into a gnuplot formatted string.
    virtual auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << m_title << " ";
        ss << optionvaluestr("offset", m_offset);
        ss << optionvaluestr("font", fontstr(m_fontname, m_fontsize));
        ss << optionvaluestr("textcolor", m_textcolor);
        ss << m_enhanced << " ";
        ss << m_rotate << " ";
        return ss.str();
    }

private:
    std::string m_title;
    std::string m_offset;
    std::string m_fontname;
    std::string m_fontsize;
    std::string m_textcolor;
    std::string m_enhanced;
    std::string m_rotate;
};

} // namespace internal
} // namespace Capim
