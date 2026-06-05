#include "Sensor.hpp"
#include <iostream>

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
   
}