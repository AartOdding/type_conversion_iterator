#pragma once

#include "conversions.hpp"
#include "type_conversion_iterator.hpp"


template<typename Container>
class pointer_view
{
    using iterator = type_conversion_iterator<typename Container::iterator, 
        pointer_conversion<typename Container::value_type>>;
    
    iterator m_begin;
    iterator m_end;

public:

    pointer_view(Container& container)
        : m_begin(container.begin())
        , m_end(container.end())
    { }

    iterator begin() const
    {
        return m_begin;
    }

    iterator end() const
    {
        return m_end;
    }
};

template<typename Container>
class const_pointer_view
{
    using iterator = type_conversion_iterator<typename Container::const_iterator, 
        const_pointer_conversion<typename Container::value_type>>;

    iterator m_begin;
    iterator m_end;

public:

    const_pointer_view(const Container& container)
        : m_begin(container.begin())
        , m_end(container.end())
    { }

    iterator begin() const
    {
        return m_begin;
    }

    iterator end() const
    {
        return m_end;
    }
};

template<typename Container>
class reference_view
{
    using iterator = type_conversion_iterator<typename Container::iterator, 
        reference_conversion<typename Container::value_type>>;
    
    iterator m_begin;
    iterator m_end;

public:

    reference_view(Container& container)
        : m_begin(container.begin())
        , m_end(container.end())
    { }

    iterator begin() const
    {
        return m_begin;
    }

    iterator end() const
    {
        return m_end;
    }
};

template<typename Container>
class const_reference_view
{
    using iterator = type_conversion_iterator<typename Container::const_iterator, 
        const_reference_conversion<typename Container::value_type>>;

    iterator m_begin;
    iterator m_end;

public:

    const_reference_view(const Container& container)
        : m_begin(container.begin())
        , m_end(container.end())
    { }

    iterator begin() const
    {
        return m_begin;
    }

    iterator end() const
    {
        return m_end;
    }
};

