#ifndef COMODO_HPP
#define COMODO_HPP

#include "Dispositivo.hpp"
#include <string>

using namespace std;

/** @class Comodo
 * @brief Representa cada espaco fisico da casa e gerencia seus dispositivos.
 * A classe Comodo armazena os dispositivos cadastrados, permite adicionar,
 * remover e buscar dispositivos pelo ID. */
class Comodo{
    
private:
    int id;                         ///< Identificador do cômodo
    string nome;                   ///< Nome do cômodo

    Dispositivo** dispositivos;    ///< Vetor de ponteiros para os dispositivos da Comodo
    int qtdDispositivos;           ///< Quantidade de dispositivos cadastrados

public:
    /** @brief Construtor padrão da classe Comodo.
     * Inicializa a estrutura do cômodo, zerando o contador de dispositivos e preparando 
     * o conteiner interno (vetor/lista) que armazenará as referências dos dispositivos. */
    Comodo() {
        id = 0;
        nome = "";
        dispositivos = nullptr;
        qtdDispositivos = 0;
    }

    /** @brief Construtor parametrizado da classe Comodo.
     * Inicializa o cômodo com um identificador e um nome.
     * @param id Identificador numérico do cômodo.
     * @param nome Nome textual do cômodo. */
    Comodo(int id, string nome) {
        this->id = id;
        this->nome = nome;
        dispositivos = nullptr;
        qtdDispositivos = 0;
    }

    /** @brief Destrutor da classe Comodo.
     * Libera a memória e os recursos associados ao cômodo, limpando o contêiner de macros 
     * e gerenciando a destruição ou desvinculação da lista de dispositivos alocados para 
     * evitar vazamentos de memória. */
    ~Comodo() {}

    /** @brief Retorna o identificador do cômodo.
     * @return int ID do cômodo. */
    int getId() const {
        return id;
    }

    /** @brief Retorna o nome do cômodo.
     * @return string Nome do cômodo. */
    string getNome() const {
        return nome;
    }

    /** @brief Busca um dispositivo cadastrado no cômodo através do seu identificador.
     * Percorre a lista interna comparando o ID fornecido com o de cada dispositivo.
     * @param id Identificador numérico único do dispositivo procurado.
     * @return Dispositivo* Ponteiro para a instância encontrada, ou nullptr caso o ID não exista no cômodo. */
    Dispositivo* getDispositivo(int id) const {
        return nullptr;
    }

    /** @brief Insere um novo dispositivo no mapa de controle do cômodo.
     * Adiciona o ponteiro do objeto ao contêiner interno, permitindo que ele receba comandos direcionados ao cômodo.
     * @param dispositivo Ponteiro para o objeto do dispositivo a ser acoplado. */
    void adicionarDispositivo(Dispositivo* dispositivo) {}

    /** @brief Remove um dispositivo do cômodo com base no seu ID.
     * Busca o dispositivo pelo identificador, retira sua referência do contêiner interno e, se necessário, 
     * libera sua memória. Se o ID não for encontrado, nenhuma ação é tomada.
     * @param id Identificador numérico do dispositivo a ser removido. */
    void removerDispositivo(int id) {}

    /** @brief Consulta o total de dispositivos atualmente vinculados a este cômodo.
     * @return int O número inteiro que representa a quantidade atual de dispositivos monitorados. */
    int getQtdDispositivos() const {
        return qtdDispositivos;
    }
};

#endif