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
#include <sciplot/Utils.hpp>
#include <sciplot/specs/TicsSpecsBaseOf.hpp>

namespace sciplot
{

/// The class used to specify options for tics.
class TicsSpecs : public TicsSpecsBaseOf<TicsSpecs>
{
  public:
    /// Construct a default TicsSpecs instance.
    TicsSpecs();

    /// Set the tics to be displayed on the front of all plot elements.
    auto stackFront() -> TicsSpecs&;

    /// Set the tics to be displayed on the back of all plot elements.
    auto stackBack() -> TicsSpecs&;

    /// Convert this TicsSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The depth where the tics are displayed (back or front).
    std::string m_depth;
};

inline TicsSpecs::TicsSpecs()
    : TicsSpecsBaseOf<TicsSpecs>()
{
    stackFront();
}

inline auto TicsSpecs::stackFront() -> TicsSpecs&
{
    m_depth = "front";
    return *this;
}

inline auto TicsSpecs::stackBack() -> TicsSpecs&
{
    m_depth = "back";
    return *this;
}

inline auto TicsSpecs::repr() const -> std::string
{
    const auto baserepr = TicsSpecsBaseOf<TicsSpecs>::repr();

    if (isHidden())
        return baserepr;

    std::stringstream ss;
    ss << baserepr << " ";
    ss << m_depth;
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
