// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/allanleal/sciplot
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
#include <string>

namespace sciplot {
namespace internal {

/// The base class for other specs classes (e.g., linespecs, plotspecs, borderspecs, etc.)
template<typename derivedspecs>
class specs
{
public:
    /// Pure virtual destructor (this class is an abstract base class).
    virtual ~specs() {};

    /// Return a string representation of this object of some class that derives from specs.
    virtual auto repr() const -> std::string = 0;

    /// Return a string representation of this object of some class that derives from specs.
    operator std::string() const { return repr(); }

    /// Return a reference to the specs object of class derived from this.
    auto derived() -> derivedspecs& { return static_cast<derivedspecs&>(*this); }

    /// Return a const reference to the specs object of class derived from this.
    auto derived() const -> const derivedspecs& { return static_cast<const derivedspecs&>(*this); }
};

/// Output the state of a specs object to a ostream object.
template<typename derivedspecs>
auto operator<<(std::ostream& stream, const specs<derivedspecs>& obj) -> std::ostream&
{
    return stream << obj.repr();
}

} // namespace internal
} // namespace sciplot
