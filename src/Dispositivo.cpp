#include "Dispositivo.hpp"

int Dispositivo::qtdDispositivos = 0;
int Dispositivo::identificador = 0;

Dispositivo::Dispositivo() : id(++Dispositivo::identificador), estado(false), erro(false), nome("") {
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

std::string Dispositivo::getNome() const {
    return nome;
}

void Dispositivo::setId(int novoId) {
    id = novoId;

    if (novoId >= identificador)
        identificador = novoId + 1;
}

void Dispositivo::alterarEstado(bool novoEstado) {
    estado = novoEstado;
}