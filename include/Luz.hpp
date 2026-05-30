#ifndef LUZ_HPP
#define LUZ_HPP

#include "Dispositivo.hpp"
#include <string>


/** @class Luz
 * @brief Classe na qual representa um dispositivo de iluminação automatizado. 
 * A classe Luz herda de Dispositivo e permite controlar a intensidade da luz (níveis de 1 a 5).  
 * Além disso, esse sistema consegue detectar erros/falhas que prejudicam o funcionamento. */
class Luz : public Dispositivo {

private:
    int intensidade;    ///< Intensidade da luz (1 a 5)

public:
    /** @brief Construtor parametrizado da classe Luz.
     * Inicializa uma nova instância de iluminação automatizada com um ID gerado automaticamente.
     * O ID exclusivo é fornecido pela classe base Dispositivo. */
    Luz();

    /** @brief Destrutor da classe Luz.
     * Libera os recursos específicos alocados para este ponto de iluminação e encerra 
     * qualquer comunicação ou rotina ativa do dispositivo. */
    ~Luz();

    /** @brief Consulta o nível atual de brilho da luz.
     * @return int Valor inteiro representando a intensidade, escalonada estritamente de 1 a 5. */
    int getIntensidade() const;

    /** @brief Altera o nível de brilho da luz.
     * Modifica o atributo interno de intensidade para o valor fornecido, atualizando o estado do hardware.
     * @param intensidade Novo valor de brilho a ser aplicado, devendo respeitar o intervalo de 1 a 5. */
    void ajustarIntensidade(int intensidade);

    /** @brief Varre o estado do dispositivo em busca de problemas operacionais.
     * Sobrescreve o método da classe base. Avalia se a intensidade está fora do limite 
     * permitido (1 a 5) ou se há perda de conexão, colocando a luz em estado de erro se necessário. */
    void detectarErro() override;

    /** @brief Retorna uma descrição textual do estado atual da luz.
     * Informa se a luz está ligada ou desligada e pode incluir
     * o nível de intensidade configurado.
     * @return std::string Texto formatado representando o estado da luz. */
    std::string getEstadoFormatado() const override;

};

#endif