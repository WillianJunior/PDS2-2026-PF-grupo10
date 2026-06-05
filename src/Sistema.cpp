#include "Sistema.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

Sistema::Sistema() : ativo(false), sensor(new Sensor(0)) {
}

Sistema::~Sistema() {
    comodos.clear();
    delete sensor;
}

const Comodo* Sistema::getComodo(int i) const {
    if (i >= 0 && i < static_cast<int>(comodos.size())) {
        return &comodos[i];
    }else{
        return nullptr;
    }
}

int Sistema::getQtdComodos() {
    return comodos.size();
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
    if (comando == "conectar" || comando == "ligar") {
    }
}

void Sistema::adicionarComodo(Comodo& comodo) {
    comodos.push_back(comodo);
}

void Sistema::removerComodo(const Comodo& comodo) {
    auto it = std::find_if(comodos.begin(), comodos.end(), [&comodo](const Comodo& c){return &c == &comodo;});
    if(it != comodos.end()){ comodos.erase(it); }
}