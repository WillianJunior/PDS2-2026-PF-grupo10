#include "doctest.h"
#include "ArCondicionado.hpp"

TEST_CASE("Testando o Construtor e Inicialização") {
    ArCondicionado ar;
    
    CHECK(ar.getId() > 0);
    
    CHECK(ar.getEstado() == false); // Deve iniciar desligado
    CHECK(ar.temErro() == false);   // Deve iniciar sem falhas
    CHECK(ar.getTemperatura() == 22); // Temperatura padrão definida no construtor
}

TEST_CASE("Testando Ligar e Desligar") {
    ArCondicionado ar;
    
    ar.ligar();
    CHECK(ar.getEstado() == true); // Deve estar ligado

    ar.desligar();
    CHECK(ar.getEstado() == false); // Deve estar desligado
}

TEST_CASE("Testando Ajuste de Temperatura - Limites Válidos") {
    ArCondicionado ar;
    
    ar.ajustarTemperatura(15);
    CHECK(ar.getTemperatura() == 15);
    
    ar.ajustarTemperatura(30);
    CHECK(ar.getTemperatura() == 30);
    
    ar.ajustarTemperatura(22);
    CHECK(ar.getTemperatura() == 22);
}

TEST_CASE("Testando Ajuste de Temperatura - Valores Inválidos") {
    ArCondicionado ar;
    ar.ajustarTemperatura(22); // Estado inicial conhecido
    
    ar.ajustarTemperatura(14); // Inválido (Abaixo)
    CHECK(ar.getTemperatura() == 22); // Deve manter o valor antigo ou lançar exceção
    
    ar.ajustarTemperatura(31); // Inválido (Acima)
    CHECK(ar.getTemperatura() == 22);
}

TEST_CASE("Testando Detecção de Erros") {
    ArCondicionado ar;
    
    // Cenário normal
    ar.ajustarTemperatura(25);
    ar.detectarErro();

    CHECK(ar.temErro() == false); // Depende de como a classe base gerencia o estado de erro
}