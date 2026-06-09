#include "doctest.h"
#include "../include/Comodo.hpp"
#include "../include/Dispositivo.hpp"
#include <type_traits>
#include <string>

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

TEST_CASE("adicionarDispositivo adiciona e getQtdDispositivos reflete o tamanho") {
    Comodo comodo;
    TestDispositivo* d1 = new TestDispositivo();
    TestDispositivo* d2 = new TestDispositivo();

    const int inicial = comodo.getQtdDispositivos();
    comodo.adicionarDispositivo(d1);
    comodo.adicionarDispositivo(d2);

    CHECK_EQ(comodo.getQtdDispositivos(), inicial + 2);
    CHECK_EQ(comodo.getDispositivoPorIndice(0), d1);
    CHECK_EQ(comodo.getDispositivoPorIndice(1), d2);
    CHECK_EQ(comodo.getDispositivo(d1->getId()), d1);
    CHECK_EQ(comodo.getDispositivo(d2->getId()), d2);
}

TEST_CASE("getDispositivo retorna nullptr quando nao encontra id") {
    Comodo comodo;
    TestDispositivo* d1 = new TestDispositivo();
    comodo.adicionarDispositivo(d1);

    CHECK(comodo.getDispositivo(d1->getId() + 1) == nullptr);
}

TEST_CASE("getDispositivoPorIndice retorna nullptr para indices invalidos") {
    Comodo comodo;
    TestDispositivo* d1 = new TestDispositivo();
    comodo.adicionarDispositivo(d1);

    CHECK(comodo.getDispositivoPorIndice(-1) == nullptr);
    CHECK(comodo.getDispositivoPorIndice(1) == nullptr);
}

TEST_CASE("removerDispositivo remove o dispositivo correto e atualiza o vetor") {
    Comodo comodo;
    TestDispositivo* d1 = new TestDispositivo();
    TestDispositivo* d2 = new TestDispositivo();
    TestDispositivo* d3 = new TestDispositivo();

    comodo.adicionarDispositivo(d1);
    comodo.adicionarDispositivo(d2);
    comodo.adicionarDispositivo(d3);

    int idRemover = d2->getId();
    comodo.removerDispositivo(idRemover);

    CHECK_EQ(comodo.getQtdDispositivos(), 2);
    CHECK_EQ(comodo.getDispositivo(d2->getId()), nullptr);
    CHECK_EQ(comodo.getDispositivoPorIndice(0), d1);
    CHECK_EQ(comodo.getDispositivoPorIndice(1), d3);
    CHECK(comodo.getDispositivoPorIndice(2) == nullptr);
}

TEST_CASE("removerDispositivo nao altera a lista quando id nao existe") {
    Comodo comodo;
    TestDispositivo* d1 = new TestDispositivo();
    comodo.adicionarDispositivo(d1);

    comodo.removerDispositivo(d1->getId() + 100);
    CHECK_EQ(comodo.getQtdDispositivos(), 1);
    CHECK_EQ(comodo.getDispositivoPorIndice(0), d1);
}

TEST_CASE("Destrutor de Comodo libera dispositivos internos") {
    const int inicial = Dispositivo::qtdDispositivos;
    {
        Comodo comodo;
        comodo.adicionarDispositivo(new TestDispositivo());
        comodo.adicionarDispositivo(new TestDispositivo());
        CHECK_EQ(Dispositivo::qtdDispositivos, inicial + 2);
    }
    CHECK_EQ(Dispositivo::qtdDispositivos, inicial);
}
