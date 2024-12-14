#include "van.hpp"
#include <stdexcept>

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

}