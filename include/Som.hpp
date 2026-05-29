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
    /** @brief Construtor da classe Som.
     * Inicializa o dispositivo de áudio definindo seu ID exclusivo e o cômodo de instalação.
     * @param id Identificador numérico único do dispositivo. */
    Som(int id);

    /** @brief Destrutor da classe Som.
     * Libera a memória alocada para a estrutura da playlist e encerra de forma segura 
     * qualquer fluxo de áudio ou comunicação ativa do dispositivo. */
    ~Som();

    /** @brief Consulta o nível de volume atual do dispositivo.
     * @return int Valor inteiro representando a escala atual de volume do aparelho. */
    int getVolume() const;

    /** @brief Lê e importa uma lista de faixas a partir de um arquivo externo.
     * Abre o arquivo especificado, faz o parser dos nomes das músicas e as insere na estrutura de dados da playlist.
     * @param nomeArquivo Caminho ou nome do arquivo de texto contendo os títulos das músicas. */
    void carregarMusicas(const string& nomeArquivo);

    /** @brief Alterna o estado de reprodução atual entre tocando e pausado.
     * Inverte o estado lógico do player; se a música estiver ativa, ela é pausada, e vice-versa. */
    void togglePause();

    //OVERLOAD~~~~~~~~~~~~~~~~~~~
    /** @brief Inicia ou retoma a reprodução da faixa atual (imprime o status na tela).
     * Dispara o áudio a partir do ponto onde foi parado ou do início da playlist caso nenhuma música tenha começado. */
    void tocar();

    /** @brief Salta diretamente para uma faixa específica e inicia a reprodução.
     * @param indice Posição numérica da música desejada dentro da playlist (base zero). */
    void tocar(int indice);
    //OVERLOAD~~~~~~~~~~~~~~~~~~~

    /** @brief Avança para a próxima faixa da playlist.
     * Altera o ponteiro/índice para a música seguinte da lista, respeitando os limites da estrutura. */
    void proxima();

    /** @brief Retorna para a faixa anterior da playlist.
     * Altera o ponteiro/índice para a música antecedente, verificando se já não está no início da lista. */
    void anterior();

    /** @brief Exibe na tela todas as músicas contidas na playlist atual.
     * Percorre a lista sequencialmente e imprime o índice e o nome de cada faixa de áudio cadastrada. */
    void printPlaylist();

    //OVERLOAD~~~~~~~~~~~~~~~~~~~
    /** @brief Insere uma nova música ao final da playlist corrente.
     * Aloca um novo elemento com o título fornecido e o anexa no final da lista de reprodução.
     * @param nome Título ou nome da música a ser inserida. */
    void adicionarMusica(const string& nome);

    /** @brief Insere uma nova música em uma posição arbitrária da playlist.
     * Desloca os elementos necessários ou ajusta os ponteiros para encaixar a nova faixa no local exato informado.
     * @param nome Título ou nome da música a ser inserida.
     * @param indice Posição desejada na lista onde a música será encaixada. */
    void adicionarMusica(const string& nome, int indice);
    //OVERLOAD~~~~~~~~~~~~~~~~~~~

    /** @brief Elimina uma música da playlist buscando pelo seu título.
     * Procura o nome correspondente na lista, remove o elemento, ajusta a estrutura e libera a memória associada.
     * @param nome Título exato da música que será removida da lista. */
    void removerMusica(const string& nome);

    /** @brief Verifica possíveis falhas no funcionamento do aparelho de som.
     * Realiza a análise do estado interno do dispositivo para identificar
     * erros relacionados à reprodução, volume ou operação geral do sistema de áudio. */
    void detectarErro() override;
    
    /** @brief Retorna uma descrição textual do estado atual do aparelho de som.
     * Informa se o dispositivo está ligado ou desligado e pode incluir
     * detalhes como volume ou modo de reprodução.
     * @return std::string Texto formatado representando o estado do aparelho de som. */
    std::string getEstadoFormatado() const override;
};

#endif