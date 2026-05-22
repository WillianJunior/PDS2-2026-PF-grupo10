#include "ArCondicionado.hpp"
#include <string>

ArCondicionado::ArCondicionado(int id) : Dispositivo(id), temperatura(22) {
}

ArCondicionado::~ArCondicionado() {
}

int ArCondicionado::getTemperatura() const {
    return temperatura;
}

void ArCondicionado::ajustarTemperatura(int temp) {
    if (temp >= 15 && temp <= 30) {
        temperatura = temp;
    }
}

void ArCondicionado::detectarErro() {
    // Implementação vazia
}

// ✅ IMPLEMENTAÇÃO CORRETA (com const)
std::string ArCondicionado::getEstadoFormatado() const {
    return "ArCondicionado: Desligado";  // Implementação vazia simples
}