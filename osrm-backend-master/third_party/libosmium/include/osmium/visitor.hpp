#ifndef OSMIUM_VISITOR_HPP
#define OSMIUM_VISITOR_HPP

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

#include <osmium/fwd.hpp>
#include <osmium/handler.hpp>
#include <osmium/io/reader_iterator.hpp> // IWYU pragma: keep
#include <osmium/memory/buffer.hpp>
#include <osmium/osm.hpp>
#include <osmium/osm/entity.hpp>
#include <osmium/osm/item_type.hpp>

#include <type_traits>
#include <utility>

namespace osmium {

    namespace detail {

        template <typename T, typename U>
        using ConstIfConst = typename std::conditional<std::is_const<T>::value, typename std::add_const<U>::type, U>::type;

        template <typename THandler, typename TItem>
        inline void apply_item_impl(TItem& item, THandler&& handler) {
            switch (item.type()) {
                case osmium::item_type::undefined:
                    break;
                case osmium::item_type::node:
                    handler.osm_object(static_cast<ConstIfConst<TItem, osmium::OSMObject>&>(item));
                    handler.node(static_cast<ConstIfConst<TItem, osmium::Node>&>(item));
                    break;
                case osmium::item_type::way:
                    handler.osm_object(static_cast<ConstIfConst<TItem, osmium::OSMObject>&>(item));
                    handler.way(static_cast<ConstIfConst<TItem, osmium::Way>&>(item));
                    break;
                case osmium::item_type::relation:
                    handler.osm_object(static_cast<ConstIfConst<TItem, osmium::OSMObject>&>(item));
                    handler.relation(static_cast<ConstIfConst<TItem, osmium::Relation>&>(item));
                    break;
                case osmium::item_type::area:
                    handler.osm_object(static_cast<ConstIfConst<TItem, osmium::OSMObject>&>(item));
                    handler.area(static_cast<ConstIfConst<TItem, osmium::Area>&>(item));
                    break;
                case osmium::item_type::changeset:
                    handler.changeset(static_cast<ConstIfConst<TItem, osmium::Changeset>&>(item));
                    break;
                case osmium::item_type::tag_list:
                    handler.tag_list(static_cast<ConstIfConst<TItem, osmium::TagList>&>(item));
                    break;
                case osmium::item_type::way_node_list:
                    handler.way_node_list(static_cast<ConstIfConst<TItem, osmium::WayNodeList>&>(item));
                    break;
                case osmium::item_type::relation_member_list:
                case osmium::item_type::relation_member_list_with_full_members:
                    handler.relation_member_list(static_cast<ConstIfConst<TItem, osmium::RelationMemberList>&>(item));
                    break;
                case osmium::item_type::outer_ring:
                    handler.outer_ring(static_cast<ConstIfConst<TItem, osmium::OuterRing>&>(item));
                    break;
                case osmium::item_type::inner_ring:
                    handler.inner_ring(static_cast<ConstIfConst<TItem, osmium::InnerRing>&>(item));
                    break;
                case osmium::item_type::changeset_discussion:
                    handler.changeset_discussion(static_cast<ConstIfConst<TItem, osmium::ChangesetDiscussion>&>(item));
                    break;
            }
        }

        template <typename THandler>
        inline void apply_item_impl(const osmium::OSMEntity& item, THandler&& handler) {
            switch (item.type()) {
                case osmium::item_type::node:
                    handler.osm_object(static_cast<const osmium::OSMObject&>(item));
                    handler.node(static_cast<const osmium::Node&>(item));
                    break;
                case osmium::item_type::way:
                    handler.osm_object(static_cast<const osmium::OSMObject&>(item));
                    handler.way(static_cast<const osmium::Way&>(item));
                    break;
                case osmium::item_type::relation:
                    handler.osm_object(static_cast<const osmium::OSMObject&>(item));
                    handler.relation(static_cast<const osmium::Relation&>(item));
                    break;
                case osmium::item_type::area:
                    handler.osm_object(static_cast<const osmium::OSMObject&>(item));
                    handler.area(static_cast<const osmium::Area&>(item));
                    break;
                case osmium::item_type::changeset:
                    handler.changeset(static_cast<const osmium::Changeset&>(item));
                    break;
                default:
                    throw osmium::unknown_type{};
            }
        }

        template <typename THandler>
        inline void apply_item_impl(osmium::OSMEntity& item, THandler&& handler) {
            switch (item.type()) {
                case osmium::item_type::node:
                    handler.osm_object(static_cast<osmium::OSMObject&>(item));
                    handler.node(static_cast<osmium::Node&>(item));
                    break;
                case osmium::item_type::way:
                    handler.osm_object(static_cast<osmium::OSMObject&>(item));
                    handler.way(static_cast<osmium::Way&>(item));
                    break;
                case osmium::item_type::relation:
                    handler.osm_object(static_cast<osmium::OSMObject&>(item));
                    handler.relation(static_cast<osmium::Relation&>(item));
                    break;
                case osmium::item_type::area:
                    handler.osm_object(static_cast<osmium::OSMObject&>(item));
                    handler.area(static_cast<osmium::Area&>(item));
                    break;
                case osmium::item_type::changeset:
                    handler.changeset(static_cast<osmium::Changeset&>(item));
                    break;
                default:
                    throw osmium::unknown_type{};
            }
        }

