#ifndef VAN_HPP_
#define VAN_HPP_

#include <cstddef>
#include <cstdlib>
#include <map>
#include <iostream>
#include <stdexcept>
#include <format>
#include <string>

using std::invalid_argument;

//my great train
namespace mgt {

enum van_type{
    restaurant,
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

const std::map<van_type, std::string> type_to_str{
    {restaurant, "restaurant"},
    {seated, "seated"},
    {economy, "economy"},
    {luxury, "luxury"}
};

const std::map<std::string, van_type> str_to_type{
    {"restaurant", restaurant},
    {"seated", seated},
    {"economy", economy},
    {"luxury", luxury}
};

class van{
    private:
    size_t capacity, occupied_seats;
    van_type type;

    size_t countPercentage(size_t capacity, size_t occupied_seats)const noexcept{
        if(!capacity)
            return 0;
        return static_cast<size_t>
        ((static_cast<double>(occupied_seats)/static_cast<double>(capacity)) * 100);
    }
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
        return countPercentage(capacity, occupied_seats);
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

    van& operator >>(van&);

    void addPassengers(size_t ps){
        setOccupiedSeats(occupied_seats + ps);
    }

    void removePassengers(size_t ps)noexcept{
        setOccupiedSeats((occupied_seats < ps)?0 : occupied_seats - ps);
    }

    void output(std::ostream &os)const noexcept{
        os << std::format("{}/{} {}", occupied_seats, capacity, type_to_str.find(type)->second);
    }

    void input(std::istream &is);

    friend std::istream& operator >> (std::istream& is, van &v)noexcept{
        v.input(is);
        return is;
    }

    friend std::ostream& operator << (std::ostream& os, van &v){
        v.output(os);
        return os;
    }

    van& operator += (size_t num){
        addPassengers(num);
        return *this;
    }

    van& operator -= (size_t num)noexcept{
        removePassengers(num);
        return *this;
    }
};

}

#endif