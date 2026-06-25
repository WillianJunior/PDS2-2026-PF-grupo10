#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>
#include <memory>
#include "Macro.hpp"
#include "Sistema.hpp"

/** @brief Representa um usuário do sistema. 
 * Armazena nome e senha, permitindo autenticação
 * e alteração dos dados do usuário. */
class Usuario{

private:
    std::string _nome;                             ///< Nome do usuário
    std::string _senha;                            ///< Senha do usuário
    std::vector<std::unique_ptr<Macro>> macros;    ///< Vetor de macros do sistema


public:
    /** @brief Cria um usuário a partir do nome e senha escolhidos.
    * @param nome nome do usuario
    * @param senha senha do usuario */
    Usuario(std::string nome, std::string senha); 

    /** @brief Destrutor padrão da classe Usuario */
    ~Usuario() = default;

    /** @brief retorna o nome do usuário
    * @return string nome cadastrado no sistema */
    std::string getNome() const;

    /** @brief Altera o nome do usuário
    * @param nome novo nome a ser atribuido */
    void setNome(std::string& nome);

    /** @brief Verifica se um usuário pode ser autenticado
    * Confere se existe um usuário com o nome e a senha informados
    * @param nome nome do usuário
    * @param senha senha do usuário
    * @return true se as informações forem válidas */
    bool autenticar(std::string& nome, std::string& senha) const;

    /** @brief Identifica uma macro específica cadastrada no sistema através do seu índice.
     * @param i Índice posicional da macro dentro do vetor de macros do sistema.
     * @param user Nome do usuario que tem o macro.
     * @return Macro* Ponteiro para o objeto Macro encontrado se o índice for válido;
     * Retorna `nullptr` se o índice não for válido */
    Macro* getMacro(int i) const;

    /** @brief Exibe todas as macros cadastradas pelo usuário.
     *  Percorre o vetor de macros e apresenta o nome de cada evento registrado no sistema. */
    void listarMacros() const;

    /** @brief Registra e armazena uma nova macro vazia no sistema.
     * Cria uma nova estrutura de automação baseada no nome de um evento fornecido e a
     * adiciona ao vetor de macros. A partir do registro, ações podem ser vinculadas a este evento.
     * @param evento Nome identificador único que será associado à nova macro (ex: "sair_de_casa").
     * @param sistema Referência ao sistema de dispositivos para executar as ações. */
    Macro* adicionarMacro(const std::string& evento, Sistema& sistema);

    /** @brief Remove uma macro existente do sistema com base no nome de evento fornecido.
     * Busca no vetor de macros o evento correspondente. Se encontrado, o objeto é
     * destruído da memória e sua referência é removida do vetor.
     * Caso o evento não exista, nenhuma ação é tomada.
     * @param evento Nome identificador da macro que deseja remover. */
    void removerMacro(std::string evento);

    /** @brief Dispara e executa a sequência de ações de uma macro cadastrada.
     * Procura pela macro associada ao nome do evento fornecido. Se encontrada, o sistema
     * intercepta e executa todos os comandos e alterações de estado agendados
     * para aquela macro específica.
     * @param evento Nome do evento cuja macro correspondente deve ser disparada.
     * @param sistema Referência ao sistema de dispositivos para executar as ações. */
    void executarMacro(std::string evento, Sistema& sistema);

    /** @brief Registra as informações de um usuário em um arquivo de texto dentro de data/ */
    void salvarDados(const Sistema& sistema);

    /** @brief Lê as informações de um usuário e salva novamente no sistema 
     * a partir de um arquivo de texto dentro de data/ */
    bool carregarDados(Sistema& sistema);

    /** @brief Remove todas as macros cadastradas pelo usuário.
     *  Limpa o vetor de macros, liberando os recursos associados e restaurando a lista de macros ao estado vazio. */
    void limparMacros();
    
};


#endif