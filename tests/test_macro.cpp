#include "doctest.h"
#include "../include/Macro.hpp"
#include <type_traits>
#include <string>

TEST_CASE("Classe Macro existe") {
    CHECK(sizeof(Macro) > 0);
}

TEST_CASE("Macro possui construtor com string") {
    CHECK(std::is_constructible<Macro, std::string>::value);
}

TEST_CASE("Macro possui destrutor") {
    CHECK(std::is_destructible<Macro>::value);
}

TEST_CASE("getEvento retorna string") {
    CHECK(
        std::is_same<
            decltype(std::declval<Macro>().getEvento()),
            std::string
        >::value
    );
}

TEST_CASE("getLista retorna Node*") {
    CHECK(
        std::is_same<
            decltype(std::declval<Macro>().getLista()),
            Node*
        >::value
    );
}

TEST_CASE("qtdMacros eh atributo estatico inteiro") {
    CHECK(std::is_same<decltype(Macro::qtdMacros), int>::value);
}