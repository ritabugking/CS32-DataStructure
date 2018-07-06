//
//  Dictionary.cpp
//  Dictionary
//
//  Created by YI-JU WANG on 2018/6/6.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include "Dictionary.h"

// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include <string>
#include <cctype>
#include <utility>  // for swap
#include <algorithm>
using namespace std;


const int size_bucket = 50000;
const int num_alphabet = 26;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

struct Node
{
    Node(string value, long primary_key)
    : value(value), primary_key(primary_key), next(nullptr)
    {}
    string value;
    long primary_key;
    Node* next;
};


class DictionaryImpl
{
public:
    DictionaryImpl();
    ~DictionaryImpl();
    void insert(string& word);
    void lookup(string& letters, void callback(string));
private:
    Node* hash_table[size_bucket];
    int hashFunction(string& word);
    long primeKey;
};

DictionaryImpl::DictionaryImpl()
{
    for (int i = 0; i < size_bucket; i++)
        hash_table[i] = nullptr;
}

DictionaryImpl::~DictionaryImpl()
{
    for (int i = 0; i < size_bucket; i++)
    {
        Node* first = hash_table[i];
        while (first != nullptr)
        {
            Node* tmp = first;
            first = first->next;
            delete tmp;
        }
    }
}

int DictionaryImpl::hashFunction(string& word)
{
    removeNonLetters(word);
    
    int prime[num_alphabet] = {59, 61, 67, 71, 73, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 79, 83, 89, 97, 101};
    primeKey = 1;
    for (int i = 0; i < word.length(); i++)
        primeKey *= prime[word[i] - 'a'];
    return primeKey % size_bucket;
}

void DictionaryImpl::insert(string& word)
{
    removeNonLetters(word);
    if (word.empty())
        return;
    
    int hash_key = hashFunction(word);
    Node*& firstNode = hash_table[hash_key];
    if (firstNode == nullptr)
        firstNode= new Node(word, primeKey);
    else
    {
        Node* temp = new Node(word, primeKey);
        Node* last = firstNode;
        while (last->next)
            last = last->next;
        last->next = temp;
    }
}

void DictionaryImpl::lookup(string& letters, void callback(string))
{
    if (callback == nullptr)
        return;
    
    removeNonLetters(letters);
    if (letters.empty())
        return;
    
    int hash_key = hashFunction(letters);
    const long private_key = primeKey;
    Node* checkNode = hash_table[hash_key];
    while (checkNode != nullptr)
    {
        if (checkNode->primary_key == private_key)
        {
            callback(checkNode->value);
            checkNode = checkNode->next;
        }
        else
            checkNode = checkNode->next;
    }
}


void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;
    
    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}

