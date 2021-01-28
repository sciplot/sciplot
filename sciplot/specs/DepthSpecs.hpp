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
#include <sciplot/specs/Specs.hpp>

namespace sciplot
{

/// The class used to specify options for front or back placement of plot elements..
template <typename DerivedSpecs>
class DepthSpecs : virtual public specs<DerivedSpecs>
{
  public:
    /// Construct a default DepthSpecs instance.
    DepthSpecs();

    /// Convert this DepthSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the plot element to be displayed on the front of all plot elements.
    auto front() -> DerivedSpecs&
    {
        m_depth = "front";
        return static_cast<DerivedSpecs&>(*this);
    }

    /// Set the plot element to be displayed on the back of all plot elements.
    auto back() -> DerivedSpecs&
    {
        m_depth = "back";
        return static_cast<DerivedSpecs&>(*this);
    }

  private:
    /// The depth of the plot element (front or back) if applicable.
    std::string m_depth;
};

template <typename DerivedSpecs>
DepthSpecs<DerivedSpecs>::DepthSpecs()
{
    back();
}

template <typename DerivedSpecs>
auto DepthSpecs<DerivedSpecs>::repr() const -> std::string
{
    return m_depth;
}

} // namespace sciplot
