#include "van.hpp"
#include <stdexcept>
#include <exception>

using std::invalid_argument;

namespace mgt {

van::van(size_t cp, size_t os, van_type tp):
capacity(cp), occupied_seats(os), type(tp){
    if(!tp && cp)
        throw invalid_argument(
        "Error: capacity of restaurant van cannot increase 0");
    if(os > cp)
        throw invalid_argument(
        "Error: occupied_seats cannot increase capacity");
}

van& van::operator >>(van& other){
    if(type != other.type)
        throw invalid_argument("Cannot move passengers from different types");
    size_t both_cp = capacity + other.capacity,
           both_os = occupied_seats + other.occupied_seats,
           both_pr = countPercentage(both_cp, both_os);
    
    size_t temp_occupied_seats = static_cast<size_t>(static_cast<double>(capacity) *
    (static_cast<double>(both_pr) * 0.01));
    occupied_seats = temp_occupied_seats;
    other.occupied_seats = both_os - temp_occupied_seats;
    return *this;
}

void van::input(std::istream &is){
    size_t cp, os;
    std::string temp, tp_str;
    van_type tmp;
    is >> temp >> tp_str;
    if(is){
        try{
            size_t pos = temp.find('/');
            os = std::stol(temp.substr(0, pos));
            cp = std::stol(temp.substr(pos + 1, temp.length() - pos));
            tmp = str_to_type.find(tp_str)->second;
            *this = van(cp, os, tmp);
        }
        catch(std::exception &ex){
            is.setstate(std::istream::failbit);
        }
    }
}

}