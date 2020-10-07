#pragma once

#include <memory>
#include <vector>



template<typename FROM, typename TO>
struct converter
{

};


//------- raw pointers


template<typename T>
struct converter<T*, T&>
{
    using from_type = T*;
    using to_type = T&;

    to_type operator()(const from_type& from_value)
    {
        std::cout << "type 1" << std::endl;
        return *from_value;
    }
};


template<typename T>
struct converter<T*, const T&>
{
    using from_type = T*;
    using to_type = const T&;

    to_type operator()(const from_type& from_value)
    {
        std::cout << "type 2" << std::endl;
        return *from_value;
    }
};


//------- unique pointers


template<typename T>
struct converter<T&, std::unique_ptr<T>>
{
    using to_type = T&;
    using from_type = std::unique_ptr<T>;

    to_type operator()(const from_type& from_value)
    {
        std::cout << "type 3" << std::endl;
        return *from_value;
    }
};


template<typename T>
struct converter<const T&, std::unique_ptr<T>>
{
    using to_type = const T&;
    using from_type = std::unique_ptr<T>;

    to_type operator()(const from_type& from_value)
    {
        std::cout << "type 4" << std::endl;
        return *from_value;
    }
};


template<typename UnderlyingType>
class reference_view
{
public:

    using presented_data_type = PresentedType;
    using underlying_data_type = UnderlyingType;
    using container_type = std::vector<underlying_data_type>;

    converted_view(container_type& data)
    {

    }

private:


};

template<typename PresentedType, typename UnderlyingType>
class converted_const_view
{
public:

    using presented_data_type = PresentedType;
    using underlying_data_type = UnderlyingType;
    using container_type = std::vector<underlying_data_type>;

    converted_view(const container_type& data)
    {

    }

private:


};

// iterators

class fake_iterator
{
public:

    using iterator_category = std::random_access_iterator_tag;
    using value_type = double;
    using difference_type = int;
    using pointer = double*;
    using reference = double&;

    fake_iterator(int position);

    
    fake_iterator operator++() { fake_iterator i = *this; ptr_++; return i; }
    fake_iterator operator++(int) { ptr_++; return *this; }
    reference operator*() { return *ptr_; }
    pointer operator->() { return ptr_; }
    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

}



template<typename PresentedType, typename UnderlyingType>
class converting_iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = PresentedType;
    using difference_type = std::vector<UnderlyingType>::difference_type;
    using pointer = PresentedType*;
    using reference = PresentedType&;


};

template<typename PresentedType, typename UnderlyingType>
class converting_const_iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int*;
    using reference = int&;


};

/*
// Specialization where T is const
template <typename T>
class item_view<const T, std::unique_ptr<T>>
{
public:

    item_view(std::vector<std::unique_ptr<T>>)

private:

    std::vector<std::unique_ptr<T>>::

};


// Specialization where T is const
template <typename T>
class item_view<T, std::unique_ptr<T>>
{
public:

    using visible_type = T;
    using stored_type = std::unique_ptr<T>;
    using vector_type = std::vector<stored_type>;

    item_view(vector_type& vector);

private:

    std::vector<std::unique_ptr<T>>::

};
*/