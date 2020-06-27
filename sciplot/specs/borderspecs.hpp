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

// C++ includes
#include <sciplot/default.hpp>
#include <sciplot/specs/linespecs.hpp>
#include <sciplot/util.hpp>
#include <bitset>

// sciplot includes

namespace sciplot {

/// The class used to specify options for plot border.
class borderspecs : public linespecs<borderspecs>
{
public:
    /// Construct a default border instance.
    borderspecs();

    /// Convert this borderspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Remove all border edges from a 2d or 3d plot.
    auto clear() -> borderspecs& { m_encoding.reset(); return *this; }

    /// Set all border edges to inactive. Methods none and clear have identical effect.
    auto none() -> borderspecs& { return clear(); }

    /// Activate the bottom border edge on the xy plane for a 2d plot.
    auto bottom() -> borderspecs& { m_encoding.set(0); return *this; }

    /// Activate the left border edge on the xy plane for a 2d plot.
    auto left() -> borderspecs& { m_encoding.set(1); return *this; }

    /// Activate the top border edge on the xy plane for a 2d plot.
    auto top() -> borderspecs& { m_encoding.set(2); return *this; }

    /// Activate the right border edge on the xy plane for a 2d plot.
    auto right() -> borderspecs& { m_encoding.set(3); return *this; }

    /// Activate the border edge on the bottom xy plane going from the left corner to front corner in a 3d perspective.
    auto bottomleftfront() -> borderspecs& { m_encoding.set(0); return *this; }

    /// Activate the border edge on the bottom xy plane going from the left corder to back corner in a 3d perspective.
    auto bottomleftback() -> borderspecs& { m_encoding.set(1); return *this; }

    /// Activate the border edge on the bottom xy plane going from the right corner to front corner in a 3d perspective.
    auto bottomrightfront() -> borderspecs& { m_encoding.set(2); return *this; }

    /// Activate the border edge on the bottom xy plane going from the right corder to back corner in a 3d perspective.
    auto bottomrightback() -> borderspecs& { m_encoding.set(3); return *this; }

    /// Activate the left vertical border edge in a 3d perspective.
    auto leftvertical() -> borderspecs& { m_encoding.set(4); return *this; }

    /// Activate the back vertical border edge in a 3d perspective.
    auto backvertical() -> borderspecs& { m_encoding.set(5); return *this; }

    /// Activate the right vertical border edge in a 3d perspective.
    auto rightvertical() -> borderspecs& { m_encoding.set(6); return *this; }

    /// Activate the front vertical border edge in a 3d perspective.
    auto frontvertical() -> borderspecs& { m_encoding.set(7); return *this; }

    /// Activate the border edge on the top xy plane going from the left corner to back corner in a 3d perspective.
    auto topleftback() -> borderspecs& { m_encoding.set(7); return *this; }

    /// Activate the border edge on the top xy plane going from the right corder to back corner in a 3d perspective.
    auto toprightback() -> borderspecs& { m_encoding.set(9); return *this; }

    /// Activate the border edge on the top xy plane going from the left corner to front corner in a 3d perspective.
    auto topleftfront() -> borderspecs& { m_encoding.set(10); return *this; }

    /// Activate the border edge on the top xy plane going from the right corder to front corner in a 3d perspective.
    auto toprightfront() -> borderspecs& { m_encoding.set(11); return *this; }

    /// Set the border for polar plot.
    auto polar() -> borderspecs& { m_encoding.set(2); return *this; }

    /// Set the border to be displayed on the front of all plot elements.
    auto front() -> borderspecs& { m_depth = "front"; return *this; }

    /// Set the border to be displayed on the back of all plot elements.
    auto back() -> borderspecs& { m_depth = "back"; return *this; }

    /// Set the border to be displayed behind of all plot elements.
    /// Methods behind and back have identical effect in 2d plots.
    /// In 3d plots, the behind method is applicable when in hidden mode.
    auto behind() -> borderspecs& { m_depth = "behind"; return *this; }

private:
    /// The bits encoding the active and inactive borders.
    std::bitset<13> m_encoding;

    /// The placement depth of the borders.
    std::string m_depth;
};

borderspecs::borderspecs()
{
    left();
    bottom();
    linecolor(internal::DEFAULT_TEXTCOLOR);
    linetype(internal::DEFAULT_BORDER_LINETYPE);
    linewidth(internal::DEFAULT_BORDER_LINEWIDTH);
    linecolor(internal::DEFAULT_BORDER_LINECOLOR);
    front();
}

auto borderspecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << "set border " << m_encoding.to_ulong() << " " << m_depth << " ";
    ss << linespecs<borderspecs>::repr();
    return ss.str();
}

} // namespace sciplot
