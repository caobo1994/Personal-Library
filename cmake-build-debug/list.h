//
// Created by caobo on 17-5-31.
//

#ifndef PERSONAL_LIBRARY_LIST_H
#define PERSONAL_LIBRARY_LIST_H

#include "list_node.h"

template<class T,class RANGE=uint64_t>
class list
{
public:
    using PNODE=std::shared_ptr<list_node<T>>;
private:
    PNODE be_store;
    PNODE en_store;
    PNODE current_store;
    RANGE length_store;
    RANGE position_store;
public:
    PNODE& begin()
    {
        return be_store;
    }
    const PNODE& begin() const
    {
        return begin();
    }

    PNODE & end()
    {
        return en_store;
    }
    const PNODE & end() const
    {
        return end();
    }

    PNODE & current()
    {
        return current_store;
    }
    const PNODE & current() const
    {
        return current();
    }

    RANGE & length()
    {
        return length_store;
    }
    const RANGE& length() const
    {
        return length();
    }

    RANGE& position()
    {
        return position_store;
    }
    const RANGE& position() const
    {
        return position();
    }

    bool at_begin() const
    {
        return(be_store==current_store);
    }

    bool at_end() const
    {
        return(en_store==current_store);
    }


private:
    auto && new_node()
    {
        return std::make_shared<list_node<T>>();
    }

    auto && new_node(const list_node<T>& node)
    {
        return std::make_shared<list_node<T>>(node);
    }
public:

    list()
    {
        be_store= nullptr;
        en_store= nullptr;
        current_store= nullptr;
        length_store=0;
        position_store=0;
    }

    list(const list_node<T> & start_point)
    {
        current_store=new_node();
        current_store->data()=start_point.data();

        auto start_pointer=new_node(start_point);

        PNODE origin_pre=start_point.pre();
        PNODE origin_pre_next=start_pointer;
        PNODE origin_next=start_point.next();
        PNODE origin_next_pre=start_pointer;

        auto pre_new_next=current_store;
        auto next_new_pre=current_store;

        PNODE pre_new(nullptr);
        PNODE next_new(nullptr);

        RANGE num_pre=0;
        RANGE num_next=0;

        while(origin_pre)
        {
            pre_new=new_node();
            pre_new->data()=origin_pre->data();

            pre_new->next()=pre_new_next;
            pre_new_next->pre()=pre_new;
            pre_new_next=pre_new;

            origin_pre=origin_pre->pre();
            num_pre++;
        }
        if(pre_new)
        {
            pre_new->pre()= nullptr;
            be_store=pre_new;
        }
        else
        {
            be_store=current_store;
        }

        while(origin_next)
        {
            next_new=new_node();
            next_new->data()=origin_next->data();

            next_new->pre()=next_new_pre;
            next_new_pre->next()=next_new;
            next_new_pre=next_new;

            origin_next=origin_next->next();
            num_next++;
        }
        if(next_new)
        {
            next_new->next()=nullptr;
            en_store=next_new;
        }
        else
        {
            en_store=current_store;
        }

        length_store=num_pre+num_next+1;
        position_store=num_pre;
    }

    list(const list<T>& origin)
    {
        length_store=origin.length();
        be_store=new_node();
        be_store->data()=origin.begin()->data();
        be_store->pre()= nullptr;
        PNODE pointer;
        for(PNODE origin_pointer_next=origin.begin()->next(), pointer = be_store; origin_pointer_next; origin_pointer_next=origin_pointer_next->next(), pointer=pointer->next())
        {
            pointer->next()=new_node();
            PNODE pointer_next=pointer->next();
            pointer_next->pre()=pointer;
            pointer_next->data()=origin_pointer_next->data();
        }
        en_store=pointer;
        current_store=be_store;
        position_store=0;
    }

    ~list()= default;

    list<T>& operator++()
    {
        if(current_store==en_store)
        {
            throw(std::range_error(next_nonexist));
        }
        current_store=current_store->next();
        position_store++;
        return *this;
    }

    list<T>& operator--()
    {
        if(current_store==be_store)
        {
            throw(std::range_error(pre_nonexist))
        }
        current_store=current_store->pre();
        position_store--;
        return *this;
    }


    PNODE delete_head()
    {

        PNODE head_next=be_store->next();
        be_store->next()= nullptr;
        be_store=head_next;
        be_store->pre()= nullptr;
        if(position_store)
        {
            position_store--;
            length_store--;
        }
        else
        {
            length_store--;
            current_store=head_next;
        }
        return head_next;
    }
    PNODE delete_tail()
    {
        PNODE tail_pre=en_store->pre();
        en_store->pre()= nullptr;
        en_store=tail_pre;
        en_store->next()= nullptr;
        if(position_store<(length_store-1))
        {
            length_store--;
        }
        else
        {
            position_store--;
            length_store--;
            current_store=tail_pre;
        }
        return tail_pre;
    }
    PNODE delete_current()
    {
        if(current_store==be_store)
        {
            return delete_head();
        }
        if(current_store==en_store)
        {
            return delete_tail();
        }
        PNODE current_pre=current_store->pre();
        PNODE current_next=current_store->next();
        current_pre->next()=current_next;
        current_next->pre()=current_pre;
        current_store=current_next;
        return current_store;
    }

    PNODE delete_current_to_pre()
    {
        delete_current();
        this->--;
        return current_store;
    }

    PNODE add_head(list_node<T>& node_in)
    {
        auto be_new=PNODE(&node_in);
        be_store->pre()=be_new;
        be_new->next()=be_store;
        be_store=be_new;
        length_store++;
        position_store++;
        return be_store;
    }

    PNODE add_tail(list_node<T>& node_in)
    {
        auto en_new=PNODE(&node_in);
        en_store->next()=en_new;
        en_new->pre()=en_store;
        en_store=en_new;
        length_store++;
        return en_store;
    }

    PNODE add_current_pre(list_node<T>& node_in)
    {
        auto current_pre_new= static_cast<PNODE >(&node_in);
        PNODE current_pre=current_store->pre();
        current_store->pre()=current_pre_new;
        current_pre->next()=current_pre_new;
        current_pre_new->next()=current_store;
        current_pre_new->pre()=current_pre;
        length_store++;
        position_store++;
        return current_pre_new;
    }

    PNODE add_current_next(list_node<T>& node_in)
    {
        auto current_next_new= static_cast<PNODE >(&node_in);
        PNODE current_next=current_store->pre();
        current_store->next()=current_next_new;
        current_next->pre()=current_next_new;
        current_next_new->pre()=current_store;
        current_next_new->next()=current_next;
        length_store++;
        return current_next_new;
    }

    decltype(*PNODE())&& make_node(const T& data_in)
    {
        return decltype(*PNODE())(data_in);
    }

    PNODE add_head(const T& data_in)
    {
        auto new_node=make_node(data_in);
        return add_head(data_in);
    }

    PNODE add_tail(const T& data_in)
    {
        auto new_node=make_node(data_in);
        return add_tail(data_in)
    }

};


#endif //PERSONAL_LIBRARY_LIST_H
