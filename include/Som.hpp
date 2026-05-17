#ifndef SOM_HPP
#define SOM_HPP

#include "Dispositivo.hpp"
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

/** @class Som
 * @brief Dispositivo conectado ao sistema que executa as funcoes de tocar e gerenciar musicas.
 * A classe Som herda de Dispositivo e permite controlar a lista de faixas tocando agora, adicionar novas faixa, remover faixas,
 * alterar o volume e o estado (ligado/desligado).
 * Alem disso, esse sistema consegue detectar erros/falhas que prejudicam o funcionamento. */
class Som : public Dispositivo {

private:
    int _volume; ///< volume(0 ~ 100)
    int _indice; ///< numero da musica que esta tocando
    bool _pause;///< estado do player
    vector<string> playlist; ///< lista de musicas em um buffer

    /** @brief Escreve no arquivo a playlist atual (metodo para funcionamento interno) */
    void supplArq();

public:

    /** @brief Construtor da classe Som
     * @param id Identificador do dispositivo
     * @param comodo Nome do comodo */
    Som(int id, string comodo);

    /** @brief Destrutor da classe Som*/
    ~Som();

/*=========================getters================================*/

    /** @brief Retorna o volume em valor inteiro.
     * @return inteiro. */
    int getVolume();

/*=========================setters================================*/

/*=========================metodos================================*/


    /** @brief Carrega a lista de musicas em um arquivo para a playlist.
    * @param nomeArquivo Nome do arquivo contendo a lista de musicas a serem tocadas. */
    void carregarMusicas(const string& nomeArquivo);

    /** @brief Toca/pausa a musica */
    void togglePause();


    //OVERLOAD~~~~~~~~~~~~~~~~~~~
    /** @brief Toca(imprime na tela) uma musica. */
    void tocar();

    /** @brief Toca(imprime na tela) uma musica.
     *  @param indice toca uma musica em um indice especificado(vazio para o comeco da lista) */
    void tocar(int indice);
    //OVERLOAD~~~~~~~~~~~~~~~~~~~


    /** @brief Pula para a proxima musica */
    void proxima();

    /** @brief Pula para a musica anterior */
    void anterior();

    /** @brief Imprime a playlist na tela */
    void printPlaylist();


    //OVERLOAD~~~~~~~~~~~~~~~~~~~
    /** @brief Adiciona uma musica no final da playlist usando o nome
     *  @param nome nome da musica a ser adicionada */
    void adicionarMusica(const string& nome);

    /** @brief Adiciona uma musica em uma posicao desejada da playlist usando o nome
     *  @param nome nome da musica a ser adicionada
     *  @param indice lugar da playlist onde a musica vai ser adicionada*/
    void adicionarMusica(const string& nome, int indice);
    //OVERLOAD~~~~~~~~~~~~~~~~~~~


    /** @brief Remove uma musica da playlist
     *  @param nome  */
    void removerMusica(const string& nome);
};

#endif