#ifndef MACRO_H
#define MACRO_H

#include "Dispositivo.hpp"
#include "Casa.hpp"
#include <string>
using namespace std;

/** @struct Node
 * @brief Representa um nó da lista encadeada de uma macro. */
struct Node {
    Dispositivo* dispositivo;    ///< Ponteiro para o dispositivo associado ao nó 
    string acao;                 ///< Ação a ser executada no dispositivo (Valores esperados: "ligar", 
                                 ///"desligar", "abrir", "fechar" e "ajustar")
    Node* proximo;               ///< Ponteiro para o próximo nó da lista 
};

/** @class Macro
 * @brief Representa uma macro de ações associadas a um evento.
 * Permite agrupar múltiplas ações sobre diferentes dispositivos.
 * Esse agrupamento é feito por uma lista encadeada, onde cada nó contém o dispositivo 
 * e a operação a ser executada sobre ele. */
class Macro{

    private:
    string evento; ///< Nome do evento que ativa a macro 
    Node* lista;   ///< Lista encadeada de ações sobre dispositivos 

    public:
    /** @brief Quantidade total de macros criadas */
    static int qtdMacros;  

     /** @brief Construtor da classe Macro.
     * Inicializa o evento da macro e incrementa o contador estático.
     * A lista de ações é iniciada como vazia.
     * @param evento Nome do evento associado à macro. */
    Macro(string evento);

    /** @brief Destrutor da classe Macro. */
    ~Macro(); 
    
    /** @brief Retorna o evento da macro.
     * @return string Nome do evento. */    
    string getEvento();

    /** @brief Retorna a lista de ações da macro.
     * @return Ponteiro para o primeiro nó da lista. */        
    Node* getLista();


    /** @brief Define o evento da macro.
     * @param evento Novo nome do evento. */
    void setEvento(string evento);

    /** @brief Adiciona uma ação associada a um dispositivo na macro.
     * @details
     * Cria um novo nó a partir do id e ação a ser executada, que é inserido ao final da lista encadeada.
     * @param id Identificador do dispositivo.
     * @param acao Ação a ser executada (ex: "ligar", "desligar", "abrir", "fechar" e "ajustar"). */
    void adicionarDispositivo(int id, string acao);

    /**
     * @brief Remove uma ação de um dispositivo da macro.
     * @details
     * Remove o nó da lista de acordo com o id e a ação a ser executada.
     * Caso existam múltiplos nós iguais, apenas o primeiro encontrado é removido.
     * @param id Identificador do dispositivo.
     * @param acao Ação associada ao dispositivo a ser removida. */
    void removerDispositivo(int id, string acao); //remove nó da lista 
};

#endif