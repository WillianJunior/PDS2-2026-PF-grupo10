#include "InterfaceTextual.hpp"
#include "ArCondicionado.hpp"
#include "Som.hpp"
#include "Portao.hpp"
#include "Dispositivo.hpp"
#include "Luz.hpp"
#include "Sistema.hpp"
#include "Sensor.hpp"
#include "Usuario.hpp"
#include "Comodo.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>

InterfaceTextual::InterfaceTextual() : ativa(false), sistema(new Sistema), usuarioAtual(nullptr), menuAtual(""), comodoFocado(""), dispositivoFocadoID(0){
}

void InterfaceTextual::iniciar() {
      ativa = true;
      std::string comando;
      while (ativa) {
          if (menuAtual == "COMODO" && !comodoFocado.empty()) {
              exibirMenuComodo(comodoFocado);
          } else {
              exibirMenuPrincipal();
          }

            if (!std::getline(std::cin, comando)) break;
            limparTela();
            if (comando.empty()) continue;
            if (comando == "sair" || comando == "encerrar") {
                  encerrar();
            break;
            }
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

      if (Fcomando.find("entrar ") == 0) {
          std::string nome = Fcomando.substr(7); // remove "entrar "
          Comodo* c = sistema->getComodo(nome);
          if (c) {
              comodoFocado = nome;
              dispositivoFocadoID = -1;
              menuAtual = "COMODO";
              limparTela();
              exibirMenuComodo(nome);
          } else {
              std::cerr << "Cômodo '" << nome << "' não encontrado.\n";
          }
      }



      //inicio da leitura dos comandos

      else if(Fcomando == "ligar som") {
          if(auto som = dynamic_cast<Som*>(dispBase)) {
              som->alterarEstado(true);
              som->printPlaylist();
          }else{
              std::cout << "O dispositivo focado nao e um aparelho de som ou nao foi encontrado.\n";
          }
      }

      else if (Fcomando == "ajuda" || Fcomando == "help" || Fcomando == "?") {
          exibirAjuda();
      }

      else if(Fcomando == "tocar musica") {
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
          std::getline(std::cin, nomeComodo);

          std::transform(nomeComodo.begin(), nomeComodo.end(), nomeComodo.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

          sistema->adicionarComodo(std::unique_ptr<Comodo>(new Comodo(nomeComodo)));

      }else if (Fcomando == "remover comodo") {
          if (comodoAtual != nullptr) {
              sistema->removerComodo(comodoAtual);
          }

      }else if (Fcomando == "comodo") {
          if (comodoAtual != nullptr) {
              exibirMenuComodo(comodoFocado);
          }else{
              std::cout << "Nenhum cômodo focado" << std::endl;
        }

      }else if (Fcomando == "adicionar dispositivo") {
          if (comodoAtual != nullptr) {
              std::cout << "Tipo (1-Luz, 2-Som, 3-Ar, 4-Portao): \n";
              int tipo;
              std::cin >> tipo;
              std::unique_ptr<Dispositivo> novo = nullptr;
              if (tipo == 1)      novo = std::make_unique<Luz>();
              else if (tipo == 2) novo = std::make_unique<Som>();
              else if (tipo == 3) novo = std::make_unique<ArCondicionado>();
              else if (tipo == 4) novo = std::make_unique<Portao>();

              if (novo != nullptr) {
                  int id = novo->getId();
                  comodoAtual->adicionarDispositivo(std::move(novo));
                  std::cout << "Dispositivo adicionado com ID: " << id << std::endl;
              }
          }
      }else if (Fcomando == "remover dispositivo") {
          if (comodoAtual != nullptr) {
              int id;
              std::cout << "Digite o ID do dispositivo a remover: ";
              std::cin >> id;
              comodoAtual->removerDispositivo(id);
          }
      }else if (Fcomando == "ajuda"){
          exibirAjuda();
    }

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
              usuarioAtual->adicionarMacro(evento);
          }
      }else if (Fcomando == "remover macro") {
          if (usuarioAtual != nullptr) {
              std::string evento;
              std::cout << "Nome do evento da macro a remover: ";
              std::cin >> evento;
              usuarioAtual->removerMacro(evento);
          }
      }else if (Fcomando == "executar macro") {
          if (usuarioAtual != nullptr) {
              std::string evento;
              std::cout << "Nome do evento para executar: ";
              std::cin >> evento;
              usuarioAtual->executarMacro(evento);

        }
    }else if (Fcomando == "voltar") {
              menuAtual = "PRINCIPAL";
              comodoFocado.clear();
              dispositivoFocadoID = -1;
          }

      else {
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
      limparTela();
      std::cout << "Interface encerrada." << std::endl;
}

void InterfaceTextual::exibirMenuPrincipal() {
      // limparTela();

      menuAtual = "PRINCIPAL";
      dispositivoFocadoID = -1;

      std::cout << "Bem-vindo ao Sistema Smart Home (digite 'sair' para encerrar)" << std::endl;
      std::cout << "=== Menu Principal ===" << std::endl;
      exibirComodos();

      std::cout << "\nPara exibir comandos possíveis, execute \"ajuda\" \n";
      std::cout << "> ";
}

void InterfaceTextual::exibirMenuComodo(const std::string &nomeComodo) {
    limparTela();
    if (sistema == nullptr) {
        std::cout << "Sistema não inicializado." << std::endl;
        return;
    }

    if (nomeComodo.empty()) {
        std::cout << "Nenhum comodo focado" << std::endl;
        return;
    }

    // Procura o cômodo pelo nome para garantir que ele existe
    Comodo* comodoAtual = nullptr;
    int qtd = sistema->getQtdComodos();
    for (int i = 0; i < qtd; ++i) {
        const Comodo* c = sistema->getComodo(i);
        if (c != nullptr && c->getNome() == nomeComodo) {
            comodoAtual = const_cast<Comodo*>(c);
            break;
        }
    }

    if (comodoAtual == nullptr) {
        std::cout << "Cômodo '" << nomeComodo << "' não encontrado." << std::endl;
        return;
    }

    menuAtual = "COMODO";
    comodoFocado = nomeComodo;

    std::string comandoComodo;
    bool noComodo = true;

    while (noComodo && ativa) {
        limparTela();
        std::cout << "=== Cômodo: " << nomeComodo << " ===" << std::endl;

        int qtdDisp = comodoAtual->getQtdDispositivos();
        if (qtdDisp == 0) {
            std::cout << "(nenhum dispositivo cadastrado)" << std::endl;
        } else {
            std::cout << "Dispositivos no cômodo:" << std::endl;
            for (int i = 0; i < qtdDisp; ++i) {
                Dispositivo* d = comodoAtual->getDispositivoPorIndice(i);
                if (d != nullptr) {
                    std::cout << "  " << d->getEstadoFormatado() << std::endl;
                }
            }
        }

        std::cout << "\nComandos de Cômodo disponíveis (digite 'ajuda' para detalhes ou 'voltar'):" << std::endl;
        std::cout << "codo> ";

        if (!std::getline(std::cin, comandoComodo)) break;
        if (comandoComodo.empty()) continue;

        // Converter comando local para minúsculo
        std::string Fcmd = comandoComodo;
        std::transform(Fcmd.begin(), Fcmd.end(), Fcmd.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });

        if (Fcmd == "voltar") {
            menuAtual = "PRINCIPAL";
            comodoFocado.clear();
            dispositivoFocadoID = -1;
            noComodo = false;
            limparTela();
            break;
        }

        if (Fcmd == "sair" || Fcmd == "encerrar") {
            encerrar();
            break;
        }

        if (Fcmd == "ajuda") {
            // Função vazia de ajuda local conforme solicitado
            std::cout << "\n--- AJUDA DO CÔMODO ---" << std::endl;
            std::cout << "Comandos suportados aqui:" << std::endl;
            std::cout << "  ligar <id> / desligar <id>" << std::endl;
            std::cout << "  ativar <id> / desativar <id>" << std::endl;
            std::cout << "  voltar (retorna ao menu principal)" << std::endl;
            std::cout << "Pressione ENTER para continuar...";
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
        }

        // Processamento de comandos: ligar, desligar, ativar, desativar <id>
        std::string acao;
        int idAlvo = -1;
        std::stringstream ss(Fcmd);

        if (ss >> acao >> idAlvo) {
            Dispositivo* disp = comodoAtual->getDispositivo(idAlvo);

            if (disp != nullptr) {
                if (acao == "ligar" || acao == "ativar") {
                    // Tenta fazer o cast ou chamada genérica dependendo da sua arquitetura
                    // Exemplo usando polimorfismo se houver método genérico, ou usando os específicos:
                    if (auto luz = dynamic_cast<Luz*>(disp)) luz->ligar();
                    else if (auto ac = dynamic_cast<ArCondicionado*>(disp)) ac->ligar();
                    else if (auto som = dynamic_cast<Som*>(disp)) som->alterarEstado(true);
                    else if (auto portao = dynamic_cast<Portao*>(disp)) portao->alterarEstado(true);

                    std::cout << "Dispositivo [" << idAlvo << "] ativado/ligado com sucesso.\n";
                }
                else if (acao == "desligar" || acao == "desativar") {
                    if (auto luz = dynamic_cast<Luz*>(disp)) luz->desligar();
                    else if (auto ac = dynamic_cast<ArCondicionado*>(disp)) ac->desligar();
                    else if (auto som = dynamic_cast<Som*>(disp)) som->alterarEstado(false);
                    else if (auto portao = dynamic_cast<Portao*>(disp)) portao->alterarEstado(false);

                    std::cout << "Dispositivo [" << idAlvo << "] desativado/desligado com sucesso.\n";
                }
                else {
                    std::cout << "Ação '" << acao << "' não reconhecida para dispositivos.\n";
                }
            } else {
                std::cout << "Dispositivo com ID " << idAlvo << " não encontrado neste cômodo.\n";
            }
        } else {
            std::cout << "Comando inválido. Formato esperado: <ação> <id>\n";
        }

        std::cout << "\nPressione ENTER para continuar...";
        std::string dummy;
        std::getline(std::cin, dummy);
    }
}

