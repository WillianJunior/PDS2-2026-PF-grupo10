#include "Sensor.hpp"
#include <iostream>
#include <fstream>

Sensor::Sensor(int temp) : tempoVerificacao(temp)
{
    if (temp < 0) {
        throw std::invalid_argument(
            "Tempo de verificacao invalido."
        );
    }
}

Sensor::~Sensor() {}

int Sensor::getTempoVerificacao() const {
    return tempoVerificacao;
}

std::string Sensor::getAlerta(int i) const {
    if (i < 0 ||
        i >= static_cast<int>(alertas.size())) {

        throw std::out_of_range(
            "Indice de alerta invalido."
        );
    }

    return alertas[i];
}

void Sensor::alterarTempoVerificacao(int segundos) {
    if (segundos < 0) {
        throw std::invalid_argument(
            "Tempo de verificacao nao pode ser negativo."
        );
    }

    tempoVerificacao = segundos;
}

void Sensor::salvarAlertas() {
    std::ofstream arquivo("src/alertas.txt");

    if (!arquivo.is_open()) {
        throw std::runtime_error(
            "Nao foi possivel abrir o arquivo."
        );
    }

    for (size_t i = 0; i < alertas.size(); ++i) {
        arquivo << alertas[i] << '\n';
}

