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
#include <sciplot/Default.hpp>
#include <sciplot/specs/Specs.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to attach point options to a type.
template <typename DerivedSpecs>
class PointSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default PointSpecsOf instance.
    PointSpecsOf();

    /// Set the point type of the underlying plot object.
    auto pointType(int value) -> DerivedSpecs&;

    /// Set the point size of the underlying plot object.
    auto pointSize(int value) -> DerivedSpecs&;

    /// Convert this PointSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The point type of the underlying plot object (e.g., "pt 3").
    std::string m_pointtype;

    /// The point width of the underlying plot object (e.g., "ps 2").
    std::string m_pointsize;
};

/// The class used to specify point options.
class PointSpecs : public PointSpecsOf<PointSpecs> {};

template <typename DerivedSpecs>
PointSpecsOf<DerivedSpecs>::PointSpecsOf()
{
}

template <typename DerivedSpecs>
auto PointSpecsOf<DerivedSpecs>::pointType(int value) -> DerivedSpecs&
{
    m_pointtype = "pointtype " + internal::str(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto PointSpecsOf<DerivedSpecs>::pointSize(int value) -> DerivedSpecs&
{
    m_pointsize = "pointsize " + internal::str(value);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto PointSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream ss; // ensure it remains empty if no point style option has been given!
    ss << m_pointtype << " ";
    ss << m_pointsize;
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
