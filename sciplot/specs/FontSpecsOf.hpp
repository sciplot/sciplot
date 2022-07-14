// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2021 Allan Leal
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
#include <sciplot/Utils.hpp>
#include <sciplot/specs/Specs.hpp>

namespace sciplot {

/// The class used to attach font options to a type.
template <typename DerivedSpecs>
class FontSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default FontSpecsOf instance.
    FontSpecsOf();

    /// Set the name of the font (e.g., Helvetica, Georgia, Times).
    auto fontName(std::string name) -> DerivedSpecs&;

    /// Set the point size of the font (e.g., 10, 12, 16).
    auto fontSize(std::size_t size) -> DerivedSpecs&;

    /// Convert this FontSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The name of the font.
    std::string m_fontname;

    /// The point size of the font.
    std::string m_fontsize;
};

/// The class used to specify font options.
class FontSpecs : public FontSpecsOf<FontSpecs> {};

template <typename DerivedSpecs>
FontSpecsOf<DerivedSpecs>::FontSpecsOf()
{}

template <typename DerivedSpecs>
auto FontSpecsOf<DerivedSpecs>::fontName(std::string name) -> DerivedSpecs&
{
    m_fontname = name;
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FontSpecsOf<DerivedSpecs>::fontSize(std::size_t size) -> DerivedSpecs&
{
    m_fontsize = std::to_string(size);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto FontSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream ss;
    if(m_fontname.size() || m_fontsize.size())
        ss << "font '" << m_fontname << "," << m_fontsize << "'";
    return ss.str();
}

} // namespace sciplot
