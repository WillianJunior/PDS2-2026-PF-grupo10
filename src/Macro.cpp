#include "Macro.hpp"
#include <cctype>

int Macro::qtdMacros = 0;

Macro::Macro(std::string evento) : evento(evento), lista(nullptr)
{
    qtdMacros++;
}

Macro::~Macro() {
    qtdMacros--;
}

std::string Macro::getEvento() const {
    return evento;
}

Node* Macro::getLista() const {
    return lista.get();
}

void Macro::setEvento(std::string evento) {
    if (evento.empty()) {
        throw std::invalid_argument("Evento invalido.");
    }

    bool contemCaracterValido = false;

    for (char c : evento) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            contemCaracterValido = true;
            break;
        }
    }

    if (!contemCaracterValido) {
        throw std::invalid_argument("Evento invalido.");
    }

    this->evento = evento;
}

void Macro::adicionarDispositivo(int id, std::string acao) {

    auto novo = std::make_unique<Node>();
    novo->id = id;
    novo->acao = acao;
    novo->proximo = nullptr;

    if (!lista) {
        lista = std::move(novo);
        return;
    }

    Node* atual = lista.get();

    while (atual->proximo) {
        atual = atual->proximo.get();
    }

    atual->proximo = std::move(novo);
}

void Macro::removerDispositivo(int id, std::string acao) {

    if (!lista) {
        return;
    }

    if (lista->id == id && lista->acao == acao) {
        lista = std::move(lista->proximo);
        return;
    }

    Node* atual = lista.get();

    while (atual->proximo) {

        if (atual->proximo->id == id &&
            atual->proximo->acao == acao) {

            atual->proximo =
                std::move(atual->proximo->proximo);

            return;
        }

        atual = atual->proximo.get();
    }
}
