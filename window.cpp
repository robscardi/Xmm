#ifndef __WINDOW_CPP_GUARD
#define __WINDOW_CPP_GUARD

#include "window.hpp"
using namespace X11;

window::window(connection& con, CARD32 parent, INT16 x, INT16 y, CARD16 width,
                CARD16 height, CARD16 border_width,  CARD16 _class, VISUALID_T visual_id, CARD32 BITMASK, CARD32* options){
	
	properties.BITMASK = BITMASK;
	properties.border_width = border_width;
	properties.x = x;
	properties.y = y;
	properties.width = width;
	properties.height = height;
	properties._class = _class;
	properties.visual_id = visual_id;
	properties.parent = parent;
	properties.id = con.generate_next_id();
	opt_num = 0;
	for(int x = 0; x<sizeof(BITMASK); x++ ){
		if(BITMASK & 1<<x > 0){
			opt_num++;
		}
	}
	CARD16 lenght = sizeof(CreateWindow_PDU) + opt_num*4; 

	request_header header = {
		OPCODE::CreateWindow, 0, lenght +sizeof(request_header)
	};
	con.send<request_header>(&header, sizeof(request_header));
	con.send<CreateWindow_PDU>(&properties, lenght );
	
	
};


window::~window(){
	delete[] option_on_creation;
	UnmapWindow();
}


CARD32* window::create_option_array(std::initializer_list<CARD32> list){
	CARD32* arr = new CARD32[list.size()];
	int x = 0;
	for(auto n : list){
		arr[x] = n;
		x++;
	};
	return arr;
};



#endif