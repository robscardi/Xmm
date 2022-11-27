#include "connection.hpp"
#include "window.hpp"
#include "gcontext.hpp"

int main(void)
{
        try{
        auto con = X11::connection();
        auto opt = std::initializer_list<X11::CARD32>{0x0000FF};

        auto root = con.VecScreen[0].root;
        auto root_visual = con.VecScreen[0].root_visual;
        
        auto gcon = X11::gcontex<decltype(con)>(con, root, X11::GC_bitmask::graphics_exposures,{0});
        X11::basic_window<decltype(con)> win(con, root, 0, 0, 320, 240, 0, X11::basic_window<decltype(con)>::_class::Copy_From_Parent, root_visual, X11::bitmask_value::background_pixel, opt);

        while(true);
        }
        catch(X11::base_exception& e){
                e.Message();
        };



        return 0;
};