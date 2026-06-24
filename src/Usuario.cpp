#include "../include/Usuario.hpp"
#include <stdexcept>
#include "Luz.hpp"
#include "ArCondicionado.hpp"
#include "Som.hpp"
#include "Portao.hpp"

Usuario::Usuario(std::string nome, std::string senha) : _nome(nome), _senha(senha) {
}

std::string Usuario::getNome() const {
    return this->_nome;
}

void Usuario::setNome(std::string& nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Erro: O nome do usuário não pode ser vazio.");
    }
    this->_nome = nome;
}

bool Usuario::autenticar(std::string& nome, std::string& senha) const {
    return _nome == nome && _senha == senha;
}

Macro* Usuario::getMacro(int i) const {
    if (i < 0 || i >= static_cast<int>(macros.size())) {
        return nullptr;
    }
    return macros[i].get();
}

Macro* Usuario::adicionarMacro(const std::string& evento) {
    if (evento.empty()) {
        throw std::invalid_argument("Erro: O nome do evento para a macro não pode ser vazio.");
    }
    macros.push_back(std::unique_ptr<Macro>(new Macro(evento)));
    return macros.back().get();
}

void Usuario::removerMacro(std::string evento) {
    for (auto it = macros.begin(); it != macros.end(); ++it) {
        if ((*it)->getEvento() == evento) {
            macros.erase(it);
            return;
        }
    }
    throw std::runtime_error("Erro: Macro com o evento '" + evento + "' não encontrada.");
}

void Usuario::executarMacro(std::string evento, Sistema& sistema) {

    for (const auto& macro : macros) {

        if (macro->getEvento() != evento)
            continue;

        Node* atual = macro->getLista();

        while (atual != nullptr) {

            Dispositivo* disp = sistema.getDispositivo(atual->id);

            if (disp != nullptr) {
                if (atual->acao == "ligar") {
                    disp->alterarEstado(true);
                }
                else if (atual->acao == "desligar") {
                    disp->alterarEstado(false);
                }
                else if (atual->acao == "abrir") {
                    disp->alterarEstado(true);
                }
                else if (atual->acao == "fechar") {
                    disp->alterarEstado(false);
                }
                else if (atual->acao == "ajustar") {
                    if (auto* luz = dynamic_cast<Luz*>(disp)) {
                        luz->ajustarIntensidade(atual->valor);
                    }
                    else if (auto* ar = dynamic_cast<ArCondicionado*>(disp)) {
                        ar->ajustarTemperatura(atual->valor);
                    }
                    else if (auto* som = dynamic_cast<Som*>(disp)) {
                        som->setVolume(atual->valor);
                    }
                    else if (auto* portao = dynamic_cast<Portao*>(disp)) {
                        portao->setTemporizador(atual->valor);
                    }
                }
                else {
                    throw std::runtime_error(
                        "Acao desconhecida: " + atual->acao
                    );
                }
            }
            atual = atual->proximo.get();
        }
        return;
    }

    throw std::runtime_error(
        "Erro: Nao foi possivel executar. Macro \"" +
        evento + "\" nao encontrada."
    );
}