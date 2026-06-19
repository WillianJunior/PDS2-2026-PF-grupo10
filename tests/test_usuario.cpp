#include "doctest.h"
#include "Usuario.hpp"

TEST_CASE("Usuario::getMacro retorna nullptr para índices inválidos") {
    Usuario usuario("joao", "1234");

    CHECK(usuario.getMacro(-1) == nullptr);
    CHECK(usuario.getMacro(0) == nullptr);
    CHECK(usuario.getMacro(10) == nullptr);
}

TEST_CASE("Usuario::getMacro retorna nullptr quando não há macros cadastradas") {
    Usuario usuario("joao", "1234");

    CHECK(usuario.getMacro(0) == nullptr);
}
