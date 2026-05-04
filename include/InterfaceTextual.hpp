#ifndef INTERFACETEXTUAL_HPP
#define INTERFACETEXTUAL_HPP

#include <string>
#include <vector>
#include "Usuario.hpp"
#include "Sistema.hpp"

class InterfaceTextual{

private:
    /** @brief quantidade de interfaces */
    static int qtdInterfaces;

    /** @brief ponteiro para o sistema principal */
    Sistema* sistema;

    /** @brief indica se a interface está ativa */
    bool ativa; 

    /** @brief ponteiro para o usuário atual */
    Usuario* usuarioAtual;

public:
    /** @brief inicia o uso da interface */
    void iniciar(); 

    /** @brief le o comando inserido pelo usuário*/
    void lerComando(); 

     /** @brief interpreta um comando fornecido pelo usuário 
     * @param comando comando a ser interpretado */
    void interpretarComando(const std::string &comando); 

    /** @brief exibe uma mensagem ao usuário
     * @param mensagem mensagem a ser exibida */
    void exibirMensagem(const std::string &mensagem); 

    /** @brief exibe uma lista de alertas ao usuário
     * @param alertas veetor contendo as mensagens de alerta */
    void exibirAlerta(std::vector<std::string> &alertas); 

    /** @brief exibe o estado de um dispositivo
     * @param ID identificador do dispositivo */
    void exibirEstado(int ID); 

    /** @brief encerra o uso da interface */
    void encerrar();
};

#endif