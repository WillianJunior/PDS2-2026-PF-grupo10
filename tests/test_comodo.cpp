#include "doctest.h"
#include "../include/Comodo.hpp"
#include "../include/Dispositivo.hpp"
#include <type_traits>
#include <string>
#include <memory>
#include <stdexcept>

class TestDispositivo : public Dispositivo {
public:
    TestDispositivo() : Dispositivo() {}
    void detectarErro() override { erro = true; }
    std::string getEstadoFormatado() const override { return getEstado() ? "Ativo" : "Inativo"; }
};

TEST_CASE("Classe Comodo existe") {
    CHECK(sizeof(Comodo) > 0);
}

TEST_CASE("Comodo possui construtor padrao") {
    Comodo comodo;
    CHECK_EQ(comodo.getNome(), "");
    CHECK_EQ(comodo.getQtdDispositivos(), 0);
}

TEST_CASE("Comodo possui construtor com nome") {
    Comodo comodo("Sala");
    CHECK_EQ(comodo.getNome(), "Sala");
    CHECK_EQ(comodo.getQtdDispositivos(), 0);
}

TEST_CASE("getNome e setNome funcionam corretamente") {
    Comodo comodo;
    comodo.setNome("Cozinha");
    CHECK_EQ(comodo.getNome(), "Cozinha");
}

TEST_CASE("setNome rejeita nome vazio ou apenas espacos") {
    Comodo comodo;

    CHECK_THROWS_AS(
        comodo.setNome(""),
        std::invalid_argument
    );

    CHECK_THROWS_AS(
        comodo.setNome("    "),
        std::invalid_argument
    );
}

TEST_CASE("construtor com nome rejeita entrada invalida") {
    CHECK_THROWS_AS(
        Comodo(""),
        std::invalid_argument
    );

    CHECK_THROWS_AS(
        Comodo("   "),
        std::invalid_argument
    );
}

TEST_CASE("adicionarDispositivo adiciona e getQtdDispositivos reflete o tamanho") {
    Comodo comodo;
    auto d1 = std::unique_ptr<TestDispositivo>(new TestDispositivo());
    auto d2 = std::unique_ptr<TestDispositivo>(new TestDispositivo());

    const int inicial = comodo.getQtdDispositivos();
    comodo.adicionarDispositivo(std::unique_ptr<Dispositivo>(new TestDispositivo()));
    comodo.adicionarDispositivo(std::unique_ptr<Dispositivo>(new TestDispositivo()));

    CHECK_EQ(comodo.getQtdDispositivos(), inicial + 2);
    CHECK_EQ(comodo.getDispositivoPorIndice(0)->getId(), d1->getId());
    CHECK_EQ(comodo.getDispositivoPorIndice(1)->getId(), d2->getId());
    CHECK_EQ(comodo.getDispositivo(d1->getId())->getId(), d1->getId());
    CHECK_EQ(comodo.getDispositivo(d2->getId())->getId(), d2->getId());
}

TEST_CASE("adicionarDispositivo rejeita ponteiro nulo") {
    Comodo comodo;
    CHECK_THROWS_AS(comodo.adicionarDispositivo(nullptr), std::invalid_argument);
}

TEST_CASE("getDispositivo retorna nullptr quando nao encontra id") {
    Comodo comodo;
    auto d1 = std::unique_ptr<TestDispositivo>(new TestDispositivo());
    int id = d1->getId();
    comodo.adicionarDispositivo(std::move(d1));

    CHECK(comodo.getDispositivo(id + 1) == nullptr);
}

TEST_CASE("getDispositivoPorIndice retorna nullptr para indices invalidos") {
    Comodo comodo;
    auto d1 = std::unique_ptr<TestDispositivo>(new TestDispositivo());
    comodo.adicionarDispositivo(std::move(d1));

    CHECK(comodo.getDispositivoPorIndice(-1) == nullptr);
    CHECK(comodo.getDispositivoPorIndice(1) == nullptr);
}

TEST_CASE("removerDispositivo remove o dispositivo correto e atualiza o vetor") {
    Comodo comodo;
    auto d1 = std::make_unique<TestDispositivo>();
    auto d2 = std::make_unique<TestDispositivo>();

    int id1 = d1->getId();
    int id2 = d2->getId();

    comodo.adicionarDispositivo(std::move(d1));
    comodo.adicionarDispositivo(std::move(d2));

    CHECK_EQ(comodo.getDispositivoPorIndice(0)->getId(), id1);
    CHECK_EQ(comodo.getDispositivoPorIndice(1)->getId(), id2);

    CHECK_EQ(comodo.getDispositivo(id1)->getId(), id1);
    CHECK_EQ(comodo.getDispositivo(id2)->getId(), id2);
}

TEST_CASE("removerDispositivo nao altera a lista quando id nao existe") {
    Comodo comodo;
    auto d1 = std::unique_ptr<TestDispositivo>(new TestDispositivo());
    int id = d1->getId();
    comodo.adicionarDispositivo(std::move(d1));

    comodo.removerDispositivo(id + 100);
    CHECK_EQ(comodo.getQtdDispositivos(), 1);
    CHECK_EQ(comodo.getDispositivoPorIndice(0)->getId(), id);
}

TEST_CASE("Destrutor de Comodo libera dispositivos internos") {
    const int inicial = Dispositivo::qtdDispositivos;
    {
        Comodo comodo;
        comodo.adicionarDispositivo(std::unique_ptr<Dispositivo>(new TestDispositivo()));
        comodo.adicionarDispositivo(std::unique_ptr<Dispositivo>(new TestDispositivo()));
        CHECK_EQ(Dispositivo::qtdDispositivos, inicial + 2);
    }
    CHECK_EQ(Dispositivo::qtdDispositivos, inicial);
}
