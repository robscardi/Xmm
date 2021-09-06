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
        
        int value_num = 0;
        for (int x = 0; x < sizeof(BITMASK); x++){
                if(mask & 1<<x){
                        value_num++;
                }
        }
        CreateGC_PDU msg{
                id, drawable, mask
        };
        
        request_header head;
        head.major_opcode = OPCODE::CreateGC;
        head.lenght = sizeof(CreateGC_PDU) + value_num*4 +sizeof(request_header);

        c.send<request_header>(&head, sizeof(request_header));
        c.send<CreateGC_PDU>(&msg, sizeof(msg));
        c.send<CARD32>(list_of_options.data(), list_of_options.size());

        
};











#endif