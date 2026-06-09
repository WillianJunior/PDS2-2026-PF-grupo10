#include "Comodo.hpp"

Comodo::Comodo() : nome("") {
}

Comodo::Comodo(const std::string& nome) : nome(nome) {
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

Dispositivo* Comodo::getDispositivoPorIndice(int idx) const {
    if (idx < 0 || idx >= static_cast<int>(dispositivos.size())) return nullptr;
    return dispositivos[idx];
}

std::string Comodo::getNome() const {
    return nome;
}

void Comodo::setNome(const std::string& nome) {
    this->nome = nome;
}