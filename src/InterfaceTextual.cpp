#include "InterfaceTextual.hpp"
#include "ArCondicionado.hpp"
#include "Som.hpp"
#include "Portao.hpp"
#include "Dispositivo.hpp"
#include "Luz.hpp"
#include "Sistema.hpp"
#include "Sensor.hpp"
#include "Usuario.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

InterfaceTextual::InterfaceTextual() : ativa(false), sistema(new Sistema), usuarioAtual(nullptr), menuAtual(" "), comodoFocado(" "), dispositivoFocadoID(0){
}

void InterfaceTextual::iniciar() {
      ativa = true;
      std::string comando;
      while (ativa) {
            exibirMenuPrincipal();

            if (!std::getline(std::cin, comando)) break;
            if (comando.empty()) continue;
            if (comando == "sair" || comando == "encerrar") {
                  encerrar();
            break;
            }
            this->limparTela();
            interpretarComando(comando);
            std::cout << std::endl;
            std::cout << std::endl;

      }
}

void InterfaceTextual::interpretarComando(const std::string &comando){

      // converte tudo para minusculo
      std::string Fcomando = comando;
      std::transform(Fcomando.begin(), Fcomando.end(), Fcomando.begin(), [](unsigned char c)
      {
            return static_cast<char>(std::tolower(c));
      });

      Comodo* comodoAtual = nullptr;
      if (!comodoFocado.empty() && sistema != nullptr) {
            int qtd = sistema->getQtdComodos();
            for (int i = 0; i < qtd; ++i) {
                  const Comodo* c = sistema->getComodo(i);
                  if (c != nullptr && c->getNome() == comodoFocado) {
                        comodoAtual = const_cast<Comodo*>(c);
                        break;
                  }
            }
      }

      Dispositivo* dispBase = nullptr;
      if (comodoAtual != nullptr && dispositivoFocadoID != 0) {
          dispBase = comodoAtual->getDispositivo(dispositivoFocadoID);
      }

      //inicio da leitura dos comandos

      if       (Fcomando == "ligar som") {
          if(auto som = dynamic_cast<Som*>(dispBase)) {
              som->alterarEstado(true);
              som->printPlaylist();
          }else{
              std::cout << "O dispositivo focado nao e um aparelho de som ou nao foi encontrado.\n";
          }
      }else if(Fcomando == "tocar musica") {
           if(auto som = dynamic_cast<Som*>(dispBase)) {
              som->tocar();
          }
      }else if (Fcomando == "escolher musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              int indice;
              std::cout << "Digite o indice da musica: ";
              std::cin >> indice;
              som->tocar(indice);
          }
      }else if (Fcomando == "alterar volume") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              int volume;
              std::cout << "Digite o novo volume (0-100): ";
              std::cin >> volume;
              som->setVolume(volume);
          }
      }else if (Fcomando == "pausar som") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              som->togglePause();
          }
      }else if (Fcomando == "avancar musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              som->proxima();
          }
      }else if (Fcomando == "voltar musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              som->anterior();
          }
      }else if (Fcomando == "inserir musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              std::string nomeMusica;
              std::cout << "Digite o nome da musica: ";
              std::cin.ignore();
              std::getline(std::cin, nomeMusica);
              som->adicionarMusica(nomeMusica);
          }
      }else if (Fcomando == "remover musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              int indice;
              std::cout << "Digite o indice da musica a remover: ";
              std::cin >> indice;
              som->removerMusica(indice);
          }
      }

      //comandos de luz

      else if (Fcomando == "ligar luz") {
          if (auto luz = dynamic_cast<Luz*>(dispBase)) {
              luz->ligar();
          }
      }else if (Fcomando == "desligar luz") {
          if (auto luz = dynamic_cast<Luz*>(dispBase)) {
              luz->desligar();
          }
      }else if (Fcomando == "alterar intensidade") {
          if (auto luz = dynamic_cast<Luz*>(dispBase)) {
              int intensidade;
              std::cout << "Digite a intensidade (1 a 5): ";
              std::cin >> intensidade;
              luz->ajustarIntensidade(intensidade);
          }
      }

      // comandos do portao

      else if (Fcomando == "abrir portao") {
          if (auto portao = dynamic_cast<Portao*>(dispBase)) {
              portao->alterarEstado(true);
              portao->fecharAutomaticamente();
          }
      }else if (Fcomando == "alterar temporizador") {
          if (auto portao = dynamic_cast<Portao*>(dispBase)) {
              int segundos;
              std::cout << "Digite o tempo em segundos: ";
              std::cin >> segundos;
              portao->setTemporizador(segundos);
          }
      }

      //comandos do ar condicionado

      else if (Fcomando == "ligar ar condicionado") {
          if (auto ac = dynamic_cast<ArCondicionado*>(dispBase)) {
              ac->ligar();
          }
      }else if (Fcomando == "desligar ar condicionado") {
          if (auto ac = dynamic_cast<ArCondicionado*>(dispBase)) {
              ac->desligar();
          }
      }else if (Fcomando == "alterar temperatura") {
          if (auto ac = dynamic_cast<ArCondicionado*>(dispBase)) {
              int temp;
              std::cout << "Digite a temperatura (15 a 30): ";
              std::cin >> temp;
              ac->ajustarTemperatura(temp);
          }
      }

      // comandos do sistema

      else if (Fcomando == "fazer relatorio") {
          std::string caminho;
          std::cout << "Digite o caminho/nome do arquivo: ";
          std::cin >> caminho;
          sistema->gerarRelatorio(caminho);

      }else if (Fcomando == "adicionar comodo") {
          std::string nomeComodo;
          std::cout << "Nome do comodo: ";
          std::cin.ignore();
          std::getline(std::cin, nomeComodo);
          Comodo novoComodo(nomeComodo);
          sistema->adicionarComodo(novoComodo);
      }else if (Fcomando == "remover comodo") {
          if (comodoAtual != nullptr) {
              sistema->removerComodo(*comodoAtual);
          }
      }else if (Fcomando == "adicionar dispositivo") {
          if (comodoAtual != nullptr) {
              std::cout << "Tipo (1-Luz, 2-Som, 3-Ar, 4-Portao): ";
              int tipo;
              std::cin >> tipo;
              Dispositivo* novo = nullptr;
              if (tipo == 1)      novo = new Luz();
              else if (tipo == 2) novo = new Som();
              else if (tipo == 3) novo = new ArCondicionado();
              else if (tipo == 4) novo = new Portao();

              if (novo != nullptr) {
                  comodoAtual->adicionarDispositivo(novo);
                  std::cout << "Dispositivo adicionado com ID: " << novo->getId() << std::endl;
              }
          }
      }else if (Fcomando == "remover dispositivo") {
          if (comodoAtual != nullptr) {
              int id;
              std::cout << "Digite o ID do dispositivo a remover: ";
              std::cin >> id;
              comodoAtual->removerDispositivo(id);
          }
      }

      /*todo:
       * listar comodos
       * interface normal
       *
        */
      // comandos de usuario

      else if (Fcomando == "renomear") {
          if (usuarioAtual != nullptr) {
              std::string novoNome;
              std::cout << "Novo nome de usuario: ";
              std::cin >> novoNome;
              usuarioAtual->setNome(novoNome);
          }
      }else if (Fcomando == "ver nome") {
          if (usuarioAtual != nullptr) {
              std::cout << "Usuario logado: " << usuarioAtual->getNome() << std::endl;
          }
      }else if (Fcomando == "autenticar") {
          std::string nome, senha;
          std::cout << "Nome: "; std::cin >> nome;
          std::cout << "Senha: "; std::cin >> senha;
          if (usuarioAtual != nullptr && usuarioAtual->autenticar(nome, senha)) {
              std::cout << "Autenticado com sucesso!\n";
          } else {
              std::cout << "Falha na autenticacao.\n";
          }
      }else if (Fcomando == "adicionar macro") {
          if (usuarioAtual != nullptr) {
              std::string evento;
              std::cout << "Evento para a macro: ";
              std::cin >> evento;
              usuarioAtual->adicionarMacro(evento, *usuarioAtual);
          }
      }else if (Fcomando == "remover macro") {
          if (usuarioAtual != nullptr) {
              std::string evento;
              std::cout << "Nome do evento da macro a remover: ";
              std::cin >> evento;
              usuarioAtual->removerMacro(evento, *usuarioAtual);
          }
      }else if (Fcomando == "executar macro") {
          if (usuarioAtual != nullptr) {
              std::string evento;
              std::cout << "Nome do evento para executar: ";
              std::cin >> evento;
              usuarioAtual->executarMacro(evento, *usuarioAtual);
          }
      }else {
          std::cout << "Comando invalido ou nao reconhecido.\n";
      } // when (others <- ?)
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

      std::cout << "Bem-vindo ao Sistema Smart Home (digite 'sair' para encerrar)" << std::endl;
      std::cout << "=== Menu Principal ===" << std::endl;
      exibirComodos();

      std::cout << "\nComandos disponíveis:" << std::endl;
      std::cout << "  entrar <nome_comodo>  - acessar um cômodo\n" << std::endl;
      std::cout << "  relatorio             - gerar e exibir relatório\n" << std::endl;
      std::cout << "  alertas               - exibir alertas recentes\n" << std::endl;
      std::cout << "  macros                - listar macros cadastradas\n" << std::endl;
      std::cout << "  sair                  - encerrar a interface\n" << std::endl;

      std::cout << "> ";
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
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void InterfaceTextual::exibirMensagem(const std::string &mensagem) {
}

void InterfaceTextual::exibirAlerta(std::vector<std::string> &alertas) {
}

void InterfaceTextual::exibirEstado(int ID) {
}