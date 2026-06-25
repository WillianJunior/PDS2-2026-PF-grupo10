#include "doctest.h"
#include "Sistema.hpp"
#include "Comodo.hpp"

TEST_CASE("Testes de Unidade - Classe Sistema") {

    Sistema sistemaHome;

    SUBCASE("Inicialização Padrão e Ciclo de Vida dos Atributos") {

        CHECK(sistemaHome.estaAtivo() == false);

        CHECK(sistemaHome.getComodo(static_cast<int>(0)) == nullptr);
        CHECK(sistemaHome.getComodo(-1) == nullptr);
        CHECK(sistemaHome.getComodo("") == nullptr);
    }

    SUBCASE("Controle de Ativação e Execução") {

        sistemaHome.executarSistema();

        CHECK(sistemaHome.estaAtivo() == true);
    }

    SUBCASE("Gerenciamento de Cômodos (Adicionar, Consultar e Tratar Limites)") {
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Sala de Estar")));
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Cozinha")));
        
        CHECK(sistemaHome.getComodo(static_cast<int>(0)) != nullptr);
        CHECK(sistemaHome.getComodo(1) != nullptr);
        CHECK(sistemaHome.getComodo("Sala de Estar") != nullptr);

        CHECK(sistemaHome.getComodo(-1) == nullptr);
        CHECK(sistemaHome.getComodo(2) == nullptr);
        CHECK(sistemaHome.getComodo("Banheiro") == nullptr);
    }

    SUBCASE("Remoção de Cômodos e Validação de Ponteiros") {
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Quarto")));

        const Comodo* cAntes = sistemaHome.getComodo(static_cast<int>(0));

        REQUIRE(cAntes != nullptr);

        sistemaHome.removerComodo(cAntes);

        CHECK(sistemaHome.getComodo(static_cast<int>(0)) == nullptr);
    }

    SUBCASE("Processamento e Parser de Comandos Textuais (CLI)") {

        sistemaHome.executarSistema();

        sistemaHome.receberComando("");

        sistemaHome.receberComando(
            "PROXIMA_MUSICA_DO_MUNDO_INTEIRO_SINAL_INVALIDO 12345"
        );

        sistemaHome.receberComando("ligar 101");

        sistemaHome.receberComando("ajustar_temperatura 22");
    }
}