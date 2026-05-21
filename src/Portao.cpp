#include "Portao.hpp"

Portao::Portao(int id) : Dispositivo(id) {
}

Portao::~Portao() {
}

int Portao::getTemporizador() const {
    return 0;
}

void Portao::setTemporizador(int segundos) {
}

void Portao::fecharAutomaticamente() {
}

void Portao::detectarErro() {
}