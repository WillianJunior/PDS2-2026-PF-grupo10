#include "ArCondicionado.hpp"
#include "Usuario.hpp"
#include "Sistema.hpp"
#include "Portao.hpp"
#include "Luz.hpp"
#include "Som.hpp"


#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>


Usuario::Usuario(std::string nome, std::string senha) : _nome(nome), _senha(senha) {
}

std::string Usuario::getNome() const {
    return this->_nome;
}

void Usuario::setNome(std::string& nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Erro: O nome do usuário não pode ser vazio.");
    }
    this->_nome = nome;
}

bool Usuario::autenticar(std::string& nome, std::string& senha) const {
    return _nome == nome && _senha == senha;
}

Macro* Usuario::getMacro(int i) const {
    if (i < 0 || i >= static_cast<int>(macros.size())) {
        return nullptr;
    }
    return macros[i].get();
}

void Usuario::listarMacros() const {

    if (macros.empty()) {
        std::cout << "Nenhuma macro cadastrada." << std::endl;
        return;
    }

    std::cout << "Macros disponiveis:" << std::endl;

    for (const auto& macro : macros) {
        std::cout << "- " << macro->getEvento() << std::endl;
    }
}

Macro* Usuario::adicionarMacro(const std::string& evento, Sistema& sistema) {
    if (evento.empty()) {
        throw std::invalid_argument("Erro: O nome do evento para a macro não pode ser vazio.");
    }
    macros.push_back(std::unique_ptr<Macro>(new Macro(evento)));
    return macros.back().get();
}

void Usuario::removerMacro(std::string evento) {
    for (auto it = macros.begin(); it != macros.end(); ++it) {
        if ((*it)->getEvento() == evento) {
            macros.erase(it);
            return;
        }
    }
    throw std::runtime_error("Erro: Macro com o evento '" + evento + "' não encontrada.");
}

