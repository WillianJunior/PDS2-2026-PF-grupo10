#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario{

private:    
    /** @brief nome do usuário */
    std::string nome;

    /** @brief senha do usuário */
    std::string senha;

public:
    /** @brief Constrói um usuario com nome e senha
    * @param nome nome do usuario
    * @param senha senha do usuario */
    Usuario(std::string nome, std::string senha); 

    /** @brief retorna o nome do usuário
    * @return string nome armazenado no objeto */
    std::string getNome(); 

    /** @brief define o nome do usuário
    * @param nome novo nome a ser atribuido */
    void setNome(std::string nome);

    /** @brief Verifica se um usuário pode ser autenticado
    * Confere se existe um usuário com o nome e a senha informados
    * @param nome nome do usuário
    * @param senha senha do usuário
    * @return true se as informações forem válidas */
    bool autenticar(std::string nome, std::string senha); 
};


#endif