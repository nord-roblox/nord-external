#pragma once

#include "instance.hpp"
#include "player.hpp"

namespace nord::rbx
{
    class players : public instance
    {
        using instance::instance;

       public:
        player get_local_player() const;

       private:
    };
}  // namespace nord::rbx