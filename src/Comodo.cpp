#include "Comodo.hpp"

Comodo::Comodo() {
}

Comodo::~Comodo() {
    for (Dispositivo* dispositivo : dispositivos) {
        delete dispositivo;
    }
    dispositivos.clear();
}

Dispositivo* Comodo::getDispositivo(int id) const {
    for (Dispositivo* dispositivo : dispositivos) {
        if (dispositivo != nullptr && dispositivo->getId() == id) {
            return dispositivo;
        }
    }
    return nullptr;
}

void Comodo::adicionarDispositivo(Dispositivo* dispositivo) {
    dispositivos.push_back(dispositivo);
}

void Comodo::removerDispositivo(int id) {
    for (auto it = dispositivos.begin(); it != dispositivos.end(); ++it) {
        if (*it != nullptr && (*it)->getId() == id) {
            delete *it;
            dispositivos.erase(it);
            return;
        }
    }
}

int Comodo::getQtdDispositivos() const {
    return dispositivos.size();
}