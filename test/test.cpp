#include "../van/van.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace mgt;

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
}