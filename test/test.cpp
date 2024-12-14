#include "../van/van.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
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
}