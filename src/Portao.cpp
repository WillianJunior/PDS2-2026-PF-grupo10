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
    std::string resposta;
    
    if (this->estado) {
        resposta = "Portao [ID " + std::to_string(this->getId()) + "]: ABERTO - Fechando em: " + std::to_string(this->segundos) + "s";
    } else {
        resposta = "Portao [ID " + std::to_string(this->getId()) + "]: FECHADO";
    }

    if (this->erro) {
        resposta += " (⚠️ ESTADO DE ERRO DETECTADO)";
    }

    return resposta;
}