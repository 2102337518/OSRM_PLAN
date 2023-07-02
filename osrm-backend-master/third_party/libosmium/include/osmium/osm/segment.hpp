#ifndef OSMIUM_OSM_SEGMENT_HPP
#define OSMIUM_OSM_SEGMENT_HPP

/*

This file is part of Osmium (https://osmcode.org/libosmium).

Copyright 2013-2022 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <osmium/osm/location.hpp>

#include <iosfwd>
#include <utility>

namespace osmium {

    /**
     * A Segment is the directed connection between two Locations.
     */
    class Segment {

        osmium::Location m_first;
        osmium::Location m_second;

    public:

        explicit constexpr Segment(const osmium::Location& location1, const osmium::Location& location2) noexcept :
            m_first(location1),
            m_second(location2) {
        }

        /// Return first Location of Segment.
        constexpr osmium::Location first() const noexcept {
            return m_first;
        }

        /// Return second Location of Segment.
        constexpr osmium::Location second() const noexcept {
            return m_second;
        }

    protected:

        void swap_locations() {
            using std::swap;
            swap(m_first, m_second);
        }

    }; // class Segment

    /// Segments are equal if both their locations are equal
    inline constexpr bool operator==(const Segment& lhs, const Segment& rhs) noexcept {
        return lhs.first() == rhs.first() && lhs.second() == rhs.second();
    }

    inline constexpr bool operator!=(const Segment& lhs, const Segment& rhs) noexcept {
        return !(lhs == rhs);
    }

    /**
     * Output Segment to a stream.
     */
    template <typename TChar, typename TTraits>
    inline std::basic_ostream<TChar, TTraits>& operator<<(std::basic_ostream<TChar, TTraits>& out, const osmium::Segment& segment) {
        return out << segment.first() << "->" << segment.second();
    }

} // namespace osmium

#endif // OSMIUM_OSM_SEGMENT_HPP
