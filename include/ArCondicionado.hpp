#ifndef ARCONDICIONADO_HPP
#define ARCONDICIONADO_HPP

#include "Dispositivo.hpp"
#include <string>


/** @class ArCondicionado
 *  @brief Classe que representa um ar-condicionado automatizado.
 *  Permite controlar o estado a temperatura
 *  (entre 15 e 30 graus Celsius), além de detectar falhas. */
class ArCondicionado : public Dispositivo {

private:
    int temperatura; ///< Temperatura do ar-condicionado (15 a 30)

public:
    /** @brief Construtor da classe ArCondicionado.
     *  Inicializa o dispositivo de climatização com um ID gerado automaticamente.
     *  O ID exclusivo é fornecido pela classe base Dispositivo. */
    ArCondicionado();

    /** @brief Destrutor da classe ArCondicionado.
     *  Libera os recursos alocados para o módulo de climatização e encerra
     *  a comunicação ativa do aparelho. */
    ~ArCondicionado();

    void ligar() { this->estado = true; }

    void desligar() {this->estado = false; }

    /** @brief Consulta a temperatura atualmente configurada no aparelho.
     *  @return int Valor inteiro da temperatura ideal alvo, estabelecida entre 15°C e 30°C. */
    int getTemperatura() const;

    /** @brief Altera a temperatura alvo do dispositivo.
     *  Atualiza o termostato interno com o novo valor fornecido, desde que esteja dentro da faixa operacional.
     *  @param temperatura Nova temperatura desejada, contida estritamente no intervalo de 15 a 30. */
    void ajustarTemperatura(int temperatura);

    /** @brief Avalia o estado operacional do aparelho para identificar falhas.
     *  Sobrescreve o método da classe base. Dispara alarmes caso a temperatura configurada
     *  estoure os limites permitidos (15 a 30) ou se houver perda de conexão */
    void detectarErro() override;

    /** @brief Retorna uma descrição textual do estado atual do ar-condicionado.
     *  Informa se o dispositivo está ligado ou desligado e pode incluir
     *  informações adicionais, como a temperatura configurada.
     *  @return std::string Texto formatado representando o estado do ar-condicionado. */
    std::string getEstadoFormatado() const override;
};

#endif