void Usuario::executarMacro(std::string evento, Sistema& sistema) {
    try {
        for (const auto& macro : macros) {

            if (macro->getEvento() != evento)
                continue;

            Node* atual = macro->getLista();

            while (atual != nullptr) {

                Dispositivo* disp = sistema.getDispositivo(atual->id);

                if (disp != nullptr) {
                    if (atual->acao == "ligar") {
                        disp->alterarEstado(true);
                    }
                    else if (atual->acao == "desligar") {
                        disp->alterarEstado(false);
                    }
                    else if (atual->acao == "abrir") {
                        disp->alterarEstado(true);
                    }
                    else if (atual->acao == "fechar") {
                        disp->alterarEstado(false);
                    }
                    else if (atual->acao == "ajustar") {
                        if (auto* luz = dynamic_cast<Luz*>(disp)) {
                            luz->ajustarIntensidade(atual->valor);
                        }
                        else if (auto* ar = dynamic_cast<ArCondicionado*>(disp)) {
                            ar->ajustarTemperatura(atual->valor);
                        }
                        else if (auto* som = dynamic_cast<Som*>(disp)) {
                            som->setVolume(atual->valor);
                        }
                        else if (auto* portao = dynamic_cast<Portao*>(disp)) {
                            portao->setTemporizador(atual->valor);
                        }
                    }
                    else {
                        throw std::runtime_error("Acao desconhecida: " + atual->acao);
                    }
                }
                atual = atual->proximo.get();
            }
            return;
        }

        throw std::runtime_error("Nao foi possivel executar. Macro \"" + evento + "\" nao encontrada.");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}


void Usuario::salvarDados(const Sistema& sistema){

    std::string caminho = "data/" + _nome + ".txt";
    std::ofstream registro(caminho);

    if (!registro.is_open()) {
        std::cerr << "Erro: não foi possível abrir o arquivo " << caminho << std::endl;
        return;
    }

    registro << "USUARIO\n";
    registro << _nome << '\n';
    registro << _senha << "\n\n";

    registro << "COMODOS\n";

    for (int i = 0; i < sistema.getQtdComodos(); i++) {

        Comodo* comodo = sistema.getComodo(i);

        registro << comodo->getNome() << '\n';

        for (int j = 0; j < comodo->getQtdDispositivos(); j++) {

            Dispositivo* disp = comodo->getDispositivoPorIndice(j);

            int valor = 0;

            if (auto* luz = dynamic_cast<Luz*>(disp))
                valor = luz->getIntensidade();

            else if (auto* ar = dynamic_cast<ArCondicionado*>(disp))
                valor = ar->getTemperatura();

            else if (auto* som = dynamic_cast<Som*>(disp))
                valor = som->getVolume();

            else if (auto* portao = dynamic_cast<Portao*>(disp))
                valor = portao->getTemporizador();

            registro << disp->getNome() << ' ' << disp->getId() << ' ' << disp->getEstado() << ' ' << valor << '\n';
        }

        registro << "FIM_COMODO\n";
    }
    registro << "FIM_COMODOS\n\n";

    registro << "MACROS\n";

    for (const auto& macro : macros) {

        registro << macro->getEvento() << '\n';

        Node* atual = macro->getLista();

        while (atual != nullptr) {

            registro << atual->id << ' ' << atual->acao << ' ' << atual->valor << '\n';

            atual = atual->proximo.get();
        }

        registro << "FIM_MACRO\n";
    }
    registro << "FIM_MACROS\n";

    registro.close();
}


bool Usuario::carregarDados(Sistema& sistema) {

    std::string caminho = "data/" + _nome + ".txt";
    std::ifstream registro(caminho);

    if (!registro.is_open()) {
        std::cerr << "Erro: não foi possível abrir o arquivo " << caminho << std::endl;
        return false;
    }

    sistema.limparSistema();
    macros.clear();

    std::string linha;

    // ---------- USUARIO ----------
    std::getline(registro, linha); // USUARIO
    std::getline(registro, _nome);
    std::getline(registro, _senha);

    std::getline(registro, linha); // linha vazia

    // ---------- COMODOS ----------
    std::getline(registro, linha); // COMODOS

    while (std::getline(registro, linha)) {

        if (linha == "FIM_COMODOS")
            break;

         std::unique_ptr<Comodo> novoComodo(new Comodo(linha));
        Comodo* ptrComodo = novoComodo.get();

        while (std::getline(registro, linha)) {

            if (linha == "FIM_COMODO")
                break;

            std::stringstream ss(linha);

            std::string tipo;
            int id;
            bool estado;
            int valor;

            ss >> tipo >> id >> estado >> valor;

            std::unique_ptr<Dispositivo> disp;

            if (tipo == "Luz") {

                auto luz = std::unique_ptr<Luz>(new Luz());
                luz->setId(id);
                luz->alterarEstado(estado);
                luz->ajustarIntensidade(valor);

                disp = std::move(luz);
            }

            else if (tipo == "Som") {

                auto som = std::unique_ptr<Som>(new Som());
                som->setId(id);
                som->alterarEstado(estado);
                som->setVolume(valor);

                disp = std::move(som);
            }

            else if (tipo == "ArCondicionado") {

                auto ar = std::unique_ptr<ArCondicionado>(new ArCondicionado());
                ar->setId(id);
                ar->alterarEstado(estado);
                ar->ajustarTemperatura(valor);

                disp = std::move(ar);
            }

            else if (tipo == "Portao") {

                auto portao = std::unique_ptr<Portao>(new Portao());
                portao->setId(id);
                portao->alterarEstado(estado);
                portao->setTemporizador(valor);

                disp = std::move(portao);
            }

            if (disp)
                ptrComodo->adicionarDispositivo(std::move(disp));
        }

        sistema.adicionarComodo(std::move(novoComodo));
    }

    // ---------- MACROS ----------
    std::getline(registro, linha); // linha vazia
    std::getline(registro, linha); // MACROS

    while (std::getline(registro, linha)) {

        if (linha == "FIM_MACROS")
            break;

        std::unique_ptr<Macro> macro(new Macro(linha));

        while (std::getline(registro, linha)) {

            if (linha == "FIM_MACRO")
                break;

            std::stringstream ss(linha);

            int id;
            int valor;
            std::string acao;

            ss >> id >> acao >> valor;

            macro->adicionarDispositivo(id, acao, valor);
        }

        macros.push_back(std::move(macro));
    }
    registro.close();

    return true;
}

void Usuario::limparMacros() {
    macros.clear();
}