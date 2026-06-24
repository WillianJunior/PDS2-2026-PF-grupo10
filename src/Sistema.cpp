#include "../include/Sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdexcept> 
#include <memory>    

Sistema::Sistema() : ativo(false), comodos() {
}

Comodo* Sistema::getComodo(int i) const {
    if (i < 0 || i >= static_cast<int>(comodos.size())) {
        return nullptr;
    }

    return comodos[i].get();
}

Comodo* Sistema::getComodo(const std::string& nome) {
    for (auto& c : comodos) {
        if (c->getNome() == nome) return c.get();
    }
    return nullptr;
}

int Sistema::getQtdComodos() const {
    int quantidade = comodos.size();
    return quantidade;
}

bool Sistema::estaAtivo() const {
    return ativo;
}

Dispositivo* Sistema::getDispositivo(int id) {
    int qtd = getQtdComodos();

    for (int i = 0; i < qtd; i++) {
        Comodo* comodo = this->getComodo(i);

        if (comodo != nullptr) {
            Dispositivo* disp = comodo->getDispositivo(id);

            if (disp != nullptr) {
                return disp;
            }
        }
    }
    return nullptr;
}

void Sistema::executarSistema() {
    ativo = true;
}

void Sistema::adicionarComodo(std::unique_ptr<Comodo> comodo) {
    comodos.push_back(std::move(comodo));
}

void Sistema::removerComodo(const Comodo* comodo) {
    auto it = std::find_if(comodos.begin(), comodos.end(), [&comodo](const std::unique_ptr<Comodo>& c){
        return c.get() == comodo;});

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
        arquivo << std::endl << comodo->getNome() << std::endl;
        
        for (int i = 0; i < comodo->getQtdDispositivos(); i++) {
            const Dispositivo* dispositivo = comodo->getDispositivoPorIndice(i);
            if (dispositivo != nullptr) {
                arquivo << dispositivo->getEstadoFormatado() << std::endl;
            }
        }
    }
}

void Sistema::receberComando(std::string comando) {
    return;
}