#ifndef __WINDOW_CPP_GUARD
#define __WINDOW_CPP_GUARD

#include "window.hpp"

using namespace X11;

window::window(connection& c, CARD32 parent, INT16 x, INT16 y, CARD16 width,
                CARD16 height, CARD16 border_width,  CARD16 _class, VISUALID visual_id, CARD32 BITMASK, std::initializer_list<CARD32> options):
		con(c),
		options_list(options)
{
	options_list.shrink_to_fit();

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
	window_id = properties.id;

	opt_num = options_list.size();
	
	CARD16 lenght = 8 + opt_num; 

	request_header header = {
		OPCODE::CreateWindow, 0, lenght
	};
	con.send<request_header>(&header, sizeof(request_header));
	con.send<CreateWindow_PDU>(&properties, sizeof(CreateWindow_PDU) );
	con.send<CARD32>(options_list.data(), opt_num*4);
	MapWindow();

	CARD8 response[response_size];
	con.receive<CARD8>(response, response_size);
	/*if(response[0] == 0){
		auto CN = reinterpret_cast<error_struct*>(response);
		throw Server_error(*CN, __FILE__, __LINE__, "Unable to create window" );

	}*/
};


window::~window(){
	std::cout << "Destroying window " << window_id << std::endl;
	//UnmapWindow();
	//DestroyWindow();
};

void window::MapWindow(){
	request_header header {OPCODE::MapWindow, 0, 2};
	con.send<request_header>(&header, sizeof(header));
	con.send<CARD32>(&window_id, 4);
}



void window::UnmapSubwindow(){

};




#endif