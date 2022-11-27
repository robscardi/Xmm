#ifndef __WINDOW_CPP_GUARD
#define __WINDOW_CPP_GUARD

#include "window.hpp"

using namespace X11;

template<ConnectionClass connection>
basic_window<connection>::basic_window(connection& c, CARD32 parent, INT16 x, INT16 y, CARD16 width,
		CARD16 height, CARD16 border_width,  CARD16 _class, VISUALID visual_id, CARD32 BITMASK, std::initializer_list<CARD32> options):
		options_list(options),
		con(c)
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
	con.template send<request_header*>(&header, sizeof(request_header));
	con.template send<create_window_PDU*>(&properties, sizeof(create_window_PDU) );
	con.template send<CARD32*>(options_list.data(), opt_num*4);
	CARD8 response[response_size] = {1};
	con.template receive<CARD8*>(response, response_size);
	if(response[0] == 16){
		auto CN = reinterpret_cast<CreateNotify*>(response);
		parent = CN->parent;
		MapWindow();
	}else if(response[0] == 0){
		auto CN = reinterpret_cast<error_struct*>(response);
		throw Server_error(*CN, __FILE__, __LINE__, "Unable to create window" );

	}else MapWindow();

};

template<ConnectionClass connection>
basic_window<connection>::~basic_window(){
	std::cout << "Destroying window " << window_id << std::endl;
	UnmapWindow();
};

template<ConnectionClass connection>
void basic_window<connection>::MapWindow(){
	request_header header {OPCODE::MapWindow, 0, 2};
	con.template send<request_header*>(&header, sizeof(header));
	con.template send<CARD32*>(&window_id, 4);
};

template<ConnectionClass connection>
void basic_window<connection>::UnmapWindow(){
	request_header req {OPCODE::UnmapWindow, 0, 2};
	con.template send<request_header*>(&req, sizeof(request_header));
	con.template send<WINDOW*>(&window_id, sizeof(WINDOW));
};


template<ConnectionClass connection>
void basic_window<connection>::MapSubwindow(){
	request_header req {OPCODE::MapSubWindows, 0, 2};
	con.template send<request_header*>(&req, sizeof(request_header));
	con.template send<WINDOW*>(&window_id, sizeof(WINDOW));
};

template<ConnectionClass connection>
void basic_window<connection>::UnmapSubwindow(){
	request_header req {OPCODE::UnmapSubwindows, 0, 2};
	con.template send<request_header*>(&req, sizeof(request_header));
	con.template send<WINDOW*>(&window_id, sizeof(WINDOW));
};

template<ConnectionClass connection>
void basic_window<connection>::DestroyWindow(){
	request_header req {OPCODE::DestroyWindow, 0, 2};
	con.template send<request_header*>(&req, sizeof(request_header));
	con.template send<WINDOW*>(&window_id, sizeof(WINDOW));
};

template<ConnectionClass connection>
void basic_window<connection>::DestroySubwindows(){
	request_header req {OPCODE::DestroySubwindows, 0, 2};
	con.template send<request_header*>(&req, sizeof(request_header));
	con.template send<WINDOW*>(&window_id, sizeof(WINDOW));
};








#endif