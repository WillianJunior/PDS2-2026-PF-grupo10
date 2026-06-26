#include "doctest.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "InterfaceTextual.hpp"


TEST_CASE("Testes de Unidade - InterfaceTextual (sem entrada do usuario)") {

    InterfaceTextual interface;

    SUBCASE("Exibicao inicial nao deve pedir input") {
        CHECK_NOTHROW(interface.exibirMenuPrincipal());
    }

    SUBCASE("Exibir relatorio sem bloquear") {
        std::istringstream entrada("\n");
        auto* cinOriginal = std::cin.rdbuf(entrada.rdbuf());

        CHECK_NOTHROW(interface.exibirRelatorio());

        std::cin.rdbuf(cinOriginal);
    }

    SUBCASE("Interpretador aceita comandos invalidos") {
        CHECK_NOTHROW(interface.interpretarComando(""));
        CHECK_NOTHROW(interface.interpretarComando("comando_inexistente"));
        CHECK_NOTHROW(interface.interpretarComando("focar abc"));
        CHECK_NOTHROW(interface.interpretarComando("entrar "));
    }

    SUBCASE("Comandos de navegacao invalidos nao travam") {
        CHECK_NOTHROW(interface.interpretarComando("entrar quarto"));
        CHECK_NOTHROW(interface.interpretarComando("voltar"));
        CHECK_NOTHROW(interface.interpretarComando("comodo"));
    }

    SUBCASE("Exibir menu de comodo inexistente") {
        CHECK_NOTHROW(interface.exibirMenuComodo(""));
        CHECK_NOTHROW(interface.exibirMenuComodo("comodo_que_nao_existe"));
    }

    SUBCASE("Máquina de Estados de Navegação (Menus e Focos)") {

        // Cenário: Usuário simula a entrada em um cômodo específico
        // O interpretador deve atualizar internamente a string 'menuAtual' para "COMODO" e 'comodoFocado'
        interface.interpretarComando("ir_para_comodo Quarto");
        
        // Testa se o método aceita a renderização baseada na mudança de estado anterior
        interface.exibirMenuComodo("Quarto");

        // Cenário: Usuário foca em um dispositivo específico (ex: ID 42)
        interface.interpretarComando("focar_dispositivo 42");

        // Cenário: Voltar ao menu principal limpa ou altera o foco
        interface.interpretarComando("voltar_menu_principal");
    }

    SUBCASE("Robustez do Interpretador de Comandos (Parser de String)") {

        // Passar comandos inexistentes, mal formatados
        // ou vazios não pode causar travamento (Crash/Segmentation Fault) do software.
        interface.interpretarComando("");
        interface.interpretarComando("LIGAR_LUZ_SEM_ID_E_COM_TEXTO_ERRADO");
        interface.interpretarComando("ir_para_comodo  "); // Múltiplos espaços
        interface.interpretarComando("focar_dispositivo -9999"); // ID inválido / negativo
    }

    SUBCASE("Exibir ajuda sem bloquear") {
        std::istringstream entrada("\n");
        auto* cinOriginal = std::cin.rdbuf(entrada.rdbuf());

        CHECK_NOTHROW(interface.exibirAjuda());

        std::cin.rdbuf(cinOriginal);
    }

    SUBCASE("Encerrar pode ser chamado sem iniciar") {
        CHECK_NOTHROW(interface.encerrar());
    }
}
