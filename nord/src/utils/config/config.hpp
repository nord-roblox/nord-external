#pragma once

#include <windows.h>

#include <iostream>
#include <string_view>
#include <unordered_map>
#include <variant>

#include "../../imgui/imgui.h"

constexpr std::int32_t VKEY_MAX = 1024;

namespace nord
{
    namespace settings_types
    {
        typedef std::uint8_t virtual_key;

        constexpr bool is_key_extended( virtual_key key )
        {
            return key == VK_UP || key == VK_LEFT || key == VK_RIGHT || key == VK_DOWN || key == VK_RCONTROL ||
                   key == VK_RMENU || key == VK_LWIN || key == VK_RWIN || key == VK_APPS || key == VK_PRIOR ||
                   key == VK_NEXT || key == VK_END || key == VK_HOME || key == VK_INSERT || key == VK_DELETE ||
                   key == VK_DIVIDE || key == VK_NUMLOCK;
        }

        enum class esp_box_type
        {
            box_static,
            box_dynamic
        };
    }  // namespace settings_types

    class feature
    {
       public:
        std::string serialize();

        template< typename T >
        feature( T value ) : value{ value }
        {
        }

        template< typename T >
        T& get_value()
        {
            return std::get< T >( value );
        }

        template< typename T >
        void set_value( T nvalue )
        {
            value = nvalue;
        }

       private:
        std::variant< bool, float, int, ImColor, settings_types::virtual_key, settings_types::esp_box_type > value;
    };

    class configuration
    {
       public:
        template< typename T >
        T& get( std::string_view feature )
        {
            return feature_map.at( feature ).get_value< T >();
        }

        template< typename T >
        void set( std::string_view feature, T value )
        {
            feature_map.at( feature ).set_value< T >( value );
        }

        // serializes feature_map to readable format
        std::string serialize();

       private:
        std::unordered_map< std::string_view, feature > feature_map = {
            // ui settings
            { "ui_toggle_key", feature{ VK_INSERT } },

            // esp
            { "player_esp", feature{ true } },
            { "box_esp_dynamic", feature{ true } },
            
            { "name_esp", feature{ true } },
            { "autoscale_names", feature{ true } },

            { "render_distance", feature{ 250 } },
            { "ally_color", feature{ ImColor{ 85, 170, 255 } } },
            { "enemy_color", feature{ ImColor{ 255, 170, 255 } } },

            // checks
            { "team_check", feature{ true } },
            { "distance_check", feature{ true } },

            // other
            { "fps", feature{ 60 } },
            { "explorer", feature{ true } },
        };
    };

    extern configuration config_mgr;
}  // namespace nord
