


#include <iostream>

#include <forward_list>

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


int main()
{
    fake_view v;

    for (const auto& l : v)
    {
        std::cout << l << std::endl;
    }


};
