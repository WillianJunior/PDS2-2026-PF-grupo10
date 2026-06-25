#include "Comodo.hpp"
#include <stdexcept>
#include <iostream>

Comodo::Comodo() : nome("") {
}

Comodo::Comodo(const std::string& nome) : nome("") {
    setNome(nome);
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
    if (!dispositivo) {
        throw std::invalid_argument("Dispositivo nao pode ser nulo.");
    }

    if (getDispositivo(dispositivo->getId()) != nullptr) {
        throw std::invalid_argument("Dispositivo ja cadastrado no comodo.");
    }

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
    std::cout << "idx = " << idx
              << ", size = " << dispositivos.size()
              << std::endl;

    if (idx < 0 || idx >= static_cast<int>(dispositivos.size())) {
        std::cout << "retornando nullptr\n";
        return nullptr;
    }

    return dispositivos[idx].get();
}

std::string Comodo::getNome() const {
    return nome;
}

void Comodo::setNome(const std::string& nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome do comodo invalido.");
    }

    bool contemCaracterValido = false;

    for (char c : nome) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            contemCaracterValido = true;
            break;
        }
    }

    if (!contemCaracterValido) {
        throw std::invalid_argument("Nome do comodo invalido.");
    }

    this->nome = nome;
}