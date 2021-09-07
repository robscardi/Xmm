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
	
	CARD16 lenght = sizeof(CreateWindow_PDU) + opt_num*4; 

	request_header header = {
		OPCODE::CreateWindow, 0, lenght +sizeof(request_header)
	};
	con.send<request_header>(&header, sizeof(request_header));
	con.send<CreateWindow_PDU>(&properties, sizeof(CreateWindow_PDU) );
	con.send<CARD32>(options_list.data(), opt_num*4);
	

	CARD8 response[response_size];
	con.receive<CARD8>(response, response_size);
	if(response[0] == 16){
		auto CN = reinterpret_cast<CreateNotify*>(response);
		parent = CN->parent;
		MapWindow();
	}else if(response[0] == 0){
		auto CN = reinterpret_cast<error_struct*>(response);
		throw Server_error(*CN, __FILE__, __LINE__, "Unable to create window" );

	}
};


window::~window(){
	delete[] option_on_creation;
	std::cout << "Destroying window " << window_id << std::endl;
	//UnmapWindow();
};

void window::MapWindow(){
	request_header header {OPCODE::MapWindow, 0, (CARD16)(sizeof(request_header) +4)};
	con.send<request_header>(&header, sizeof(header));
	con.send<CARD32>(&window_id, 4);
}



void window::UnmapSubwindow(){

};




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