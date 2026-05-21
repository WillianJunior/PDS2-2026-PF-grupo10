#include "Sistema.hpp"

Sistema::Sistema() {
}

Sistema::~Sistema() {
}

Comodo* Sistema::getComodo(int i) const {
    return nullptr;
}

Sensor* Sistema::getSensor() const {
    return nullptr;
}

bool Sistema::estaAtivo() const {
    return false;
}

void Sistema::executarSistema() {
}

void Sistema::receberComando(const string& comando) {
}

void Sistema::adicionarComodo(Comodo& comodo) {
}

void Sistema::removerComodo(const Comodo& comodo) {
}