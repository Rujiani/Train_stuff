#include "train.hpp"

namespace mgt {
train& train::operator = (const train &other){
    if(other.reserve_size != reserve_size){
        van *temp = new van[other.reserve_size];
        delete[] vans;
        vans = temp;
    }
    size = other.size;
    reserve_size = other.reserve_size;
    std::copy_n(other.vans, size, vans);
    return *this;
}

train& train::operator = (train &&other)noexcept{
    delete[] vans;
    vans = other.vans;
    size = other.size;
    reserve_size = other.reserve_size;
    other.size = 0;
    other.reserve_size = 0;
    other.vans = nullptr;
    return *this;
}

void train::sitInMin(size_t numOfPass){
    size_t found_min = 0;
    van* temp = nullptr;
    std::for_each_n(vans, size, [&temp, &numOfPass, &found_min](auto &i){
        if(numOfPass <= i.getCapacity() - i.getOccupiedSeats() &&(
            !temp || i.getOccupiedSeats() < found_min)){
                found_min = i.getOccupiedSeats();
                temp = &i;
        }
    });
    *temp += numOfPass;
}

}