#ifndef __GCONTEXT_HPP_GUARD
#define __GCONTEXT_HPP_GUARD


#include "struct.hpp"
#include "connection.hpp"
#include <vector>
#include <initializer_list>

namespace X11{

enum GC_bitmask : CARD32 {
        function = 1<< 0,
        plane_mask = 1<<1,
        foreground = 1<<2,
        background = 1<<3,
        line_width = 1<<4,
        line_style = 1<<5, 
        cap_style = 1<<6,
        join_style = 1<<7,
        fill_style = 1<<8,
        fill_rule = 1<<9,
        tile = 1<<10,
        stipple = 1<<11,
        tile_stipple_x_origin = 1<<12,
        tile_stipple_y_origin = 1<<13,
        font = 1<<14,
        subwindow_mode = 1<<15,
        graphics_exposures = 1<<16,
        clip_x_origin = 1<<17,
        clip_y_origin = 1<<18,
        clip_mask = 1<<19,
        dash_offset = 1<<20,
        dashes = 1<<21,
        arc_mode = 1<<22
};




typedef struct __attribute((packed)){
        GCONTEXT id;
        DRAWABLE drawable;
        BITMASK bitmask;
}CreateGC_PDU;




class gcontex{
        public:
        gcontex(connection& con, DRAWABLE drawable, BITMASK bitmask, std::initializer_list<CARD32> init_list );

        private:
        DRAWABLE drawable;
        connection& c;
        GCONTEXT id;
        BITMASK mask;
        std::vector<CARD32> list_of_options;
};



}


#endif