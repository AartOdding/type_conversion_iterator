#pragma once

#include <iterator>
#include <type_traits>


namespace tci
{

    template<typename SourceIterator, typename Conversion, typename Enable = void>
    class type_conversion_iterator
    {

    };


    // Specialization for forward iterators
    template<typename SourceIterator, typename Conversion>
    class type_conversion_iterator<SourceIterator, Conversion,
        std::enable_if_t<std::is_same_v<std::forward_iterator_tag,
            typename std::iterator_traits<SourceIterator>::iterator_category>>>
    {
        SourceIterator m_iterator;

    public:

        // type_conversion_iterator can be constructed from any other iterator
        type_conversion_iterator(SourceIterator iterator)
            : m_iterator(iterator)
        { }

        // typedefs so type_conversion_iterator can be used in std::iterator_traits:
        using iterator_category = typename std::iterator_traits<SourceIterator>::iterator_category;
        using difference_type = typename std::iterator_traits<SourceIterator>::difference_type;
        using value_type = typename Conversion::output_type;
        using reference = typename Conversion::output_type;
        using pointer = typename Conversion::output_type;
        
        // requirements of std::forward_iterator concept
        type_conversion_iterator() = default;
        type_conversion_iterator(const type_conversion_iterator&) = default;
        ~type_conversion_iterator() = default;

        type_conversion_iterator& operator=(const type_conversion_iterator&) = default;

        reference operator*() const {
            return Conversion::convert(*m_iterator);
        }

        pointer operator->() const {
            return Conversion::convert(*m_iterator);
        }
        
        type_conversion_iterator& operator++() {
            ++m_iterator;
            return *this;
        }
        
        type_conversion_iterator operator++(int) {
            return type_conversion_iterator(m_iterator++);
        }
        
        bool operator==(const type_conversion_iterator& right) const {
            return m_iterator == right.m_iterator;
        }
        
        bool operator!=(const type_conversion_iterator& right) const {
            return m_iterator != right.m_iterator;
        }
    };


    // Specialization for bidirectional iterators
    template<typename SourceIterator, typename Conversion>
    class type_conversion_iterator<SourceIterator, Conversion,
        std::enable_if_t<std::is_same_v<std::bidirectional_iterator_tag,
            typename std::iterator_traits<SourceIterator>::iterator_category>>>
    {
        SourceIterator m_iterator;

    public:

        // type_conversion_iterator can be constructed from any other iterator
        type_conversion_iterator(SourceIterator iterator)
            : m_iterator(iterator)
        { }

        // typedefs so type_conversion_iterator can be used in std::iterator_traits:
        using iterator_category = typename std::iterator_traits<SourceIterator>::iterator_category;
        using difference_type = typename std::iterator_traits<SourceIterator>::difference_type;
        using value_type = typename Conversion::output_type;
        using reference = typename Conversion::output_type;
        using pointer = typename Conversion::output_type;
        
        // requirements of std::forward_iterator concept
        type_conversion_iterator() = default;
        type_conversion_iterator(const type_conversion_iterator&) = default;
        ~type_conversion_iterator() = default;

        type_conversion_iterator& operator=(const type_conversion_iterator&) = default;

        reference operator*() const {
            return Conversion::convert(*m_iterator);
        }

        pointer operator->() const {
            return Conversion::convert(*m_iterator);
        }
        
        type_conversion_iterator& operator++() {
            ++m_iterator;
            return *this;
        }
        
        type_conversion_iterator operator++(int) {
            return type_conversion_iterator(m_iterator++);
        }
        
        bool operator==(const type_conversion_iterator& right) const {
            return m_iterator == right.m_iterator;
        }
        
        bool operator!=(const type_conversion_iterator& right) const {
            return m_iterator != right.m_iterator;
        }
        
        // requirements of std::bidirectional_iterator concept
        type_conversion_iterator& operator--() {
            --m_iterator;
            return *this;
        }

        type_conversion_iterator operator--(int) {
            return type_conversion_iterator(m_iterator--);
        }
    };


    // Specialization for random access iterators
    template<typename SourceIterator, typename Conversion>
    class type_conversion_iterator<SourceIterator, Conversion,
        std::enable_if_t<std::is_same_v<std::random_access_iterator_tag,
            typename std::iterator_traits<SourceIterator>::iterator_category>>>
    {
        SourceIterator m_iterator;

    public:

        // type_conversion_iterator can be constructed from any other iterator
        type_conversion_iterator(SourceIterator iterator)
            : m_iterator(iterator)
        { }

        // typedefs so type_conversion_iterator can be used in std::iterator_traits:
        using iterator_category = typename std::iterator_traits<SourceIterator>::iterator_category;
        using difference_type = typename std::iterator_traits<SourceIterator>::difference_type;
        using value_type = typename Conversion::output_type;
        using reference = typename Conversion::output_type;
        using pointer = typename Conversion::output_type;
        
        // requirements of std::forward_iterator concept
        type_conversion_iterator() = default;
        type_conversion_iterator(const type_conversion_iterator&) = default;
        ~type_conversion_iterator() = default;

        type_conversion_iterator& operator=(const type_conversion_iterator&) = default;

        reference operator*() const {
            return Conversion::convert(*m_iterator);
        }

        pointer operator->() const {
            return Conversion::convert(*m_iterator);
        }
        
        type_conversion_iterator& operator++() {
            ++m_iterator;
            return *this;
        }
        
        type_conversion_iterator operator++(int) {
            return type_conversion_iterator(m_iterator++);
        }
        
        bool operator==(const type_conversion_iterator& right) const {
            return m_iterator == right.m_iterator;
        }
        
        bool operator!=(const type_conversion_iterator& right) const {
            return m_iterator != right.m_iterator;
        }
        
        // requirements of std::bidirectional_iterator concept
        type_conversion_iterator& operator--() {
            --m_iterator;
            return *this;
        }

        type_conversion_iterator operator--(int) {
            return type_conversion_iterator(m_iterator--);
        }

        // requirements of std::random_access_iterator concept
        type_conversion_iterator& operator+=(difference_type offset) {
            m_iterator += offset;
            return *this;
        }

        type_conversion_iterator operator+(difference_type offset) const {
            return type_conversion_iterator(m_iterator + offset);
        }

        type_conversion_iterator& operator-=(difference_type offset) {
            m_iterator -= offset;
            return *this;
        }

        type_conversion_iterator operator-(difference_type offset) const {
            return type_conversion_iterator(m_iterator + offset);
        }

        difference_type operator-(const type_conversion_iterator& right) const {
            return m_iterator - right.m_iterator;
        }

        reference operator[](const difference_type offset) const {
            return Conversion::convert(m_iterator[offset]);
        }
        
        bool operator<(const type_conversion_iterator& right) const {
            return m_iterator < right.m_iterator;
        }

        bool operator>(const type_conversion_iterator& right) const {
            return m_iterator > right.m_iterator;
        }

        bool operator<=(const type_conversion_iterator& right) const {
            return m_iterator <= right.m_iterator;
        }

        bool operator>=(const type_conversion_iterator& right) const {
            return m_iterator >= right.m_iterator;
        }
    };


    template<typename SourceIterator, typename Conversion>
    type_conversion_iterator<SourceIterator, Conversion> operator+(
        typename type_conversion_iterator<SourceIterator, Conversion>::difference_type n,
        const type_conversion_iterator<SourceIterator, Conversion>& it)
    {
        return it + n;
    }

} // namespace tci
