// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
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

// sciplot includes
#include <sciplot/default.hpp>
#include <sciplot/specs/fontspecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The class used to specify options for text elements.
template <typename derivedspecs>
class textspecs : public fontspecs<derivedspecs>
{
  public:
    /// Construct a default textspecs instance.
    textspecs();

    /// Convert this textspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the enhanced mode of the text.
    auto enhanced(bool value) -> derivedspecs&
    {
        m_enhanced = value ? "enhanced" : "noenhanced";
        return static_cast<derivedspecs&>(*this);
    }

    /// Set the color of the text (e.g., `"blue"`, `"#404040"`)
    auto textcolor(std::string color) -> derivedspecs&
    {
        m_color = "'" + color + "'";
        return static_cast<derivedspecs&>(*this);
    }

  private:
    /// The color of the title text.
    std::string m_color;

    /// The enhanced mode of the text (enhanced or noenhanced)
    std::string m_enhanced;
};

template <typename derivedspecs>
textspecs<derivedspecs>::textspecs()
{
    enhanced(true);
    textcolor(internal::DEFAULT_TEXTCOLOR);
}

template <typename derivedspecs>
auto textspecs<derivedspecs>::repr() const -> std::string
{
    std::stringstream ss;
    ss << m_enhanced << " textcolor " << m_color << " ";
    ss << fontspecs<derivedspecs>::repr();
    return ss.str();
}

} // namespace sciplot
