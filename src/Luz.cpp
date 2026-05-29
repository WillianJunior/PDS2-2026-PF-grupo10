#include "Luz.hpp"
#include <string>


Luz::Luz(int id) : Dispositivo(id), intensidade(1) {
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
    std::string resposta;

    
    if (this->estado) {
        resposta = "Luz [ID " + std::to_string(this->id) + "]: LIGADA - Intensidade: " + std::to_string(this->intensidade);
    } else {
        resposta = "Luz [ID " + std::to_string(this->id) + "]: DESLIGADA";
    }

    
    if (this->erro) {
        resposta += "(⚠️ ESTADO DE ERRO DETECTADO)";
    }

    return resposta;
}