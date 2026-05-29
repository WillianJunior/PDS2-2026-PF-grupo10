#include "doctest.h"
#include "Portao.hpp"

TEST_CASE("Construtor do Portao") {
    Portao p(1);

    CHECK(p.getId() == 1);
    CHECK(p.getEstado() == false);
    CHECK(p.temErro() == false);
}

TEST_CASE("Temporizador inicia em zero ou valor padrao") {
    Portao p(2);

    CHECK(p.getTemporizador() >= 0);
}

TEST_CASE("Set e Get do temporizador") {
    Portao p(3);

    p.setTemporizador(15);

    CHECK(p.getTemporizador() == 15);
}

TEST_CASE("Alterar estado do portao") {
    Portao p(4);

    p.alterarEstado(true);
    CHECK(p.getEstado() == true);

    p.alterarEstado(false);
    CHECK(p.getEstado() == false);
}

TEST_CASE("Fechamento automatico desliga o portao") {
    Portao p(5);

    p.alterarEstado(true);
    p.setTemporizador(0);

    p.fecharAutomaticamente();

    CHECK(p.getEstado() == false);
}

TEST_CASE("Deteccao de erro executa corretamente") {
    Portao p(6);

    CHECK_NOTHROW(p.detectarErro());
}