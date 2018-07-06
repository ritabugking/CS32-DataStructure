//
//  Sequence.cpp
//  project2
//
//  Created by YI-JU WANG on 2018/4/24.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include "Sequence.h"

#include <iostream>
#include <cstdlib>

Sequence::Sequence()
{
    head = new Node();
    m_size = 0;
    head->m_pre = nullptr;
    head->m_next = nullptr;
    
}

Sequence::~Sequence()
{
    while (head->m_next!=nullptr){
        Node* temp;
        temp = head;
        head = head->m_next;
        delete temp;
    }
    delete head;
}

Sequence::Sequence(const Sequence& other)
{
    head = new Node();
    m_size = other.m_size;
    head->m_pre = nullptr;
    head->m_next = nullptr;
    
    if (other.m_size>0){
        
        Node* temp;
        Node* temp_other;
        temp = head;
        temp_other = other.head;
        
        temp->m_data = temp_other->m_data;
        
        while (temp_other->m_next!=nullptr){
            
            temp->m_next = new Node();  // create a node
            temp->m_next->m_data = temp_other->m_next->m_data;  // put data
            temp->m_next->m_next = nullptr;  // link to the next
            temp->m_next->m_pre = temp;  // link to the previous
            
            // move the pointer
            temp = temp->m_next;
            temp_other = temp_other->m_next;
            
        }
        
        temp->m_data = temp_other->m_data;  // put data into the last node
    }
}

Sequence& Sequence::operator=(const Sequence& other)
{
    
    m_size = other.m_size;
    if (this == &other)
    {
        return *this;
    }
    
    if (other.m_size>0){
        
        Node* temp;
        Node* temp_other;
        temp = head;
        temp_other = other.head;
        
        temp->m_data = temp_other->m_data;
        
        while (temp_other->m_next!=nullptr){
            
            temp->m_next = new Node();  // create a node
            temp->m_next->m_data = temp_other->m_next->m_data;  // put data
            temp->m_next->m_next = nullptr;  // link to the next
            temp->m_next->m_pre = temp;  // link to the previous
            
            // move the pointer
            temp = temp->m_next;
            temp_other = temp_other->m_next;
        }
        temp->m_data = temp_other->m_data;  // put data into the last node
    }
    return *this;
}


bool Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos > size())
        return false;
    
    Node* temp = new Node();
    temp->m_data = value;
    temp->m_next = nullptr;
    temp->m_pre = nullptr;
    
    if (pos == 0){  // insert new node into the first position
        
        if (m_size==0){
            head->m_data = value;
            m_size++;
            return true;
        }
        temp->m_next = head;
        temp->m_pre = nullptr;
        head->m_pre = temp;
        head = temp;
    }
    else if (pos == m_size){ // insert new node into the last position
        
        Node* current;
        current = head;
        while(current->m_next!=nullptr){  // find the last node
            
            current = current->m_next;
        }
        current->m_next = temp;
        temp->m_pre = current;
    }
    else{  // insert new node into the middle of sequence
        
        Node* middle;
        middle = head;
        
        for(int i=0; i<pos; i++){
            
            middle = middle->m_next;
        }
        middle = middle->m_pre;
        
        temp->m_next = middle->m_next;
        temp->m_pre = middle;
        middle->m_next = temp;
        temp->m_next->m_pre = temp;
    }
    
    m_size++;
    return true;
}

int Sequence::insert(const ItemType& value)
{
    if (m_size==0){
        head->m_data = value;
        m_size++;
        return 0;
    }
    
    int pos;
    Node* temp = new Node();  // create a new node
    temp->m_data = value;
    temp->m_next = nullptr;
    temp->m_pre = nullptr;
    
    Node* current;
    current = head;
    for (pos = 0; current->m_next!=nullptr &&  value > current->m_data; pos++){ // find the correct position insert new node
        current = current->m_next;
    }
    if (current->m_next==nullptr){
        if(value>current->m_data){
            pos=1;
        }
        else{
            pos=0;
        }
    }
    if (pos == m_size-1){
        if (value > current->m_data)
            pos++;
    }
    
    
    if (pos == m_size){  // insert new node into the last position
        
        Node* last;
        last = head;
        while(last->m_next!=nullptr){  // find the last node
            
            last = last->m_next;
        }
        last->m_next = temp;
        temp->m_pre = last;
        
    }
    else if(pos == 0){  // insert new node into the first position
        
        temp->m_next = head;
        temp->m_pre = nullptr;
        head-> m_pre = temp;
        head = temp;
        
    }
    else{  // insert new node into the middle of sequence
        
        Node* middle;
        middle = head;
        
        for(int i=0; i<pos; i++){
            
            middle = middle->m_next;
        }
        middle = middle->m_pre;
        
        temp->m_next = middle->m_next;
        temp->m_pre = middle;
        middle->m_next = temp;
        temp->m_next->m_pre = temp;
    }
    
    m_size++;
    return pos;
}

