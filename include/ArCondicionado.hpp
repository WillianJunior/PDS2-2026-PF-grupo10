#ifndef ARCONDICIONADO_HPP
#define ARCONDICIONADO_HPP

#include "Dispositivo.hpp"
#include <string>

using namespace std;

/** @class ArCondicionado
 * @brief Classe na qual representa um ar condicionado automatizado.
 * Permite controlar a temperatura (entre 18 e 30 graus Celsius) e 
 * o estado (ligado/desligado), além de detectar falhas/erros. */
class ArCondicionado : public Dispositivo {
    
private:
    /** @brief Temperatura do ar condicionado (18 a 30) */
    int temperatura;  

public:

    /** @brief Construtor da classe ArCondicionado
     * @param id Identificador do dispositivo
     * @param comodo Nome do cômodo que o dispositivo está instalado */
    ArCondicionado(int id, string comodo);

    /** @brief Destrutor da classe ArCondicionado. */
    ~ArCondicionado();

    /** @brief Retorna o estado atual do ar condicionado 
     * @return "ligado" ou "desligado" */
    string getEstado() override;

    /** @brief Retorna a temperatura atual
     * @return int Temperatura (18 a 30) */
    int getTemperatura();

    /** @brief Ajusta a temperatura do ar-condicionado 
     * @param temperatura Nova temperatura (18 a 30) */
    void ajustarTemperatura(int temperatura);

    /** @brief Detecta erros no funcionamento
     * Verifica:
     * - Estado incompreendido 
     * - Temperatura fora do intervalo permitido
     * - Dispositivo offline */
    void detectarErro() override;
};

#endif