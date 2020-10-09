#pragma once

#include <memory>


template<typename T>
struct pointer_conversion
{
    using input_type = T;
    using output_type = T*;

    static output_type convert(input_type& input)
    {
        return &input;
    }
};

template<typename T>
struct pointer_conversion<T*>
{
    using input_type = T*;
    using output_type = T*;

    static output_type convert(input_type& input)
    {
        return input;
    }
};

template<typename T>
struct pointer_conversion<std::unique_ptr<T>>
{
    using input_type = std::unique_ptr<T>;
    using output_type = T*;

    static output_type convert(input_type& input)
    {
        return input.get();
    }
};

template<typename T>
struct pointer_conversion<std::shared_ptr<T>>
{
    using input_type = std::shared_ptr<T>;
    using output_type = T*;

    static output_type convert(input_type& input)
    {
        return input.get();
    }
};


template<typename T>
struct const_pointer_conversion
{
    using input_type = T;
    using output_type = const T*;

    static output_type convert(const input_type& input)
    {
        return &input;
    }
};

template<typename T>
struct const_pointer_conversion<T*>
{
    using input_type = T*;
    using output_type = const T*;

    static output_type convert(const input_type& input)
    {
        return input;
    }
};

template<typename T>
struct const_pointer_conversion<std::unique_ptr<T>>
{
    using input_type = std::unique_ptr<T>;
    using output_type = const T*;

    static output_type convert(const input_type& input)
    {
        return input.get();
    }
};

template<typename T>
struct const_pointer_conversion<std::shared_ptr<T>>
{
    using input_type = std::shared_ptr<T>;
    using output_type = const T*;

    static output_type convert(const input_type& input)
    {
        return input.get();
    }
};


template<typename T>
struct reference_conversion
{
    using input_type = T;
    using output_type = T&;

    static output_type convert(input_type& input)
    {
        return input;
    }
};

template<typename T>
struct reference_conversion<T*>
{
    using input_type = T*;
    using output_type = T&;

    static output_type convert(input_type& input)
    {
        return *input;
    }
};

template<typename T>
struct reference_conversion<std::unique_ptr<T>>
{
    using input_type = std::unique_ptr<T>;
    using output_type = T&;

    static output_type convert(input_type& input)
    {
        return *input.get();
    }
};

template<typename T>
struct reference_conversion<std::shared_ptr<T>>
{
    using input_type = std::shared_ptr<T>;
    using output_type = T&;

    static output_type convert(input_type& input)
    {
        return *input.get();
    }
};


template<typename T>
struct const_reference_conversion
{
    using input_type = T;
    using output_type = const T&;

    static output_type convert(const input_type& input)
    {
        return input;
    }
};

template<typename T>
struct const_reference_conversion<T*>
{
    using input_type = T*;
    using output_type = const T&;

    static output_type convert(const input_type& input)
    {
        return *input;
    }
};

template<typename T>
struct const_reference_conversion<std::unique_ptr<T>>
{
    using input_type = std::unique_ptr<T>;
    using output_type = const T&;

    static output_type convert(const input_type& input)
    {
        return *input.get();
    }
};

template<typename T>
struct const_reference_conversion<std::shared_ptr<T>>
{
    using input_type = std::shared_ptr<T>;
    using output_type = const T&;

    static output_type convert(const input_type& input)
    {
        return *input.get();
    }
};