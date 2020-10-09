
#include "views.hpp"

#include <iostream>

#include <forward_list>
#include <list>
#include <vector>

#include <string>


class fake_iterator
{
public:

    using iterator_category = std::forward_iterator_tag;
    using value_type = std::string;
    using difference_type = int;
    using pointer = std::string;
    using reference = std::string;

    int m_pos = 0;

    fake_iterator(int position) : m_pos(position) { }

    fake_iterator() = default;
    fake_iterator(const fake_iterator&) = default;
    ~fake_iterator() = default;
    fake_iterator& operator=(const fake_iterator&) = default;

    fake_iterator& operator++() { ++m_pos; return *this; }
    fake_iterator operator++(int) { return fake_iterator(m_pos++); }
    reference operator*() { return "hi"; }
    pointer operator->() { return "hi"; }
    bool operator==(const fake_iterator& rhs) { return m_pos == rhs.m_pos; }
    bool operator!=(const fake_iterator& rhs) { return m_pos != rhs.m_pos; }

};

struct fake_view
{
    int dummy;
    fake_iterator begin() { return 0; }
    fake_iterator end() { return 10; }
};

template<typename It>
struct simple_view
{
    It beginIt;
    It endIt;

    It begin() { return beginIt; }
    It end() { return endIt; }
};

int main()
{
    std::list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 8};
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 8};
    std::forward_list<int> f{1, 2, 3, 4, 5, 6, 7, 8, 8};

    std::list<std::unique_ptr<const int>> lu;
    lu.emplace_back(new int(1));
    lu.emplace_back(new int(2));
    lu.emplace_back(new int(3));
    lu.emplace_back(new int(4));
    lu.emplace_back(new int(5));
    lu.emplace_back(new int(6));

    const auto& clu = lu;

    const_pointer_view<decltype(lu)> lu_view{ lu };
    for (auto p : lu_view)
    {
        //*p = 100 - *p;
        std::cout << p << "\t" << *p << std::endl;
    }

    pointer_view<std::list<int>> list_view{ l };
    for (auto p : list_view)
    {
        std::cout << p << "\t" << *p << std::endl;
    }
/*
    pointer_view<std::vector<int>> vec_view{ v };
    for (auto p : vec_view)
    {
        std::cout << p << "\t" << *p << std::endl;
    }*/

    pointer_view<std::forward_list<int>> fw_view{ f };
    for (auto p : fw_view)
    {
        std::cout << p << "\t" << *p << std::endl;
    }


    // std::list<int>::iterator::iterator_category;

    // type_conversion_iterator<decltype(l)::iterator, convert_to_pointer<int>> l_it;
    // type_conversion_iterator<decltype(v)::iterator, convert_to_pointer<int>> v_it;
    // type_conversion_iterator<decltype(f)::iterator, convert_to_pointer<int>> f_it;

    // v.insert(v.begin(), {10, 12, 12, 434, 2133, 1, 54});

    // using v_iter = type_conversion_iterator<
    //     std::vector<int>::iterator, convert_to_pointer<int>>;
    
    // simple_view<v_iter> maView;
    // maView.beginIt = v_iter(v.begin());
    // maView.endIt =  v_iter(v.end());

    // for (auto i : maView)
    // {
    //     std::cout << i << std::endl;
    // }


};
