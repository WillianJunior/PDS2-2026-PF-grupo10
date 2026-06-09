#include "doctest.h"
#include "Usuario.hpp"

TEST_CASE("Usuario::getMacro retorna nullptr para índices inválidos") {
    Usuario usuario("joao", "1234");

    CHECK(usuario.getMacro(-1, usuario) == nullptr);
    CHECK(usuario.getMacro(0, usuario) == nullptr);
    CHECK(usuario.getMacro(10, usuario) == nullptr);
}

TEST_CASE("Usuario::getMacro retorna nullptr quando não há macros cadastradas") {
    Usuario usuario("joao", "1234");

    CHECK(usuario.getMacro(0, usuario) == nullptr);
}
