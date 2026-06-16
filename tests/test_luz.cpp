/**
 * @file test_luz.cpp
 * @brief Testes unitários para a classe Luz utilizando o framework Doctest.
 * Componente do sistema Smart Home - PDS2 (UFMG)
 */

#include "doctest.h" // Certifique-se de que o doctest.h está na sua pasta include ou de terceiros
#include "Luz.hpp"

TEST_CASE("Testando a classe Luz - Gerenciamento de Iluminação") {
    
    // Instanciamos uma lâmpada base que será reinicializada para cada SUBCASE
    Luz lampada;

    SUBCASE("Cenário 1: Inicialização e Valores Padrão") {
        // Valida se o dispositivo recebeu um identificador válido
        CHECK(lampada.getId() > 0);
   //     CHECK(lampada.getComodo() == "Cozinha");
        
        // Atributos herdados da base Dispositivo
        CHECK(lampada.getEstado() == false); // Deve iniciar desligada
        CHECK(lampada.temErro() == false);   // Deve iniciar sem falhas
        
        // Atributo específico da Luz
        CHECK(lampada.getIntensidade() == 1); // Intensidade inicial padrão (mínima)
    }

    SUBCASE("Cenário 2: Alteração de Estados (Ligar/Desligar)") {
        // Testa a função herdada de alterar o estado lógico
        lampada.ligar();
        CHECK(lampada.getEstado() == true);

        lampada.desligar();
        CHECK(lampada.getEstado() == false);
    }

    SUBCASE("Cenário 3: Ajuste de Intensidade Dentro dos Limites") {
        // Testa valores válidos de brilho (limite intermediário e superior)
        lampada.ajustarIntensidade(3);
        CHECK(lampada.getIntensidade() == 3);

        lampada.ajustarIntensidade(5);
        CHECK(lampada.getIntensidade() == 5);
    }

    SUBCASE("Cenário 4: Formatação Polimórfica do Estado para a Interface") {
        lampada.desligar();
        lampada.ajustarIntensidade(4);
        
        std::string formato = lampada.getEstadoFormatado();
        
        // Verifica se a string gerada contém informações cruciais sobre o estado atual
        CHECK(formato.find("Ligada") != std::string::npos);
        CHECK(formato.find("4") != std::string::npos);
    }

    SUBCASE("Cenário 5: Monitoramento e Detecção de Erros (User Story 8)") {
        // Simulamos uma anomalia forçando um valor de intensidade inválido (fora de 1..5)
        lampada.ajustarIntensidade(12);
        
        // Dispara o método de varredura
        lampada.detectarErro();
        
        // O sistema deve identificar o parâmetro incorreto e ativar a flag de erro
        CHECK(lampada.temErro() == true);
    }
}