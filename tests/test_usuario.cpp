#include "doctest.h"
#include "Usuario.hpp"
#include "Sistema.hpp"
#include <stdexcept>

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

TEST_CASE("Construtor e getNome") {
    Usuario usuario("joao", "1234");

    CHECK(usuario.getNome() == "joao");
}

TEST_CASE("setNome altera o nome") {
    Usuario usuario("joao", "1234");

    std::string novoNome = "maria";
    usuario.setNome(novoNome);

    CHECK(usuario.getNome() == "maria");
}

TEST_CASE("setNome lança exceção para nome vazio") {
    Usuario usuario("joao", "1234");

    std::string nome = "";

    CHECK_THROWS_AS(usuario.setNome(nome), std::invalid_argument);
}

TEST_CASE("Autenticação correta") {
    Usuario usuario("joao", "1234");

    std::string nome = "joao";
    std::string senha = "1234";

    CHECK(usuario.autenticar(nome, senha));
}

TEST_CASE("Autenticação incorreta") {
    Usuario usuario("joao", "1234");

    std::string nome = "joao";
    std::string senha = "4321";

    CHECK_FALSE(usuario.autenticar(nome, senha));
}

TEST_CASE("Adicionar macro") {
    Usuario usuario("joao", "1234");
    Sistema sistema;

    Macro* macro = usuario.adicionarMacro("cheguei", sistema);

    REQUIRE(macro != nullptr);
    CHECK(macro->getEvento() == "cheguei");
    CHECK(usuario.getMacro(0) == macro);
}

TEST_CASE("Adicionar macro com nome vazio lança exceção") {
    Usuario usuario("joao", "1234");
    Sistema sistema;

    CHECK_THROWS_AS(usuario.adicionarMacro("", sistema), std::invalid_argument);
}

TEST_CASE("Remover macro existente") {
    Usuario usuario("joao", "1234");
    Sistema sistema;

    usuario.adicionarMacro("cheguei", sistema);

    usuario.removerMacro("cheguei");

    CHECK(usuario.getMacro(0) == nullptr);
}

TEST_CASE("Remover macro inexistente lança exceção") {
    Usuario usuario("joao", "1234");

    CHECK_THROWS_AS(usuario.removerMacro("teste"), std::runtime_error);
}

TEST_CASE("Limpar macros remove todas") {
    Usuario usuario("joao", "1234");
    Sistema sistema;

    usuario.adicionarMacro("m1", sistema);
    usuario.adicionarMacro("m2", sistema);

    usuario.limparMacros();

    CHECK(usuario.getMacro(0) == nullptr);
}


