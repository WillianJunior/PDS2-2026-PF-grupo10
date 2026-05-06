#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>

using std::string;

/**
 * @class Sensor
 * @brief Monitora dispositivos e gera alertas de falhas.
 */
class Sensor {
private:
    int tempoVerificacao;
    string alertas[100];

public:
    /**
     * @brief Construtor da classe Sensor.
     * @param tempoVerificacao Tempo entre verificações.
     */
    Sensor(int tempoVerificacao);

    /**
     * @brief Destrutor da classe Sensor.
     */
    ~Sensor();

    /**
     * @brief Retorna o tempo de verificação.
     * @return Tempo em segundos.
     */
    int getTempoVerificacao();

    /**
     * @brief Retorna um alerta pelo índice.
     * @param i Índice do alerta.
     * @return Texto do alerta.
     */
    string getAlertas(int i);

    /**
     * @brief Altera o tempo de verificação.
     * @param segundos Novo tempo em segundos.
     */
    void alterarTempoVerificacao(int segundos);

    /**
     * @brief Verifica dispositivos e salva alertas.
     */
    void salvarAlertas();
};

#endif
