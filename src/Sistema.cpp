#include "Sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

Sistema::Sistema() : ativo(false), sensor(new Sensor(0)) {
}

Sistema::~Sistema() {
    comodos.clear();
    delete sensor;
}

const Comodo* Sistema::getComodo(int i) const {
    int quantidade = comodos.size();
    if (i < 0 || i >= quantidade) {
        return nullptr;
    }
    return &comodos[i];
}

int Sistema::getQtdComodos() const{
    int quantidade = comodos.size();
    return quantidade;
}

Sensor* Sistema::getSensor() const {
    return sensor;
}

bool Sistema::estaAtivo() const {
    return ativo;
}

void Sistema::executarSistema() {
    ativo = true;
}

void Sistema::receberComando(const std::string& comando) {
    if(!ativo){
        std::cout << "Sistema inativo. Ative o sistema para receber comandos." << std::endl;
        return;
    }
    std::istringstream parser(comando);
    std::string acao;
    parser >> acao;
    std::string objeto;
    parser >> objeto;

    if (acao == "conectar" || acao == "ligar") {
        return;
    }
    if (acao == "desconectar" || acao == "desligar") {
        return;
    }

}

void Sistema::adicionarComodo(Comodo& comodo) {
    comodos.push_back(comodo);
}

void Sistema::removerComodo(const Comodo& comodo) {
    auto it = std::find_if(comodos.begin(), comodos.end(), [&comodo](const Comodo& c){return &c == &comodo;});
    if(it != comodos.end()){ comodos.erase(it); }
}