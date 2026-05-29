#include "Portao.hpp"
#include <string>

Portao::Portao(int id) : Dispositivo(id), segundos(0) {
}

Portao::~Portao() {
}

int Portao::getTemporizador() const {
    return segundos;
}

void Portao::setTemporizador(int segundos) {
    this->segundos = segundos;
}

void Portao::fecharAutomaticamente() {
    // Implementação vazia
}

void Portao::detectarErro() {
    // Implementação vazia
}

std::string Portao::getEstadoFormatado() const {
    return "Portão: Fechado";  // Implementação vazia simples
}