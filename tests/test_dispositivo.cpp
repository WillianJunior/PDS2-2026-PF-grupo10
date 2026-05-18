#include "doctest.h"
#include "Dispositivo.hpp"
#include <string>

// Classe auxiliar para testar a classe abstrata Dispositivo
class DispositivoTeste : public Dispositivo {
public:
    DispositivoTeste(int id, const std::string& comodo)
        : Dispositivo(id, comodo) {}

    void detectarErro() override {
        erro = true;
    }

    std::string getEstadoFormatado() const override {
        return estado ? "Ligado" : "Desligado";
    }
};

TEST_CASE("Construtor inicializa corretamente") {
    DispositivoTeste d(1, "Sala");

    CHECK(d.getId() == 1);
    CHECK(d.getComodo() == "Sala");
    CHECK(d.getEstado() == false);
    CHECK(d.temErro() == false);
}

TEST_CASE("Alterar estado do dispositivo") {
    DispositivoTeste d(2, "Quarto");

    d.alterarEstado(true);
    CHECK(d.getEstado() == true);

    d.alterarEstado(false);
    CHECK(d.getEstado() == false);
}

TEST_CASE("Deteccao de erro altera flag de erro") {
    DispositivoTeste d(3, "Cozinha");

    d.detectarErro();

    CHECK(d.temErro() == true);
}

TEST_CASE("Estado formatado retorna texto correto") {
    DispositivoTeste d(4, "Banheiro");

    CHECK(d.getEstadoFormatado() == "Desligado");

    d.alterarEstado(true);

    CHECK(d.getEstadoFormatado() == "Ligado");
}

TEST_CASE("Contador de dispositivos aumenta corretamente") {
    int qtdInicial = Dispositivo::qtdDispositivos;

    {
        DispositivoTeste d1(5, "Sala");
        DispositivoTeste d2(6, "Quarto");

        CHECK(Dispositivo::qtdDispositivos == qtdInicial + 2);
    }

    CHECK(Dispositivo::qtdDispositivos == qtdInicial);
}