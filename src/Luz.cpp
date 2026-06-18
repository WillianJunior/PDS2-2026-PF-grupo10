#include "Luz.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

Luz::Luz() : Dispositivo(), intensidade(1) {
    this->estado = false; 
    this->erro = false;
}

Luz::~Luz() {
}

void Luz::ligar() { 
    this->estado = true; 
}

void Luz::desligar() {
    this->estado = false; 
}

int Luz::getIntensidade() const {
    return intensidade;
}


void Luz::ajustarIntensidade(int novaIntensidade) {
    try {
        if (novaIntensidade < 1 || novaIntensidade > 5) {
            throw std::invalid_argument("Intensidade inválida.");
        }

        this->intensidade = novaIntensidade;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}


void Luz::detectarErro() {
    this->erro = (this->intensidade < 1 || this->intensidade > 5);
}


std::string Luz::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "Ligada" : "Desligada";
    std::string resposta = std::to_string(this->getId()) + " Luz " + estado_str + " Intensidade: " + std::to_string(this->intensidade);
    if (this->erro) {
        resposta += " ⚠️";
    }
    return resposta;
}