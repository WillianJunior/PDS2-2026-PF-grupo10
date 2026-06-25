#include "doctest.h"
#include "Portao.hpp"

TEST_CASE("Construtor do Portao") {
    Portao p;

    CHECK(p.getId() > 0);
    CHECK(p.getEstado() == false);
    CHECK(p.temErro() == false);
}

TEST_CASE("Temporizador inicia valor padrao") {
    Portao p;

    CHECK(p.getTemporizador() == 30);
}

TEST_CASE("Set e Get do temporizador") {
    Portao p;

    p.setTemporizador(15);
    CHECK(p.getTemporizador() == 15);
    // O temporizador não deve aceitar valores negativos ou zero, mantendo o valor anterior.
    p.setTemporizador(0);
    CHECK(p.getTemporizador() == 15); 
    p.setTemporizador(-5);
    CHECK(p.getTemporizador() == 15);
}

TEST_CASE("Alterar estado do portao") {
    Portao p;

    p.alterarEstado(true);
    CHECK(p.getEstado() == true);

    p.alterarEstado(false);
    CHECK(p.getEstado() == false);
}

TEST_CASE("Deteccao de erro executa corretamente") {
    Portao p;

    CHECK_NOTHROW(p.detectarErro());
}