#include "Som.hpp"
#include <string>

Som::Som(int id) : Dispositivo(id), _volume(50), _indice(0), _pause(true) {
}

Som::~Som() {
}

void Som::supplArq() {
}

int Som::getVolume() const {
    return _volume;
}

void Som::carregarMusicas(const string& nomeArquivo) {
    // Implementação vazia
}

void Som::togglePause() {
    _pause = !_pause;
}

void Som::tocar() {
    // Implementação vazia
}

void Som::tocar(int indice) {
    // Implementação vazia
}

void Som::proxima() {
    // Implementação vazia
}

void Som::anterior() {
    // Implementação vazia
}

void Som::printPlaylist() {
    // Implementação vazia
}

void Som::adicionarMusica(const string& nome) {
    // Implementação vazia
}

void Som::adicionarMusica(const string& nome, int indice) {
    // Implementação vazia
}

void Som::removerMusica(const string& nome) {
    // Implementação vazia
}

void Som::detectarErro() {
    // Implementação vazia
}

std::string Som::getEstadoFormatado() const {
    return "Som: Desligado";  // Implementação vazia simples
}
