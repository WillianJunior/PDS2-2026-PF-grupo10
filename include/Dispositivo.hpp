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
    static int qtdDispositivos; ///< Quantidade total de dispositivos criados

    /** @brief Construtor da classe Dispositivo.
     * @param id Identificador do dispositivo 
     * @param comodo Nome do cômodo onde ele está instalado */
    Dispositivo(int id, const std::string &comodo);

    /** @brief Destrutor virtual da classe Dispositivo. 
     * @note Essencial como virtual para o correto funcionamento do polimorfismo. */
    virtual ~Dispositivo(); 


    /** @brief Retorna o identificador do dispositivo.
     * @return int ID do dispositivo */
    int getId() const;

    /** @brief Retorna o cômodo do dispositivo.
     * @return std::string Nome do cômodo */
    std::string getComodo() const;

    /** @brief Retorna o estado do dispositivo.
     * @return true Se o dispositivo estiver ativo (ligado/aberto).
     * @return false Se o dispositivo estiver inativo (desligado/fechado). */
    bool getEstado() const;

    /** @brief Indica se o dispositivo apresenta erro.
     * @return true Se o dispositivo estiver com falha.
     * @return false Caso contrário. */
    bool temErro() const;
    

    /** @brief Altera o estado do dispositivo.
     * @param novoEstado Novo estado desejado. */
    virtual void alterarEstado(bool novoEstado); 

    /** @brief Detecta falhas no dispositivo.
     * @note Método virtual puro (torna a classe abstrata). */
    virtual void detectarErro() = 0; 

    /** @brief Formata e retorna o estado atual específico do dispositivo.
     * Exemplo: "Ligado - Intensidade 5" ou "Aberto".
     * @return std::string Estado formatado */
    virtual std::string getEstadoFormatado() const = 0;
};

#endif