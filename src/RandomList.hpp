#ifndef RANDOM_LIST_HPP
#define RANDOM_LIST_HPP

#include <concepts>
#include <optional>

namespace RL
{
    template <typename T>
    struct Node
    {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& data) : data(data) {}
        Node(const Node& other) = default;
        Node& operator=(const Node& other) = default;
    };

    template <typename T>
    class List
    {
    private:
        Node<T>* head;
        Node<T>* tail;
        unsigned length;

    public:
        List(void);
        ~List(void);

        List(const List& other);
        List(List&& other);

        List& operator=(const List& other) const;
        List& operator=(List&& other);

        void push_back(const T& data);
        void push_front(const T& data);

        std::optional<T> pop_back(void);
        std::optional<T> pop_front(void);

        unsigned size(void) const;

        friend class Iterator;
        friend class const_Iterator;

        Iterator<T> begin(void) { return Iterator<T>(head); }
        Iterator<T> end(void)   { return Iterator<T>(tail); }

        const_Iterator<T> cbegin(void) const { return const_Iterator<T>(head); }
        const_Iterator<T> cend(void)   const { return const_Iterator<T>(tail); }

    private:
        void delete_node(Node<T>* node);
        void delete_list(void);
    };

    template <typename T>
    class Iterator
    {
    private:
        Node<T>* node;

    public:
        Iterator(void) = delete;
        Iterator(Node<T>* node);

        Iterator(const Iterator& other) = default;
        Iterator& operator=(const Iterator& other) = default;

        T& operator*(void);
        T& operator->(void);

        operator bool(void) const;

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

        Iterator& operator++(void);
        Iterator operator++(int);

        Iterator& operator--(void);
        Iterator operator--(int);

        friend class const_Iterator;
    };

    template <typename T>
    class const_Iterator
    {
    private:
        const Node<T>* node;

    public:
        const_Iterator(void) = delete;
        const_Iterator(Node<T>* node);

        const_Iterator(const const_Iterator& other) = default;
        const_Iterator& operator=(const const_Iterator& other) = default;

        const_Iterator(const Iterator<T>& other);
        const_Iterator& operator=(const Iterator<T>& other);

        const T& operator*(void) const;
        const T& operator->(void) const;

        operator bool(void) const;

        bool operator==(const const_Iterator& other) const;
        bool operator!=(const const_Iterator& other) const;

        const_Iterator& operator++(void);
        const_Iterator operator++(int);

        const_Iterator& operator--(void);
        const_Iterator operator--(int);
    };

    template <typename T, typename P>
    concept UnaryPredicate = requires(T a, P p)
    {
        { p(a) } -> std::same_as<bool>;
    };

    template <typename T, UnaryPredicate P>
    Iterator<T> find_if(Iterator<T> first, Iterator<T> last, P pred);

    template <typename T, UnaryPredicate P>
    const_Iterator<T> find_if(const_Iterator<T> first, const_Iterator<T> last, P pred);
}

#include "RandomList.tpp" // Template definitions

#endif // RANDOM_LIST_HPP
