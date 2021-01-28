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
#include <sciplot/util.hpp>
#include <sciplot/specs/Specs.hpp>

namespace sciplot
{

/// The class used to specify options for font.
template <typename DerivedSpecs>
class FontSpecs : virtual public internal::specs<DerivedSpecs>
{
  public:
    /// Construct a default FontSpecs instance.
    FontSpecs();

    /// Convert this FontSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the name of the font (e.g., Helvetica, Georgia, Times).
    auto fontname(std::string name) -> DerivedSpecs&
    {
        m_fontname = name;
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the point size of the font (e.g., 10, 12, 16).
    auto fontsize(std::size_t size) -> DerivedSpecs&
    {
        m_fontsize = size;
        return static_cast<DerivedSpecs&>(*this);
    }

  private:
    /// The name of the font.
    std::string m_fontname;

    /// The point size of the font.
    std::size_t m_fontsize;
};

template <typename DerivedSpecs>
FontSpecs<DerivedSpecs>::FontSpecs()
{
    fontname(internal::DEFAULT_FONTNAME);
    fontsize(internal::DEFAULT_FONTSIZE);
}

template <typename DerivedSpecs>
auto FontSpecs<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream ss;
    ss << "font '" << m_fontname << "," << m_fontsize << "'";
    return ss.str();
}

} // namespace sciplot
