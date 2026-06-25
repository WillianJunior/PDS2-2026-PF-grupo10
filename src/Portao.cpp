#include "Portao.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

Portao::Portao() : Dispositivo(), segundos(30) {
    this->nome = "Portao";
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
    if (this->erro) return;

    std::thread([this]() {

        int tempoRestante = this->segundos;

        while (tempoRestante > 0) {
            std::cout << "Portao fechando em " << tempoRestante << "s\r" << std::flush;

            std::this_thread::sleep_for(std::chrono::seconds(1));
            tempoRestante--;
        }

        this->alterarEstado(false);

    }).detach();
}

void Portao::detectarErro() {

    this->erro = (this->segundos < 0);

    if (this->erro) {
        this->segundos = 0;
    }
}

std::string Portao::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "Aberto" : "Fechado";
    std::string resposta = std::to_string(this->getId()) + " " + this->nome + " " + estado_str + " Temporizador: " + std::to_string(this->segundos);
    if (this->erro) {
        resposta += " erro";
    }
    return resposta;
}