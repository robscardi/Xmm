#ifndef __GCONTEX_CPP_GUARD
#define __GCONTEX_CPP_GUARD


#include "gcontext.hpp"

X11::gcontex::gcontex(connection& con, DRAWABLE drawable, BITMASK bitmask, std::initializer_list<CARD32> init_list)
        :
        mask(bitmask),
        list_of_options(init_list),
        c(con),
        drawable(drawable)
{
        list_of_options.shrink_to_fit();
        id = c.generate_next_id();
        


        CreateGC_PDU msg{
                id, drawable, mask
        };
        
        request_header head = {0};
        head.major_opcode = OPCODE::CreateGC;
        head.lenght = list_of_options.size() +sizeof(request_header);

        c.send<request_header>(&head, sizeof(request_header));
        c.send<CreateGC_PDU>(&msg, sizeof(CreateGC_PDU));
        c.send<CARD32>(list_of_options.data(), list_of_options.size()*sizeof(CARD32));
	
        CARD8 response[response_size];
	con.receive<CARD8>(response, response_size);

	/*if(response[0] == 0){
		auto CN = reinterpret_cast<error_struct*>(response);
		throw Server_error(*CN, __FILE__, __LINE__, "Unable to create Graphical Context" );

	}*/


};











#endif