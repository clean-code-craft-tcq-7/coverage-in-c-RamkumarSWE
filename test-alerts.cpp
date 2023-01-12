#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <unistd.h>
#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
  REQUIRE(inferBreach(-10.0, 100.2, 1000.67) == TOO_LOW);
}

TEST_CASE("infers the breach according to cooling type") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 12) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -10.0) == TOO_LOW);
}

TEST_CASE("function to test upper limit value based on the cooling type") {
  REQUIRE(cooling_type_setLimit(PASSIVE_COOLING) == 35);
  REQUIRE(cooling_type_setLimit(HI_ACTIVE_COOLING) == 45);
  REQUIRE(cooling_type_setLimit(MED_ACTIVE_COOLING) == 40);
}