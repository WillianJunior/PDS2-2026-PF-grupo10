#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>

#include "Comodo.hpp"
#include "Sensor.hpp"
#include "Macro.hpp"

using std::string;

/** @class Sistema
 * @brief Controla o funcionamento geral do sistema Smart Home.
 * A classe Sistema é responsável por controlar a execução do sistema,
 * gerenciar a casa, sensores, macros e comandos recebidos da interface textual. */
class Sistema {
    
private:

    bool ativo;           ///< Indica se o sistema está ativo
    Comodo** comodos;     ///< Vetor de ponteiros para os cômodos
    Sensor* sensor;       ///< Sensor responsável pelo monitoramento do sistema
    Macro** macros;       ///< Vetor de macros do sistema
    int qtdMacros;        ///< Quantidade de macros cadastradas

public:
    /** @brief Construtor da classe Sistema.
     * Inicializa a Comodo, o sensor, o vetor de macros e cria a macro padrão
     * "sair de casa". */
    Sistema();

    /** @brief Destrutor da classe Sistema. */
    ~Sistema();

    /** @brief Retorna um cômodo pelo índice.
     * @param i Índice da cômodo no vetor.
     * @return Ponteiro para o cômodo, ou nullptr se o índice for inválido. */
    Comodo* getComodo(int i);

    /** @brief Retorna o sensor associado ao sistema.
     * @return Ponteiro para o objeto Sensor. */
    Sensor* getSensor();

    /** @brief Retorna uma macro pelo índice.
     * @param i Índice da macro no vetor.
     * @return Ponteiro para a macro encontrada, ou nullptr se o índice for inválido. */
    Macro* getMacro(int i);

    /** @brief Verifica se o sistema está ativo.
     * @return true se o sistema estiver ativo, false caso contrário. */
    bool estaAtivo() const;

    /** @brief Liga ou executa o sistema. */
    void executarSistema();

    /** @brief Adiciona uma nova macro ao sistema.
     * @param evento Nome do evento associado à macro. */
    void adicionarMacro(string evento);

    /** @brief Remove uma macro do sistema.
     * @param evento Nome do evento associado à macro. */
    void removerMacro(string evento);

    /** @brief Executa uma macro cadastrada.
     * @param evento Nome do evento da macro que será executada. */
    void executarMacro(string evento);

    /** @brief Recebe e processa um comando vindo da interface textual.
     * @param comando Comando textual recebido. */
    void receberComando(const string& comando);

    /** @brief Adiciona um novo cômodo ao sistema.
     * @param comodo Cômodo a ser adicionado ao sistema. */
    void adicionarComodo(Comodo comodo);

    /** @brief Remove um cômodo do sistema.
     * @param comodo Referência para o cômodo a ser removido. */
    void removerComodo(const Comodo& comodo);
};

#endif
