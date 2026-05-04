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
    /** @brief Quantidade de interfaces */
    static int qtdInterfaces;

    /** @brief Ponteiro para o sistema principal */
    Sistema* sistema;

    /** @brief Indica se a interface está ativa */
    bool ativa; 

    /** @brief Ponteiro para o usuário atual */
    Usuario* usuarioAtual;

public:
    /** @brief Inicia o uso da interface */
    void iniciar(); 

    /** @brief Lê o comando inserido pelo usuário*/
    void lerComando(); 

     /** @brief Interpreta um comando fornecido pelo usuário 
     * @param comando comando a ser interpretado */
    void interpretarComando(const std::string &comando); 

    /** @brief Exibe uma mensagem ao usuário
     * @param mensagem mensagem a ser exibida */
    void exibirMensagem(const std::string &mensagem); 

    /** @brief Exibe uma lista de alertas ao usuário
     * @param alertas veetor contendo as mensagens de alerta */
    void exibirAlerta(std::vector<std::string> &alertas); 

    /** @brief Exibe o estado de um dispositivo
     * @param ID identificador do dispositivo */
    void exibirEstado(int ID); 

    /** @brief Encerra o uso da interface */
    void encerrar();
};

#endif