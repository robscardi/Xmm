#ifndef __GUARD_CONNECTION_CPP
#define __GUARD_CONNECTION_CPP

#include "connection.hpp"

X11::connection::connection(){
        //initialize connection data
        X11::connection_request init_data = {0};
                init_data.major_version = _PROT_MAJOR_VERSION;
                init_data.minor_version = _PROT_MINOR_VERSION;
                init_data.order = _ORDER;
                init_data.auth_proto_name_len = 18;
                init_data.auth_proto_data_len = 16;
        //socket connection
        socket_fd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);

        struct sockaddr_un serv_addr = { 0 };
        serv_addr.sun_family = AF_UNIX;
        strcpy(serv_addr.sun_path, _SOCKET_FILE);
        
        connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        
        //reading .Xauthority
        char xauth_cookie[1000];

        auto username = std::string(getlogin());

        FILE *xauth_file = fopen(( "/home/" + username + "/.Xauthority").c_str(), "rb");
        size_t xauth_len = fread(xauth_cookie, 1, sizeof(xauth_cookie), xauth_file);

        fclose(xauth_file);

        char* str = xauth_cookie + xauth_len -16;

        
        send<connection_request*>(&init_data, sizeof(connection_request));
        write(socket_fd, "MIT-MAGIC-COOKIE-1\0\0", 20);
        write(socket_fd, str, 16);
        
        recvfrom(socket_fd, &header, sizeof(connection_reply_header_t), 0, NULL, NULL);
        if (header.success == 1){
                receive<connection_reply_success_body_t*>(&body, sizeof(connection_reply_success_body_t));
                curr_resource_id = body.id_base;

                for(int x = 0; x < body.num_pixmap_formats; x++){
                        FORMAT f;
                        receive<FORMAT*>(&f, sizeof(FORMAT));
                        VecFormat.emplace_back(f);
                };
                for(int x = 0; x <body.num_screens; x++){
                        SCREEN screens;
                        receive<SCREEN*>(&screens, sizeof(SCREEN));
                        for(int y = 0; y < screens.number_of_DEPTH; y++ ){
                                DEPTH d;
                                receive<DEPTH*>(&d, sizeof(DEPTH));
                                for(int z = 0; z < d.number_of_VISUALTYPE; z++){
                                        VISUALTYPE vis;
                                        receive<VISUALTYPE*>(&vis, sizeof(VISUALTYPE));
                                        VecVisualtype.emplace_back(vis);
                                }
                                VecDepth.emplace_back(d);
                        }
                        VecScreen.emplace_back(screens);
                };





        }else if(header.success == 0){
                int lenght = header.len * 4;
                char* failed_connection = new char[lenght];
                receive<char*>(failed_connection, lenght);
                std::string failed_con(failed_connection);
                delete[] failed_connection;
                throw base_exception(__FILE__, __LINE__, std::string("Failed Connection: \n Reason: ") + failed_con);
        }
};


#endif