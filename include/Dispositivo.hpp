#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <string>
using namespace std;

/** @class Dispositivo
 * @brief Classe abstrata que representa um dispositivo genérico da casa inteligente.
 * Esta classe define atributos e comportamentos comuns a todos os dispositivos,
 * como identificação, cômodo onde está localizado, estado e possíveis falhas.
 */
class Dispositivo{
    private:
    int id;         /**< Identificador único do dispositivo */
    string comodo;  /**< Nome do cômodo onde o dispositivo está localizado */
    bool estado;    /**< Estado atual do dispositivo (0 = ligado/aberto, 1 = desligado/fechado) */
    bool erro;      /**< Indica se o dispositivo apresenta falha */

    public:
    static int qtdDispositivos; /**< Quantidade total de dispositivos criados */

    /**
     * @brief Construtor da classe Dispositivo.
     * @details
     * Inicializa o dispositivo com um id e um cômodo, além de incrementar
     * o contador estático de dispositivos.
     * @param id Identificador do dispositivo
     * @param comodo Nome do cômodo onde o dispositivo está
     */
    Dispositivo(int id, string comodo);

     /**
     * @brief Destrutor da classe Dispositivo.
     */
    ~Dispositivo(); 

    /**
     * @brief Retorna o identificador do dispositivo.
     * @return int ID do dispositivo
     */
    int getId();

    /**
     * @brief Retorna o cômodo em que o dispositivo está.
     * @return string Nome do cômodo em que o dispositivo está.
     */
    string getComodo();

        /**
     * @brief Retorna o estado do dispositivo.
     * @details
     * O valor retornado representa o estado lógico do dispositivo.
     * A interpretação de true ou false depende da subclasse.
     * @return true Se o dispositivo estiver ativo (ligado/aberto).
     * @return false Se o dispositivo estiver inativo (desligado/fechado).
     */
    bool getEstado();

    /**
     * @brief Indica se o dispositivo apresenta erro.
     * @return true Se o dispositivo estiver com falha.
     * @return false Caso contrário.
     */
    bool temErro();
    
    /**
     * @brief Altera o estado do dispositivo.
     * @details
     * O estado só é modificado se for diferente do atual.
     * @param estado Novo estado desejado.
     */
    void alterarEstado(bool estado); 

    /**
     * @brief Detecta falhas no dispositivo.
     * @details
     * Método abstrato que deve ser implementado pelas subclasses,
     * definindo como cada tipo de dispositivo identifica erros.
     */
    virtual void detectarErro() = 0; 

};

#endif