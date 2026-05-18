#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "ArCondicionado.hpp"

#include <type_traits>

TEST_CASE("ArCondicionado herda de Dispositivo") {

    CHECK(std::is_base_of<Dispositivo, ArCondicionado>::value);

}

TEST_CASE("Classe ArCondicionado existe") {

    CHECK(sizeof(ArCondicionado) > 0);
}