#include "Sensor.hpp"

Sensor::Sensor(int tempoVerificacao) {
    this->tempoVerificacao = 10;
}

Sensor::~Sensor() {
    this->tempoVerificacao = 10;
}

int Sensor::getTempoVerificacao() const {
    return this->tempoVerificacao;
}

std::string Sensor::getAlertas(int i) const {
    return alertas[i];
}

void Sensor::alterarTempoVerificacao(int segundos) {
    this->tempoVerificacao = segundos;
    return;
}

void Sensor::salvarAlertas() {
   
}