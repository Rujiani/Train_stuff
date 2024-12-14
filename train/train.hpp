#ifndef TRAIN_HPP_
#define TRAIN_HPP_

#include "../van/van.hpp"
#include <algorithm>
#include <stdexcept>

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

    void output(std::ostream &os)const noexcept{
        os << "{";
        std::for_each_n(vans, size - 1, [&os](auto &i){os << i << ", ";});
        os << vans[size - 1] << "}";
    }

    void input(std::istream &is)noexcept{
        van temp;
        is >> temp;
        if(is)
            *this = train(temp);
    }

    friend std::ostream& operator << (std::ostream &os, const train& tr)noexcept{
        tr.output(os);
        return os;
    }

    friend std::istream& operator >> (std::istream &is, train &tr)noexcept{
        tr.input(is);
        return is;
    }

    van& operator [](size_t index){
        if(index >= size)
            throw std::range_error("Out of train range");
        return vans[index];
    }

    const van& operator[](size_t index)const{
        if(index >= size)
            throw std::range_error("Out of train range");
        return vans[index];
    }

    void operator += (const van &v){
        if(size == reserve_size)
            double_size();
        vans[size++] = v;
    }

    size_t getSize()const noexcept{return size;}
};

}

#endif