#include "ArCondicionado.hpp"
#include <string>

ArCondicionado::ArCondicionado() : Dispositivo(), temperatura(22) {
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
    if (temperatura < 15 || temperatura > 30){
        this->erro = true;
    }
}

std::string ArCondicionado::getEstadoFormatado() const {
    std::string resposta;

    
    if (this->estado) {
        resposta = "Ar condicionado [ID " + std::to_string(this->getId()) + "]: LIGADO - Temperatura: " + std::to_string(this->temperatura);
    } else {
        resposta = "Ar condicionado [ID " + std::to_string(this->getId()) + "]: DESLIGADO";
    }

    if (this->erro) {
        resposta += "(⚠️ ESTADO DE ERRO DETECTADO)";
    }

    return resposta;
}