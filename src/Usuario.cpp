#include "ArCondicionado.hpp"
#include "Usuario.hpp"
#include "Sistema.hpp"
#include "Portao.hpp"
#include "Luz.hpp"
#include "Som.hpp"


#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>


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


void Usuario::salvarDados(const Sistema& sistema){
/*
 * Formato de salvamento:
 * USUARIO1,SENHA1;MACRO1,MACRO2, ... ,MACROn;COMODO1,COMODO2,COMODO3, ... ,COMODOn;
 * USUARIO2,SENHA2;MACRO1,MACRO2, ... ,MACROn;COMODO1,COMODO2,COMODO3, ... ,COMODOn;
 * ...
*/

    std::string caminho = "data/" + _nome + ".txt";
    std::ofstream registro(caminho);

    if (!registro.is_open()) {
        std::cerr << "Erro: não foi possível abrir o arquivo " << caminho << std::endl;
        return;
    }

    registro << _nome << "," << _senha << ";";
    for (size_t i = 0; i < macros.size(); ++i) {
        if (macros[i] != nullptr) {
            registro << macros[i]->getEvento();
            if (i < macros.size() - 1) registro << ",";
        }
    }
    registro << ";";

    int qtdComodos = sistema.getQtdComodos();
    for (int i = 0; i < qtdComodos; ++i) {
        const Comodo* c = sistema.getComodo(i);
        if (c != nullptr) {
            registro << c->getNome();
            if (i < qtdComodos - 1) registro << ",";
        }
    }
    registro<< ";";
    registro.close();

    std::cout << "Dados registrados com sucesso!" << std::endl;
}


bool Usuario::carregarDados(Sistema& sistema) {

    std::string caminho = "data/" + _nome + ".txt";
    std::ifstream registro(caminho);

    if (!registro.is_open()) {
        std::cerr << "Erro: não foi possível abrir o arquivo " << caminho << std::endl;
        return false;
    }

    std::string conteudo;
    std::getline(registro, conteudo);
    registro.close();

    if (!conteudo.empty() && conteudo.back() == ';') {
        conteudo.pop_back();
    }

    // divide em cada ';'

    std::vector<std::string> partes;
    std::stringstream ss(conteudo);
    std::string parte;
    while (std::getline(ss, parte, ';')) {
        partes.push_back(parte);
    }


    if (partes.size() < 3) {
        std::cerr << "Arquivo corrompido ou formato inválido." << std::endl;;
        return false;
    }

    std::stringstream ssUser(partes[0]);
    std::string nome, senha;
    if (std::getline(ssUser, nome, ',') && std::getline(ssUser, senha, ',')) {
        _nome = nome;
        _senha = senha;
    } else {
        std::cerr << "Erro ao ler nome/senha." << std::endl;;
        return false;
    }


    std::stringstream ssMacros(partes[1]);
    std::string novomacro;
    macros.clear();
    while (std::getline(ssMacros, novomacro, ',')) {
        if (!novomacro.empty()) {
            macros.push_back(std::make_unique<Macro>(novomacro));
        }
    }


    std::stringstream ssComodos(partes[2]);
    std::string comodo;
    while (std::getline(ssComodos, comodo, ',')) {
        if (!comodo.empty()) {
            if (sistema.getComodo(comodo) == nullptr) {
                sistema.adicionarComodo(std::make_unique<Comodo>(comodo));
            }
        }
    }
    return true;
}