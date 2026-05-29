#include "Dispositivo.hpp"

int Dispositivo::qtdDispositivos = 0;

Dispositivo::Dispositivo(int id) : id(id), estado(false), erro(false) {
    qtdDispositivos++;
}

Dispositivo::~Dispositivo() {
    qtdDispositivos--;
}

int Dispositivo::getId() const {
    return id;
}

bool Dispositivo::getEstado() const {
    return estado;
}

bool Dispositivo::temErro() const {
    return erro;
}

void Dispositivo::alterarEstado(bool novoEstado) {
    estado = novoEstado;
}