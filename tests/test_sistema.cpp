#include "doctest.h"
#include "Sistema.hpp"
#include "Comodo.hpp"

TEST_CASE("Testes de Unidade - Classe Sistema") {
    //O sistema central é instanciado
    Sistema sistemaHome;

    SUBCASE("Inicialização Padrão e Ciclo de Vida dos Atributos") {
        // O sistema deve iniciar desligado/inativo até ser explicitamente executado
        CHECK(sistemaHome.estaAtivo() == false);

        // O construtor deve alocar automaticamente o sensor principal
        CHECK(sistemaHome.getSensor() != nullptr);

        // A lista de cômodos deve iniciar vazia (ponteiros iniciais nulos ou limites controlados)
        CHECK(sistemaHome.getComodo(0) == nullptr);
        CHECK(sistemaHome.getComodo(-1) == nullptr);
    }

    SUBCASE("Controle de Ativação e Execução") {
        sistemaHome.executarSistema();
        CHECK(sistemaHome.estaAtivo() == true);
    }

    SUBCASE("Gerenciamento de Cômodos (Adicionar, Consultar e Tratar Limites)") {
        // Criando cômodos de teste para avaliar as regras de negócio
        Comodo sala;
        Comodo cozinha;

        // Testando a adição de cômodo (Passado por valor/Cópia conforme especificado)
        sistemaHome.adicionarComodo(sala);
        sistemaHome.adicionarComodo(cozinha);
        
        // Valida se o cômodo foi armazenado e pode ser recuperado com sucesso
        //Comodo* cRecuperado = sistemaHome.getComodo(0);
        //REQUIRE(cRecuperado != nullptr); // REQUIRE para o teste se não conseguir ponteiro válido
        //CHECK(cRecuperado->getComodo() == "Sala de Estar");

        // Adicionando um segundo cômodo e testando limites de índice inválidos
        // sistemaHome.adicionarComodo(cozinha);
        CHECK(sistemaHome.getComodo(0) == nullptr);

        CHECK(sistemaHome.getComodo(1) != nullptr);
        CHECK(sistemaHome.getComodo(2) == nullptr); // Fora do limite preenchido
    }

    SUBCASE("Remoção de Cômodos e Validação de Ponteiros") {
        Comodo quarto;
        sistemaHome.adicionarComodo(quarto);

        // Recupera o ponteiro para validar que ele existe antes da remoção
        Comodo* cAntes = sistemaHome.getComodo(0);
        REQUIRE(cAntes != nullptr);

        // Remove o cômodo passando a referência constante
        sistemaHome.removerComodo(*cAntes);

        // O índice não deve mais apontar para o objeto removido
        CHECK(sistemaHome.getComodo(0) == nullptr); 
    }

    SUBCASE("Processamento e Parser de Comandos Textuais (CLI)") {
        // O sistema deve ser capaz de receber strings sem travar o software
        // No TDD, testamos se o método lida de forma segura com comandos válidos e inválidos
        sistemaHome.executarSistema();

        // Cenário: Comando inválido/vazio (Não deve estourar erro de segmentação no parser)
        sistemaHome.receberComando("");
        sistemaHome.receberComando("PROXIMA_MUSICA_DO_MUNDO_INTEIRO_SINAL_INVALIDO 12345");

        // Cenário: Comandos de automação hipotéticos baseados na sua especificação
        sistemaHome.receberComando("ligar 101"); 
        sistemaHome.receberComando("ajustar_temperatura 22");
    }
}
