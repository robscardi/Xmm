#ifndef __WINDOW_HPP_GUARD
#define __WINDOW_HPP_GUARD
#include "connection.hpp"
#include "struct.hpp"
#include <memory>
#include <initializer_list>

namespace X11{

enum bitmask_value{
        background_pixmap = 1,
        background_pixel = 1<<1,
        border_pixmap = 1<<2,
        border_pixel = 1<<3,
        bit_gravity = 1<<4,
        win_gravity = 1<<5,
        backing_store = 1<<6,
        backing_planes = 1<<7,
        backing_pixel = 1<<8,
        override_redirect = 1<<9,
        save_under = 1<<10,
        event_mask = 1<<11,
        do_not_propagate_mask = 1<<12,
        colormap = 1<<13,
        cursor = 1<<14
};

enum backgound_pixmap : CARD32{
        None = 0,
        ParentRelative
};

enum backing_store : CARD32{
        NotUseful = 0,
        WhenMapped,
        Always
};




typedef struct __attribute__((packed)) {
        CARD32 id;
        CARD32 parent;
        INT16 x, y;
        CARD16 width, height;
        CARD16 border_width;
        CARD16 _class;
        VISUALID_T visual_id;
        CARD32 BITMASK;
}CreateWindow_PDU;



class window{
        public:
        window(X11::connection& con, CARD32 parent, INT16 x, INT16 y, CARD16 width,
                CARD16 height, CARD16 border_width, CARD16 _class, VISUALID_T visual_id, CARD32 BITMASK, CARD32* options);
        window(X11::connection& con, CreateWindow_PDU& win_req, CARD32* options);
        window(window& win) = delete;
        static constexpr CARD32* create_option_array(std::initializer_list<CARD32>);
        void MapWindow();
        void UnmapWindow();
        void MapSubwindow();
        void UnmapSubwindow();


        ~window();
        private:
        CreateWindow_PDU properties;
        CARD32* option_on_creation; 
        int opt_num;


};




}



#endif