#include "Sistema.hpp"
#include <iostream>
#include <algorithm>

Sistema::Sistema() : ativo(false), sensor(new Sensor(0)) {
}

Sistema::~Sistema() {
    for (Comodo* comodo : comodos) {
        delete comodo;
    }
    comodos.clear();

    if (sensor != nullptr) {
        delete sensor;
    }
}

Comodo* Sistema::getComodo(int i) const {
    if (i >= 0 && i < static_cast<int>(comodos.size())) {
        return comodos[i];
    }
    return nullptr;
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
    comodos.push_back(&comodo);
}

void Sistema::removerComodo(const Comodo& comodo) {
    for (auto it = comodos.begin(); it != comodos.end(); ++it) {
        if (*it == &comodo) {
            comodos.erase(it);
            break; 
        }
    }
}