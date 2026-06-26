#include "doctest.h"
#include "Dispositivo.hpp"
#include <string>

// Classe auxiliar para testar Dispositivo
class DispositivoTeste : public Dispositivo {
public:
    DispositivoTeste()
        : Dispositivo() {}

    void detectarErro() override {
        erro = true;
    }

    std::string getEstadoFormatado() const override {
        return estado ? "Ligado" : "Desligado";
    }
};

TEST_CASE("Construtor inicializa corretamente") {
    DispositivoTeste d;

    CHECK(d.getId() > 0);
    CHECK(d.getEstado() == false);
    CHECK(d.temErro() == false);
}

TEST_CASE("Construtor inicializa nome vazio") {
    DispositivoTeste d;

    CHECK(d.getNome() == "");
}

TEST_CASE("IDs gerados sao unicos") {
    DispositivoTeste d1;
    DispositivoTeste d2;
    DispositivoTeste d3;

    CHECK(d1.getId() != d2.getId());
    CHECK(d2.getId() != d3.getId());
    CHECK(d1.getId() != d3.getId());
}

TEST_CASE("Alterar estado do dispositivo") {
    DispositivoTeste d;

    d.alterarEstado(true);
    CHECK(d.getEstado() == true);

    d.alterarEstado(false);
    CHECK(d.getEstado() == false);
}

TEST_CASE("Detectar erro nao altera estado ligado") {
    DispositivoTeste d;

    d.alterarEstado(true);
    d.detectarErro();

    CHECK(d.getEstado());
    CHECK(d.temErro());
}

TEST_CASE("Deteccao de erro altera flag de erro") {
    DispositivoTeste d;

    d.detectarErro();

    CHECK(d.temErro() == true);
}

TEST_CASE("Estado formatado retorna texto correto") {
    DispositivoTeste d;

    CHECK(d.getEstadoFormatado() == "Desligado");

    d.alterarEstado(true);

    CHECK(d.getEstadoFormatado() == "Ligado");
}

TEST_CASE("Contador de dispositivos aumenta corretamente") {
    int qtdInicial = Dispositivo::qtdDispositivos;

    {
        DispositivoTeste d1;
        DispositivoTeste d2;

        CHECK(Dispositivo::qtdDispositivos == qtdInicial + 2);
    }

    CHECK(Dispositivo::qtdDispositivos == qtdInicial);
}