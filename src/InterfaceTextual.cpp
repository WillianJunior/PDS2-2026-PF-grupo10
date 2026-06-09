#include "InterfaceTextual.hpp"
#include <fstream>
#include <iostream>

void InterfaceTextual::iniciar() {
	ativa = true;
	std::cout << "Bem-vindo ao Sistema Smart Home (digite 'sair' para encerrar)" << std::endl;
	exibirMenuPrincipal();

	std::string comando;
	while (ativa) {
		std::cout << "> ";
		if (!std::getline(std::cin, comando)) break;
		if (comando.empty()) continue;
		if (comando == "sair" || comando == "encerrar") {
			encerrar();
			break;
		}
		interpretarComando(comando);
	}
}

void InterfaceTextual::lerComando() {
}

void InterfaceTextual::interpretarComando(const std::string &comando) {
}

void InterfaceTextual::encerrar() {
	ativa = false;
	// Limpa estado de navegação
	menuAtual.clear();
	comodoFocado.clear();
	dispositivoFocadoID = -1;
	// Remove referência ao usuário atual
	usuarioAtual = nullptr;
	std::cout << "Interface encerrada." << std::endl;
}

void InterfaceTextual::exibirMenuPrincipal() {
	menuAtual = "PRINCIPAL";
	comodoFocado.clear();
	dispositivoFocadoID = -1;

	std::cout << "=== Menu Principal ===" << std::endl;
	exibirComodos();

	std::cout << "\nComandos disponíveis:" << std::endl;
	std::cout << "  entrar <nome_comodo>  - acessar um cômodo" << std::endl;
	std::cout << "  relatorio             - gerar e exibir relatório" << std::endl;
    std::cout << "  alertas               - exibir alertas recentes" << std::endl;
    std::cout << "  macros                - listar macros cadastradas" << std::endl;
	std::cout << "  sair                  - encerrar a interface" << std::endl;
}

void InterfaceTextual::exibirMenuComodo(const std::string &nomeComodo) {
	if (sistema == nullptr) {
		std::cout << "Sistema não inicializado." << std::endl;
		return;
	}

	// Procura o cômodo pelo nome
	const Comodo* alvo = nullptr;
	int qtd = sistema->getQtdComodos();
	for (int i = 0; i < qtd; ++i) {
		const Comodo* c = sistema->getComodo(i);
		if (c != nullptr && c->getNome() == nomeComodo) {
			alvo = c;
			break;
		}
	}

	if (alvo == nullptr) {
		std::cout << "Cômodo '" << nomeComodo << "' não encontrado." << std::endl;
		return;
	}

	menuAtual = "COMODO";
	comodoFocado = nomeComodo;
	dispositivoFocadoID = -1;

	std::cout << "=== Cômodo: " << nomeComodo << " ===" << std::endl;
	int qtdDisp = alvo->getQtdDispositivos();
	if (qtdDisp == 0) {
		std::cout << "(nenhum dispositivo cadastrado)" << std::endl;
	} else {
		std::cout << "Dispositivos:" << std::endl;
		for (int i = 0; i < qtdDisp; ++i) {
			Dispositivo* d = alvo->getDispositivoPorIndice(i);
			if (d != nullptr) {
				std::cout << "  " << d->getEstadoFormatado() << std::endl;
			}
		}
	}

	std::cout << "\nComandos disponíveis:" << std::endl;
	std::cout << "  ligar <id>            - ligar dispositivo" << std::endl;
	std::cout << "  desligar <id>         - desligar dispositivo" << std::endl;
	std::cout << "  voltar                - voltar ao menu principal" << std::endl;
    //adicionar mais comandos específicos.
}

void InterfaceTextual::exibirRelatorio() {
	if (sistema == nullptr) {
		std::cerr << "Sistema não inicializado." << std::endl;
		return;
	}

	const std::string caminho = "relatorio.txt";
	sistema->gerarRelatorio(caminho);

	std::ifstream arq(caminho);
	if (!arq.is_open()) {
		std::cerr << "Não foi possível abrir o relatório: " << caminho << std::endl;
		return;
	}

	std::string linha;
	while (std::getline(arq, linha)) {
		std::cout << linha << std::endl;
	}

	arq.close();
}

void InterfaceTextual::exibirComodos() {
	if (sistema == nullptr) {
		std::cout << "(Sistema não inicializado)" << std::endl;
		return;
	}

	int qtd = sistema->getQtdComodos();
	std::cout << "Cômodos cadastrados: " << qtd << std::endl;
	for (int i = 0; i < qtd; ++i) {
		const Comodo* c = sistema->getComodo(i);
		if (c != nullptr) {
			std::cout << " - " << c->getNome() << std::endl;
		}
	}
}

void InterfaceTextual::limparTela() {
}

void InterfaceTextual::exibirMensagem(const std::string &mensagem) {
}

void InterfaceTextual::exibirAlerta(std::vector<std::string> &alertas) {
}

void InterfaceTextual::exibirEstado(int ID) {
}