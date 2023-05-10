// Copyright 2013-2023 Daniel Parker
// Distributed under Boost license

#include <jsoncons/json.hpp>
#include <jsoncons/json_encoder.hpp>
#include <catch/catch.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>
#include <map>

using namespace jsoncons;

void check_swap(const json& j1, const json& j2)
{
    json j3 = j1;
    //json j4 = j2;

    //j3.swap(j4);
    //CHECK(j1 == j4);
    //CHECK(j2 == j3);
}

TEST_CASE("test_swap")
{
    json j6 = "Small";
    json j7 = "String too large for small string";

    check_swap(j7,j6);
}

