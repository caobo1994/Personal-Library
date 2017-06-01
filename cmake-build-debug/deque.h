//
// Created by caobo on 17-6-1.
//

#ifndef PERSONAL_LIBRARY_DEQUE_H
#define PERSONAL_LIBRARY_DEQUE_H

#include "list.h"
#include <utility>

template <class T>
class deque
{
private:
    list<T> data;
public:
    T& get_head()
    {
        return data.begin()->data();
    }
    const T& get_head() const
    {
        return get_head();
    }
    T& get_tail()
    {
        return data.end()->data();
    }
    const T& get_tail() const
    {
        return get_tail();
    }

    T&& pop_head()
    {
        T value=std::move(get_head());
        data.delete_head();
        return value;
    }

    T&& pop_tail()
    {
        T value=std::move(get_tail());
        data.delete_tail();
        return value;
    }

    void push_head(const T& data_in)
    {
        data.add_head(data_in);
    }

    void push_tail(const T& data_in)
    {
        data.add_tail(data_in);
    }
};


#endif //PERSONAL_LIBRARY_DEQUE_H
