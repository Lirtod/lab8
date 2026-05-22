#define CATCH_CONFIG_MAIN
#include "catch.hpp"

struct Runner {
    int number;
    std::string last;
    std::string first;
    std::string middle;
    std::string start;
    std::string finish;
    std::string club;
    int time;
};

std::string bestTime(Runner a[], int n);

TEST_CASE("basic") {
    Runner a[2];
    a[0].time = 3600;
    a[1].time = 1800;

    REQUIRE(bestTime(a, 2) == "00:30:00");
}

TEST_CASE("single") {
    Runner a[1];
    a[0].time = 3661;

    REQUIRE(bestTime(a, 1) == "01:01:01");
}

TEST_CASE("equal") {
    Runner a[2];
    a[0].time = 3000;
    a[1].time = 3000;

    REQUIRE(bestTime(a, 2) == "00:50:00");
}
