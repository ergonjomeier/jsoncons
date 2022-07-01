// Copyright 2020 Daniel Parker
// Distributed under Boost license

#if defined(_MSC_VER)
#include "windows.h" // test no inadvertant macro expansions
#endif
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonata/jsonata.hpp>
#include <catch/catch.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <ctime>
#include <new>
#include <unordered_set> // std::unordered_set
#include <fstream>

using namespace jsoncons;

void jsonata_tests(const std::string& fpath)
{
    std::fstream is(fpath);
    REQUIRE(is); //-V521

    json tests = json::parse(is);
    for (const auto& test_group : tests.array_range())
    {
        const json& root = test_group["given"];

        for (const auto& test_case : test_group["cases"].array_range())
        {
            std::string expr = test_case["expression"].as<std::string>();
            try
            {
                json actual = jsonata::search(root, expr);
                if (test_case.contains("result"))
                {
                    const json& expected = test_case["result"];
                    if (actual != expected)
                    {
                        if (test_case.contains("comment"))
                        {
                            std::cout << "\n" << test_case["comment"] << "\n";
                        }
                        std::cout << "Input:\n" << pretty_print(root) << "\n\n";
                        std::cout << "Expression: " << expr << "\n\n";
                        std::cout << "Actual: " << pretty_print(actual) << "\n\n";
                        std::cout << "Expected: " << pretty_print(expected) << "\n\n";
                    }
                    CHECK(actual == expected); //-V521
                }
                else if (test_case.contains("error"))
                {
                    if (test_case.contains("comment"))
                    {
                        std::cout << "Comment: " << test_case["comment"] << "\n";
                    }
                    std::cout << "Error: " << test_case["error"] << "\n\n";
                    std::cout << "Input:\n" << pretty_print(root) << "\n\n";
                    std::cout << "Expression: " << expr << "\n\n";
                    std::cout << "Actual: " << pretty_print(actual) << "\n\n";
                    CHECK(false); //-V521
                }

            }
            catch (const std::exception& e)
            {
                if (test_case.contains("result"))
                {
                    const json& expected = test_case["result"];
                    std::cout << e.what() << "\n";
                    if (test_case.contains("comment"))
                    {
                        std::cout << "Comment: " << test_case["comment"] << "\n\n";
                    }
                    std::cout << "Input\n" << pretty_print(root) << "\n\n";
                    std::cout << "Expression: " << expr << "\n\n";
                    std::cout << "Expected: " << expected << "\n\n";
                    CHECK(false); //-V521
                }
            }
        }
    }
}

TEST_CASE("jsonata-tests")
{
    SECTION("Examples and tutorials")
    {
        jsonata_tests("./jsonata/input/examples/jsonata-examples.json"); 
    }
    /* SECTION("Issues")
    {
        jsonata_tests("./jsonata/input/issues/issues.json"); 
    }
    SECTION("compliance")
    {
        jsonata_tests("./jsonata/input/compliance/syntax.json"); // OK

        jsonata_tests("./jsonata/input/compliance/basic.json"); // OK
        jsonata_tests("./jsonata/input/compliance/boolean.json"); // OK
        jsonata_tests("./jsonata/input/compliance/current.json"); // OK
        jsonata_tests("./jsonata/input/compliance/escape.json"); // OK
        jsonata_tests("./jsonata/input/compliance/filters.json"); // OK
        jsonata_tests("./jsonata/input/compliance/identifiers.json"); // OK
        jsonata_tests("./jsonata/input/compliance/indices.json");  // OK
        jsonata_tests("./jsonata/input/compliance/literal.json"); // OK
        jsonata_tests("./jsonata/input/compliance/multiselect.json"); // OK 
        jsonata_tests("./jsonata/input/compliance/pipe.json"); // OK
        jsonata_tests("./jsonata/input/compliance/slice.json"); // OK
        jsonata_tests("./jsonata/input/compliance/unicode.json"); // OK
        jsonata_tests("./jsonata/input/compliance/wildcard.json"); // OK
        jsonata_tests("./jsonata/input/compliance/benchmarks.json"); // OK
        jsonata_tests("./jsonata/input/compliance/functions.json"); // OK
    }*/
}

