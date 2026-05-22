#include "ArCondicionado.hpp"

ArCondicionado::ArCondicionado(int id) : Dispositivo(id) {
}

ArCondicionado::~ArCondicionado() {
}

int ArCondicionado::getTemperatura() const {
    return 0;
}

void ArCondicionado::ajustarTemperatura(int temperatura) {
}

void ArCondicionado::detectarErro() {
}

std::string getEstadoFormatado() const{
}
