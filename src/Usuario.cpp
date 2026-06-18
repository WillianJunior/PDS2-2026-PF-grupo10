#include "../include/Usuario.hpp"
#include <stdexcept>

Usuario::Usuario(std::string nome, std::string senha) : _nome(nome), _senha(senha) {
}

Usuario::~Usuario() {
}

std::string Usuario::getNome() const {
    return this->_nome;
}

void Usuario::setNome(std::string nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Erro: O nome do usuário não pode ser vazio.");
    }
    this->_nome = nome;
}

bool Usuario::autenticar(std::string nome, std::string senha) const {
    return _nome == nome && _senha == senha;
}

Macro* Usuario::getMacro(int i, Usuario& user) const {
    if (i < 0 || i >= static_cast<int>(macros.size())) {
        return nullptr;
    }
    return macros[i].get();
}

void Usuario::adicionarMacro(std::string evento, Usuario& user) {
    if (evento.empty()) {
        throw std::invalid_argument("Erro: O nome do evento para a macro não pode ser vazio.");
    }
    macros.push_back(std::unique_ptr<Macro>(new Macro(evento)));
}

void Usuario::removerMacro(std::string evento, Usuario& user) {
    for (auto it = macros.begin(); it != macros.end(); ++it) {
        if ((*it)->getEvento() == evento) {
            macros.erase(it);
            return;
        }
    }
    throw std::runtime_error("Erro: Macro com o evento '" + evento + "' não encontrada.");
}

void Usuario::executarMacro(std::string evento, Usuario& user) {
    for (const auto& macro : macros) {
        if (macro->getEvento() == evento) {
            return;
        }
    }
    throw std::runtime_error("Erro: Não foi possível executar. Macro '" + evento + "' não encontrada.");
}