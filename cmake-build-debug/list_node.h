//
// Created by caobo on 17-5-31.
//

#ifndef PERSONAL_LIBRARY_LIST_NODE_H
#define PERSONAL_LIBRARY_LIST_NODE_H


#include <memory>

template<class T>
class list_node
{

public:
    using PT=std::shared_ptr<list_node<T>>;

private:
    T data_store;
    PT pre_store;
    PT next_store;

public:
    auto& data()
    {
        return data_store;
    }
    const auto& data() const
    {
        return data();
    }

    PT& pre()
    {
        return pre_store;
    }
    const PT& pre() const
    {
        return pre();
    }

    PT& next()
    {
        return next_store;
    }
    const PT& next() const
    {
        return next();
    }

    bool pre_exist() const
    {
        return static_cast<bool>(pre);
    }

    bool next_exist() const
    {
        return static_cast<bool>(next);
    }

    bool single() const
    {
        return (!pre_exist())&&(!next_exist());
    }

    T& data_pre()
    {
        if( pre_exist())
        {
            return pre_store->data_store;
        }
        else
        {
            throw(std::range_error("Previous node does not exist."));
        }
    }

    const T& data_pre() const
    {
        return data_pre();
    }

    T& data_next()
    {
        if(next_exist())
        {
            return next_store->data_store;
        }
        else
        {
            throw(std::range_error("Next node does not exist."));
        }
    }

    const T& data_next() const
    {
        return data_next();
    }

    list_node()= default;
    list_node(const list_node<T>&)= default;
    list_node(list_node<T>&&)= default;
    list_node(T&& data_in= static_cast<T>(0), PT pre_in=static_cast<PT >(nullptr), PT next_in=static_cast<PT >(nullptr))
    {
        data_store=data_in;
        pre_store=pre_in;
        next_store=next_in;
    }

    ~list_node()= default;
};


#endif //PERSONAL_LIBRARY_LIST_NODE_H
