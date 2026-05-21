#include "Dispositivo.hpp"

int Dispositivo::qtdDispositivos = 0;

Dispositivo::Dispositivo(int id) {
}

Dispositivo::~Dispositivo() {
}

int Dispositivo::getId() const {
    return 0;
}

bool Dispositivo::getEstado() const {
    return false;
}

bool Dispositivo::temErro() const {
    return false;
}

void Dispositivo::alterarEstado(bool novoEstado) {
}