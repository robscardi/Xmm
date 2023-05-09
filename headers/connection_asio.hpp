#ifndef __ASIOCONNECT_HPP_GUARD
#define __ASIOCONNECT_HPP_GUARD

#include <cstdlib>
#include <asio/io_service.hpp>
#include <asio/local/stream_protocol.hpp>


#include "struct.hpp"
#include "headers/exception.hpp"


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



namespace X11{


class asio_connect{
        
        public:
        asio_connect();
        ~asio_connect();

        template <typename T>
        std::size_t send(T t, std::size_t s){
                auto buffer = asio::const_buffer(t, s);
                socket.send(buffer);
                return s;
        };

        template <typename T>
        std::size_t receive(T t, std::size_t s){
                auto buffer = asio::mutable_buffer(t, s);
                socket.receive(buffer);
                return s;
        };


        private:
        asio::io_service io_serv;
        asio::local::stream_protocol::socket socket;


        std::vector<xPixmapFormat> VecFormat;
        std::vector<xWindowRoot> VecScreen;
        std::vector<xDepth> VecDepth;
        std::vector<xVisualType> VecVisualType;

        std::string VendorString; 

        
};



}



#endif