void InterfaceTextual::exibirRelatorio() {
      if (sistema == nullptr) {
            std::cerr << "Sistema não inicializado." << std::endl;
            return;
      }

      const std::string caminho = "src/relatorio.txt";
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
            std::cerr << "(Sistema não inicializado)" << std::endl;
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

void InterfaceTextual::exibirAjuda() {
    limparTela();
    std::cout << "\n========== AJUDA - COMANDOS DISPONÍVEIS ==========\n\n";

    std::cout << "  **COMANDOS DO SOM** (necessário ter um dispositivo Som focado):\n";
    std::cout << "  ligar som           - Liga o aparelho de som\n";
    std::cout << "  desligar som        - Desliga o aparelho de som\n";
    std::cout << "  tocar musica        - Toca a música atual\n";
    std::cout << "  escolher musica     - Escolhe uma música pelo índice\n";
    std::cout << "  alterar volume      - Altera o volume (0-100)\n";
    std::cout << "  pausar som          - Pausa/retoma a reprodução\n";
    std::cout << "  avancar musica      - Avança para a próxima música\n";
    std::cout << "  voltar musica       - Volta para a música anterior\n";
    std::cout << "  inserir musica      - Adiciona uma música à playlist\n";
    std::cout << "  remover musica      - Remove uma música da playlist\n\n";

    std::cout << "  **COMANDOS DA ILUMINAÇÃO** (necessário ter uma Luz focada):\n";
    std::cout << "  ligar luz           - Liga a luz\n";
    std::cout << "  desligar luz        - Desliga a luz\n";
    std::cout << "  alterar intensidade - Altera a intensidade (1-5)\n\n";

    std::cout << "  **COMANDOS DO PORTÃO** (necessário ter um Portão focado):\n";
    std::cout << "  abrir portao        - Abre o portão\n";
    std::cout << "  alterar temporizador - Altera o tempo de fechamento automático (segundos)\n\n";

    std::cout << "  **COMANDOS DO AR CONDICIONADO** (necessário ter um Ar focado):\n";
    std::cout << "  ligar ar condicionado   - Liga o ar-condicionado\n";
    std::cout << "  desligar ar condicionado - Desliga o ar-condicionado\n";
    std::cout << "  alterar temperatura     - Ajusta a temperatura (15-30°C)\n\n";

    std::cout << "  **COMANDOS DO SISTEMA** (gerais):\n";
    std::cout << "  fazer relatorio     - Gera um relatório do sistema\n";
    std::cout << "  adicionar comodo    - Adiciona um novo cômodo\n";
    std::cout << "  remover comodo      - Remove o cômodo atual\n";
    std::cout << "  adicionar dispositivo - Adiciona um dispositivo ao cômodo atual\n";
    std::cout << "  remover dispositivo - Remove um dispositivo do cômodo atual\n\n";

    std::cout << "  **COMANDOS DO USUÁRIO** (requer usuário logado):\n";
    std::cout << "  renomear            - Altera o nome do usuário\n";
    std::cout << "  ver nome            - Mostra o nome do usuário logado\n";
    std::cout << "  autenticar          - Autentica o usuário\n";
    std::cout << "  adicionar macro     - Cria uma nova macro\n";
    std::cout << "  remover macro       - Remove uma macro\n";
    std::cout << "  executar macro      - Executa uma macro\n\n";

    std::cout << "  **COMANDOS DE NAVEGAÇÃO** (sempre disponíveis):\n";
    std::cout << "  entrar <nome>       - Entra em um cômodo\n";
    std::cout << "  sair                - Encerra a interface\n";
    std::cout << "  ajuda               - Exibe esta mensagem de ajuda\n\n";

    std::cout << "=====================================================\n";
    std::cout << "Pressione qualquer tecla para sair\n";
    std::cout << "> ";

    std::string info = " ";
    std::getline(std::cin, info);

    limparTela();

}

void InterfaceTextual::exibirMensagem(const std::string &mensagem) {
}

void InterfaceTextual::exibirAlerta(std::vector<std::string> &alertas) {
}

void InterfaceTextual::exibirEstado(int ID) {
}