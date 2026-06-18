#ifndef MACRO_H
#define MACRO_H

#include <string>
#include <memory>

/** @struct Node
 * @brief Representa um nó da lista encadeada de uma macro. */
struct Node {
    int id;                       ///< Identificador do dispositivo associado à ação
    std::string acao;             ///< Ação a ser executada no dispositivo (valores esperados: "ligar",
                                  ///"desligar", "abrir", "fechar" e "ajustar")
    std::unique_ptr<Node> proximo;                ///< Ponteiro para o próximo nó da lista
};

/** @class Macro
 * @brief Representa uma macro de ações associadas a um evento.
 * Permite agrupar múltiplas ações sobre diferentes dispositivos.
 * Esse agrupamento é feito por uma lista encadeada, onde cada nó contém o dispositivo 
 * e a operação a ser executada sobre ele. */
class Macro{

    private:
    std::string evento; ///< Nome do evento que ativa a macro 
    std::unique_ptr<Node> lista;        ///< Lista encadeada de ações sobre dispositivos

public:
    /** @brief Contador global que rastreia o número total de instâncias de macros ativas.
     *  Atributo estático compartilhado por todas as instâncias da classe, incrementado no
     *  construtor e decrementado no destrutor. */
    static int qtdMacros;  

    /** @brief Construtor da classe Macro.
     *  Inicializa o nome do evento, configura o ponteiro da lista encadeada de ações como nulo
     *  (lista vazia) e incrementa o contador estático global `qtdMacros`.
     *  @param evento Nome identificador do evento associado a esta macro. */
    Macro(std::string evento);

    /** @brief Destrutor da classe Macro.
     *  Libera a memória de todos os nós da lista encadeada de ações para evitar vazamento de memória
     *  e decrementa o contador estático global `qtdMacros`. */
    ~Macro(); 
    
    /** @brief Consulta o nome do evento associado à macro.
     *  @return string O nome do evento que dispara esta macro. */
    std::string getEvento() const;

    /** @brief Retorna o ponto de entrada para a sequência de ações da macro.
     *  @return Node* Ponteiro para o primeiro elemento da lista encadeada de comandos. */
    Node* getLista() const;

    /** @brief Atualiza o nome do evento atrelado à macro.
     *  @param evento Novo nome identificador para o gatilho da macro. */
    void setEvento(std::string evento);

    /** @brief Insere uma nova instrução de comando no final da sequência de execução.
     *  Aloca dinamicamente um novo nó contendo o ID do alvo e a operação desejada, inserindo-o
     *  no final da lista encadeada.
     *  @param id Identificador numérico do dispositivo que sofrerá a ação.
     *  @param acao Comando textual a ser disparado (ex: "ligar", "desligar", "abrir", "fechar", "ajustar"). */
    void adicionarDispositivo(int id, std::string acao);

    /** @brief Remove uma instrução de comando específica da sequência da macro.
     *  Varre a lista encadeada em busca do primeiro nó que coincida simultaneamente com o ID e a ação fornecidos.
     *  Se encontrado, ajusta os ponteiros vizinhos, libera a memória do nó e encerra a busca.
     *  @param id Identificador do dispositivo cuja ação será removida.
     *  @param acao A descrição exata do comando que se deseja retirar da sequência. */
    void removerDispositivo(int id, std::string acao);
};

#endif