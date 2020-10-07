#pragma once

#include <iterator>
#include <type_traits>


/*

// The following pattern is used to incrementally give the iterator its functionality.

struct A_tag {};
struct B_tag : public A_tag {};
struct C_tag : public B_tag {};

struct A_part
{
    void do_A() {}
};

template<typename Tag, typename Enable = void>
struct B_part : A_part
{
    // B_part does not have do_B() if tag has no B
};

template<typename Tag>
struct B_part<Tag, std::enable_if_t<std::is_base_of_v<B_tag, Tag>>> : A_part
{
    void do_B() {}
};

template<typename Tag, typename Enable = void>
struct C_part : B_part<Tag>
{
    // C_part does not have do_C() if tag has no C
};

template<typename Tag>
struct C_part <Tag, std::enable_if_t<std::is_base_of_v<C_tag, Tag>>> : B_part<Tag>
{
    void do_C() {}
};

template<typename Tag>
struct parts : C_part<Tag>
{

};

parts<A_tag> a; // only has do_A()
parts<B_tag> b; // has do_A() and do_B()
parts<C_tag> c; // has do_A(), do_B() and do_C()

*/



template<typename T>
struct no_conversion
{
    using input_value_type = T;

    using output_value_type = T;
    using output_reference = T&;
    using output_pointer = T*;
};

template<typename T>
struct convert_to_pointer
{
    using input_type = T;

    using converted_value_type = T*;
    using converted_reference = T*;
    using converted_pointer = T*;
    
    static converted_value_type convert_to_value_type(const input_type& input_value)
    {
        return &input_value;
    }

    static converted_reference convert_to_reference(const input_type& input_value)
    {
        return &input_value;
    }

    static converted_pointer convert_to_pointer(const input_type& input_value)
    {
        return &input_value;
    }
};

template<typename T>
struct convert_to_pointer<T*>
{
    using input_type = T*;

    using converted_value_type = T*;
    using converted_reference = T*;
    using converted_pointer = T*;

    static converted_value_type convert_to_value_type(const input_type& input_value)
    {
        return input_value;
    }

    static converted_reference convert_to_reference(const input_type& input_value)
    {
        return input_value;
    }

    static converted_pointer convert_to_pointer(const input_type& input_value)
    {
        return input_value;
    }
};

template<typename T>
struct convert_to_pointer<std::unique_ptr<T>>
{
    using input_type = std::unique_ptr<T>;

    using converted_value_type = T*;
    using converted_reference = T*;
    using converted_pointer = T*;

    static converted_value_type convert_to_value_type(const input_type& input_value)
    {
        return input_value.get();
    }

    static converted_reference convert_to_reference(const input_type& input_value)
    {
        return input_value.get();
    }

    static converted_pointer convert_to_pointer(const input_type& input_value)
    {
        return input_value.get();
    }
};


template<typename SourceIterator, typename Converter>
struct converting_iterator_forward_part
{
    SourceIterator m_iterator;
};


template<typename SourceIterator, typename Converter, typename Enable = void>
struct converting_iterator_bidirectional_part 
    : converting_iterator_forward_part<SourceIterator, Converter>
{
    // leave empty
};

template<typename SourceIterator, typename Converter>
struct converting_iterator_bidirectional_part<
        SourceIterator, 
        Converter,
        std::enable_if_t<
            std::is_base_of_v<
                typename std::iterator_traits<SourceIterator>::iterator_category, 
                std::bidirectional_iterator_tag
            >
        >
    > : converting_iterator_forward_part<SourceIterator, Converter>
{
    // bidirectional iterator functions.
};


template<typename SourceIterator, typename Converter, typename Enable = void>
struct converting_iterator_random_access_part 
    : converting_iterator_bidirectional_part<SourceIterator, Converter>
{
    // leave empty
};

template<typename SourceIterator, typename Converter>
struct converting_iterator_random_access_part<
        SourceIterator, 
        Converter,
        std::enable_if_t<
            std::is_base_of_v<
                typename std::iterator_traits<SourceIterator>::iterator_category, 
                std::random_access_iterator_tag
            >
        >
    > : converting_iterator_bidirectional_part<SourceIterator, Converter>
{
    // bidirectional iterator functions.
};


template<typename SourceIterator, typename Converter /* = convert_to_pointer<std::iterator_traits<SourceIterator>::value_type> */>
class converting_iterator
{

};




template<typename T>
struct reference_converter
{

};

