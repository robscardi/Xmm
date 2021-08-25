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
                init_data.auth_proto_data_len = 20;
        //socket connection
        socket_fd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);

        struct sockaddr_un serv_addr = { 0 };
        serv_addr.sun_family = AF_UNIX;
        strcpy(serv_addr.sun_path, _SOCKET_FILE);
        
        int c = connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        
        //reading .Xauthority
        char xauth_cookie[1000];

        FILE *xauth_file = fopen("/home/roberto/.Xauthority", "rb");
        size_t xauth_len = fread(xauth_cookie, 1, sizeof(xauth_cookie), xauth_file);

        fclose(xauth_file);

        char* str = xauth_cookie + xauth_len -16;

        
        write(socket_fd, &init_data, sizeof(connection_request));
        write(socket_fd, "MIT-MAGIC-COOKIE-1\0\0", 20);
        write(socket_fd, str, 16);
        
        connection_reply_header_t head;
        int m = recvfrom(socket_fd, &head, sizeof(connection_reply_header_t), 0, NULL, NULL);
        std::cout << header.success << std::endl;
}

#endif