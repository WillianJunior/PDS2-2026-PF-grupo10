#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>

using std::string;

/** @class Sensor
 * @brief Monitora dispositivos e gera alertas de falhas. */
class Sensor {

private:
    int tempoVerificacao;   ///< Tempo entre verificações dos dispositivos (em segundos) 
    string alertas[100];    ///< Lista de alertas gerados pelo sensor 

public:
    /** @brief Construtor da classe Sensor.
     * Inicializa o módulo de monitoramento configurando o intervalo inicial de varredura 
     * e alocando a estrutura interna para o histórico de alertas.
     * @param tempoVerificacao Intervalo de tempo inicial (em segundos) entre as checagens do sensor. */
    Sensor(int tempoVerificacao);

    /** @brief Destrutor da classe Sensor.
     * Libera a memória e os recursos associados ao sensor, limpando o histórico de strings 
     * armazenadas no vetor de alertas para evitar desperdício de memória. */
    ~Sensor();

    /** @brief Consulta o intervalo atual de varredura do sensor.
     * @return int O tempo de ciclo atual configurado, expresso em segundos. */
    int getTempoVerificacao() const;

    /** @brief Recebe uma mensagem de alerta específica com base no índice.
     * @param i Índice posicional da mensagem dentro do vetor de alertas do sensor.
     * @return string O texto descritivo do alerta encontrado se o índice for válido, ou uma 
     *         string vazia caso esteja fora dos limites. */
    string getAlertas(int i) const;

    /** @brief Atualiza a frequência de varredura e checagem do sensor.
     * Modifica o temporizador interno que dita de quanto em quanto tempo o sensor lê o ambiente.
     * @param segundos Novo intervalo de tempo desejado para as verificações. */
    void alterarTempoVerificacao(int segundos);

    /** @brief Realiza a leitura dos dispositivos conectados e registra anomalias encontradas.
     * Varre o estado atual do hardware do sistema, gera as mensagens de erro pertinentes e as 
     * armazena sequencialmente no vetor interno de alertas. */
    void salvarAlertas();
};

#endif
