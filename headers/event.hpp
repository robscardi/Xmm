#ifndef __EVENT_HPP_GUARD
#define __EVENT_HPP_GUARD

#include "struct.hpp"

namespace X11{
enum events_code : CARD32 {
        KeyPress_ = 1,
        KeyRelease = 1<<1,
        ButtonPress = 1<<2,
        ButtonRelease = 1<<3,
        EnterWindow = 1<<4,
        LeaveWindow = 1<<5,
        PointerMotion =  1<<6,
        PointerMotionHint = 1<<7,
        Button1Motion = 1<<8,
        Button2Motion = 1<<9,
        Button3Motion = 1<<10,
        Button5Motion = 1<<11,
        ButtonMotion = 1<<12,
        KeymapState = 1<<13,
        Exposure = 1<<14,
        StructureNotify = 1<<15,
        ResizeRedirect = 1<<16,
        SubstructureNotify = 1<<17,
        SubstructureRedirect = 1<<18,
        FocusChange = 1<<19,
        PropertyChange = 1<<20,
        ColormapChange = 1<<21,
        OwnerGrabButton = 1<<22
};


typedef struct{
	CARD8 code;
        WINDOW parent;
	WINDOW window_id;
	INT16 x, y;
	CARD16 width, height, border_width;
	BOOL override_redirect;
	CARD8 pad2[9];
}CreateNotify;

typedef struct{
        CARD8 code;
        CARD8 keycode;
        CARD16 sequence_number;
        TIMESTAMP time;
        WINDOW root;
        WINDOW event;
        WINDOW child;
        INT16 root_x, root_y, event_x, event_y;
        CARD16 state;
        BOOL same_screen;
        CARD8 pad;
}KeyPress;





















};

#endif
