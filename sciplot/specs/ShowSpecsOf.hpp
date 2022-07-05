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
#include <sciplot/specs/Specs.hpp>

namespace sciplot {

/// The class used to attach visibility options to a type.
template <typename DerivedSpecs>
class ShowSpecsOf : virtual public Specs<DerivedSpecs>
{
public:
    /// Construct a default ShowSpecsOf instance.
    ShowSpecsOf();

    /// Set the visibility status of the plot element.
    auto show(bool value=true) -> DerivedSpecs&;

    /// Set the visibility status of the plot element as hidden.
    auto hide() -> DerivedSpecs&;

    /// Return true if the underlying plot element is hidden.
    auto isHidden() const -> bool;

    /// Convert this ShowSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

private:
    /// The boolean flag that indicates if the plot element is shown or not.
    bool m_show;
};

/// The class used to specify visibility options.
class ShowSpecs : public ShowSpecsOf<ShowSpecs> {};

template <typename DerivedSpecs>
ShowSpecsOf<DerivedSpecs>::ShowSpecsOf()
{
    show();
}

template <typename DerivedSpecs>
auto ShowSpecsOf<DerivedSpecs>::show(bool value) -> DerivedSpecs&
{
    m_show = value;
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto ShowSpecsOf<DerivedSpecs>::hide() -> DerivedSpecs&
{
    return show(false);
}

template <typename DerivedSpecs>
auto ShowSpecsOf<DerivedSpecs>::isHidden() const -> bool
{
    return !m_show;
}

template <typename DerivedSpecs>
auto ShowSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    return m_show ? "" : "no";
}

} // namespace sciplot
