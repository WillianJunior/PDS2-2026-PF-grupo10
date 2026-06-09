
#include "doctest.h"
#include "Comodo.hpp"
#include <type_traits>

TEST_CASE("Classe Comodo existe") {
    CHECK(sizeof(Comodo) > 0);
}

TEST_CASE("Comodo possui construtor padrao") {
    CHECK(std::is_default_constructible<Comodo>::value);
}

TEST_CASE("Comodo possui destrutor") {
    CHECK(std::is_destructible<Comodo>::value);
}

TEST_CASE("getDispositivo retorna Dispositivo*") {
    CHECK(
        std::is_same<
            decltype(std::declval<Comodo>().getDispositivo(1)),
            Dispositivo*
        >::value
    );
}

TEST_CASE("getQtdDispositivos retorna int") {
    CHECK(
        std::is_same<
            decltype(std::declval<Comodo>().getQtdDispositivos()),
            int
        >::value
    );
}