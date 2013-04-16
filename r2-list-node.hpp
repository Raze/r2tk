/* HEADER
 *
 * File:   r2-list-node.hpp
 * Created by: Rasmus Jarl (Raze Dux)
 * Created on: October 31, 2010, 20:13
 *
 * License:
 *   Copyright (C) 2010 Rasmus Jarl
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Comments:
 *
 *  Depends on:
 *  + r2::priv::ExceptionBase
 *
 * Updates:
 *
 */


#ifndef R2_LIST_NODE_HPP
#define	R2_LIST_NODE_HPP

namespace r2 {
    #define null 0

    namespace priv {

        template<typename T>
        class Node {
        public:
            // Constructors and destructors.
            Node() : m_next(null), m_prev(null) {}
            Node(const T& p_item) : m_next(null), m_prev(null), m_item(p_item) {}
            Node(const T& p_item, Node* p_prev, Node<T>* p_next);
           ~Node() throw();

           inline Node<T>*  GetNext() const { return m_next; }
           inline Node<T>*  GetPrev() const { return m_prev; }
           inline T&        GetItem() const { return m_item; }
           inline T&        GetItem()       { return m_item; }
        private:
            // This will point to the next node in the list.
            Node<T>* m_next;
            // This will point to the previous node in the list.
            Node<T>* m_prev;

            // This will store the content.
            T m_item;
        };

        template<typename T>
        Node::Node(const T& p_item, Node<T>* p_prev, Node* p_next) : m_item(p_item), m_prev(p_prev), m_next(p_next) {
            // Points the next Node to this.
            if(m_next) m_next->m_prev = this;

            // Points the privous Node to this.
            if(m_prev) m_prev->m_next = this;
        }

        template<typename T>
        Node::~Node() throw() {
            // Points the next Node to the previous.
            if(m_next) m_next->m_prev = m_prev;

            // Points the previous Node to the next.
            if(m_prev) m_prev->m_next = m_next;
        }
    }
}

#endif	/* R2_LIST_NODE_HPP */