template<typename T>
struct reference_converter<std::unique_ptr<T>>
{
    using actual_type = std::unique_ptr<T>;
    using value_type = T;
    using reference_type = T&;
    using const_reference_type = const T&;
    using pointer_type = T*;
    using const_pointer_type = const T*;

    static reference_type get_reference(const actual_type& from_value)
    {
        return *from_value;
    }
    
    static pointer_type get_pointer(const actual_type& from_value)
    {
        return from_value.get();
    }
};


template<typename ContainerType, typename Converter = reference_converter<typename ContainerType::value_type>>
class data_iterator
{
public:

    using converter_type = Converter;
    using container_iterator = typename ContainerType::iterator;

    using iterator_category = typename std::iterator_traits<container_iterator>::iterator_category;
    using value_type = typename converter_type::value_type;
    using difference_type = typename std::iterator_traits<container_iterator>::difference_type;
    using pointer = typename converter_type::pointer_type;
    using reference = typename converter_type::reference_type;

    static_assert(!std::is_same_v<iterator_category, std::input_iterator_tag>, "Using an input iterator is not supported.");
    static_assert(!std::is_same_v<iterator_category, std::output_iterator_tag>, "Using an output iterator is not supported.");

    static constexpr bool atleast_random_access = std::is_same_v<iterator_category, std::random_access_iterator_tag>;
    static constexpr bool atleast_bidirectional = std::is_same_v<iterator_category, std::bidirectional_iterator_tag> || atleast_random_access;
    static constexpr bool atleast_forward = std::is_same_v<iterator_category, std::forward_iterator_tag> || atleast_bidirectional;

    data_iterator(container_iterator it)
        : m_iterator(it)
    { }

    // Requirements of std::forward_iterator

    data_iterator() = default;
    data_iterator(const data_iterator&) = default;
    ~data_iterator() = default;

    data_iterator& operator=(const data_iterator&) = default;

    reference operator*() const {
        return converter_type::get_reference(*m_iterator);
    }

    pointer operator->() const {
        return converter_type::get_pointer(*m_iterator);
    }
    
    data_iterator& operator++() {
        ++m_iterator;
        return *this;
    }

    data_iterator operator++(int) {
        data_iterator temp = *this;
        ++m_iterator;
        return temp;
    }

    bool operator==(const data_iterator& right) const {
        return m_iterator == right.m_iterator;
    }

    bool operator!=(const data_iterator& right) const {
        return m_iterator != right.m_iterator;
    }

    // Requirements of std::bidirectional_iterator
    /*
    std::enable_if_t<atleast_bidirectional, data_iterator&>
    operator--() {
        --m_iterator;
        return *this;
    }

    std::enable_if_t<atleast_bidirectional, data_iterator>
    operator--(int) {
        data_iterator temp = *this;
        --m_iterator;
        return temp;
    }*/

    // Requirements of std::random_access_iterator
    /*
    std::enable_if_t<atleast_random_access, data_iterator&>
    operator+=(const difference_type offset) {
        m_iterator += offset;
        return *this;
    }

    std::enable_if_t<atleast_random_access, data_iterator>
    operator+(const difference_type offset) const {
        data_iterator temp = *this;
        return temp += offset;
    }

    std::enable_if_t<atleast_random_access, data_iterator&>
    operator-=(const difference_type offset) {
        m_iterator -= offset;
        return *this;
    }

    std::enable_if_t<atleast_random_access, data_iterator>
    operator-(const difference_type offset) const {
        data_iterator temp = *this;
        return temp -= offset;
    }

    std::enable_if_t<atleast_random_access, difference_type>
    operator-(const data_iterator& right) const {
        return m_iterator - right.m_iterator;
    }

    std::enable_if_t<atleast_random_access, reference>
    operator[](const difference_type offset) const {
        return *(*this + offset);
    }
    
    std::enable_if_t<atleast_random_access, bool>
    operator<(const data_iterator& right) const {
        return m_iterator < right.m_iterator;
    }

    std::enable_if_t<atleast_random_access, bool>
    operator>(const data_iterator& right) const {
        return m_iterator > right.m_iterator;
    }

    std::enable_if_t<atleast_random_access, bool>
    operator<=(const data_iterator& right) const {
        return m_iterator <= right.m_iterator;
    }

    std::enable_if_t<atleast_random_access, bool>
    operator>=(const data_iterator& right) const {
        return m_iterator >= right.m_iterator;
    }*/

private:

    container_iterator m_iterator;

};
