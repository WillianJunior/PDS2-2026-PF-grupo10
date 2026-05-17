#ifndef COMODO_HPP
#define COMODO_HPP

#include "Dispositivo.hpp"

/** @class Comodo
 * @brief Representa cada espaco fisico da casa e gerencia seus dispositivos.
 * A classe Comodo armazena os dispositivos cadastrados, permite adicionar,
 * remover e buscar dispositivos pelo ID. */
class Comodo{
    
private:
    Dispositivo** dispositivos;   ///< Vetor de ponteiros para os dispositivos da Comodo
    int qtdDispositivos;          ///< Quantidade de dispositivos cadastrados

public:
    /** @brief Construtor da classe Comodo. */
    Comodo();

    /** @brief Destrutor da classe Comodo. */
    ~Comodo();

    /** @brief Busca um dispositivo pelo seu ID.
     * @param id ID do dispositivo procurado.
     * @return Ponteiro para o dispositivo encontrado, ou nullptr se não existir. */
    Dispositivo* getDispositivo(int id);

    /** @brief Adiciona um dispositivo ao Comodo.
     * @param dispositivo Ponteiro para o dispositivo que será adicionado. */
    void adicionarDispositivo(Dispositivo* dispositivo);

    /** @brief Remove um dispositivo do Comodo pelo ID.
     * @param id ID do dispositivo que será removido. */
    void removerDispositivo(int id);

    /** @brief Retorna a quantidade atual de dispositivos cadastrados.
     * @return Quantidade de dispositivos. */
    int getQtdDispositivos() const;
};

#endif
