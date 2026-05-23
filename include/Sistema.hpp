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
 * gerenciar os cômodos, sensores e comandos recebidos da interface textual. */
class Sistema {
    
private:

    bool ativo;           ///< Indica se o sistema está ativo
    Comodo** comodos;     ///< Vetor de ponteiros para os cômodos
    Sensor* sensor;       ///< Sensor responsável pelo monitoramento do sistema

public:

    /** @brief Construtor padrão da classe Sistema. 
     * Inicializa os componentes principais do sistema de automação residencial.
     * Aloca e configura a estrutura interna da casa, inicializa o sensor principal
     * e o vetor dinâmico de macros. */
    Sistema();

    /** @brief Destrutor da classe Sistema. 
     * Garante a liberação correta de memória e recursos. Desaloca os ponteiros
     * armazenados no vetor de comodos e destrói o objeto sensor associado, 
     * evitando vazamentos de memória. */
    ~Sistema();

    /** @brief Identifica um cômodo específico da casa com base no seu índice de armazenamento. 
     * @param i Índice posicional do cômodo dentro do vetor de gerenciamento da casa.
     * @return Comodo* Ponteiro para o objeto do cômodo correspondente se o índice for válido; 
     *         Retorna `nullptr` caso o índice seja negativo ou maior/igual ao tamanho do vetor. */
    Comodo* getComodo(int i) const;

    /** @brief Retorna o sensor principal associado e gerenciado pelo sistema. 
     * Permite o acesso externo ao objeto de monitoramento para leitura de estados,
     * ou configurações diretas no dispositivo de entrada.
     * @return Sensor* Ponteiro para a instância do objeto Sensor ativo no sistema. */
    Sensor* getSensor() const;


    /** @brief Verifica o estado de operação atual do sistema. 
     * Método de consulta que indica se as rotinas de automação, monitoramento
     * e resposta à comandos estão ativos no momento.
     * @return true Se o sistema estiver inicializado e rodando ativamente.
     * @return false Se o sistema estiver desligado. */
    bool estaAtivo() const;

    /** @brief Inicia o loop principal de execução do sistema.
     * Altera o estado do sistema para ativo, coloca os sensores em modo de leitura
     * e passa a receber, processar e responder aos comandos do usuário. */
    void executarSistema();

    /** @brief Interpreta e processa comandos textuais brutos recebidos da interface com o usuário (CLI). 
     * Este método atua como o parser do sistema. Ele analisa a string de comando recebida,
     * valida a sintaxe e a semântica em relação às funções do sistema e invoca os métodos 
     * internos correspondentes (como ligar aparelhos, listar cômodos ou criar macros).
     * @param comando Referência constante para a string contendo a linha de comando enviada pelo usuário. */
    void receberComando(const string& comando);

    /** @brief Adiciona um novo cômodo à estrutura de gerenciamento da casa. 
     * Insere o objeto fornecido no vetor interno de cômodos do sistema.
     * @param comodo Referência para o objeto Comodo que se deseja vincular ao sistema. */
    void adicionarComodo(Comodo& comodo);

    /** @brief Remove um cômodo específico do sistema de monitoramento. 
     * Varre a lista de cômodos cadastrados para encontrar o que corresponda à referência fornecida. 
     * O cômodo deixa de responder aos comandos globais do sistema.
     * @param comodo Referência constante para o objeto Comodo que se deseja desvincular do sistema. */
    void removerComodo(const Comodo& comodo);
};

#endif
