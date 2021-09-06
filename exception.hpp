#ifndef __EXCEPTION_HPP_GUARD
#define __EXCEPTION_HPP_GUARD

#include <exception>
#include <string>
#include <iostream>
#include "struct.hpp"


using namespace X11;
class base_exception : public std::exception{
        public:
        base_exception(const wchar_t* file, int line) :
                File(file),
                Line(line){};
        std::wstring GetFile(){
                return File;
        };
        int GetLine(){
                return Line;
        };
        

        virtual void Message(std::string s){
                std::cout << s;
        };

        protected:
        std::wstring File;
        int Line;
};

class Server_error : public base_exception{
        public:
        Server_error(const wchar_t* file, int line, error_struct er_strct):

                base_exception(file, line),
                error_(er_strct)
                {
                        switch(error_.code){
                                case 1 :
                                error_name = "Request";
                                case 2 :
                                error_name = "Value";
                                case 3 :
                                error_name = "Window";
                                case 4 :
                                error_name = "Pixmap";
                                case 5 :
                                error_name = "atom";
                                case 6 : 
                                error_name = "Cursor";
                                case 7 :
                                error_name = "Font";
                                case 8 :
                                error_name = "Match";
                                case 9 :
                                error_name = "Drawable";
                                case 10 :
                                error_name = "Access";
                                case 11 :
                                error_name = "Alloc";
                                case 12 :
                                error_name = "Colormap";
                                case 13 : 
                                error_name = "Graphical Context";
                                case 14 :
                                error_name = "IDChoice" ;
                                case 15 :
                                error_name = "Name";
                                case 16 :
                                error_name = "Lenght";
                                case 17 :
                                error_name = "Implementation";
                        }
                        error_name += " error";
                };
        
        void Message(){
                using namespace std;
                cout << "Server Error" << endl;
                cout << "Error Type: " << error_name << endl;
        };


        protected:
        error_struct error_;
        std::string error_name;
};


#endif