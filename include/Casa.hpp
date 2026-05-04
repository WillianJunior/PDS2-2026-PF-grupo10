#ifndef CASA_HPP
#define CASA_HPP

#include "Dispositivo.hpp"

/** @class Casa
 * @brief Representa a residência e gerencia seus dispositivos.
 * A classe Casa armazena os dispositivos cadastrados, permite adicionar,
 * remover e buscar dispositivos pelo ID. */
class Casa {
    
private:
    static const int MAX_DISPOSITIVOS = 50;

    Dispositivo* dispositivos[MAX_DISPOSITIVOS];
    int qtdDispositivos;

public:
    /** @brief Construtor da classe Casa. */
    Casa();

    /** @brief Destrutor da classe Casa. */
    ~Casa();

    /** @brief Busca um dispositivo pelo seu ID.
     * @param id ID do dispositivo procurado.
     * @return Ponteiro para o dispositivo encontrado, ou nullptr se não existir. */
    Dispositivo* getDispositivo(int id);

    /** @brief Adiciona um dispositivo à casa.
     * @param dispositivo Ponteiro para o dispositivo que será adicionado. */
    void adicionarDispositivo(Dispositivo* dispositivo);

    /** @brief Remove um dispositivo da casa pelo ID.
     * @param id ID do dispositivo que será removido. */
    void removerDispositivo(int id);

    /** @brief Retorna a quantidade atual de dispositivos cadastrados.
     * @return Quantidade de dispositivos. */
    int getQtdDispositivos() const;
};

#endif
