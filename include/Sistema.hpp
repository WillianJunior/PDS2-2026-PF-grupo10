#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <vector>
#include <memory> // Incluído para usar o std::unique_ptr (C9 - RAII)

#include "Comodo.hpp"
#include "Macro.hpp"


/** @class Sistema
 * @brief Controla o funcionamento geral do sistema Smart Home.
 * A classe Sistema é responsável por controlar a execução do sistema,
 * gerenciar os cômodos, sensores e comandos recebidos da interface textual. */
class Sistema {

private:

    bool ativo;           ///< Indica se o sistema está ativo
    std::vector<std::unique_ptr<Comodo>> comodos;    ///< Vetor de cômodos gerenciados por smart pointers (RAII).

public:

    /** @brief Construtor padrão da classe Sistema. 
     * Inicializa os componentes principais do sistema de automação residencial.
     * Aloca e configura a estrutura interna da casa, inicializa o sensor principal
     * e o vetor dinâmico de macros. */
    Sistema();

    /** @brief Destrutor padrão da classe Sistema. */
    ~Sistema() = default;

    /** @brief Identifica um cômodo específico da casa com base no seu índice de armazenamento. 
     * @param i Índice posicional do cômodo dentro do vetor de gerenciamento da casa.
     * @return Comodo* Ponteiro para o objeto do cômodo correspondente se o índice for válido;
     * Retorna `nullptr` caso o índice seja negativo ou maior/igual ao tamanho do vetor. */
    Comodo* getComodo(int i) const;

    /** @brief Identifica um cômodo específico da casa com base no seu nome. 
     * @param nome Nome do cômodo a ser buscado.
     * @return Comodo* Ponteiro para o objeto do cômodo correspondente se o nome for válido;
     * Retorna `nullptr` caso o cômodo não seja encontrado. */
    Comodo* getComodo(const std::string& nome);

    /** @brief Retorna a quantidade de cômodos cadastrados no sistema.
     * Esta função retorna o número total de objetos Comodo
     * armazenados no vetor de cômodos do sistema.
     * @return int Quantidade de cômodos cadastrados.*/
    int getQtdComodos() const;

    /** @brief Verifica o estado de operação atual do sistema. 
     * Método de consulta que indica se as rotinas de automação, monitoramento
     * e resposta à comandos estão ativos no momento.
     * @return true Se o sistema estiver inicializado e rodando ativamente.
     * @return false Se o sistema estiver desligado. */
    bool estaAtivo() const;

    Dispositivo* getDispositivo(int id);

    void listarDispositivos() const;
    
    /** @brief Inicia o loop principal de execução do sistema.
     * Altera o estado do sistema para ativo, coloca os sensores em modo de leitura
     * e passa a receber, processar e responder aos comandos do usuário. */
    void executarSistema();

    //removido receberComando(). Redundante com Interface Textual

    /** @brief Adiciona um novo cômodo à estrutura de gerenciamento da casa. 
     * Insere o objeto fornecido no vetor interno de cômodos do sistema.
     * @param comodo Referência para o objeto Comodo que se deseja vincular ao sistema. */
    void adicionarComodo(std::unique_ptr<Comodo> comodo);

    /** @brief Remove um cômodo específico do sistema de monitoramento. 
     * Varre a lista de cômodos cadastrados para encontrar o que corresponda à referência fornecida.
     * O cômodo deixa de responder aos comandos globais do sistema.
     * @param comodo Referência constante para o objeto Comodo que se deseja desvincular do sistema. */
    void removerComodo(const Comodo* comodo);

    /** @brief Gera um arquivo com as informações atuais de todos os cômodos e dispositivos.
     * O arquivo contém uma linha por dispositivo com formato: id dispositivo estado valor [emoji_alerta]
     * @param caminhoArquivo Caminho e nome do arquivo a ser gerado. */
    void gerarRelatorio(const std::string& caminhoArquivo) const;

    /** @brief Recebe e processa um comando informado pelo usuário.
     * Este método realiza a leitura de um comando ja interpretado 
     * pela interface textual, eexecuta a ação correspondente no 
     * sistema. Caso o comando seja inválido, uma mensagem de erro
     * poderá ser exibida ao usuário.
     * @note O comportamento específico depende da implementação do método.
     * @param comando Texto contendo o comando a ser executado.*/
    void receberComando(std::string comando);

    void limparSistema();
};

#endif