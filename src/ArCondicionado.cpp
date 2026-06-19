#include "ArCondicionado.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

ArCondicionado::ArCondicionado() : Dispositivo(), temperatura(22) {
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
    try {
        if (temp < 15 || temp > 30) {
            throw std::out_of_range("Temperatura inválida.");
        }

        temperatura = temp;
    }
    catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

void ArCondicionado::detectarErro() {
    this->erro = (temperatura < 15 || temperatura > 30);
}

std::string ArCondicionado::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "Ligado" : "Desligado";
    std::string resposta = std::to_string(this->getId()) + " ArCondicionado " + estado_str + " Temperatura: " + std::to_string(this->temperatura);
    if (this->erro) {
        resposta += " ⚠️";
    }
    return resposta;
}