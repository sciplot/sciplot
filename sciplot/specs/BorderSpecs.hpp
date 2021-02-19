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

// C++ includes
#include <bitset>
#include <sciplot/Default.hpp>
#include <sciplot/specs/DepthSpecsOf.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/Utils.hpp>

// sciplot includes

namespace sciplot {

/// The class used to specify options for plot border.
class BorderSpecs : public LineSpecsOf<BorderSpecs>, public DepthSpecsOf<BorderSpecs>
{
  public:
    /// Construct a default border instance.
    BorderSpecs();

    /// Remove all border edges from a 2d or 3d plot.
    auto clear() -> BorderSpecs&;

    /// Set all border edges to inactive. Methods none and clear have identical effect.
    auto none() -> BorderSpecs&;

    /// Activate the bottom border edge on the xy plane for a 2d plot.
    auto bottom() -> BorderSpecs&;

    /// Activate the left border edge on the xy plane for a 2d plot.
    auto left() -> BorderSpecs&;

    /// Activate the top border edge on the xy plane for a 2d plot.
    auto top() -> BorderSpecs&;

    /// Activate the right border edge on the xy plane for a 2d plot.
    auto right() -> BorderSpecs&;

    /// Activate the border edge on the bottom xy plane going from the left corner to front corner in a 3d perspective.
    auto bottomLeftFront() -> BorderSpecs&;

    /// Activate the border edge on the bottom xy plane going from the left corder to back corner in a 3d perspective.
    auto bottomLeftBack() -> BorderSpecs&;

    /// Activate the border edge on the bottom xy plane going from the right corner to front corner in a 3d perspective.
    auto bottomRightFront() -> BorderSpecs&;

    /// Activate the border edge on the bottom xy plane going from the right corder to back corner in a 3d perspective.
    auto bottomRightBack() -> BorderSpecs&;

    /// Activate the left vertical border edge in a 3d perspective.
    auto leftVertical() -> BorderSpecs&;

    /// Activate the back vertical border edge in a 3d perspective.
    auto backVertical() -> BorderSpecs&;

    /// Activate the right vertical border edge in a 3d perspective.
    auto rightVertical() -> BorderSpecs&;

    /// Activate the front vertical border edge in a 3d perspective.
    auto frontVertical() -> BorderSpecs&;

    /// Activate the border edge on the top xy plane going from the left corner to back corner in a 3d perspective.
    auto topLeftBack() -> BorderSpecs&;

    /// Activate the border edge on the top xy plane going from the right corder to back corner in a 3d perspective.
    auto topRightBack() -> BorderSpecs&;

    /// Activate the border edge on the top xy plane going from the left corner to front corner in a 3d perspective.
    auto topLeftFront() -> BorderSpecs&;

    /// Activate the border edge on the top xy plane going from the right corder to front corner in a 3d perspective.
    auto topRightFront() -> BorderSpecs&;

    /// Set the border for polar plot.
    auto polar() -> BorderSpecs&;

    /// Convert this BorderSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The bits encoding the active and inactive borders.
    std::bitset<13> m_encoding;

    /// The placement depth of the borders.
    std::string m_depth;
};

inline BorderSpecs::BorderSpecs()
{
    left();
    bottom();
    lineType(internal::DEFAULT_BORDER_LINETYPE);
    lineWidth(internal::DEFAULT_BORDER_LINEWIDTH);
    lineColor(internal::DEFAULT_BORDER_LINECOLOR);
    front();
}

inline auto BorderSpecs::clear() -> BorderSpecs&
{
    m_encoding.reset();
    return *this;
}

inline auto BorderSpecs::none() -> BorderSpecs&
{
    return clear();
}

inline auto BorderSpecs::bottom() -> BorderSpecs&
{
    m_encoding.set(0);
    return *this;
}

inline auto BorderSpecs::left() -> BorderSpecs&
{
    m_encoding.set(1);
    return *this;
}

inline auto BorderSpecs::top() -> BorderSpecs&
{
    m_encoding.set(2);
    return *this;
}

inline auto BorderSpecs::right() -> BorderSpecs&
{
    m_encoding.set(3);
    return *this;
}

inline auto BorderSpecs::bottomLeftFront() -> BorderSpecs&
{
    m_encoding.set(0);
    return *this;
}

inline auto BorderSpecs::bottomLeftBack() -> BorderSpecs&
{
    m_encoding.set(1);
    return *this;
}

inline auto BorderSpecs::bottomRightFront() -> BorderSpecs&
{
    m_encoding.set(2);
    return *this;
}

inline auto BorderSpecs::bottomRightBack() -> BorderSpecs&
{
    m_encoding.set(3);
    return *this;
}

inline auto BorderSpecs::leftVertical() -> BorderSpecs&
{
    m_encoding.set(4);
    return *this;
}

inline auto BorderSpecs::backVertical() -> BorderSpecs&
{
    m_encoding.set(5);
    return *this;
}

inline auto BorderSpecs::rightVertical() -> BorderSpecs&
{
    m_encoding.set(6);
    return *this;
}

inline auto BorderSpecs::frontVertical() -> BorderSpecs&
{
    m_encoding.set(7);
    return *this;
}

inline auto BorderSpecs::topLeftBack() -> BorderSpecs&
{
    m_encoding.set(8);
    return *this;
}

inline auto BorderSpecs::topRightBack() -> BorderSpecs&
{
    m_encoding.set(9);
    return *this;
}

inline auto BorderSpecs::topLeftFront() -> BorderSpecs&
{
    m_encoding.set(10);
    return *this;
}

inline auto BorderSpecs::topRightFront() -> BorderSpecs&
{
    m_encoding.set(11);
    return *this;
}

inline auto BorderSpecs::polar() -> BorderSpecs&
{
    m_encoding.set(2);
    return *this;
}

inline auto BorderSpecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << "set border " << m_encoding.to_ulong() << " ";
    ss << DepthSpecsOf<BorderSpecs>::repr() << " ";
    ss << LineSpecsOf<BorderSpecs>::repr();
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
