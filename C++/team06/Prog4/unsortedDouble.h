/*************************************************************************//**
 * @file
 * @brief Header file that contains the unsortedDouble class
 ****************************************************************************/
#include <iostream>
#include <string>
#include <functional>

using std::ostream;
using std::string;
using std::function;

#ifndef __UNSORTEDDOUBLE__H
#define __UNSORTEDDOUBLE__H

/*!
* @brief allows for creation and use of an unsorted doubly linked list
*/
template <class TY>
class unsortedDouble
{
public:
    unsortedDouble();
    unsortedDouble ( const unsortedDouble<TY> &l ); 
    ~unsortedDouble();

    void clear();
    void print ( ostream &out, bool forward = true,
        string seperator = ", " );
    bool insert ( TY val, int pos = 1 );
    bool remove ( int pos = 1 );
    bool removeVal ( TY val );
    bool rfind ( TY val );
    bool find ( TY val );
    bool isEmpty( );
    int size();
    bool push_back ( TY val );
    bool push_front ( TY val );
    bool pop_back ( TY &val );
    bool pop_front ( TY &val );
    void swap ( unsortedDouble<TY> &l );
    int countIf ( function<bool ( TY ) > cond );
    int retrieve ( TY val );
    int rretrieve ( TY val );
    bool retrieve ( TY &item, int position );

private:
    /*!
    * @brief creates node which contains item, pointer to next, and pointer to
    *     last.
    */
    struct node
    {
        TY item;
        node *next;
        node *last;
    };
    node *headptr;
    node *tailptr;
};

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Creates a copy of the list that you pass in.
*
* @param[in]       l - list
*
******************************************************************************/
template <class TY>
unsortedDouble<TY>::unsortedDouble(const unsortedDouble<TY> &l) // copy constructor
{
    node *src, *dest;

    //create empty list
    headptr = nullptr;
    tailptr = nullptr;

    //return if list we are trying to copy is empty
    if ( const_cast<unsortedDouble&>(l).size() == 0 ) 
        return;

    //assign source and destination
    src = l.headptr;
    dest = headptr;

    //create first node and copy in item
    dest = new (nothrow) node;
    headptr = dest;
    dest->item = src->item;
    dest->next = nullptr;
    tailptr = dest;
    dest->last = tailptr;
    src = src->next;

    //copy in all the rest of the items
    while (src != nullptr)
    {
        dest->next = new (nothrow) node;
        dest->next->last = dest;
        dest = dest->next;
        dest->item = src->item;
        dest->next = nullptr;
        tailptr = dest;
        src = src->next;
    }
    return;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Returns position of the item, moving forwards in the list 
*
* @param[in]       val - item in the list that we are looking for
*
* @returns position of item
******************************************************************************/
template <class TY>
int unsortedDouble<TY>::retrieve(TY val)
{
    //walk through doubly linked list until first val, then return val
    node * temp;
    temp = headptr;
    int index = 1;

    //if an empty list, return error right off the bat
    if (temp == nullptr)
        return 0;

    while (temp->item != val)
    {
        //go to next node, and increment index
        temp = temp->next;
        index++;

        //if you've reached the end of the list, return 0
        if (temp == nullptr)
        {
            return 0;
        }
    }

    return index;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Returns position of the item, moving backwards in the list 
*
* @param[in]       val - item in the list that we are looking for
*
* @returns position of item
******************************************************************************/
template <class TY>
int unsortedDouble<TY>::rretrieve(TY val)
{
    //walk backwards through list until we reach val
    node * temp;
    temp = tailptr;
    int index = size();

    if (temp == nullptr)
        return 0;

    while (temp->item != val)
    {
        temp = temp->last;
        index--;

        if (temp == nullptr)
            return 0;
    }

    return index;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Returns the item in the list at the position passed in
*
* @param[out]       item - item at position
* @param[in]        position - position in the list where the item we are tryna
*                              return lives
*
* @returns true item was returned
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::retrieve(TY &item, int position)
{
    //walk through until position
    //but make sure position is within the size of the list, and greater than 1
    int lSize = size();
    if (position > lSize || position < 1)
        return false;

    int index = 1;
    node * temp;
    temp = headptr;
    while (index != position)
    {
        temp = temp->next;
        index++;
    }

    item = temp->item;
    return true;

}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Returns the number of items that match the requested data in the function
*
* @param[in]       cond - a function with the condition we are looking to match
*
* @returns number of items that match cond
******************************************************************************/
template <class TY>
int unsortedDouble<TY>::countIf(function<bool(TY)> cond)
{
    node * temp;
    temp = headptr;
    int count = 0;
    while (temp != nullptr)
    {
        if (cond(temp->item) == true)
            count++;
        temp = temp->next;
    }

    return count;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Query if this object is empty. Both pointers must be nullptr.
*
* @returns true if empty
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::isEmpty()
{
    if (headptr == nullptr && tailptr == nullptr)
        return true;
    else
        return false;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Returns the number of nodes in the list
*
* @returns number of nodes in the list
******************************************************************************/
template <class TY>
int unsortedDouble<TY>::size()
{
    //check if it's empty
    if (headptr == nullptr && tailptr == nullptr)
        return 0;

    //check if there is one node
    if (headptr == tailptr)
        return 1;

    //if there are many nodes, find how many
    int count = 0;
    node *temp;
    temp = headptr;
    while (temp != nullptr)
    {
        ++count;
        temp = temp->next;
    }
    return count; 
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Pushes the given value to the end of the list.
*
* @param[in]       val - the item we are puting at the end of the list
*
* @returns true if inserted
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::push_back(TY val)
{
    return insert(val, size()+1);
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Pushes a value to the front of the list. 
*
* @param[in]       val - the item we are puting at the front of the list
*
* @returns true if inserted
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::push_front(TY val)
{
    return insert(val, 1);
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Removes the value at the end of the list. This value is copied into the
*   variable val if the value exists.
*
* @param[out]       val - the item we are removing from the end of the list
*
* @returns true if removed
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::pop_back(TY &val)
{
    node *temp;
    temp = tailptr;

    //if list is empty
    if (headptr == nullptr)
    {
        return false;
    }

    //if youre removing the last item in the list
    if (headptr == tailptr)
    {
        val = temp->item;
        headptr = nullptr;
        tailptr = nullptr;
        delete temp;
        return true;
    }

    //if theres stuff in the list
    if (headptr != nullptr)
    {
        val = temp->item;
        temp->last->next = nullptr;
        tailptr = temp->last;
        delete temp;
        return true;
    }

    return false;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Removes the value at the front of the list. This value is copied into the
*   variable val if the value exists.
*
* @param[out]       val - the item we are removing from the front of the list
*
* @returns true if removed
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::pop_front(TY &val)
{
    node *temp;
    temp = headptr;

    //if list is empty
    if (headptr == nullptr)
    {
        return false;
    }

    //if only one value in list
    if (headptr == tailptr)
    {
        val = temp->item;
        headptr = nullptr;
        tailptr = nullptr;
        delete temp;
        return true;
    }

    //if many values in the list
    if (headptr != nullptr)
    {
        val = temp->item;
        headptr = temp->next;
        temp->next->last = nullptr;
        delete temp;
        return true;
    }

    return false;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Exchange the contents of two lists
*
* @param[out]       l - list we are swapping with
*
******************************************************************************/
template <class TY>
void unsortedDouble<TY>::swap(unsortedDouble<TY> &l)
{
    node *temp;

    //change the list given by headptr and tailptr with list l
    temp = l.headptr;
    l.headptr = headptr;
    headptr = temp;

    temp = l.tailptr;
    l.tailptr = tailptr;
    tailptr = temp;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Removes the node at the given position in the list. The first node is at 
*   position 1.
*
* @param[in]       pos - the position where we are to remove a node
*
* @returns true if removed
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::remove(int pos)
{
    node *curr;
    int count = 1;
    curr = headptr;

    //if invalid position
    if (pos <= 0)
    {
        return false;
    }

    //if list is empty
    if (headptr == nullptr)
    {
        return false;
    }

    //if removing last node from list
    if (curr->next == nullptr)
    {
        headptr = nullptr;
        tailptr = nullptr;
        return true;
    }

    //if removing first node
    if (pos == 1)
    {
        headptr = curr->next;
        curr->next->last = nullptr;
        delete curr;
        return true;
    }

    //traversal
    while (count < pos && curr->next != nullptr)
    {
        curr = curr->next;
        ++count;
    }
    //if invalid node
    if (count < pos)
    {
        return false;
    }
    //if removing from end
    if (curr->next == nullptr)
    {
        curr->last->next = nullptr;
        tailptr = curr->last;
        delete curr;
        return true;
    }
    //if in middle of list
    if (count == pos)
    {
        curr->last->next = curr->next;
        curr->next->last = curr->last;
        delete curr;
        return true;
    }
    return false;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Removes the first given val that is found going forward in the list.
*
* @param[in]       val - the value we are searching for and removing
*
* @returns true if removed
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::removeVal (TY val)
{
    node *curr;
    curr = headptr;
    bool found = false;

    //traverse through list until item is found
    while (curr != nullptr && found == false)
    {
        //if item is found
        if (val == curr->item)
        {
            found = true;
        }
        else
        {
            curr = curr->next;
        }
    }

    //if value is not found in list
    if (found == false)
    {
        return false;
    }

    //if value is at begining of list
    if (headptr == curr)
    {
        //if value is only value in list
        if (curr->next == nullptr)
        {
            headptr = nullptr;
            tailptr = nullptr;
            return true;
        }
        headptr = curr->next;
        curr->next->last = nullptr;
        delete curr;
        return true;
    }
    //if value is at end of list
    else if (curr->next == nullptr)
    {
        curr->last->next = nullptr;
        tailptr = curr->last;
        delete curr;
        return true;
    }
    //if value is in the middle of list
    else
    {
        curr->last->next = curr->next;
        curr->next->last = curr->last;
        delete curr;
        return true;
    }

    return false;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Searches for the first match of the given string starting from the front
*   of the list.
*
* @param[in]       val - the value we are searching for
*
* @returns true if found and returned
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::find(TY val)
{
    node *curr = headptr;
    bool found = false;

    //traverse through list until item is found
    while (curr != nullptr && found == false)
    {
        //if item is found
        if (val == curr->item)
        {
            found = true;
            return true;
        }
        else
        {
            curr = curr->next;
        }
    }

    //if item was not found, return false
    if (found == false)
    {
        return false;
    }

    return false;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Searches for the first match of the given string starting from the back
*   of the list.
*
* @param[in]       val - the value we are searching for
*
* @returns true if found and returned
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::rfind(TY val)
{
    node *curr = tailptr;
    bool found = false;

    //traverse through list until item is found
    while (curr != nullptr && found == false)
    {
        //if item is found
        if (val == curr->item)
        {
            found = true;
            return true;
        }
        else
        {
            curr = curr->last;
        }
    }

    //if item was not found, return false
    if (found == false)
    {
        return false;
    }

    return false;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Constructor
*
******************************************************************************/
template <class TY>
unsortedDouble<TY>::unsortedDouble()
{
    headptr = nullptr;
    tailptr = nullptr;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Clears this object to its blank / initial state. Both pointers will be set
*   to nullptr.
*
******************************************************************************/
template <class TY>
void unsortedDouble<TY>::clear()
{
    node *curr;

    curr = headptr;

    //traversal
    while (curr != tailptr)
    {
        node *temp;
        temp = curr;
        curr = curr->next;
        delete temp;
    }

    headptr = nullptr;
    tailptr = nullptr;
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Destructor - will free all the nodes in the list. 
*
******************************************************************************/
template <class TY>
unsortedDouble<TY>::~unsortedDouble()
{
    clear();
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Prints the list out either forwards or backwards using a seperator that was
*   passed in. Forward is the default using a seperator of ", ". Both of these
*   values can be changed. forward = false will print the list out backwards.
*   Any string can be used to seperate the lists values. NO new line will be
*   outputted on any output. 
*
* @param[out]      out - our output stream
* @param[in]       forward - if true, print forwards. If false, print backwards
* @param[in]       separator - what the values will be separated by when outputted
*
******************************************************************************/
template <class TY>
void unsortedDouble<TY>::print(ostream &out, bool forward,
    string separator)
{
    //print forwards
    if (forward == true)
    {
        node *curr;
        curr = headptr;
        while (curr != nullptr)
        {
            out << curr->item;
            if (curr->next != nullptr)
            {
                out << seperator;
            }
            curr = curr->next;
        }
    }
    //print backwards
    else
    {
        node *curr;
        curr = tailptr;
        while (curr != nullptr)
        {
            out << curr->item;
            if (curr->last != nullptr)
            {
                out << seperator;
            }
            curr = curr->last;
        }
    }
}

/**************************************************************************//**
* @author Erica Keeble
* @author Riley Campbell
*
* @par Description:
*   Inserts value into the list at the given position
*
* @param[in]       val - the value we are inserting
* @param[in]       pos - the position where we are inserting val
*
* @returns true if inserted
* @returns false otherwise
******************************************************************************/
template <class TY>
bool unsortedDouble<TY>::insert(TY val, int pos)
{
    //define variables and allocate memory for temp
    int index = 0;
    node *temp;
    temp = new (nothrow) node;
    if (temp == nullptr)
    {
        cout << "Not enough memory." << endl;
        return false;
    }
    temp->item = val;
    temp->next = nullptr;
    temp->last = nullptr;

    //if invalid position, return false
    if (pos <= 0)
    {
        return false;
    }

    //insert into empty list
    if (isEmpty())
    {
        if (pos != 1)
        {
            return false;
        }
        headptr = temp;
        tailptr = temp;
        return true;
    }

    //insert into beg of list
    if (pos == 1)
    {
        temp->next = headptr;
        headptr->last = temp;
        headptr = temp;
        return true;
    }

    //insert into middle of list
    node *prev, *curr;
    prev = headptr;
    curr = headptr;
    while (curr != nullptr)
    {
        if (pos - 1 == index)
        {
            temp->next = curr;
            temp->last = prev;
            prev->next = temp;
            curr->last = temp;
            return true;
        }
        else
        {
            prev = curr;
            curr = curr->next;
            ++index;
        }

    }
    //insert at the end of list
    if (pos - 1 == index)
    {
        temp->next = nullptr;
        temp->last = prev;
        prev->next = temp;
        tailptr = temp;
        return true;
    }

    return false;
}

#endif