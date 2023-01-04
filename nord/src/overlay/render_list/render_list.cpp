#include "render_list.hpp"

namespace nord::render
{
    void rectangle::render( ImDrawList* dl )
    {
        ImGui::GetBackgroundDrawList()->AddRect( point1, point2, col );
    }

    void render_list::begin() noexcept
    {
        mutex.lock();
    }

    void render_list::end() noexcept
    {
        mutex.unlock();
    }

    void render_list::clear() noexcept
    {
        list.clear();
    }

    void render_list::draw( ImDrawList* dl )
    {
        for ( const auto& item : list )
            item->render( dl );
    }
}  // namespace nord::render