#ifndef INTERFACETEXTUAL_HPP
#define INTERFACETEXTUAL_HPP

#include <string>
#include <vector>
#include <memory>
#include "Usuario.hpp"
#include "Sistema.hpp"

/** @brief Interface textual para interação com o sistema de Smart Home.
 * Controla os estados de navegação (menus), captura comandos do usuário
 * e exibe o estado dos cômodos, dispositivos e alertas. */
class InterfaceTextual {

private: 
    static int qtdInterfaces;                   ///< Quantidade de interfaces ativas
    std::unique_ptr<Sistema> sistema;           ///< Ponteiro para o sistema principal (regras de negócio)
    bool ativa;                                 ///< Indica se o loop da interface está ativo  
    std::unique_ptr<Usuario> usuarioAtual;      ///< smart pointer para o usuário logado no sistema

    std::string menuAtual;      ///< Armazena a tela atual (ex: "PRINCIPAL", "COMODO", "DISPOSITIVO")
    std::string comodoFocado;   ///< Armazena o nome do cômodo que o usuário está inspecionando no momento
    int dispositivoFocadoID;    ///< ID do dispositivo selecionado para configurações detalhadas

public:

    InterfaceTextual();
    /** @brief Inicializa a interface, exibe as boas-vindas e carrega o menu inicial. */
    void iniciar(); 

    /** @brief Lê a entrada do usuário, analisa a sintaxe e executa a ação correspondente ao comando recebido.
     *  @param comando Referência para a string contendo o comando a ser processado. */
    void interpretarComando(const std::string &comando); 

    /** @brief Finaliza as atividades da interface e limpa o estado de execução. */
    void encerrar();
    
    /** @brief Exibe o menu principal com as opções de navegação da casa (Ver cômodos, alertas, macros, relatório). */
    void exibirMenuPrincipal();

    /** @brief Exibe as opções e comandos possíveis dentro de um cômodo específico.
     *  @param nomeComodo Nome do cômodo a ser renderizado. */
    void exibirMenuComodo(const std::string &nomeComodo);

    /** @brief Exibe as opções e comandos possíveis dentro de um dispositivo.
     *  @param id ID do dispositivo a ser renderizado. */
    void exibirDispositivoFocado(int id);

    /** @brief Exibe o arquivo de relatório detalhado com informações sobre todos os cômodos e dispositivos. */
    void exibirRelatorio();

    /** @brief Percorre o sistema e lista textualmente todos os cômodos cadastrados. */
    void exibirComodos();

    /** @brief Limpa o console para garantir que a interface textual fique organizada a cada comando. */
    void limparTela();

    /** @brief Imprime uma mensagem padrão de feedback na tela do usuário.
     *  @param mensagem Texto a ser exibido. */
    void exibirMensagem(const std::string &mensagem); 

    /** @brief Percorre e exibe de forma destacada os avisos e problemas detectados por sensores.
     *  @param alertas Vetor de strings contendo o histórico de alertas do sistema. */
    void exibirAlerta(std::vector<std::string> &alertas); 

    /** @brief Busca e exibe detalhadamente as propriedades atuais de um aparelho específico.
     *  @param ID Identificador único do dispositivo. */
    void exibirEstado(int ID); 

    void exibirAjuda();
};

#endif