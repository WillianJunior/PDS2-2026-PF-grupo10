#include "Dispositivo.hpp"

int Dispositivo::qtdDispositivos = 0;
int Dispositivo::identificador = 0;

Dispositivo::Dispositivo() : id(++Dispositivo::identificador), estado(false), erro(false) {
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