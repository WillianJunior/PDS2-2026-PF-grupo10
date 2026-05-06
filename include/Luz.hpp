#ifndef LUZ_HPP
#define LUZ_HPP

#include "Dispositivo.hpp"
#include <string>

using namespace std;

/** @class Luz
 * @brief Classe na qual representa um dispositivo de iluminação automatizado. 
 * A classe Luz herda de Dispositivo e permite controlar a intensidade da luz (níveis de 1 a 5).  
 * Além disso, esse sistema consegue detectar erros/falhas que prejudicam o funcionamento. */
class Luz : public Dispositivo {

private:
    int intensidade;    ///< Intensidade da luz (1 a 5)

public:

    /** @brief Construtor da classe Luz 
     * @param id Identificador do dispositivo
     * @param comodo Nome do cômodo onde a luz está instalada */
    Luz(int id, string comodo);

    /** @brief Destrutor da classe Luz */
    ~Luz();

    /** @brief Retorna a intensidade atual da luz 
     * @return int Intensidade (1 a 5) */
    int getIntensidade();

    /** @brief Regula a intensidade da luz 
     * @param intensidade Novo valor (1 a 5) */
    void ajustarIntensidade(int intensidade);

    /** @brief Detecta falhas no funcionamento do dispositivo 
     * Verifica:
     * - Intensidade fora do intervalo permitido
     * - Dispositivo offline */
    void detectarErro() override;
};

#endif