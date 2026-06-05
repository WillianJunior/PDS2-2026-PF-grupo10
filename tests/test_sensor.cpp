#include "doctest.h"
#include "Sensor.hpp"

TEST_CASE("Testes de Unidade - Classe Sensor") {
    // Cenário inicial: Um sensor configurado para checagens a cada 10 segundos
    Sensor meuSensor(10);

    SUBCASE("Inicialização e Atributos") {
        CHECK(meuSensor.getTempoVerificacao() == 10);
        
        // No início, a lista de alertas deve estar limpa/vazia
        // Testando os limites iniciais do array
        CHECK(meuSensor.getAlerta(0) == "");
        CHECK(meuSensor.getAlerta(50) == "");
    }

    SUBCASE("Modificação do Tempo de Verificação") {
        meuSensor.alterarTempoVerificacao(30);
        CHECK(meuSensor.getTempoVerificacao() == 30);

        // O tempo não deve ser negativo ou zero
        meuSensor.alterarTempoVerificacao(-5);
        CHECK(meuSensor.getTempoVerificacao() > 0); // Deve ignorar o valor inválido ou manter o anterior
    }

    SUBCASE("Tratamento de Índices Inválidos no Histórico de Alertas") {
        // Testando os limites estritos do array de tamanho 100 (0 a 99)
        // Devem retornar uma string vazia conforme especificado na documentação
        CHECK(meuSensor.getAlerta(-1) == "");
        CHECK(meuSensor.getAlerta(100) == "");
        CHECK(meuSensor.getAlerta(999) == "");
    }

    SUBCASE("Varredura de Dispositivos e Geração de Alertas") {
        // Executa a rotina que varre o sistema em busca de erros
        meuSensor.salvarAlertas();

        // Em uma simulação de TDD onde não há dispositivos reais acoplados ainda,
        // o comportamento padrão esperado pode ser nenhum alerta gerado:
        CHECK(meuSensor.getAlerta(0) == "");
    }
}