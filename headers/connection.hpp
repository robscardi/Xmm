#ifndef __GUARD_CONNECTION_HPP
#define __GUARD_CONNECTION_HPP



#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <type_traits>
#include <concepts>


#include "struct.hpp"
#include "src/exception.hpp"

namespace X11{


#define _ORDER 'l'
#define _PROT_MAJOR_VERSION 11
#define _PROT_MINOR_VERSION 0
//#define _SOCAT_DEBUG


#ifdef _SOCAT_DEBUG
        #define _SOCKET_FILE "/tmp/socat-listen"
#else
        #define _SOCKET_FILE "/tmp/.X11-unix/X0"
#endif
#define _AUTH_PROTOCOL "MIT-MAGIC-COOKIE-1\0\0"



template <typename T>
concept ConnectionClass = requires(T t, std::size_t s){
        {t.send([]{struct S{}; return S{};}(), s)} -> std::convertible_to<std::size_t>;
        {t.receive([]{struct S{}; return S{};}(), s)} -> std::convertible_to<std::size_t>;
};


class connection{
        public:
        connection();
        
        template<typename T>
        size_t send(T data, std::size_t size){
                size_t s = write(socket_fd, data, size);
                if (s != size){
                        throw send_error();
                };
                return s;
        };

        template<typename T>
        size_t receive(T data, std::size_t size){
                size_t s = recv(socket_fd, data, size, MSG_DONTWAIT);
                return s;
        };

        size_t generate_next_id(){
                return curr_resource_id++;
        };

        

        private:
        int socket_fd;
        int curr_resource_id = 0;
        X11::connection_reply_header_t header;
        X11::connection_reply_success_body_t body;
        public:
        std::vector<FORMAT> VecFormat;
        std::vector<SCREEN> VecScreen;
        std::vector<DEPTH> VecDepth;
        std::vector<VISUALTYPE> VecVisualtype;
        
          


};

}

#endif
