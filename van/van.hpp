#ifndef VAN_HPP_
#define VAN_HPP_

#include <cstddef>
#include <map>
#include <stdexcept>

using std::invalid_argument;

//my great train
namespace mgt {

enum van_type{
    restaurant = 0,
    seated,
    economy,
    luxury
};

const std::map<van_type, size_t> default_capacity{
    {restaurant, 0},
    {seated, 80},
    {economy, 54},
    {luxury, 12}
};

class van{
    private:
    size_t capacity, occupied_seats;
    van_type type;
    public:

    van()noexcept : capacity{0}, occupied_seats{0},
                    type{restaurant}{};

    explicit van(const size_t cp,const size_t os,const van_type tp);

    explicit van(const van_type tp): capacity(default_capacity.find(tp)->second),
                               occupied_seats(0), type(tp){}

    size_t getCapacity()const noexcept{return capacity;}

    size_t getOccupiedSeats()const noexcept{return occupied_seats;}

    size_t getType()const noexcept{return type;}

    size_t percentage()const noexcept{
        if(!capacity)
            return 0;
        return static_cast<size_t>
        ((static_cast<double>(occupied_seats)/static_cast<double>(capacity)) * 100);
    }

    void setCapacity(size_t cp){
        if(!type && cp)
            throw invalid_argument(
            "Error: capacity of restaurant van cannot increase 0");
        if(occupied_seats > cp)
            throw invalid_argument("Error: occupied_seats cannot increase capacity");
        capacity = cp;
    }

    void setOccupiedSeats(size_t os){
        if(os > capacity)
            throw invalid_argument("Error: occupied_seats cannot increase capacity");
        occupied_seats = os;
    }

    void setType(van_type tp){
        if(!tp && capacity)
            throw invalid_argument(
            "Error: capacity of restaurant van cannot increase 0");
        type = tp;
    }

};

}

#endif