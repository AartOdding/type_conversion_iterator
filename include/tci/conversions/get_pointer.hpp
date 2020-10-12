#pragma once

#include <memory>


namespace tci
{
    namespace conversions
    {
        
        template<typename T>
        struct get_pointer
        {
            using input_type = T;
            using output_type = T*;

            static output_type convert(input_type& input)
            {
                return &input;
            }
        };

        template<typename T>
        struct get_pointer<T*>
        {
            using input_type = T*;
            using output_type = T*;

            static output_type convert(input_type& input)
            {
                return input;
            }
        };

        template<typename T>
        struct get_pointer<std::unique_ptr<T>>
        {
            using input_type = std::unique_ptr<T>;
            using output_type = T*;

            static output_type convert(input_type& input)
            {
                return input.get();
            }
        };

        template<typename T>
        struct get_pointer<std::shared_ptr<T>>
        {
            using input_type = std::shared_ptr<T>;
            using output_type = T*;

            static output_type convert(input_type& input)
            {
                return input.get();
            }
        };


        //-------------------------------------------------------------------------


        template<typename T>
        struct get_const_pointer
        {
            using input_type = T;
            using output_type = const T*;

            static output_type convert(const input_type& input)
            {
                return &input;
            }
        };

        template<typename T>
        struct get_const_pointer<T*>
        {
            using input_type = T*;
            using output_type = const T*;

            static output_type convert(const input_type& input)
            {
                return input;
            }
        };

        template<typename T>
        struct get_const_pointer<std::unique_ptr<T>>
        {
            using input_type = std::unique_ptr<T>;
            using output_type = const T*;

            static output_type convert(const input_type& input)
            {
                return input.get();
            }
        };

        template<typename T>
        struct get_const_pointer<std::shared_ptr<T>>
        {
            using input_type = std::shared_ptr<T>;
            using output_type = const T*;

            static output_type convert(const input_type& input)
            {
                return input.get();
            }
        };

    } // namespace conversions
} // namespace tci
