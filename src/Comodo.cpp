#include "Comodo.hpp"
#include <string>

Comodo::Comodo() {
}

Comodo::~Comodo() {
}

Dispositivo* Comodo::getDispositivo(int id) const {
    // Implementação vazia - retorna nullptr
    return nullptr;
}

void Comodo::adicionarDispositivo(Dispositivo* d) {
    dispositivos.push_back(d);
}

void Comodo::removerDispositivo(int id) {
    // Implementação vazia
}

int Comodo::getQtdDispositivos() const {
    return dispositivos.size();
}