bool Sequence::erase(int pos)
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    Node* temp;
    Node* temp2;
    temp = head;
    if(pos == 0 && m_size==1){
        //temp->m_data=NULL;
        temp->m_next=nullptr;
        temp->m_pre=nullptr;
        m_size=0;
        delete temp;
    }
    else if (pos ==0 && m_size>1){  // erase the first node
        
        head = head->m_next;
        head->m_pre = nullptr;
        delete temp;
    }
    else if(pos == m_size-1){
        
        while(temp->m_next!=nullptr){  // find the last node and erase it
            temp = temp->m_next;
        }
        temp->m_pre->m_next = nullptr;
        delete temp;
        //temp = temp->m_pre;
        //temp->m_next = nullptr;
    }
    else{
        for (int i=0; i<pos; i++){  // find the position of node and erase it
            
            temp = temp->m_next;
        }
        temp2 = temp;
        temp = temp->m_pre;
        if(temp->m_next->m_next!=nullptr)
            temp->m_next = temp->m_next->m_next;
        else
            temp->m_next = nullptr;
        temp->m_next->m_pre = temp;
        delete temp2;
    }
    
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value)  //
{
    int pos = find(value);
    if (pos == -1)  // if the value cannot be found, return 0
        return 0;
    
    // if the value was found at pos
    int count = 1;
    erase(pos);
    
    for (int i=pos; i<m_size; i++)  // find the value start from pos where we find the value last time
    {
        pos = find(value);
        if (pos == -1)
            break;
        else
        {
            count++;
            erase(pos);
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    Node* temp;
    temp = head;
    
    for (int i=0; i<pos; i++){  // find the position of node
        
        temp = temp->m_next;
    }
    value = temp->m_data;  // get the value at position pos
    
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    Node* temp;
    temp = head;
    
    for (int i=0; i<pos; i++){  // find the position of node
        
        temp = temp->m_next;
    }
    temp->m_data = value;  // set the value into position pos
    
    return true;
}

int Sequence::find(const ItemType& value) const
{
    Node* temp;
    temp = head;
    for (int pos = 0; pos < size(); pos++){  // find the first position of node which containing the value we want
        if (temp->m_data == value)
            return pos;
        if (temp->m_next!=nullptr)
            temp = temp->m_next;
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    // Swap pointers to the elements.
    
    Node* temp;
    temp = other.head;
    other.head = head;
    head = temp;
    
    int temp_size;
    temp_size = other.m_size;
    other.m_size = m_size;
    m_size = temp_size;
    
    
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq2.empty() || seq2.size() > seq1.size())
        return -1;
    
    ItemType value1, value2;
    for (int pos=0; pos<=seq1.size()-seq2.size(); pos++){
        
        seq1.get(pos, value1);
        seq2.get(0, value2);
        
        if (value1==value2){
            
            int pos1=pos, pos2=0;
            while(pos2<seq2.size()){
                
                seq1.get(pos1, value1);
                seq2.get(pos2, value2);
                if (value1!=value2)
                    break;
                pos1++;
                pos2++;
                
            }
            if (pos2==seq2.size())
                return pos;
        }
    }
    return -1;
}


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    
    Sequence result2;
    if (seq1.empty())
        result2 = seq2;
    else if (seq2.empty())
        result2 = seq1;
    else{
        
        int pos=0, pos1=0, pos2=0;
        ItemType value1, value2;
        
        if (seq1.size()>seq2.size()){
            
            for (int i=0; i<seq2.size(); i++){
                
                seq1.get(pos1, value1);
                seq2.get(pos2, value2);
                result2.insert(pos, value1);
                pos++;
                pos1++;
                result2.insert(pos, value2);
                pos++;
                pos2++;
            }
            for (int i=seq2.size(); i<seq1.size(); i++){
                
                seq1.get(pos1, value1);
                result2.insert(pos, value1);
                pos++;
                pos1++;
                
            }
            
            
        }
        
        else if (seq1.size()<seq2.size()){
            for (int i=0; i<seq1.size(); i++){
                
                seq1.get(pos1, value1);
                seq2.get(pos2, value2);
                result2.insert(pos, value1);
                pos++;
                pos1++;
                result2.insert(pos, value2);
                pos++;
                pos2++;
            }
            for (int i=seq1.size(); i<seq2.size(); i++){
                
                seq2.get(pos2, value2);
                result2.insert(pos, value2);
                pos++;
                pos2++;
                
            }
            
        }
        
        else{
            for (int i=0; i<seq2.size(); i++){
                
                seq1.get(pos1, value1);
                seq2.get(pos2, value2);
                result2.insert(pos, value1);
                pos++;
                pos1++;
                result2.insert(pos, value2);
                pos++;
                pos2++;
            }
            
        }
        
    }
    
    result.swap(result2);
    
}
