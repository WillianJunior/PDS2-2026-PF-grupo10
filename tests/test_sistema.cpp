#include "doctest.h"
#include "Sistema.hpp"
#include "Comodo.hpp"

TEST_CASE("Testes de Unidade - Classe Sistema") {

    // O sistema central é instanciado
    Sistema sistemaHome;

    SUBCASE("Inicialização Padrão e Ciclo de Vida dos Atributos") {

        // O sistema deve iniciar desligado/inativo até ser explicitamente executado
        CHECK(sistemaHome.estaAtivo() == false);

        // O construtor deve alocar automaticamente o sensor principal
        CHECK(sistemaHome.getSensor() != nullptr);

        // A lista de cômodos deve iniciar vazia
        CHECK(sistemaHome.getComodo(0) == nullptr);
        CHECK(sistemaHome.getComodo(-1) == nullptr);
    }

    SUBCASE("Controle de Ativação e Execução") {

        sistemaHome.executarSistema();

        CHECK(sistemaHome.estaAtivo() == true);
    }

    SUBCASE("Gerenciamento de Cômodos (Adicionar, Consultar e Tratar Limites)") {

        // Criando cômodos de teste
        Comodo sala(1, "Sala de Estar");
        Comodo cozinha(2, "Cozinha");

        // Adicionando cômodo
        sistemaHome.adicionarComodo(sala);

        // Recuperando cômodo
        Comodo* cRecuperado = sistemaHome.getComodo(0);

        REQUIRE(cRecuperado != nullptr);

        CHECK(cRecuperado->getNome() == "Sala de Estar");

        // Adicionando segundo cômodo
        sistemaHome.adicionarComodo(cozinha);

        CHECK(sistemaHome.getComodo(1) != nullptr);

        // Índice fora do limite
        CHECK(sistemaHome.getComodo(2) == nullptr);
    }

    SUBCASE("Remoção de Cômodos e Validação de Ponteiros") {

        Comodo quarto(3, "Quarto");

        sistemaHome.adicionarComodo(quarto);

        // Recupera ponteiro antes da remoção
        Comodo* cAntes = sistemaHome.getComodo(0);

        REQUIRE(cAntes != nullptr);

        // Remove cômodo
        sistemaHome.removerComodo(*cAntes);

        // Verifica remoção
        CHECK(sistemaHome.getComodo(0) == nullptr);
    }

    SUBCASE("Processamento e Parser de Comandos Textuais (CLI)") {

        sistemaHome.executarSistema();

        // Comandos inválidos
        sistemaHome.receberComando("");

        sistemaHome.receberComando(
            "PROXIMA_MUSICA_DO_MUNDO_INTEIRO_SINAL_INVALIDO 12345"
        );

        // Comandos válidos
        sistemaHome.receberComando("ligar 101");

        sistemaHome.receberComando("ajustar_temperatura 22");
    }
}