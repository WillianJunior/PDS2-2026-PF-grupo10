#include "../include/Sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdexcept> 
#include <memory>    

Sistema::Sistema() : ativo(false), sensor(std::make_unique<Sensor>(10)) {
}

Sistema::~Sistema() {
}

const Comodo* Sistema::getComodo(int i) const {
    int quantidade = comodos.size();
    if (i < 0 || i >= quantidade) {
        return nullptr;
    }
    return &comodos[i];
}

int Sistema::getQtdComodos() const {
    int quantidade = comodos.size();
    return quantidade;
}

Sensor* Sistema::getSensor() const {
    return sensor.get();
}

bool Sistema::estaAtivo() const {
    return ativo;
}

void Sistema::executarSistema() {
    ativo = true;
}

void Sistema::adicionarComodo(Comodo& comodo) {
    comodos.push_back(comodo);
}

void Sistema::removerComodo(const Comodo& comodo) {
    auto it = std::find_if(comodos.begin(), comodos.end(), [&comodo](const Comodo& c){
        return &c == &comodo;
    });
    if (it != comodos.end()) { 
        comodos.erase(it); 
    }
}

void Sistema::gerarRelatorio(const std::string& caminhoArquivo) const {
    std::ofstream arquivo(caminhoArquivo);
    
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro crítico: Não foi possível abrir ou criar o arquivo de relatório em: " + caminhoArquivo);
    }

    for (const auto& comodo : comodos) {
        arquivo << std::endl << comodo.getNome() << std::endl;
        
        for (int i = 0; i < comodo.getQtdDispositivos(); ++i) {
            const Dispositivo* dispositivo = comodo.getDispositivoPorIndice(i);
            if (dispositivo != nullptr) {
                arquivo << dispositivo->getEstadoFormatado() << std::endl;
            }
        }
    }

    arquivo.close();
}

void Sistema::receberComando(std::string comando) {
    return;
}