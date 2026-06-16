#include "ArCondicionado.hpp"
#include <string>

ArCondicionado::ArCondicionado() : Dispositivo(), temperatura(22) {
    this->estado = false;
    this->erro = false;
}

ArCondicionado::~ArCondicionado() {
}

void ArCondicionado::ligar() {
    this->estado = true;
}

void ArCondicionado::desligar() {
    this->estado = false;
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
    if (temperatura < 15 || temperatura > 30){
        this->erro = true;
    }
}

std::string ArCondicionado::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "ligado" : "desligado";
    std::string resposta = std::to_string(this->getId()) + " ArCondicionado " + estado_str + " " + std::to_string(this->temperatura);
    if (this->erro) {
        resposta += " ⚠️";
    }
    return resposta;
}