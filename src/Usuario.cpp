#include "Usuario.hpp"

using namespace std;

Usuario::Usuario(string nome, string senha) {
}

Usuario::~Usuario() {
}

std::string Usuario::getNome() const {
    return "";
}

void Usuario::setNome(string nome) {
}

bool Usuario::autenticar(string nome, string senha) const {
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