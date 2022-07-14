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
#include <sciplot/specs/TextSpecsOf.hpp>
#include <sciplot/Utils.hpp>

namespace sciplot {

/// The class used to attach offset options to a type.
template <typename DerivedSpecs>
class OffsetSpecsOf : virtual public Specs<DerivedSpecs>
{
  public:
    /// Construct a default OffsetSpecsOf instance.
    OffsetSpecsOf();

    /// Shift the underlying plot element along the x direction by given number of characters (can be fraction).
    auto shiftAlongX(double chars) -> DerivedSpecs&;

    /// Shift the underlying plot element along the y direction by given number of characters (can be fraction).
    auto shiftAlongY(double chars) -> DerivedSpecs&;

    /// Shift the underlying plot element along the x direction within the graph coordinate system.
    auto shiftAlongGraphX(double val) -> DerivedSpecs&;

    /// Shift the underlying plot element along the y direction within the graph coordinate system.
    auto shiftAlongGraphY(double val) -> DerivedSpecs&;

    /// Shift the underlying plot element along the x direction within the screen coordinate system.
    auto shiftAlongScreenX(double val) -> DerivedSpecs&;

    /// Shift the underlying plot element along the y direction within the screen coordinate system.
    auto shiftAlongScreenY(double val) -> DerivedSpecs&;

    /// Convert this OffsetSpecsOf object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The offset of the title element along x direction.
    std::string xoffset = "0";

    /// The offset of the title element along y direction.
    std::string yoffset = "0";
};

/// The class used to specify offset options.
class OffsetSpecs : public OffsetSpecsOf<OffsetSpecs> {};

template <typename DerivedSpecs>
OffsetSpecsOf<DerivedSpecs>::OffsetSpecsOf()
{
}

template <typename DerivedSpecs>
auto OffsetSpecsOf<DerivedSpecs>::shiftAlongX(double chars) -> DerivedSpecs&
{
    xoffset = internal::str(chars);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto OffsetSpecsOf<DerivedSpecs>::shiftAlongY(double chars) -> DerivedSpecs&
{
    yoffset = internal::str(chars);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto OffsetSpecsOf<DerivedSpecs>::shiftAlongGraphX(double val) -> DerivedSpecs&
{
    xoffset = "graph " + internal::str(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto OffsetSpecsOf<DerivedSpecs>::shiftAlongGraphY(double val) -> DerivedSpecs&
{
    yoffset = "graph " + internal::str(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto OffsetSpecsOf<DerivedSpecs>::shiftAlongScreenX(double val) -> DerivedSpecs&
{
    xoffset = "screen " + internal::str(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto OffsetSpecsOf<DerivedSpecs>::shiftAlongScreenY(double val) -> DerivedSpecs&
{
    yoffset = "screen " + internal::str(val);
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto OffsetSpecsOf<DerivedSpecs>::repr() const -> std::string
{
    std::string offset;

    if(xoffset != "0" || yoffset != "0")
        offset = "offset " + xoffset + ", " + yoffset;

    std::stringstream ss;
    ss << gnuplot::optionStr(offset);
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
