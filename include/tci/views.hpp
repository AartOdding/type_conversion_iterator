#pragma once

#include <map>

#include <tci/conversions/get_pointer_to_second.hpp>
#include <tci/conversions/get_pointer.hpp>
#include <tci/type_conversion_iterator.hpp>


namespace tci
{

    template<typename Container>
    class view
    {
        using iterator = type_conversion_iterator<typename Container::iterator, 
            conversions::get_pointer<typename Container::value_type>>;
        
        iterator m_begin;
        iterator m_end;

    public:

        view(Container& container)
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
    class const_view
    {
        using iterator = type_conversion_iterator<typename Container::const_iterator, 
            conversions::get_const_pointer<typename Container::value_type>>;

        iterator m_begin;
        iterator m_end;

    public:

        const_view(const Container& container)
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
    class values_view
    {
        using key_type = typename Container::key_type;
        using mapped_type = typename Container::mapped_type;

        using iterator = type_conversion_iterator<typename Container::iterator, 
            conversions::get_pointer_to_second<const key_type, mapped_type>>;
        
        iterator m_begin;
        iterator m_end;

    public:

        values_view(Container& container)
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
    class const_values_view
    {
        using key_type = typename Container::key_type;
        using mapped_type = typename Container::mapped_type;

        using iterator = type_conversion_iterator<typename Container::const_iterator, 
            conversions::get_const_pointer_to_second<const key_type, mapped_type>>;

        iterator m_begin;
        iterator m_end;

    public:

        const_values_view(const Container& container)
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

} // namespace tci
