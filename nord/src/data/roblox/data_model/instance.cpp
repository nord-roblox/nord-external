#include "instance.hpp"

#include "../../process_hook.hpp"

namespace nord::rbx
{
    std::vector< instance > instance::get_children()
    {
        const auto container = process_hook_mgr.mem.proc->read< std::uintptr_t >( get_address() + 0x28 );

        return process_hook_mgr.mem.proc->read_vector< instance >( container );
    }

    instance instance::get_child_by_name( std::string_view name )
    {
        for ( auto& child : get_children() )
        {
            if ( child.name() == name )
                return child;
        }
    }

    instance instance::get_child_by_class_name( std::string_view name )
    {
        for ( auto& child : get_children() )
        {
            if ( child.descriptor().name() == name )
                return child;
        }
    }

    std::string instance::name()
    {
        const auto ptr = process_hook_mgr.mem.proc->read< std::uintptr_t >( get_address() + 0x24 );
        return process_hook_mgr.mem.proc->read_str( ptr );
    }

    class_descriptor instance::descriptor()
    {
        return process_hook_mgr.mem.proc->read< std::uintptr_t >( get_address() + 0xC );
    }

    std::string class_descriptor::name()
    {
        const auto ptr = process_hook_mgr.mem.proc->read< std::uintptr_t >( get_address() + 0x4 );
        return process_hook_mgr.mem.proc->read_str( ptr );
    }
}  // namespace nord::rbx