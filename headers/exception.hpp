#ifndef __EXCEPTION_HPP_GUARD
#define __EXCEPTION_HPP_GUARD

#include <exception>
#include <string>
#include <iostream>
#include "struct.hpp"


namespace X11{

class base_exception : public std::exception{
        public:
        base_exception(const char* file, int line, std::string mes) :
                File(file),
                Line(line),
                message(mes){};
        std::string GetFile(){
                return File;
        };
        int GetLine(){
                return Line;
        };
        

        virtual void Message(){
                std::cout << "Message: ";
                if (message.size())
                        std::cout << message;
                else std::cout << "NONE" <<std::endl; 
        };

        protected:
        std::string File;
        int Line;
        std::string message;
};

class Server_error : public base_exception{
        public:
        Server_error(error_struct er_strct, const char* file, int line, std::string message = nullptr):

                base_exception(file, line, message),
                error_(er_strct)
                {
                        switch(error_.code){
                                case 1 :
                                error_name = "Request";
                                break;
                                case 2 :
                                error_name = "Value";
                                break;
                                case 3 :
                                error_name = "Window";
                                break;
                                case 4 :
                                error_name = "Pixmap";
                                break;
                                case 5 :
                                error_name = "atom";
                                break;
                                case 6 : 
                                error_name = "Cursor";
                                break;
                                case 7 :
                                error_name = "Font";
                                break;
                                case 8 :
                                error_name = "Match";
                                break;
                                case 9 :
                                error_name = "Drawable";
                                break;
                                case 10 :
                                error_name = "Access";
                                break;
                                case 11 :
                                error_name = "Alloc";
                                break;
                                case 12 :
                                error_name = "Colormap";
                                break;
                                case 13 : 
                                error_name = "Graphical Context";
                                break;
                                case 14 :
                                error_name = "IDChoice" ;
                                break;
                                case 15 :
                                error_name = "Name";
                                break;
                                case 16 :
                                error_name = "Lenght";
                                break;
                                case 17 :
                                error_name = "Implementation";
                                break;
                                default: 
                                error_name = "Unknown Error";
                                break;
                        }
                };
        
        void Message(){
                using namespace std;
                cout << "Server Error" << endl;
                cout << "Error Type: " << error_name << endl;
                cout << "Sequence Number = " << error_.sequence_number << endl;
                cout << "Message: ";
                if (message.size())
                        cout << message << endl;
                else cout << "NONE" <<endl;
                cout << "File : " << File << "    " << "Line : " << Line << endl;
        };


        protected:
        error_struct error_;
        std::string error_name;
};


class send_error : public base_exception{
        
        public:
        send_error()
        :
        base_exception("connection.hpp", 0, "error occured while sending data")
        {};
};






}
#endif
