#include "Binder.h"
#include "ObjectRegistry.h"

#include "balance.hpp"
#include "order.hpp"

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using ClassesToSerialize::Balance;
using ClassesToSerialize::LimitPolicy;
using ClassesToSerialize::MarketPolicy;
using ClassesToSerialize::Order;

#define BIND_MEMBER(ClassName, MemberName) binder.set(#MemberName, &ClassName::MemberName);
#define BIND_CLASS(ClassName) Binder<ClassName> binder(#ClassName);


TEST_CASE( "check contents of target.ts", "[single-file]" )
{
    {
        BIND_CLASS(MarketPolicy)
    }

    {
        BIND_CLASS(LimitPolicy)
            BIND_MEMBER(LimitPolicy, price)
            BIND_MEMBER(LimitPolicy, stop)
    }

    {
        BIND_CLASS(Order)
            BIND_MEMBER(Order, symbol)
            BIND_MEMBER(Order, quantity)
            BIND_MEMBER(Order, is_buy)
            BIND_MEMBER(Order, policy)
    }

    {
        BIND_CLASS(Balance)
            BIND_MEMBER(Balance, free)
            BIND_MEMBER(Balance, locked)
    }

    std::string rendered_result = ObjectRegistry::instance().render();
    std::cout << rendered_result << std::endl;
    
    std::string target_file_name = "target.ts";
    std::ifstream target_file(target_file_name);
    if (!target_file.is_open()) {
        target_file_name = "../" + target_file_name;
        target_file.open(target_file_name);
    }
    CHECK(target_file.is_open());
    std::string expected_result((std::istreambuf_iterator<char>(target_file)),
        std::istreambuf_iterator<char>());
    
    REQUIRE(rendered_result.compare(expected_result) == 0);
}

int main(int argc, char *argv[]) {
    int result = Catch::Session().run( argc, argv );
    return result;
};
