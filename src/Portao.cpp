#include "Portao.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

Portao::Portao() : Dispositivo(), segundos(30) {
    this->estado = false;
    this->erro = false;
}

Portao::~Portao() {
}

int Portao::getTemporizador() const {
    return segundos;
}

void Portao::setTemporizador(int segundos) {
    try {
        if (segundos <= 0) {
            throw std::invalid_argument("O tempo deve ser maior que zero");
        }

        this->segundos = segundos;

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

void Portao::fecharAutomaticamente() {
    if (!this->estado || this->erro) {
        return;
    }

    if (this->segundos < 0) {
        detectarErro();
        return;
    }

    if (this->segundos > 0) {
        std::time_t tempoInicial = std::time(nullptr);
        int tempoRestante = this->segundos;

        while (tempoRestante > 0) {
            std::time_t tempoAtual = std::time(nullptr);
            tempoRestante = this->segundos - static_cast<int>(tempoAtual - tempoInicial);
        }
    }

    this->alterarEstado(false);
}

void Portao::detectarErro() {

    this->erro = (this->segundos < 0);

    if (this->erro) {
        this->segundos = 0;
    }
}

std::string Portao::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "Aberto" : "Fechado";
    std::string resposta = std::to_string(this->getId()) + " Portao " + estado_str + " Temporizador: " + std::to_string(this->segundos);
    if (this->erro) {
        resposta += " ⚠️";
    }
    return resposta;
}