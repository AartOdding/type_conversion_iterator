#pragma once

#include <memory>
#include <utility>


namespace tci
{
    namespace conversions
    {
        
        template<typename K, typename V>
        struct get_pointer_to_second
        {
            using input_type = std::pair<K, V>;
            using output_type = V*;

            static output_type convert(input_type& input)
            {
                return &input.second;
            }
        };

        template<typename K, typename V>
        struct get_pointer_to_second<K, V*>
        {
            using input_type = std::pair<K, V*>;
            using output_type = V*;

            static output_type convert(input_type& input)
            {
                return input.second;
            }
        };

        template<typename K, typename V>
        struct get_pointer_to_second<K, std::unique_ptr<V>>
        {
            using input_type = std::pair<K, std::unique_ptr<V>>;
            using output_type = V*;

            static output_type convert(input_type& input)
            {
                return input.second.get();
            }
        };

        template<typename K, typename V>
        struct get_pointer_to_second<K, std::shared_ptr<V>>
        {
            using input_type = std::pair<K, std::shared_ptr<V>>;
            using output_type = V*;

            static output_type convert(input_type& input)
            {
                return input.second.get();
            }
        };


        //-------------------------------------------------------------------------

        
        template<typename K, typename V>
        struct get_const_pointer_to_second
        {
            using input_type = std::pair<K, V>;
            using output_type = const V*;

            static output_type convert(const input_type& input)
            {
                return &input.second;
            }
        };

        template<typename K, typename V>
        struct get_const_pointer_to_second<K, V*>
        {
            using input_type = std::pair<K, V*>;
            using output_type = const V*;

            static output_type convert(const input_type& input)
            {
                return input.second;
            }
        };

        template<typename K, typename V>
        struct get_const_pointer_to_second<K, std::unique_ptr<V>>
        {
            using input_type = std::pair<K, std::unique_ptr<V>>;
            using output_type = const V*;

            static output_type convert(const input_type& input)
            {
                return input.second.get();
            }
        };

        template<typename K, typename V>
        struct get_const_pointer_to_second<K, std::shared_ptr<V>>
        {
            using input_type = std::pair<K, std::shared_ptr<V>>;
            using output_type = const V*;

            static output_type convert(const input_type& input)
            {
                return input.second.get();
            }
        };

    } // namespace conversions

} // namespace tci
