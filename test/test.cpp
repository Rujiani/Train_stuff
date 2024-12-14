#include "../van/van.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <stdexcept>

using namespace mgt;
using std::invalid_argument;

TEST_CASE("Van"){
    SECTION("Default constructor"){
        van temp;
        REQUIRE(!temp.getCapacity());
        REQUIRE(!temp.getOccupiedSeats());
        REQUIRE(temp.getType() == restaurant);
    }

    SECTION("Constructor"){
        van_type a = seated;
        size_t cp = 12, os2 = 5;
        van van1(cp, os2, a);
    }

    SECTION("Setters"){
        van van;
        REQUIRE_THROWS_AS(van.setOccupiedSeats(12), invalid_argument);
        REQUIRE_THROWS_AS(van.setCapacity(12), invalid_argument);
        REQUIRE_NOTHROW(van.setType(seated));
        REQUIRE_NOTHROW(van.setCapacity(50));
        REQUIRE_NOTHROW(van.setOccupiedSeats(45));
        REQUIRE_THROWS_AS(van.setType(restaurant), invalid_argument);
        REQUIRE(van.percentage() == 90);
    }

    SECTION("move operator >>"){
        van a(40, 25, seated), b(10, 0, luxury);
        REQUIRE_THROWS_AS(a >> b, invalid_argument);
        b.setType(seated);
        REQUIRE_NOTHROW(a >> b);
        REQUIRE(a.percentage() == b.percentage());
        REQUIRE(a.percentage() == 50);
        REQUIRE(a.getOccupiedSeats() == 20);
        REQUIRE(b.getOccupiedSeats() == 5);
    }

    SECTION("Output"){
        std::ostringstream ostr;
        van a(12, 2, seated);
        ostr << a;
        REQUIRE(ostr.str() == "2/12 seated");
    }

    SECTION("Input"){
        van a;
        std::istringstream istr("13/14 seated");
        istr >> a;
        REQUIRE(a.getCapacity() == 14);
        REQUIRE(a.getOccupiedSeats() == 13);
        REQUIRE(a.getType() == seated);
        istr.str("15/1 restaurant");
        istr >> a;
        REQUIRE(!istr); 
    }

    SECTION("Add and remove pass"){
        van a(15, 2, seated);
        REQUIRE_NOTHROW(a.addPassengers(12));
        REQUIRE(a.getOccupiedSeats() == 14);
        REQUIRE_NOTHROW(a.removePassengers(2));
        REQUIRE(a.getOccupiedSeats() == 12);
        REQUIRE_NOTHROW(a.removePassengers(40));
        REQUIRE(!a.getOccupiedSeats());
    }
}

#include "../train/train.hpp"

TEST_CASE("Train"){
    SECTION("operator == "){
        van *a = new van[10], *b = new van[2];
        train tr1(a, 10), tr2(a, 10), tr3(b, 2);
        REQUIRE(tr1 == tr2);
        REQUIRE(tr1 != tr3);
        delete [] a;
        delete [] b;
    }

    SECTION("Move and copy construct"){
        van *a = new van[10];
        train tr1(a, 10), tr2(tr1);
        REQUIRE(tr1 == tr2);
        train tr3(std::move(tr1));
        REQUIRE(tr1 != tr3);
        delete[]a;
    }

    SECTION("Move and copy ="){
        van *a = new van[10];
        train tr1(a, 10), tr2;
        tr2 = tr1;
        REQUIRE(tr1 == tr2);
        train tr3;
        tr3 = (std::move(tr1));
        REQUIRE(tr1 != tr3);
        delete[]a;
    }

    SECTION("input output"){
        std::istringstream istr("12/13, seated");
        train a;
        istr >> a;
        REQUIRE(istr);
        std::ostringstream ostr;
        ostr << a;
        REQUIRE(ostr.str() == "{12/13 seated}");
    }

    SECTION("Operator []"){
        van *a = new van[12];
        train tr(a, 12);
        REQUIRE(tr[0] == tr[1]);
        REQUIRE_THROWS(tr[43]);
        delete[] a;
    }

    SECTION("+="){
        van temp = van{23, 12, seated};
        train a(van{23, 12, seated});
        REQUIRE_NOTHROW(a += temp);
        REQUIRE(a[0] == temp);
        REQUIRE(a[1] == temp);
        REQUIRE(a.getSize() == 2);
    }
}