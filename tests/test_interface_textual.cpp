#include "doctest.h"
#include <string>
#include <vector>
#include "InterfaceTextual.hpp"


TEST_CASE("Testes de Unidade - Classe InterfaceTextual") {
    // Cenário inicial: Instanciação da interface
    InterfaceTextual interface;

    SUBCASE("Inicialização Padrão e Controle de Ciclo de Vida") {
        // Antes de iniciar(), o estado deve estar bem definido ou inativo
        // Vamos forçar a rotina de inicialização via TDD
        // interface.iniciar();

        // No TDD, definimos os comportamentos esperados após o boot da interface:
        // O menu inicial padrão esperado pela regra de negócio deve ser o "PRINCIPAL"
        // Como esses atributos são privados, testamos a estabilidade dos métodos de exibição iniciais:
        interface.exibirMenuPrincipal();
        interface.exibirRelatorio();
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

    SUBCASE("Rotinas de Encerramento da Aplicação") {
       interface.iniciar();
        
        // Garante o desligamento correto do loop da interface textual
        interface.encerrar();
        // Após encerrar, o estado da interface deve ser limpo ou inativo
    }
}