        template <typename THandler>
        inline void apply_item_impl(const osmium::OSMObject& item, THandler&& handler) {
            switch (item.type()) {
                case osmium::item_type::node:
                    handler.osm_object(item);
                    handler.node(static_cast<const osmium::Node&>(item));
                    break;
                case osmium::item_type::way:
                    handler.osm_object(item);
                    handler.way(static_cast<const osmium::Way&>(item));
                    break;
                case osmium::item_type::relation:
                    handler.osm_object(item);
                    handler.relation(static_cast<const osmium::Relation&>(item));
                    break;
                case osmium::item_type::area:
                    handler.osm_object(item);
                    handler.area(static_cast<const osmium::Area&>(item));
                    break;
                default:
                    throw osmium::unknown_type{};
            }
        }

        template <typename THandler>
        inline void apply_item_impl(osmium::OSMObject& item, THandler&& handler) {
            switch (item.type()) {
                case osmium::item_type::node:
                    handler.osm_object(item);
                    handler.node(static_cast<osmium::Node&>(item));
                    break;
                case osmium::item_type::way:
                    handler.osm_object(item);
                    handler.way(static_cast<osmium::Way&>(item));
                    break;
                case osmium::item_type::relation:
                    handler.osm_object(item);
                    handler.relation(static_cast<osmium::Relation&>(item));
                    break;
                case osmium::item_type::area:
                    handler.osm_object(item);
                    handler.area(static_cast<osmium::Area&>(item));
                    break;
                default:
                    throw osmium::unknown_type{};
            }
        }

        template <typename TFunc>
        struct wrapper_handler : TFunc {

            template <typename T>
            explicit wrapper_handler(T&& func) : TFunc(std::forward<T>(func)) { // NOLINT(bugprone-forwarding-reference-overload)
            }

            // Fallback that always matches.
            void operator()(const osmium::memory::Item& /*item*/) const noexcept {
            }

            // The function we are wrapping.
            using TFunc::operator();

            void osm_object(const osmium::OSMObject& /*osm_object*/) const noexcept {
            }

            void node(const osmium::Node& node) const {
                operator()(node);
            }

            // cppcheck-suppress constParameter
            void node(osmium::Node& node) const {
                operator()(node);
            }

            void way(const osmium::Way& way) const {
                operator()(way);
            }

            // cppcheck-suppress constParameter
            void way(osmium::Way& way) const {
                operator()(way);
            }

            void relation(const osmium::Relation& relation) const {
                operator()(relation);
            }

            // cppcheck-suppress constParameter
            void relation(osmium::Relation& relation) const {
                operator()(relation);
            }

            void area(const osmium::Area& area) const {
                operator()(area);
            }

            // cppcheck-suppress constParameter
            void area(osmium::Area& area) const {
                operator()(area);
            }

            void changeset(const osmium::Changeset& changeset) const {
                operator()(changeset);
            }

            // cppcheck-suppress constParameter
            void changeset(osmium::Changeset& changeset) const {
                operator()(changeset);
            }

            void tag_list(const osmium::TagList& /*tag_list*/) const noexcept {
            }

            void way_node_list(const osmium::WayNodeList& /*way_node_list*/) const noexcept {
            }

            void relation_member_list(const osmium::RelationMemberList& /*relation_member_list*/) const noexcept {
            }

            void outer_ring(const osmium::OuterRing& /*outer_ring*/) const noexcept {
            }

            void inner_ring(const osmium::InnerRing& /*inner_ring*/) const noexcept {
            }

            void changeset_discussion(const osmium::ChangesetDiscussion& /*changeset_discussion*/) const noexcept {
            }

            void flush() const noexcept {
            }

        }; // struct wrapper_handler

        // Is the class T derived from osmium::handler::Handler?
        template <typename T>
        using is_handler = std::is_base_of<osmium::handler::Handler, typename std::remove_reference<T>::type>;

        // This is already a handler, use it as it is.
        template <typename T, typename = typename std::enable_if<is_handler<T>::value>::type>
        T make_handler(T&& func) {
            return std::forward<T>(func);
        }

        // This is not a handler, but a functor. Wrap a handler around it.
        template <typename T, typename = typename std::enable_if<!is_handler<T>::value>::type>
        wrapper_handler<typename std::decay<T>::type> make_handler(T&& func) {
            return wrapper_handler<typename std::decay<T>::type>(std::forward<T>(func));
        }

    } // namespace detail

    template <typename TItem, typename... THandlers>
    inline void apply_item(TItem& item, THandlers&&... handlers) {
        (void)std::initializer_list<int>{
            (detail::apply_item_impl(item, std::forward<THandlers>(handlers)), 0)...};
    }

    template <typename... THandlers>
    inline void apply_flush(THandlers&&... handlers) {
        (void)std::initializer_list<int>{
            (std::forward<THandlers>(handlers).flush(), 0)...};
    }

    template <typename TIterator, typename... THandlers>
    inline void apply_impl(TIterator it, TIterator end, THandlers&&... handlers) {
        for (; it != end; ++it) {
            apply_item(*it, handlers...);
        }
        apply_flush(std::forward<THandlers>(handlers)...);
    }

    template <typename TIterator, typename... THandlers>
    inline void apply(TIterator it, TIterator end, THandlers&&... handlers) {
        apply_impl(it, end, detail::make_handler<THandlers>(std::forward<THandlers>(handlers))...);
    }

    template <typename TContainer, typename... THandlers>
    inline void apply(TContainer& c, THandlers&&... handlers) {
        using std::begin;
        using std::end;
        apply(begin(c), end(c), std::forward<THandlers>(handlers)...);
    }

    template <typename... THandlers>
    inline void apply(const osmium::memory::Buffer& buffer, THandlers&&... handlers) {
        apply(buffer.cbegin(), buffer.cend(), std::forward<THandlers>(handlers)...);
    }

} // namespace osmium

#endif // OSMIUM_VISITOR_HPP