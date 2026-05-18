#include "doctest.h"
/**
 * @file test_luz.cpp
 * @brief Testes unitários automatizados para a classe concreta Luz.
 * Componente do sistema Smart Home - PDS2 (UFMG)
 */

#include <iostream>
#include <cassert>
#include <string>
#include "Luz.hpp"

int main() {
    // Sinaliza o início dos testes no console
    std::cout << "=========================================" << std::endl;
    std::cout << "    INICIANDO TESTES DA CLASSE LUZ       " << std::endl;
    std::cout << "=========================================" << std::endl;

    // ------------------------------------------------------------------------
    // CENÁRIO 1: Teste de Instanciação e Inicialização Padrão
    // ------------------------------------------------------------------------
    // Criamos uma lâmpada com ID 101 na cozinha para validar o construtor.
    Luz lampada1(101, "Cozinha");
    
    // Verificamos os atributos herdados e específicos
    assert(lampada1.getId() == 101);
    assert(lampada1.getComodo() == "Cozinha");
    assert(lampada1.getEstado() == false);       // Deve iniciar inativa (desligada)
    assert(lampada1.getIntensidade() == 1);       // Valor padrão mínimo configurado no construtor
    assert(lampada1.temErro() == false);          // Deve iniciar em estado estável (sem falhas)
    
    std::cout << "[PASSO 1/5] Inicializacao e getters basicos: OK!" << std::endl;

    // ------------------------------------------------------------------------
    // CENÁRIO 2: Teste de Ajuste de Intensidade Válida
    // ------------------------------------------------------------------------
    // Modificamos a intensidade para o valor limite superior e valores intermediários
    lampada1.ajustarIntensidade(4);
    assert(lampada1.getIntensidade() == 4);
    
    lampada1.ajustarIntensidade(5);
    assert(lampada1.getIntensidade() == 5);
    
    std::cout << "[PASSO 2/5] Controle de intensidade (limites validos): OK!" << std::endl;

    // ------------------------------------------------------------------------
    // CENÁRIO 3: Teste do Comportamento Herdado (Ligar/Desligar)
    // ------------------------------------------------------------------------
    // Testamos o método da classe base adaptado para herança
    lampada1.alterarEstado(true); // Liga a lâmpada
    assert(lampada1.getEstado() == true);
    
    std::cout << "[PASSO 3/5] Heranca do metodo alterarEstado: OK!" << std::endl;

    // ------------------------------------------------------------------------
    // CENÁRIO 4: Teste de Formatação de Estado Polimórfico
    // ------------------------------------------------------------------------
    // Avaliamos se a string de exibição para a InterfaceTextual contém os dados necessários
    std::string stringEstado = lampada1.getEstadoFormatado();
    
    // O assert abaixo valida se as palavras-chave esperadas existem na string gerada
    assert(stringEstado.find("Ligada") != std::string::npos || stringEstado.find("5") != std::string::npos);
    
    std::cout << "[PASSO 4/5] Polimorfismo de getEstadoFormatado: OK!" << std::endl;

    // ------------------------------------------------------------------------
    // CENÁRIO 5: Teste de Detecção de Erros (User Story 8 - Simulação de Falhas)
    // ------------------------------------------------------------------------
    // Simulamos um comportamento anormal que viola a regra de negócio (intensidade fora de 1..5)
    // Para testar, configuramos uma intensidade inválida diretamente (ou simulando falha do hardware)
    lampada1.ajustarIntensidade(12); 
    
    // Disparamos a varredura do sensor de segurança
    lampada1.detectarErro();
    
    // O sistema deve reconhecer a quebra de parâmetros e setar a flag de erro para true
    assert(lampada1.temErro() == true);
    
    std::cout << "[PASSO 5/5] Infeccao e deteccao automatica de falhas: OK!" << std::endl;

    // ------------------------------------------------------------------------
    // CONCLUSÃO DOS TESTES
    // ------------------------------------------------------------------------
    std::cout << "=========================================" << std::endl;
    std::cout << " [SUCESSO] Todos os testes de Luz passaram!" << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}