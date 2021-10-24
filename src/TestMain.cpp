#include "RandomList.hpp"

#include <iostream>

template <typename T>
void print_list(const RL::List<T>& list);

int main()
{
    RL::List<int> l1;
    l1.push_back(5);
    l1.push_back(7);
    l1.push_back(2);
    l1.push_back(14);
    print_list(l1);

    return 0;
}

template <typename T>
void print_list(const RL::List<T>& list)
{
    for (const auto& item : list)
        std::cout << item << '\n';
}
