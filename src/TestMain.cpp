#include "RandomList.hpp"

#include <iostream>

template <typename T>
void print_list(const RL::List<T>& list);

int main(int, char*[])
{
    RL::List<int> l1;
    l1.push_back(5);
    l1.push_back(7);
    l1.push_back(2);
    l1.push_back(14);
    std::cout << "List1:" << '\n';
    print_list<int>(l1);
    std::cout << '\n';

    auto l2 = l1; // Copy
    std::cout << "List2:" << '\n';
    print_list<int>(l2);
    std::cout << '\n';

    auto l3 = std::move(l2); // Move
    std::cout << "List2:" << '\n';
    print_list<int>(l2);
    std::cout << '\n';
    std::cout << "List3:" << '\n';
    print_list<int>(l3);
    std::cout << '\n';

    return 0;
}

template <typename T>
void print_list(const RL::List<T>& list)
{
    for (const auto& item : list)
        std::cout << item << '\n';
}
