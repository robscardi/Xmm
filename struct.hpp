#ifndef __GUARD_STRUCT_HPP
#define __GUARD_STRUCT_HPP
#include <cstdint>



namespace X11{


#define response_size 32



enum OPCODE : int{
	CreateWindow = 1,
	ChangeWindowAttribute,
	GetWindowAttribute,
	DestroyWindow,
	DestroySubwindows,
	ChangeSaveSet,
	ReparentWindow,
	MapWindow,
	MapSubWindows,
	UnmapWindow,
	UnmapSubwindows,
	ConfigureWindow,
	CirculateWindow,
	GetGeometry,
	QueryTree,
	InternAtom,
	


	//*****

	CreateGC = 55


};




typedef int8_t INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;

typedef uint8_t CARD8;
typedef uint16_t CARD16;
typedef uint32_t CARD32;
typedef uint64_t CARD64;

typedef CARD32 WINDOW;
typedef CARD8 BOOL;
typedef CARD32 PIXMAP;
typedef CARD32 COLORMAP;
typedef CARD32 CURSOR;
typedef CARD32 VISUALID;

typedef CARD8 BITGRAVITY;
typedef CARD8 WINGRAVITY;

typedef CARD32 TIMESTAMP;
typedef CARD32 BITMASK;
typedef CARD32 GCONTEXT;
typedef CARD32 DRAWABLE;
typedef CARD32 FONTABLE;
typedef CARD32 ATOM;


typedef struct {
	CARD8 code;
	CARD8 pad;
	CARD16 data;
}response_struct;

typedef struct  {
    uint8_t order;
    uint8_t pad1;
    uint16_t major_version, minor_version;
    uint16_t auth_proto_name_len;
    uint16_t auth_proto_data_len;
    uint16_t pad2;
} connection_request;


typedef struct  {
    uint32_t root_id;
    uint32_t colormap;
    uint32_t white, black;
    uint32_t input_mask;
    uint16_t width, height;
    uint16_t width_mm, height_mm;
    uint16_t maps_min, maps_max;
    uint32_t root_visual_id;
    uint8_t backing_store;
    uint8_t save_unders;
    uint8_t depth;
    uint8_t allowed_depths_len;
} screen_t;


typedef struct  {
    uint8_t depth;
    uint8_t bpp;
    uint8_t scanline_pad;
    uint8_t pad[5];
} pixmap_format_t;


typedef struct  {
    uint32_t release;
    uint32_t id_base, id_mask;
    uint32_t motion_buffer_size;
    uint16_t vendor_len;
    uint16_t request_max;
    uint8_t num_screens;
    uint8_t num_pixmap_formats;
    uint8_t image_byte_order;
    uint8_t bitmap_bit_order;
    uint8_t scanline_unit, scanline_pad;
    uint8_t keycode_min, keycode_max;
    uint32_t pad;
    char vendor_string[20];
} connection_reply_success_body_t;


typedef struct  {
    uint8_t success;
    uint8_t pad;
    uint16_t major_version, minor_version;
    uint16_t len;
} connection_reply_header_t;


typedef struct  {
    	uint8_t group;
    	uint8_t bits;
    	uint16_t colormap_entries;
    	uint32_t mask_red, mask_green, mask_blue;
    	uint32_t pad;
} visual_t;


typedef struct {
	CARD8 major_opcode;
	CARD8 pad;
	CARD16 lenght;
}request_header;


typedef struct {
	CARD8 Error;
	CARD8 code;
	CARD16 sequence_number;
	CARD32 error_data;
	CARD8 minor_opcode;
	CARD16 major_opcode;
}error_struct;

typedef struct {
	CARD8 depth;
	CARD8 bits_per_pixel;
	CARD8 scanline_pad;
	CARD8 unused[5];
}FORMAT;


typedef struct {
	WINDOW root;
	COLORMAP default_colormap;
	CARD32 white_pixel;
	CARD32 black_pixel;
	CARD32 current_input_mask;
	CARD16 width_in_pixel;
	CARD16 height_in_pixel;
	CARD16 width_in_millimeter;
	CARD16 height_in_millimeter;
	CARD16 min_installed_maps;
	CARD16 max_installed_maps;
	VISUALID root_visual;
	CARD8 backing_store;
	BOOL saves_under;
	CARD8 root_depth;
	CARD8 number_of_DEPTH;
}SCREEN;
typedef struct {
	CARD8 depth;
	CARD8 pad;
	CARD16 number_of_VISUALTYPE;
	CARD32 pad2;
}DEPTH;

typedef struct{
	VISUALID visual_id;
	CARD8 class_;
	CARD8 bits_per_rgb_value;
	CARD16 colormap_entries;
	CARD32 red_mask;
	CARD32 green_mask;
	CARD32 blue_mask;
	CARD32 pad;
}VISUALTYPE;












}



#endif