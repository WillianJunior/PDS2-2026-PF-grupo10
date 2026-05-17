#ifndef INTERFACETEXTUAL_HPP
#define INTERFACETEXTUAL_HPP

#include <string>
#include <vector>
#include "Usuario.hpp"
#include "Sistema.hpp"

/** @brief Interface textual para interação com o sistema.
 * Permite ao usuário enviar comandos, visualizar mensagens,
 * alertas e estados de dispositivos. */
class InterfaceTextual{

private: 
    static int qtdInterfaces;   ///< Quantidade de interfaces 
    Sistema* sistema;           ///< Ponteiro para o sistema principal 
    bool ativa;                 ///< Indica se a interface está ativa  
    Usuario* usuarioAtual;      ///< Ponteiro para o usuário atual

public:
    /** @brief Inicializa a interface textual/gráfica para o usuário.
     * Prepara o ambiente de interação, exibe a mensagem de boas-vindas e coloca a interface 
     * pronta para receber os primeiros dados de entrada. */
    void iniciar(); 

    /** @brief Captura a entrada de texto fornecida pelo usuário no console.
     * Aguarda a digitação de uma linha de comando, limpa buffers se necessário e encaminha 
     * o texto capturado para as rotinas de processamento. */
    void lerComando(); 

    /** @brief Analisa a sintaxe e executa a ação correspondente ao comando recebido.
     * Atua como o núcleo de controle da interface, mapeando a string de texto para as 
     * funções internas do sistema de automação.
     * @param comando Referência constante para a string contendo o comando a ser processado. */
    void interpretarComando(const std::string &comando); 

    /** @brief Imprime uma mensagem na tela do usuário.
     * @param mensagem Referência constante para o texto que deve ser exibido no console. */
    void exibirMensagem(const std::string &mensagem); 

    /** @brief Percorre e exibe todas as mensagens de erro ou avisos do sistema.
     * @param alertas Referência para o vetor de strings contendo o histórico de problemas 
     * detectados pelos sensores. */
    void exibirAlerta(std::vector<std::string> &alertas); 

    /** @brief Busca e exibe na tela os parâmetros atuais (ex: ligado/desligado, temperatura) de um aparelho.
     * @param ID Identificador numérico único do dispositivo que terá seu estado consultado. */
    void exibirEstado(int ID); 

    /** @brief Finaliza as atividades da interface e libera seus recursos visuais.
     * Exibe a mensagem de despedida, fecha fluxos de entrada/saída abertos e interrompe o 
     * loop de captura de comandos. */
    void encerrar();
};

#endif