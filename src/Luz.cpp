#include "Luz.hpp"
#include "Dispositivo.hpp"

Luz::Luz(int id) : Dispositivo(id) {
}

Luz::~Luz() {
}

int Luz::getIntensidade() const {
    return 0;
}

void Luz::ajustarIntensidade(int intensidade) {
}

void Luz::detectarErro() {
}