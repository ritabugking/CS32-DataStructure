//
//  newSequence.cpp
//  homework1
//
//  Created by YI-JU WANG on 2018/4/17.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include "newSequence.h"

/*
Sequence::Sequence()
{
    
    m_size = 0;
    m_max = DEFAULT_MAX_ITEMS;
    m_sequence = new ItemType[m_max];
    
}
*/
Sequence::Sequence(int max)
{
    
    m_size = 0;
    m_max = max;
    m_sequence = new ItemType[m_max];
    
}


Sequence::~Sequence()
{

    delete [] m_sequence;
}

Sequence::Sequence(const Sequence& another)
{

    
    m_size = another.m_size;
    m_max = another.m_max;
    m_sequence = new ItemType[m_max];
    
    for (int i=0; i < m_size; i++)
    {
    
        m_sequence[i] = another.m_sequence[i];
    }
    
}

Sequence& Sequence::operator=(const Sequence& another)
{
    if (this != &another)
    {
        Sequence t(another);
        swap(t);
    }
    
    return *this;
}

bool Sequence::empty() const
{
    
    return m_size == 0;
    
}

int Sequence::size() const
{
    
    return m_size;
    
}

bool Sequence::insert(int pos, const ItemType& value)
{
    
    if (m_size == m_max)
        return false;
    if (pos < 0 || pos > size())
        return false;
    
    int _size = m_size;
    if (pos == size())
    {
        m_size++;
        m_sequence[size()-1] = value;
        return true;
    }
    for (int i =_size-1; i > pos; i--)
    {
        m_sequence[i+1] = m_sequence[i];
    }
    m_sequence[pos+1] = m_sequence[pos];
    m_sequence[pos] = value;
    m_size++;
    
    return true;
    
}

int Sequence::insert(const ItemType& value)
{
    
    if (m_size == m_max)
        return -1;
    if (empty())
    {
        
        m_sequence[0] = value;
        m_size++;
        return 1;
    }
    
    for (int p=0; p < m_size - 1; p++)
    {
        
        if (value <= m_sequence [p])
        {
            
            int _size = m_size;
            for (int i =_size-1; i > p; i--)
            {
                m_sequence[i+1] = m_sequence[i];
                
            }
            m_sequence[p+1] = m_sequence[p];
            m_sequence[p] = value;
            m_size++;
            return p;
            
        }
        
    }
    m_sequence [m_size] = value;
    m_size++;
    return size()-1;
    
    return -1;
}

bool Sequence::erase(int pos)
{
    
    if (pos >= 0 && pos < size())
    {
        for (int i = pos; i < m_size-1; i++)
        {
            m_sequence[pos] = m_sequence[pos+1];
        }
        
        m_size--;
        return true;
    }
    
    return false;
}

int Sequence::remove(const ItemType& value)
{
    
    int num = 0;
    for (int p = 0; p < m_size; p++)
    {
        
        if (m_sequence[p]==value)
        {
            
            for (int p2 = p; p2 < m_size; p++)
            {
                m_sequence[p2] = m_sequence[p2+1];
            }
            num++;
            m_size--;
            p--;
        }
        
    }
    return num;
}


bool Sequence::get(int pos, ItemType& value) const
{
    if (pos >= 0 && pos < size())
    {
        
        value = m_sequence[pos];
        return true;
    }
    return false;
    
}

bool Sequence::set(int pos, const ItemType& value)
{
    
    if (pos >= 0 && pos < size())
    {
        
        m_sequence[pos] = value;
        return true;
    }
    return false;
    
    
}

int Sequence::find(const ItemType& value) const
{
    
    for (int p=0; p < size(); p++)
    {
        if (m_sequence [p] == value)
        {
            return p;
        }
    }
    return -1;
    
}

void Sequence::swap(Sequence& other)
{
    
    ItemType* temp;
    int temp_size;
    int temp_max;
    
    temp = m_sequence;
    m_sequence = other.m_sequence;
    other.m_sequence = temp;
    
    temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    temp_max = m_max;
    m_max = other.m_max;
    other.m_max = temp_max;
    
}
