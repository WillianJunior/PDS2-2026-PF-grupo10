#ifndef PORTAO_HPP
#define PORTAO_HPP

#include "Dispositivo.hpp"
#include <string>
#include <ctime> //temporizador

/**
 * @class Portão
 * @brief Classe que representa o algoritmo de controle automático do portão.
 *
 * Implementa funções de abrir/fechar o portão e manter um temporizador enquanto aberto.
 *
 */

class Portao : public Dispositivo{
private:
    int segundos;
public:
    /** @brief Construtor de cada objeto.*/
    Portao(int id);

    /** @brief Destrutor */
    ~Portao();

//--------------------

    //getters

    /** @brief Retorna o valor do estado do portão
    *   @return "aberto" ou "fechado"
    *
    */
    bool getEstado() override;

    /** @brief Retorna o valor do temporizador atual*/
    int getTemporizador();

    //setters

    /** @brief Muda o valor do temporizador com base no parâmetro dado
    *   @param seg tempo até fechar
    */
    void setTemporizador(int seg);

//------------------

    /** @brief Execução do fechamento automático com temporizador */
    void fecharAutomaticamente();

    /** @brief Muda o estado de erro caso detecte algum problema */
    void detectarErro() override;

};

#endif
