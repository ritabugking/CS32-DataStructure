//
//  Sequence.h
//  project2
//
//  Created by YI-JU WANG on 2018/4/24.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <stdio.h>
#include <string>

//typedef unsigned long ItemType;
typedef std::string ItemType;

//const int DEFAULT_MAX_ITEMS = 200;

class Sequence
{
public:
    Sequence();
    // Create an empty sequence
    
    // Housekeeping functions
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);
    
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    
    bool insert(int pos, const ItemType& value);
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item at position pos and those that
    // follow it end up at positions one higher than they were at before.
    // Return true if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // (e.g., because it's implemented using a fixed-size array) and is
    // full.)  Otherwise, leave the sequence unchanged and return false.
    // Notice that if pos is equal to size(), the value is inserted at the
    // end.
    
    int insert(const ItemType& value);
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item at position
    // p.  The original item at position p and those that follow it end
    // up at positions one higher than before.  Return p if the value
    // was actually inserted.  Return -1 if the value was not inserted
    // (perhaps because the sequence has a fixed capacity and is full).
    
    bool erase(int pos);
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed this item end up at
    // a position one lower than before), and return true.  Otherwise,
    // leave the sequence unchanged and return false.
    
    int remove(const ItemType& value);
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item at position pos
    // in the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    
    bool set(int pos, const ItemType& value);
    // If 0 <= pos < size(), replace the item at position pos in the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.
    
    int find(const ItemType& value) const;
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.
    
    void swap(Sequence& other);
    // Exchange the contents of this sequence with the other one.
    
    
    
private:
    struct Node {
        ItemType m_data;
        Node* m_pre;
        Node* m_next;
    };
    int m_size;
    Node* head;
    
};

// Inline implementations

inline
int Sequence::size() const
{
    return m_size;
}

inline
bool Sequence::empty() const
{
    return size() == 0;
}

int subsequence(const Sequence& seq1, const Sequence& seq2);
// if seq2 is a consecutive subsequence of seq1, the function returns
// the earliest place in seq1 where that subsequence starts

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
// This function produces as a result a sequence that consists of the
// first item in seq1, then the first in seq2, then the second in seq1,
// then the second in seq2, etc.



#endif /* Sequence_h */
