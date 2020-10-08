#pragma once

#include <iterator>
#include <type_traits>



template<typename SourceIterator, typename Converter>
struct type_conversion_iterator_forward_part
{
    SourceIterator m_iterator;
};


template<typename SourceIterator, typename Converter, typename Enable = void>
struct type_conversion_iterator_bidirectional_part 
    : type_conversion_iterator_forward_part<SourceIterator, Converter>
{
    /* 
     * Left empty, type_conversion_iterator inherits this specialization,
     * if it should not support bidirectional iteration.
     */
};


template<typename SourceIterator, typename Converter>
struct type_conversion_iterator_bidirectional_part<
        SourceIterator, 
        Converter,
        std::enable_if_t<
            std::is_base_of_v<
                typename std::iterator_traits<SourceIterator>::iterator_category, 
                std::bidirectional_iterator_tag
            >
        >
    > : type_conversion_iterator_forward_part<SourceIterator, Converter>
{
    // bidirectional iterator functions.
};


template<typename SourceIterator, typename Converter, typename Enable = void>
struct type_conversion_iterator_random_access_part 
    : type_conversion_iterator_bidirectional_part<SourceIterator, Converter>
{
    /* 
     * Left empty, type_conversion_iterator inherits this specialization,
     * if it should not support bidirectional iteration.
     */
};


template<typename SourceIterator, typename Converter>
struct type_conversion_iterator_random_access_part<
        SourceIterator, 
        Converter,
        std::enable_if_t<
            std::is_base_of_v<
                typename std::iterator_traits<SourceIterator>::iterator_category, 
                std::random_access_iterator_tag
            >
        >
    > : type_conversion_iterator_bidirectional_part<SourceIterator, Converter>
{
    // bidirectional iterator functions.
};


template<typename SourceIterator, typename Converter /* = convert_to_pointer<std::iterator_traits<SourceIterator>::value_type> */>
class type_conversion_iterator
{

};


