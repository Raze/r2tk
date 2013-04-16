/* HEADER
 *
 * File:   r2-list.hpp
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
 *  + r2::ExceptionAssert
 *  + r2::priv::Node
 *
 * Todo:
 *  Complete the declared methods.
 *  Add a empty list exception to the remove methods.
 *  Add an typecast to int (the size).
 *  Add an Iterator.
 *  Add an Sorting method.
 *  
 *
 * Updates:
 *
 */


#ifndef R2_LIST_HPP
#define	R2_LIST_HPP

#include <list>
#include <vector>
#include <queue>
#include "r2-list-node.hpp"

namespace std {
    template<typename T>
    class list;

    template<typename T>
    class vector;

    template<typename T>
    class queue;
}

namespace r2 {

#define NULL (void*)0
    
    typedef unsigned int UInt;

    template<typename T>
    class List {
    public:

                 List() : m_start(NULL), m_end(NULL), m_size(0) { }
        explicit List(const T& p_item)                          { InsertAtFront(p_item); }
                 List(const List<T>& p_list)                    { operator = (p_list); }
                 List(const std::list<T>& p_list)               { operator = (p_list); }
                 List(const std::vector<T>& p_vector)           { operator = (p_vector); }
                 List(const std::queue<T>& p_queue)             { operator = (p_queue); }
        virtual ~List() throw()                                 { Clear(); }


        List&       operator = (const List& p_list);
        List&       operator = (const std::list& p_list);
        List&       operator = (const std::vector& p_vector);
        List&       operator = (const std::queue& p_queue);

        /**
         * Removes every item from the list and Clear the list members.
         * @return itself.
         */
        List&       Clear();

        /**
         * @return true if the list lacks items, otherwise false.
         */
        inline bool IsEmpty() const { return m_size == 0; }
        /**
         * @return return the number of items in list.
         */
        inline UInt Size()    const { return m_size; }

      
        /**
         * Insert a item into the front of the list.
         * @param p_item is the item wished to be copied into the list.
         * @return the item.
         */
        T&         InsertAtFront   (const T& p_item);

        /**
         * Insert a item into the back of the list.
         * @param p_item is the item wished to be copied into the list.
         * @return the inserted item.
         */
        T&         InsertAtBack    (const T& p_item);

        /**
         * Insert a item into at the a specific position.
         * @param p_item is the item wished to be copied into the list.
         * @param p_index is the position in the list the item will get.
         * @return the inserted item.
         */
        T&          InsertAt        (const T& p_item, const UInt p_index);


        /**
         * Removes the first Item in the list.
         */
        void       RemoveFirst     ();

        /**
         * Removes the last Item in the list.
         */
        void       RemoveLast      ();

        /**
         * Removes the item at the specific position.
         * @param p_index is the position in the list that will be removed.
         */
        void       Remove          (const UInt p_index);
        
        
        /**
         * Retrievs a specific item from the list.
         * @param p_index is the position of the item.
         * @return the item.
         */
        const T&    GetItem(const UInt p_index) const;
        /**
         * Retrievs a specific item from the list.
         * @param p_index is the position of the item.
         * @return the item.
         */
              T&    GetItem(const UInt p_index);

        /**
         * Retrievs a specific item from the list.
         * @param p_index is the position of the item.
         * @return the item.
         */
        const List& operator [] (const UInt p_index) const { return GetItem(p_index); }

        /**
         * Retrievs a specific item from the list.
         * @param p_index is the position of the item.
         * @return the item.
         */
              List& operator [] (const UInt p_index)       { return GetItem(p_index); }

        /**
         * Checks if the operand list is identical to the operator list.
         * Beware, the item type needs to have a defined == operator which returns a bool.
         * @param p_list is the operand list.
         * @return true if every item is identical.
         */
        bool        operator == (const List& p_list)            const;
        /**
         * Checks if the another list is identical to the operator list.
         * Beware, the item type needs to have a defined == operator which returns a bool.
         * @param p_list is the operand list.
         * @return true if every item is identical.
         */
        bool        operator == (const std::list& p_list)       const;
        bool        operator == (const std::vector& p_vector)   const;
        bool        operator == (const std::queue p_queue)      const;

        /**
         * Checks if the another list is identical to the operator list.
         * Beware, the item type needs to have a defined == operator which returns a bool.
         * @param p_list is the operand list.
         * @return false if every item is identical.
         */
        bool        operator != (const List& p_list)            const { return !operator == (p_list); }

        /**
         * Checks if the another list is identical to the operator list.
         * Beware, the item type needs to have a defined == operator which returns a bool.
         * @param p_list is the operand list.
         * @return false if every item is identical.
         */
        bool        operator != (const std::list& p_list)       const { return !operator == (p_list); }
        bool        operator != (const std::vector& p_vector)   const { return !operator == (p_vector); }
        bool        operator != (const std::queue& p_queue)     const { return !operator == (p_queue); }



    private:
        const priv::Node<T>*  GetNode(UInt p_index) const;
              priv::Node<T>*  GetNode(UInt p_index);

        // Points to the first item in the list.
        priv::Node<T>*    m_start;

        // Points to the last item in the list.
        priv::Node<T>*    m_end;

        // Stores the number of items the list contains.
        UInt              m_size;
    };


    template<typename T>
    List& List::InsertAtFront(const T& p_item) {
        m_start = new priv::Node<T>(p_item, NULL, m_start);
        ++m_size;
        if(m_size == 0) m_end = m_start;
        return *this;
    }

    template<typename T>
    List& List::InsertAtBack(const T& p_item) {
        m_end = new priv::Node<T>(p_item, m_end, NULL);
        ++m_size;
        if(m_size == 0) m_start = m_end;
        return *this;
    }

    template<typename T>
    void List::RemoveFirst() {
        priv::Node<T> l_temp = m_start->GetNext();
        delete m_start;
        --m_size;
        m_start = l_temp;
        if(m_size <= 1) m_end = m_start;
        return *this;
    }

    template<typename T>
    void List::RemoveLast() {
        priv::Node<T> l_temp = m_end->GetPrev();
        delete m_end;
        --m_size;
        m_end = l_temp;
        if(m_size <= 1) m_start = m_end;
        return *this;
    }

    template<typename T>
    bool List::operator ==(const List& p_list) const {
        if(m_size == p_list.Size()) {
            priv::Node<T> l_iterator = m_start;
            priv::Node<T> l_operand_iterator = p_list.m_start;
            for(UInt i = 0; i < m_size; ++i) {
                if(l_iterator->GetItem() != l_operand_iterator->GetItem()) return false;
            }
            return true;
        }
        return false;
    }


    template<typename T>
    List& List::Clear() {
        priv::Node<T>* temp;
        for(UInt i = 0; i < m_size; ++i) {
            temp = m_start->GetNext();
            delete m_start;
            m_start = temp;
        }
        memset(this, 0, sizeof(List));
        return *this;
    }

}

#endif	/* R2_LIST_HPP */

