#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <string>

/** @class Dispositivo
 * @brief Classe abstrata que representa um dispositivo genérico da casa inteligente.
 * Esta classe define atributos e comportamentos comuns a todos os dispositivos. */
class Dispositivo {

protected: // Mudado para protected para que as subclasses tenham acesso
    int id;               ///< Identificador único do dispositivo
    std::string comodo;   ///< Cômodo onde o dispositivo está localizado
    bool estado;          ///< Estado atual (false = desligado/fechado, true = ligado/aberto)
    bool erro;            ///< Indica se o dispositivo apresenta falha 

public:
    /** @brief Contador global que rastreia o número total de dispositivos criados no sistema. */
    static int qtdDispositivos;

    /** @brief Construtor da classe base Dispositivo.
     * Define o ID e o cômodo de instalação e incrementa o contador estático global `qtdDispositivos`.
     * @param id Identificador numérico único que representará o dispositivo.
     * @param comodo Referência constante para a string com o nome do cômodo de instalação. */
    Dispositivo(int id, const std::string &comodo);

    /** @brief Destrutor virtual da classe Dispositivo.
     * Garante que os destrutores das classes derivadas (como Luz, Som, ArCondicionado) sejam chamados 
     * corretamente ao deletar um objeto por meio de um ponteiro da classe base, evitando vazamentos de memória.
     * Também decrementa o contador estático `qtdDispositivos`. */
    virtual ~Dispositivo(); 

    /** @brief Consulta o identificador numérico único do dispositivo.
     * @return int O ID correspondente ao dispositivo corrente. */
    int getId() const;

    /** @brief Consulta o local/cômodo onde o dispositivo está fisicamente mapeado.
     * @return std::string String contendo o nome do cômodo associado. */
    std::string getComodo() const;

    /** @brief Consulta o estado lógico de funcionamento do dispositivo.
     * @return true Se o aparelho estiver ativo.
     * @return false Se o aparelho estiver inativo. */
    bool getEstado() const;

    /** @brief Verifica se o dispositivo foi marcado com alguma falha de funcionamento.
     * @return true Se houver um problema técnico detectado previamente pelo sensor ou hardware.
     * @return false Se o funcionamento do aparelho estiver normal. */
    bool temErro() const;

    /** @brief Modifica o estado lógico (ativo/inativo) do dispositivo.
     * @param novoEstado Flag booleano representando o comando desejado (true para ligar/abrir, false para desligar/fechar). */
    virtual void alterarEstado(bool novoEstado); 

    /** @brief Realiza a varredura e diagnóstico interno de falhas no hardware ou parâmetros.
     * Método virtual puro. */
    virtual void detectarErro() = 0; 

    /** @brief Monta uma string descritiva com os detalhes atuais e específicos da operação do dispositivo.
     * Método virtual puro. 
     * @return std::string Texto legível detalhando o estado atual (ex: "Ligado - Volume 12" ou "Fechado"). */
    virtual std::string getEstadoFormatado() const = 0;
};

#endif