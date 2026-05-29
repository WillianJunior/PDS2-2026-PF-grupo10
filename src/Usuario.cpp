#include "Usuario.hpp"

Usuario::Usuario(std::string nome, std::string senha) {
}

Usuario::~Usuario() {
}

std::string Usuario::getNome() const {
    return "";
}

void Usuario::setNome(std::string nome) {
}

bool Usuario::autenticar(std::string nome, std::string senha) const {
    return false;
}

Macro* Usuario::getMacro(int i, Usuario& user) const {
    return nullptr;
}

void Usuario::adicionarMacro(string evento, Usuario& user) {
}

void Usuario::removerMacro(string evento, Usuario& user) {
}

void Usuario::executarMacro(string evento, Usuario& user) {
}