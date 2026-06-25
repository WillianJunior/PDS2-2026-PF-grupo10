#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <string>

/** @class Dispositivo
 *  @brief Classe abstrata que representa um dispositivo genérico da casa inteligente.
 *  Esta classe define atributos e comportamentos comuns a todos os dispositivos. */
class Dispositivo {

protected: // Protected para que as subclasses tenham acesso
    int id;               ///< Identificador único do dispositivo
    bool estado;          ///< Estado atual (false = desligado/fechado, true = ligado/aberto)
    bool erro;            ///< Indica se o dispositivo está com algum problema de funcionamento
    std::string nome;     ///< Nome da classe do dispositivo

public:
    /** @brief Contador global que rastreia o número total de dispositivos criados no sistema. */
    static int qtdDispositivos;

    /** @brief Contador estático usado para gerar IDs únicos de dispositivos.
     *  Nunca é decrementado para garantir unicidade. */
    static int identificador;

    /** @brief Construtor da classe base Dispositivo.
     *  Gera um ID único para a nova instância, configura o estado inicial e incrementa
     *  o contador estático global `qtdDispositivos`. */
    Dispositivo();

    Dispositivo(const Dispositivo&) = delete;

    Dispositivo& operator=(const Dispositivo&) = delete;

    /** @brief Destrutor virtual da classe Dispositivo.
     *  Garante que os destrutores das classes derivadas (como Luz, Som, ArCondicionado) sejam chamados
     *  corretamente ao deletar um objeto por meio de um ponteiro da classe base, evitando vazamentos de memória.
     *  Também decrementa o contador estático `qtdDispositivos`. */
    virtual ~Dispositivo(); 

    /** @brief Retorna o identificador do dispositivo.
     *  @return int ID do dispositivo */
    int getId() const;

    /** @brief Retorna o estado do dispositivo.
     *  @return true Se o dispositivo estiver ativo (ligado/aberto).
     *  @return false Se o dispositivo estiver inativo (desligado/fechado). */
    bool getEstado() const;

    /** @brief Verifica se o dispositivo foi marcado com alguma falha de funcionamento.
     *  @return true Se houver um problema técnico detectado previamente pelo sensor ou hardware.
     *  @return false Se o funcionamento do aparelho estiver normal. */
    bool temErro() const;

    /** @brief Retorna o nome da classe do dispositivo.
     *  @return std::string Nome do tipo de dispositivo (ex: "Luz", "Som", "ArCondicionado"). */
    std::string getNome() const;

    void setId(int novoId);
    
    /** @brief Modifica o estado lógico (ativo/inativo) do dispositivo.
     *  @param novoEstado Flag booleano representando o comando desejado (true para ligar/abrir, false para desligar/fechar). */
    virtual void alterarEstado(bool novoEstado); 

    /** @brief Realiza a varredura e diagnóstico interno de falhas no hardware ou parâmetros.
     *  Método virtual puro. */
    virtual void detectarErro() = 0; 

    /** @brief Monta uma string descritiva com os detalhes atuais e específicos da operação do dispositivo.
     *  Método virtual puro.
     *  @return std::string Texto legível detalhando o estado atual (ex: "Ligado - Volume 12" ou "Fechado"). */
    virtual std::string getEstadoFormatado() const = 0;
};

#endif