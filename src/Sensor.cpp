#include "Sensor.hpp"
#include <iostream>
#include <fstream>

Sensor::Sensor(int temp) : tempoVerificacao(temp) {
}

Sensor::~Sensor() {
    alertas.clear();
}

int Sensor::getTempoVerificacao() const {
    return tempoVerificacao;
}

std::string Sensor::getAlerta(int i) const {
    if((i < 0) || i >= static_cast<int>(alertas.size())){
        std::cerr << "Erro: Alerta inexistente" << std::endl;
        return "";
    }else{
        return alertas[i];
    }
}

void Sensor::alterarTempoVerificacao(int segundos) {
    if(segundos < 0){
        std::cerr << "Erro: Tempo de verificação não pode ser negativo" << std::endl;
        return;
    }
    tempoVerificacao = segundos;
}

void Sensor::salvarAlertas() {
    std::ofstream arquivo("src/alertas.txt");

    if (!arquivo.is_open()) {
        std::cerr << "Erro: Não foi possível criar ou abrir o arquivo alertas.txt" << std::endl;
        return;
    }

    for (size_t i = 0; i < alertas.size(); ++i) {
        arquivo << alertas[i] << "\n";
    }
}

