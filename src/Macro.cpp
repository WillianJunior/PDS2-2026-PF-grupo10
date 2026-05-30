#include "Macro.hpp"

int Macro::qtdMacros = 0;

Macro::Macro(std::string evento) : evento(evento), lista(nullptr) {
    qtdMacros++;
}

Macro::~Macro() {
    Node* atual = lista;
    while (atual != nullptr) {
        Node* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    qtdMacros--;
}

std::string Macro::getEvento() const {
    return evento;
}

Node* Macro::getLista() const {
    return lista;
}

void Macro::setEvento(std::string evento) {
    this->evento = evento;
}

void Macro::adicionarDispositivo(int id, std::string acao) {
    Node* novo = new Node;
    novo->id = id;
    novo->acao = acao;
    novo->proximo = nullptr;

    if (lista == nullptr) {
        lista = novo;
        return;
    }

    Node* atual = lista;
    while (atual->proximo != nullptr) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
}

void Macro::removerDispositivo(int id, std::string acao) {
    Node* atual = lista;
    Node* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->id == id && atual->acao == acao) {
            if (anterior == nullptr) {
                lista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            delete atual;
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}
