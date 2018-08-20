// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
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
#include <bitset>

// Capim includes
#include <Capim/default.hpp>
#include <Capim/specs/linespecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The class used to specify options for plot border.
class borderspecs : public linespecs<borderspecs>
{
public:
    /// Construct a default border instance.
    borderspecs()
    {
        left();
        bottom();
        linecolor(DEFAULT_TEXTCOLOR);
        linetype(1);
        linewidth(1);
    }

    /// Remove all borders from the plot.
    auto clear() -> borderspecs& { m_encoding.reset(); return *this; }

    /// Set all border to inactive. This is equivalent to method clear.
    auto none() -> borderspecs& { return clear(); }

    /// Set the left border active.
    auto left() -> borderspecs& { m_encoding.set(1); return *this; }

    /// Set the right border active.
    auto right() -> borderspecs& { m_encoding.set(3); return *this; }

    /// Set the bottom border active.
    auto bottom() -> borderspecs& { m_encoding.set(0); return *this; }

    /// Set the top border active.
    auto top() -> borderspecs& { m_encoding.set(2); return *this; }

    /// Convert this border object into a gnuplot formatted string.
    virtual auto repr() const -> std::string
    {
        std::stringstream ss;
        ss << m_encoding.to_ulong() << " ";
        ss << linespecs<borderspecs>::repr();
        return ss.str();
    }

private:
    /// The bits encoding the active and inactive borders.
    std::bitset<4> m_encoding;

    /// The name of the font.
    std::string m_fontname;

    /// The point size of the font.
    std::size_t m_fontsize;
};

} // namespace internal
} // namespace Capim
