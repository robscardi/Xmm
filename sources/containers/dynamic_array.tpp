#ifndef __DYNAMIC_ARRAY_CPP
#define __DYNAMIC_ARRAY_CPP


#include <memory>
#include <memory_resource>
#include <algorithm>
#include <string>

#ifdef __INCLUDE__ASIO
#include <asio/buffer.hpp>
#endif

namespace X11{

template<typename T>
  concept TriviallyDestructible = std::is_trivially_destructible<T>::value;


template <TriviallyDestructible T, typename allocator = std::pmr::polymorphic_allocator<T>>
class basic_dynamic_array{

        public:
        basic_dynamic_array() :
                _data(nullptr),
                _size(0),
                _alloc(
                        std::pmr::polymorphic_allocator<T>()
                ),
                _T_size(sizeof(T)) 
        {};
        
        basic_dynamic_array(std::size_t size){
                basic_dynamic_array();
                _data = _alloc.allocate(size * _T_size);
                _size = size;
        };
        
        basic_dynamic_array(std::size_t size, allocator alloc) :
                _data(alloc.allocate(size * _T_size)),
                _size(size),
                _alloc(alloc),
                _T_size(sizeof(T))
        {};
        
        basic_dynamic_array(basic_dynamic_array& src, allocator alloc){
                basic_dynamic_array(src._size, alloc);
                std::memcpy(_data, src._data, src._size);
        };
        basic_dynamic_array(basic_dynamic_array& src){
                basic_dynamic_array(src, src._alloc);
        };
        basic_dynamic_array(std::vector<T> vec, allocator alloc){
                basic_dynamic_array(vec.size());
                std::memcpy(_data, vec.data(), vec.size());
        };

        basic_dynamic_array(std::vector<T> vec){
                basic_dynamic_array(vec.size(), std::pmr::polymorphic_allocator<T>());
        };

        T* data(){
                return _data;
        }
        std::size_t size(){
                return size;
        }


        T operator[] (int i){
                std::byte n[_T_size];
                std::memcpy(n, _data + _T_size*i, _T_size);
                return static_cast<T>(n);
        }

        
        ~basic_dynamic_array(){
                _alloc.deallocate(_data, _size);
        };

        private:

        void resize(signed long delta){
                auto new_data = _alloc.allocate(_size + delta);
                std::memcpy(new_data, _data, std::min<std::size_t>(_size+delta, _size));
        }



        private:
        T* _data;
        std::size_t _size;
        allocator _alloc;
        std::size_t _T_size;


};


using dynamic_string = basic_dynamic_array<char>;

template<typename T>
concept SameAsChar = std::is_same<char, T>::value;


template <SameAsChar T>
std::string string_from_dynamic_array(basic_dynamic_array<T> arr){
        return std::string();
};

};


#endif
