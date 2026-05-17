#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

/** @brief Representa um usuário do sistema. 
 * Armazena nome e senha, permitindo autenticação
 * e alteração dos dados do usuário. */
class Usuario{

private:     
    std::string nome;   ///< Nome do usuário
    std::string senha;  ///< Senha do usuário 

public:
    /** @brief Cria um usuário a partir do nome e senha escolhidos.
    * @param nome nome do usuario
    * @param senha senha do usuario */
    Usuario(std::string nome, std::string senha); 

    /** @brief Remove o usuário cadastrado
     *
     */
    ~Usuario(); 

    /** @brief retorna o nome do usuário
    * @return string nome cadastrado no sistema
    */
    std::string getNome() const;

    /** @brief Altera o nome do usuário
    * @param nome novo nome a ser atribuido
    */
    void setNome(std::string nome);

    /** @brief Verifica se um usuário pode ser autenticado
    * Confere se existe um usuário com o nome e a senha informados
    * @param nome nome do usuário
    * @param senha senha do usuário
    * @return true se as informações forem válidas
    */
    bool autenticar(std::string nome, std::string senha) const;
};


#endif