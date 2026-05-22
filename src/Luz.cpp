#include "Luz.hpp"
#include <string>

Luz::Luz(int id) : Dispositivo(id), intensidade(1) {
}

Luz::~Luz() {
}

int Luz::getIntensidade() const {
    return intensidade;
}

void Luz::ajustarIntensidade(int intensidade) {
    // Implementação vazia
}

void Luz::detectarErro() {
    // Implementação vazia
}

std::string Luz::getEstadoFormatado() const {
    return "Luz: Desligada";  // Implementação vazia simples
}