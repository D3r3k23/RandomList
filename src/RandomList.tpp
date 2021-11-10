#include "RandomList.hpp"

namespace RL
{
    //////////////////////////////
    //---------- List ----------//
    //////////////////////////////

    template <typename T>
    List<T>::List(void)
    {
        init();
    }

    template <typename T>
    List<T>::~List(void)
    {
        delete_list();
    }

    template <typename T>
    List<T>::List(const List<T>& other)
    {
        init();
        for (const auto& item : other)
            push_back(item);
    }

    template <typename T>
    List<T>::List(List<T>&& other)
    {
        head = other.head;
        tail = other.tail;
        length = other.length;

        other.init();
    }

    template <typename T>
    List<T>& List<T>::operator=(const List<T>& other)
    {
        if (this != &other)
        {
            delete_list();

            for (auto node = other.head; node = node->next; node)
                push_back(node->data);
        }
        return *this;
    }

    template <typename T>
    List<T>& List<T>::operator=(List<T>&& other)
    {
        if (this != &other)
        {
            delete_list();

            head = other.head;
            tail = other.tail;
            length = other.length;

            other.init();
        }
        return *this;
    }

    template <typename T>
    void List<T>::push_back(const T& data)
    {
        auto node = new Node<T>(data);
        if (!head && !tail)
        {
            head = node;
            tail = node;
            length = 1;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
            length++;
        }
    }

    template <typename T>
    void List<T>::push_front(const T& data)
    {
        auto node = new Node<T>(data);
        if (!head && !tail)
        {
            head = node;
            tail = node;
            length = 1;
        }
        else
        {
            head->prev = node;
            node->next = head;
            head = node;
            length++;
        }
    }

    template <typename T>
    std::optional<T> List<T>::pop_back(void)
    {
        if (tail)
        {
            T back = tail->data;
            delete_node(tail);
            return back;
        }
        else
            return {};
    }

    template <typename T>
    std::optional<T> List<T>::pop_front(void)
    {
        if (head)
        {
            T front = head->data;
            delete_node(head);
            return front;
        }
        else
            return {};
    }

    template <typename T>
    unsigned List<T>::size(void) const
    {
        return length;
    }

    template <typename T>
    void List<T>::init(void)
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    template <typename T>
    void List<T>::delete_node(Node<T>* node)
    {
        if (node == head && node == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else if (node == head)
            head = node->next;
        else if (node == tail)
            tail = node->prev;

        if (node != head)
            node->prev->next = node->next;
        if (node != tail)
            node->next->prev = node->prev;

        length--;
        delete node;
    }

    template <typename T>
    void List<T>::delete_list(void)
    {
        auto node = head;
        while (node)
        {
            auto next = node->next;
            delete node;
            node = next;
        }
        init();
    }

    //////////////////////////////
    //-------- Iterator --------//
    //////////////////////////////

    template <typename T>
    Iterator<T>::Iterator(Node<T>* node)
        : node(node)
    { }

    template <typename T>
    T& Iterator<T>::operator*(void)
    {
        return node->data;
    }

    template <typename T>
    T& Iterator<T>::operator->(void)
    {
        return node->data;
    }

    template <typename T>
    Iterator<T>::operator bool(void) const
    {
        return bool(node);
    }

    template <typename T>
    bool Iterator<T>::operator==(const Iterator& other) const
    {
        return node == other.node;
    }

    template <typename T>
    bool Iterator<T>::operator!=(const Iterator& other) const
    {
        return !(*this == other);
    }

    template <typename T>
    Iterator<T>& Iterator<T>::operator++(void)
    {
        if (node)
            node = node->next;
        return *this;
    }

    template <typename T>
    Iterator<T> Iterator<T>::operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    template <typename T>
    Iterator<T>& Iterator<T>::operator--(void)
    {
        if (node)
            node = node->prev;
        return *this;
    }

    template <typename T>
    Iterator<T> Iterator<T>::operator--(int)
    {
        auto temp = *this;
        --(*this);
        return temp;
    }

    //////////////////////////////
    //----- Const Iterator -----//
    //////////////////////////////

    template <typename T>
    const_Iterator<T>::const_Iterator(Node<T> const* node)
        : node(node)
    { }

    template <typename T>
    const_Iterator<T>::const_Iterator(const Iterator<T>& other)
        : node(other.node)
    { }

    template <typename T>
    const_Iterator<T>& const_Iterator<T>::operator=(const Iterator<T>& other)
    {
        node = other.node;
    }

    template <typename T>
    const T& const_Iterator<T>::operator*(void) const
    {
        return node->data;
    }

    template <typename T>
    const T& const_Iterator<T>::operator->(void) const
    {
        return node->data;
    }

    template <typename T>
    const_Iterator<T>::operator bool(void) const
    {
        return bool(node);
    }

    template <typename T>
    bool const_Iterator<T>::operator==(const const_Iterator& other) const
    {
        return node == other.node;
    }

    template <typename T>
    bool const_Iterator<T>::operator!=(const const_Iterator& other) const
    {
        return !(*this == other);
    }

    template <typename T>
    const_Iterator<T>& const_Iterator<T>::operator++(void)
    {
        if (node)
            node = node->next;
        return *this;
    }

    template <typename T>
    const_Iterator<T> const_Iterator<T>::operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    template <typename T>
    const_Iterator<T>& const_Iterator<T>::operator--(void)
    {
        if (node)
            node = node->prev;
        return *this;
    }

    template <typename T>
    const_Iterator<T> const_Iterator<T>::operator--(int)
    {
        auto temp = *this;
        --(*this);
        return temp;
    }
}
