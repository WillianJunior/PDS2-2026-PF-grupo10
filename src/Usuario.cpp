#include "Usuario.hpp"

Usuario::Usuario(std::string nome, std::string senha) : _nome(nome), _senha(senha), macros(nullptr), qtdMacros(0) {
}

Usuario::~Usuario() {
    for (int i = 0; i < qtdMacros; i++) {
        delete macros[i];
    }
    delete[] macros;
}

std::string Usuario::getNome() const {
    return this->_nome;
}

void Usuario::setNome(std::string nome) {
    this->_nome = nome;
}

bool Usuario::autenticar(std::string nome, std::string senha) const {
    return _nome == nome && _senha == senha;
}

Macro* Usuario::getMacro(int i, Usuario& user) const {
    if (i < 0 || i >= qtdMacros || macros == nullptr) {
        return nullptr;
    }
    else{
    return macros[i];
    }
}

void Usuario::adicionarMacro(std::string evento, Usuario& user) {
}

void Usuario::removerMacro(std::string evento, Usuario& user) {
}

void Usuario::executarMacro(std::string evento, Usuario& user) {
}