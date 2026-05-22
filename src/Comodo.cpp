#include "Comodo.hpp"
#include <string>

Comodo::Comodo() : qtdDispositivos(0) {
    // Aloca array de dispositivos (tamanho 10 por exemplo)
    dispositivos = new Dispositivo*[10];
}

Comodo::~Comodo() {
    delete[] dispositivos;
}

Dispositivo* Comodo::getDispositivo(int id) const {
    // Implementação vazia - retorna nullptr
    return nullptr;
}

void Comodo::adicionarDispositivo(Dispositivo* dispositivo) {
    // Implementação vazia
}

void Comodo::removerDispositivo(int id) {
    // Implementação vazia
}

int Comodo::getQtdDispositivos() const {
    return qtdDispositivos;
}