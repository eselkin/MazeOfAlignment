#ifndef node_H
#define node_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

template<typename T>
struct node
{
    node(const T &d, int c = 0, int h = 0);
    ~node();
    node(const node<T> &other);
    node<T>& operator=(const node<T>& other);
    T& operator=(const T& other);
    node<T>& operator+=(const node<T>& rhs);
    T& theData();
    T theData() const;
    int &theCount();  // only for bst
    int &theHeight(); // only for BST

    template<typename U, typename V>
    friend
    V& operator<<(V& out, node<U> &n);

    template<typename U>
    friend
    bool operator<(const node<U> &n, const node<U> &m );

    template<typename U>
    friend
    bool operator>(const node<U> &n, const node<U> &m );


    template<typename U>
    friend
    bool operator==(const node<U> &n, const node<U> &m );

    template<typename U>
    friend
    bool operator!=(const node<U> &n, const node<U> &m );

    T data;
    int count;
    int height;
    void nukem();
    void copy(const node<T> &other);
};

template<typename T>
node<T>::node(const T& d, int c, int h)
{
    data = d;
    count = c;
    height= h;

}


template<typename T>
node<T>::~node()
{
    nukem();
}

template<typename T>
node<T>::node(const node<T> &other)
{
    copy(other);
}

template<typename T>
node<T>& node<T>::operator=(const node<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
node<T>& node<T>::operator+=(const node<T> &rhs)
{
    count+=rhs.count;
    // does not change balance
    return *this;
}

template<typename T>
T& node<T>::theData()
{
    // Return by ref the data so we can assign to it as LVALUE
    return data;
}

template<typename T>
T node<T>::theData() const
{
    // Return by ref the data so we can assign to it as LVALUE
    return data;
}


template<typename T>
int& node<T>::theCount()
{
   // Return by ref the count, so we can assign to it!
    return count;

}

template<typename T>
int& node<T>::theHeight()
{
   // Return by ref the height, so we can assign to it!
    return height;
}

template<typename T>
void node<T>::nukem()
{
    // there is no DYNAMIC MEMORY, NO LEFT RIGHT! HANDLED NOW BY ITS INDEX
}

template<typename T>
void node<T>::copy(const node<T> &other)
{
    count = other.count;
    data = other.data;
}

template<typename U>
bool operator<(const node<U> &n,const node<U> &m )
{
    return (n.data < m.data);
}

template<typename U>
bool operator>(const node<U> &n,const node<U> &m )
{
    return (n.data > m.data);
}

template<typename U>
bool operator==(const node<U> &n,const node<U> &m )
{
    return n.data == m.data;
}

template<typename U>
bool operator!=(const node<U> &n,const node<U> &m )
{
    return n.data != m.data;
}


#endif // node_H
