#include "Luz.hpp"
#include <string>


Luz::Luz() : Dispositivo(), intensidade(1) {
}


Luz::~Luz() {
}


int Luz::getIntensidade() const {
    return intensidade;
}


void Luz::ajustarIntensidade(int novaIntensidade) {
    if (novaIntensidade >= 1 && novaIntensidade <= 5) {
        this->intensidade = novaIntensidade;
    }
}


void Luz::detectarErro() {
    if (this->intensidade < 1 || this->intensidade > 5) {
        this->erro = true;  
    }
}


std::string Luz::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "ligada" : "desligada";
    std::string resposta = std::to_string(this->getId()) + " Luz " + estado_str + " " + std::to_string(this->intensidade);
    if (this->erro) {
        resposta += " ⚠️";
    }
    return resposta;
}