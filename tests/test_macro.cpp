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
        std::is_same<decltype(std::declval<Macro>().getEvento()),std::string>::value
    );
}

TEST_CASE("getLista retorna Node*") {
    CHECK(
        std::is_same<decltype(std::declval<Macro>().getLista()),Node*>::value
    );
}

TEST_CASE("qtdMacros eh atributo estatico inteiro") {
    CHECK(std::is_same<decltype(Macro::qtdMacros), int>::value);
}

TEST_CASE("Construtor atualiza qtdMacros e destrutor decrementa") {
    const int inicial = Macro::qtdMacros;
    {
        Macro macro("evento1");
        CHECK(Macro::qtdMacros == inicial + 1);
    }
    CHECK(Macro::qtdMacros == inicial);
}

TEST_CASE("setEvento altera o evento da macro") {
    Macro macro("evento_inicial");
    CHECK_EQ(macro.getEvento(), "evento_inicial");
    macro.setEvento("evento_alterado");
    CHECK_EQ(macro.getEvento(), "evento_alterado");
}

TEST_CASE("adicionarDispositivo insere nos e preserva ordem") {
    Macro macro("evento_lista");
    CHECK(macro.getLista() == nullptr);

    macro.adicionarDispositivo(1, "ligar", 0);
    REQUIRE(macro.getLista() != nullptr);
    CHECK_EQ(macro.getLista()->id, 1);
    CHECK_EQ(macro.getLista()->acao, "ligar");
    CHECK(macro.getLista()->proximo == nullptr);

    macro.adicionarDispositivo(2, "desligar", 0);
    REQUIRE(macro.getLista()->proximo != nullptr);
    CHECK_EQ(macro.getLista()->proximo->id, 2);
    CHECK_EQ(macro.getLista()->proximo->acao, "desligar");
    CHECK(macro.getLista()->proximo->proximo == nullptr);
}

TEST_CASE("removerDispositivo elimina o primeiro no da lista") {
    Macro macro("evento_remover_cabeca");
    macro.adicionarDispositivo(10, "abrir", 0);
    macro.adicionarDispositivo(20, "fechar", 0);
    macro.removerDispositivo(10, "abrir");

    REQUIRE(macro.getLista() != nullptr);
    CHECK_EQ(macro.getLista()->id, 20);
    CHECK_EQ(macro.getLista()->acao, "fechar");
    CHECK(macro.getLista()->proximo == nullptr);
}

TEST_CASE("removerDispositivo elimina um no do meio da lista") {
    Macro macro("evento_remover_meio");
    macro.adicionarDispositivo(100, "ligar", 0);
    macro.adicionarDispositivo(200, "desligar", 0);
    macro.adicionarDispositivo(300, "ajustar", 0);

    macro.removerDispositivo(200, "desligar");

    REQUIRE(macro.getLista() != nullptr);
    CHECK_EQ(macro.getLista()->id, 100);
    CHECK_EQ(macro.getLista()->proximo->id, 300);
    CHECK_EQ(macro.getLista()->proximo->acao, "ajustar");
    CHECK(macro.getLista()->proximo->proximo == nullptr);
}

TEST_CASE("removerDispositivo nao altera a lista quando o elemento nao existe") {
    Macro macro("evento_remover_inexistente");
    macro.adicionarDispositivo(5, "ligar", 0);
    macro.removerDispositivo(6, "desligar");

    REQUIRE(macro.getLista() != nullptr);
    CHECK_EQ(macro.getLista()->id, 5);
    CHECK_EQ(macro.getLista()->acao, "ligar");
    CHECK(macro.getLista()->proximo == nullptr);
}
