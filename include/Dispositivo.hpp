#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <string>
using namespace std;

/** @class Dispositivo
 * @brief Classe abstrata que representa um dispositivo genérico da casa inteligente.
 * Esta classe define atributos e comportamentos comuns a todos os dispositivos,
 * como identificação, cômodo onde está localizado, estado e possíveis falhas. */
class Dispositivo{

    private:
    int id;         ///< Identificador único do dispositivo
    bool estado;    ///< Estado atual do dispositivo (0 = ligado/aberto, 1 = desligado/fechado)
    bool erro;      ///< Indica se o dispositivo apresenta falha 

public:
    static int qtdDispositivos; ///< Quantidade total de dispositivos criados

    /** @brief Construtor da classe Dispositivo.
     * @param id Identificador do dispositivo */
    Dispositivo(int id);

     /** @brief Destrutor da classe Dispositivo. */
    ~Dispositivo(); 

    /** @brief Retorna o identificador do dispositivo.
     * @return int ID do dispositivo */
    int getId();

    /** @brief Retorna o estado do dispositivo.
     * @return true Se o dispositivo estiver ativo (ligado/aberto).
     * @return false Se o dispositivo estiver inativo (desligado/fechado). */
    bool getEstado();

    /** @brief Indica se o dispositivo apresenta erro.
     * @return true Se o dispositivo estiver com falha.
     * @return false Caso contrário. */
    bool temErro();
    
    /** @brief Altera o estado do dispositivo.
     * @details O estado só é modificado se for diferente do atual.
     * @param estado Novo estado desejado. */
    void alterarEstado(bool estado); 

    /** @brief Detecta falhas no dispositivo. */
    virtual void detectarErro() = 0; 

};

#endif