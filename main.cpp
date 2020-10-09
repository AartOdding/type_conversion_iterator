
#include "type_conversion_iterator.hpp"
#include "reference_view.hpp"

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
    std::list<int> l;
    std::vector<int> v;
    std::forward_list<int> f;

    std::list<int>::iterator::iterator_category;

    type_conversion_iterator<decltype(l)::iterator, convert_to_pointer<int>> l_it;
    type_conversion_iterator<decltype(v)::iterator, convert_to_pointer<int>> v_it;
    type_conversion_iterator<decltype(f)::iterator, convert_to_pointer<int>> f_it;

    v.insert(v.begin(), {10, 12, 12, 434, 2133, 1, 54});

    using v_iter = type_conversion_iterator<
        std::vector<int>::iterator, convert_to_pointer<int>>;
    
    simple_view<v_iter> maView;
    maView.beginIt = v_iter(v.begin());
    maView.endIt =  v_iter(v.end());

    for (auto i : maView)
    {
        std::cout << i << std::endl;
    }


};
