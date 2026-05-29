#include "doctest.h"
#include "Dispositivo.hpp"
#include <string>

// Classe auxiliar para testar Dispositivo
class DispositivoTeste : public Dispositivo {
public:
    DispositivoTeste(int id)
        : Dispositivo(id) {}

    void detectarErro() override {
        erro = true;
    }

    std::string getEstadoFormatado() const override {
        return estado ? "Ligado" : "Desligado";
    }
};

TEST_CASE("Construtor inicializa corretamente") {
    DispositivoTeste d(1);

    CHECK(d.getId() == 1);
    CHECK(d.getEstado() == false);
    CHECK(d.temErro() == false);
}

TEST_CASE("Alterar estado do dispositivo") {
    DispositivoTeste d(2);

    d.alterarEstado(true);
    CHECK(d.getEstado() == true);

    d.alterarEstado(false);
    CHECK(d.getEstado() == false);
}

TEST_CASE("Deteccao de erro altera flag de erro") {
    DispositivoTeste d(3);

    d.detectarErro();

    CHECK(d.temErro() == true);
}

TEST_CASE("Estado formatado retorna texto correto") {
    DispositivoTeste d(4);

    CHECK(d.getEstadoFormatado() == "Desligado");

    d.alterarEstado(true);

    CHECK(d.getEstadoFormatado() == "Ligado");
}

TEST_CASE("Contador de dispositivos aumenta corretamente") {
    int qtdInicial = Dispositivo::qtdDispositivos;

    {
        DispositivoTeste d1(5);
        DispositivoTeste d2(6);

        CHECK(Dispositivo::qtdDispositivos == qtdInicial + 2);
    }

    CHECK(Dispositivo::qtdDispositivos == qtdInicial);
}