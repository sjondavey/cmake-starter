#include "catch.hpp"
#include "../src/formula/Black76Formula.h"
#include <cmath> // std::isnan in C++11

using namespace std;
using namespace sjd;

TEST_CASE("Black76 implementation", "[functions]") {
    double F, X, sd, df;
    unique_ptr<Black76Option> call;
    unique_ptr<Black76Option> put;

    SECTION("Check that invalid paramenters result in NaN return values") {
        F = -100, X = 110, sd = 0.2, df = 0.97;
        call = make_unique<Black76Call>(F,X,sd,df);
        put = make_unique<Black76Put>(F,X,sd,df);
        REQUIRE(std::isnan(put->value()));
        REQUIRE(std::isnan(call->value()));
        REQUIRE(std::isnan(put->delta()));
        REQUIRE(std::isnan(call->delta()));

        F = 100;
        sd = 0;
        call = make_unique<Black76Call>(F,X,sd,df);
        put = make_unique<Black76Put>(F,X,sd,df);
        REQUIRE(std::isnan(put->value()));
        REQUIRE(std::isnan(call->value()));
        REQUIRE(std::isnan(put->delta()));
        REQUIRE(std::isnan(call->delta()));

        sd = 0.2;
        call = make_unique<Black76Call>(F,X,sd,df);
        put = make_unique<Black76Put>(F,X,sd,df);
        REQUIRE(abs(put->value() - 13.8632506131676) < 1e-14);
        REQUIRE(abs(call->value() - 4.163250613167595) < 1e-14);
        REQUIRE(abs(put->delta() + 0.6273439192177788) < 1e-14) ;
        REQUIRE(abs(call->delta() - 0.3426560807822211) < 1e-14);
    }

    SECTION("Check put / call parity") {
        F = 100, X = 110, sd = 0.2, df = 0.97;
        call = make_unique<Black76Call>(F,X,sd,df);
        put = make_unique<Black76Put>(F,X,sd,df);
        REQUIRE(abs(put->value() - call->value() - (X-F) * df) < 1e-14);

    }
}
