#ifndef TRAIN_HPP_
#define TRAIN_HPP_

#include "../van/van.hpp"
#include <algorithm>

namespace mgt {

class train{
    private:
    van* vans;
    size_t size, reserve_size;

    void change_size(size_t sz){
        van* temp = new van[sz];
        std::copy_n(vans, size, temp);
        delete[] vans;
        vans = temp;
    }

    void double_size(){
        change_size(reserve_size * 2);
        reserve_size *=2;
    }

    void halve_size(){
        change_size(reserve_size / 2);
        reserve_size /= 2;
    }

    public:

    train()noexcept : vans(new van[1]), size(0), reserve_size(1){}

    train(const van *ptr, size_t size): vans(new van[size]), size(size), reserve_size(size){
        std::copy_n(ptr, size, vans);
    }

    train(const van &vn) : vans(new van[1]), size(1), reserve_size(1){
        vans[0] = vn;
    }

    train(const train &other): vans(new van[other.reserve_size]), size(other.size), reserve_size(other.reserve_size){
        std::copy_n(other.vans, size, vans);
    }

    train(train &&other)noexcept:vans(other.vans), size(other.size), reserve_size(other.reserve_size){
        other.size = 0;
        other.reserve_size = 0;
        other.vans = nullptr;
    }

    ~train(){
        delete[] vans;
    }

    bool operator == (const train &other)const{
        if(!vans || !other.vans)
            return vans == other.vans;
        return std::equal(vans, vans + size, other.vans);
    }

    bool operator != (const train &other)const{
        return !(*this == other);
    }

    train& operator = (const train &other);

    train& operator = (train &&other)noexcept;
};

}

#endif