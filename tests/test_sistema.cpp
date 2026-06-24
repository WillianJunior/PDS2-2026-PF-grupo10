#include "doctest.h"
#include "Sistema.hpp"
#include "Comodo.hpp"

TEST_CASE("Testes de Unidade - Classe Sistema") {

    // O sistema central é instanciado
    Sistema sistemaHome;

    SUBCASE("Inicialização Padrão e Ciclo de Vida dos Atributos") {

        // O sistema deve iniciar desligado/inativo até ser explicitamente executado
        CHECK(sistemaHome.estaAtivo() == false);

        // A lista de cômodos deve iniciar vazia
        CHECK(sistemaHome.getComodo(0) == nullptr);
        CHECK(sistemaHome.getComodo(-1) == nullptr);
    }

    SUBCASE("Controle de Ativação e Execução") {

        sistemaHome.executarSistema();

        CHECK(sistemaHome.estaAtivo() == true);
    }

    SUBCASE("Gerenciamento de Cômodos (Adicionar, Consultar e Tratar Limites)") {
        // Adicionando cômodos
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Sala de Estar")));
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Cozinha")));
        // Verifica se os cômodos foram armazenados corretamente
        CHECK(sistemaHome.getComodo(0) != nullptr);
        CHECK(sistemaHome.getComodo(1) != nullptr);

        // Índices inválidos
        CHECK(sistemaHome.getComodo(-1) == nullptr);
        CHECK(sistemaHome.getComodo(2) == nullptr);
    }

    SUBCASE("Remoção de Cômodos e Validação de Ponteiros") {
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Quarto")));

        // Recupera ponteiro antes da remoção
        const Comodo* cAntes = sistemaHome.getComodo(0);

        REQUIRE(cAntes != nullptr);

        // Remove cômodo
        sistemaHome.removerComodo(cAntes);

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