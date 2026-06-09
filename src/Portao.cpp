#include "Portao.hpp"
#include <string>

Portao::Portao() : Dispositivo(), segundos(0) {
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
    
    if (this->segundos < 0) {
        this->erro = true;
        this->segundos = 0; 
    }
}

std::string Portao::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "aberto" : "fechado";
    std::string resposta = std::to_string(this->getId()) + " Portao " + estado_str + " " + std::to_string(this->segundos);
    if (this->erro) {
        resposta += " ⚠️";
    }
    return resposta;
}