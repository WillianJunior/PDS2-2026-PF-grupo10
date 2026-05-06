#ifndef ARCONDICIONADO_HPP
#define ARCONDICIONADO_HPP

#include "Dispositivo.hpp"
#include <string>

using namespace std;

/** @class ArCondicionado
 * @brief Classe que representa um ar-condicionado automatizado.
 * Permite controlar o estado a temperatura
 * (entre 15 e 30 graus Celsius), além de detectar falhas. */
class ArCondicionado : public Dispositivo {

private:
    int temperatura; ///< Temperatura do ar-condicionado (15 a 30)

public:
    /** @brief Construtor da classe ArCondicionado 
     * @param id Identificador do dispositivo
     * @param comodo Nome do cômodo */
    ArCondicionado(int id, string comodo);

    /** @brief Destrutor da classe ArCondicionado */
    ~ArCondicionado();

    /** @brief Retorna a temperatura atual 
     * @return int Temperatura (15 a 30) */
    int getTemperatura();

    /** @brief Ajusta a temperatura do dispositivo 
     * @param temperatura Nova temperatura (15 a 30) */
    void ajustarTemperatura(int temperatura);

    /** @brief Detecta erros no funcionamento 
     * Verifica:
     * - Temperatura fora do intervalo permitido
     * - Dispositivo offline */
    void detectarErro() override;
};

#endif