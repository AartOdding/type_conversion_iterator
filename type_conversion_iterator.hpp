#pragma once

#include <iterator>
#include <type_traits>

#include <iostream> // TODO: remove


template<typename SourceIterator, typename Conversion>
struct type_conversion_iterator_forward_part
{
    // type_conversion_iterator can be constructed from any other iterator
    type_conversion_iterator_forward_part(SourceIterator iterator)
        : m_iterator(iterator)
    { }

    // typedefs so type_conversion_iterator can be used in std::iterator_traits:
    using iterator_category = typename std::iterator_traits<SourceIterator>::iterator_category;
    using difference_type = typename std::iterator_traits<SourceIterator>::difference_type;
    using value_type = typename Conversion::output_value_type;
    using reference = typename Conversion::output_reference_type;
    using pointer = typename Conversion::output_pointer_type;
    
    // requirements of std::forward_iterator concept
    type_conversion_iterator_forward_part() = default;
    type_conversion_iterator_forward_part(const type_conversion_iterator_forward_part&) = default;
    ~type_conversion_iterator_forward_part() = default;

    type_conversion_iterator_forward_part& operator=(const type_conversion_iterator_forward_part&) = default;

    reference operator*() const {
        return Conversion::get_reference(*m_iterator);
    }

    pointer operator->() const {
        return Conversion::get_pointer(*m_iterator);
    }
    
    type_conversion_iterator_forward_part& operator++() {
        ++m_iterator;
        return *this;
    }
    
    type_conversion_iterator_forward_part operator++(int) {
        return type_conversion_iterator_forward_part(m_iterator++);
    }
    
    bool operator==(const type_conversion_iterator_forward_part& right) const {
        return m_iterator == right.m_iterator;
    }
    
    bool operator!=(const type_conversion_iterator_forward_part& right) const {
        return m_iterator != right.m_iterator;
    }

private:

    SourceIterator m_iterator;

};


template<typename SourceIterator, typename Conversion, typename Enable = void>
struct type_conversion_iterator_bidirectional_part 
    : type_conversion_iterator_forward_part<SourceIterator, Conversion>
{
    /* 
     * Left empty, type_conversion_iterator inherits this specialization,
     * if it should not support bidirectional iteration.
     */
};


template<typename SourceIterator, typename Conversion>
struct type_conversion_iterator_bidirectional_part<
        SourceIterator, 
        Conversion,
        std::enable_if_t<
            std::is_base_of_v<
                std::bidirectional_iterator_tag,
                typename std::iterator_traits<SourceIterator>::iterator_category
            >
        >
    > : type_conversion_iterator_forward_part<SourceIterator, Conversion>
{
    // bidirectional iterator functions.
    void bidirectional_stuff()
    {
        std::cout << "bidirectional stuff" << std::endl;
    }
};


template<typename SourceIterator, typename Conversion, typename Enable = void>
struct type_conversion_iterator_random_access_part 
    : type_conversion_iterator_bidirectional_part<SourceIterator, Conversion>
{
    /* 
     * Left empty, type_conversion_iterator inherits this specialization,
     * if it should not support bidirectional iteration.
     */
};


template<typename SourceIterator, typename Conversion>
struct type_conversion_iterator_random_access_part<
        SourceIterator, 
        Conversion,
        std::enable_if_t<
            std::is_base_of_v<
                std::random_access_iterator_tag,
                typename std::iterator_traits<SourceIterator>::iterator_category
            >
        >
    > : type_conversion_iterator_bidirectional_part<SourceIterator, Conversion>
{
    // random access iterator functions.
    void random_access_stuff()
    {
        std::cout << "random access stuff" << std::endl;
    }
};


template<typename SourceIterator, typename Conversion>
class type_conversion_iterator 
    : public type_conversion_iterator_random_access_part<SourceIterator, Conversion>
{

};


