#ifndef PORTAO_HPP
#define PORTAO_HPP

#include "Dispositivo.hpp"
#include <string>
#include <ctime> //temporizador

/** @class Portão
 *  @brief Classe que representa o algoritmo de controle automático do portão.
 *  Implementa funções de abrir/fechar o portão e manter um temporizador enquanto aberto. */
class Portao : public Dispositivo{

private:
    int segundos; ///< Armazena o tempo em segundos

public:
    /** @brief Construtor da classe Portao.
     *  Inicializa uma nova instância de um portão automatizado com um identificador único.
     *  Configura o estado inicial do portão como fechado, coloca valor padrão no temporizador 
     * (30 segundos) para fechamento automático e garante que os flags de erro comecem limpos (falsos). */
    Portao();

    /** @brief Destrutor da classe Portao.
     *  Responsável por liberar quaisquer recursos de hardware ou memória alocados
     *  dinamicamente para este portão específico. Garante um encerramento seguro,
     *  interrompendo rotinas de temporização ativas antes da destruição do objeto. */
    ~Portao();

    /** @brief Consulta o tempo restante ou configurado no temporizador.
     *  Recupera o valor atual do cronômetro interno que gerencia o fechamento
     *  automático do portão.
     *  @return int O tempo configurado ou a contagem regressiva atual em segundos. */
    int getTemporizador() const;

    /** @brief Define ou atualiza o tempo de espera para o fechamento automático.
     *  Modifica o atributo interno do temporizador. Este valor define por quanto tempo
     *  o portão permanecerá totalmente aberto antes que o sistema envie o comando
     *  de fechamento automático.
     *  @param seg Tempo de espera desejado, expresso estritamente em segundos, deve ser maior que 0. */
    void setTemporizador(int seg);

    /** @brief Inicia a rotina de contagem regressiva e executa o fechamento do portão.
     *  Monitora o estado do portão durante o tempo definido no temporizador.
     *  Assim que a contagem chega a zero (e se nenhum erro for encontrado),
     *  altera o estado do portão para "fechando" e, posteriormente, "fechado". */
    void fecharAutomaticamente();

    /** @brief Analisa os sensores físicos do portão para identificar e registrar falhas.
     *  Sobrescreve o método da classe base. Realiza uma varredura em busca de
     *  problemas operacionais.
     *  Caso um problema seja detectado, altera o estado interno do portão para "Erro" e
     *  interrompe imediatamente qualquer movimento ou temporização por motivos de segurança. */
    void detectarErro() override;

    /** @brief Retorna uma descrição textual do estado atual do portão.
     *  Informa se o portão está aberto ou fechado, podendo incluir
     *  informações relacionadas ao tempo para fechamento automático.
     *  @return std::string Texto formatado representando o estado do portão. */
    std::string getEstadoFormatado() const override;

};

#endif
