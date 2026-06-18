#include "Comodo.hpp"

Comodo::Comodo() : nome("") {
}

Comodo::Comodo(const std::string& nome) : nome(nome) {
}

Dispositivo* Comodo::getDispositivo(int id) const {
    for (const auto& dispositivo : dispositivos) {
        if (dispositivo && dispositivo->getId() == id) {
            return dispositivo.get();
        }
    }
    return nullptr;
}

void Comodo::adicionarDispositivo(std::unique_ptr<Dispositivo> dispositivo) {
    dispositivos.push_back(std::move(dispositivo));
}

void Comodo::removerDispositivo(int id) {
    for (auto it = dispositivos.begin(); it != dispositivos.end(); ++it) {
        if (*it && (*it)->getId() == id) {
            dispositivos.erase(it);
            return;
        }
    }
}

int Comodo::getQtdDispositivos() const {
    return dispositivos.size();
}

Dispositivo* Comodo::getDispositivoPorIndice(int idx) const {
    if (idx < 0 || idx >= static_cast<int>(dispositivos.size())){
        return nullptr;
    }
    return dispositivos[idx].get();
}

std::string Comodo::getNome() const {
    return nome;
}

void Comodo::setNome(const std::string& nome) {
    this->nome = nome;
}