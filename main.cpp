#include "connection.hpp"
#include "window.hpp"
#include "gcontext.hpp"

int main(void)
{
        try{
        auto con = X11::connection();
        auto opt = std::initializer_list<X11::CARD32>{0xff00ff};

        auto root = con.VecScreen[0].root;
        auto root_visual = con.VecScreen[0].root_visual;
        
        auto gcon = X11::gcontex(con, root, X11::GC_bitmask::graphics_exposures,{0});
        X11::window win(con, root, 0, 0, 320, 240, 0, X11::window::class_::Copy_From_Parent, root_visual, X11::bitmask_value::background_pixel, opt);

        

        } catch(X11::base_exception& e){
                e.Message();
        };


        while (true);
        
        return 0;
};