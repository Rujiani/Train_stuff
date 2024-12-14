#ifndef VAN_HPP_
#define VAN_HPP_

#include <cstddef>
#include <stdexcept>

//my great train
namespace mgt {

enum van_type{
    restaurant = 0,
    seated,
    economy,
    luxury
};

class van{
    private:
    size_t capacity, occupied_seats;
    van_type type;
    public:

    van()noexcept : capacity{0}, occupied_seats{0},
                    type{restaurant}{};

    explicit van(size_t cp, size_t os, van_type tp):
    capacity(cp), occupied_seats(os), type(tp){
        if(!tp && cp)
            throw std::invalid_argument(
            "Error: capacity of restaurant van cannot increase 0");
        if(os > cp)
            throw std::invalid_argument(
            "Error: occupied_seats cannot increase capacity");
    }

    size_t getCapacity()const noexcept{return capacity;}

    size_t getOccupiedSeats()const noexcept{return occupied_seats;}

    size_t getType()const noexcept{return type;}

};

}

#endif