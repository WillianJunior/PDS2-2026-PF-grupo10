#include "ArCondicionado.hpp"
#include "Comodo.hpp"
#include "Dispositivo.hpp"
#include "InterfaceTextual.hpp"
#include "Luz.hpp"
#include "Portao.hpp"
#include "Sistema.hpp"
#include "Som.hpp"
#include "Usuario.hpp"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <exception>
#include <stdexcept>

InterfaceTextual::InterfaceTextual() : ativa(false), sistema(new Sistema), usuarioAtual(nullptr), menuAtual(""), comodoFocado(""), dispositivoFocadoID(0){
}

void InterfaceTextual::iniciar() {
    limparTela();
    while (true) {
        std::string nome;
        std::string senha;

        std::cout << "===== LOGIN =====" << std::endl;
        std::cout << "Usuario: ";
        std::getline(std::cin, nome);

        std::cout << "Senha: ";
        std::getline(std::cin, senha);

        if (senha.size() < 8) {
            std::cout << "numero insuficiente de caracteres" << std::endl;
            std::cout << "Pressione Enter para tentar novamente...";
            std::cin.get();
            limparTela();
            continue;
        }

        std::string caminho = "data/" + nome + ".txt";
        std::ifstream teste(caminho);
        bool arquivoExiste = teste.is_open();

        if (arquivoExiste) {
            std::string linha;
            std::getline(teste, linha);
            std::getline(teste, linha);
            std::string senhaArmazenada;
            std::getline(teste, senhaArmazenada);
            teste.close();

            if (senhaArmazenada != senha) {
                std::cout << "senha incorreta, tente novamente" << std::endl;
                std::cout << "Pressione Enter para tentar novamente...";
                std::cin.get();
                limparTela();
                continue;
            }
        } else {
            std::ofstream criar(caminho);
            if (!criar.is_open()) {
                std::cout << "Erro: nao foi possivel criar arquivo do usuario.\n";
                return;
            }
            criar.close();
        }

        try {
            usuarioAtual.reset(new Usuario(nome, senha));
            if (arquivoExiste) {
                usuarioAtual->carregarDados(*sistema);
            } else {
                usuarioAtual->salvarDados(*sistema);
            }
        } catch (const std::invalid_argument& erro) {
            std::cout << erro.what() << std::endl;
            std::cout << "Pressione Enter para tentar novamente...";
            std::cin.get();
            limparTela();
            continue;
        }

        std::cout << "\nLogin realizado com sucesso!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();

        limparTela();
        break;
    }



    ativa = true;
    std::string comando;
    while (ativa) {
        if (menuAtual == "COMODO" && !comodoFocado.empty()) {
            exibirMenuComodo(comodoFocado);
        } else if (menuAtual == "DISPOSITIVO" && dispositivoFocadoID > 0) {
            exibirDispositivoFocado(dispositivoFocadoID);
        } else if (menuAtual == "PRINCIPAL" || menuAtual.empty()) {
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
              menuAtual = "COMODO";
              limparTela();
              exibirMenuComodo(nome);
          } else {
              std::cerr << "Comodo '" << nome << "' nao encontrado.\n";
          }
      }



      //inicio da leitura dos comandos

      else if(Fcomando == "ligar som") {
          if(auto som = dynamic_cast<Som*>(dispBase)) {
              som->alterarEstado(true);
              som->printPlaylist();
          }else{
              std::cout << "O dispositivo focado nao eh um aparelho de som ou nao foi encontrado.\n";
          }
          usuarioAtual->salvarDados(*sistema);
      }

      else if (Fcomando == "ajuda" || Fcomando == "help" || Fcomando == "?") {
          exibirAjuda();
      }

      else if(Fcomando == "tocar musica") {
           if(auto som = dynamic_cast<Som*>(dispBase)) {
              som->tocar();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "escolher musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              int indice;
              std::cout << "Digite o indice da musica: ";
              std::cin >> indice;
              som->tocar(indice);
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "alterar volume") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              int volume;
              std::cout << "Digite o novo volume (0 a 100): ";
              std::cin >> volume;
              som->setVolume(volume);
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "pausar som") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              som->togglePause();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "avancar musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              som->proxima();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "voltar musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              som->anterior();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "inserir musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              std::string nomeMusica;
              std::cout << "Digite o nome da musica: ";
              std::getline(std::cin, nomeMusica);
              // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              som->adicionarMusica(nomeMusica);
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "remover musica") {
          if (auto som = dynamic_cast<Som*>(dispBase)) {
              int indice;
              std::cout << "Digite o indice da musica a remover: ";
              std::cin >> indice;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              som->removerMusica(indice);
          }
          usuarioAtual->salvarDados(*sistema);
      }

      //comandos de luz

      else if (Fcomando == "ligar luz") {
          if (auto luz = dynamic_cast<Luz*>(dispBase)) {
              luz->ligar();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "desligar luz") {
          if (auto luz = dynamic_cast<Luz*>(dispBase)) {
              luz->desligar();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "alterar intensidade") {
          if (auto luz = dynamic_cast<Luz*>(dispBase)) {
              int intensidade;
              std::cout << "Digite a intensidade (1 a 5): ";
              std::cin >> intensidade;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              luz->ajustarIntensidade(intensidade);
          }
          usuarioAtual->salvarDados(*sistema);
      }

      // comandos do portao

      else if (Fcomando == "abrir portao") {
          if (auto portao = dynamic_cast<Portao*>(dispBase)) {
              portao->alterarEstado(true);
              portao->fecharAutomaticamente();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "alterar tempo") {
          if (auto portao = dynamic_cast<Portao*>(dispBase)) {
              int segundos;
              std::cout << "Digite o tempo em segundos: ";
              std::cin >> segundos;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              portao->setTemporizador(segundos);
          }
          usuarioAtual->salvarDados(*sistema);
      }

      //comandos do ar condicionado

      else if (Fcomando == "ligar ar condicionado") {
          if (auto ac = dynamic_cast<ArCondicionado*>(dispBase)) {
              ac->ligar();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "desligar ar condicionado") {
          if (auto ac = dynamic_cast<ArCondicionado*>(dispBase)) {
              ac->desligar();
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "alterar temperatura") {
          if (auto ac = dynamic_cast<ArCondicionado*>(dispBase)) {
              int temp;
              std::cout << "Digite a temperatura (15 a 30): ";
              std::cin >> temp;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              ac->ajustarTemperatura(temp);
          }
          usuarioAtual->salvarDados(*sistema);
      }

      // comandos do sistema

    else if (Fcomando == "relatorio") {
          std::string caminho = "src/relatorio.txt";
          
          sistema->gerarRelatorio(caminho);
          this->exibirRelatorio();
          usuarioAtual->salvarDados(*sistema);
    } else if (Fcomando == "adicionar comodo") {
          std::string nomeComodo;
          std::cout << "Nome do comodo: ";
          std::getline(std::cin, nomeComodo);

          std::transform(nomeComodo.begin(), nomeComodo.end(), nomeComodo.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

          if (sistema->getComodo(nomeComodo) != nullptr) {
              std::cout << "Ja existe um comodo com esse nome." << std::endl;
          } else {
              sistema->adicionarComodo(std::unique_ptr<Comodo>(new Comodo(nomeComodo)));
              usuarioAtual->salvarDados(*sistema);
              std::string nomeFormatado = nomeComodo;
              if (nomeFormatado.length() > 10) {
                  nomeFormatado = nomeFormatado.substr(0, 6) + "...";
              } else {
                  nomeFormatado.append(10 - nomeFormatado.length(), ' '); 
              }

              limparTela();
              std::cout << " [ COMODO ADICIONADO COM SUCESSO! ]\n";
              std::cout << R"(
        ____________________
       /                   /|
      /_________________  / |
     |  __               |  |
     | |  | )" << nomeFormatado << R"( |  |
     | |  |              | / 
     | |__|              |/  
     ====================
     
              )" << std::endl;

              std::cout << "Pressione Enter para voltar ao menu...";
              std::string pausa;
              std::getline(std::cin, pausa); 
              limparTela();
          }
          
      }else if (Fcomando == "remover comodo") {
          if (comodoAtual != nullptr) {
              menuAtual = "PRINCIPAL";
              sistema->removerComodo(comodoAtual);
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "comodo") {
          if (comodoAtual != nullptr) {
              exibirMenuComodo(comodoFocado);
          }else{
              std::cout << "Nenhum comodo focado" << std::endl;
          }
      }

    else if (Fcomando.find("focar ") == 0) {
        try{
            int id = std::stoi(Fcomando.substr(6));
            if (comodoAtual && comodoAtual->getDispositivo(id)) {
                dispositivoFocadoID = id;
                menuAtual = "DISPOSITIVO";
                std::cout << "Dispositivo " << id << " focado.\n";
            } else {
                std::cout << "Dispositivo " << id << " nao encontrado.\n";
            }
        }
        catch (...) {
            std::cout << "ID invalido.\n";
        }
    }

    else if (Fcomando == "adicionar dispositivo") {
        try{
            std::cout << (comodoAtual == nullptr) << std::endl;
            if (comodoAtual != nullptr) {
                std::cout << "Tipo (1-Luz, 2-Som, 3-Ar, 4-Portao): \n";
                int tipo;
                if (!(std::cin >> tipo)) {
                    throw std::runtime_error("O tipo deve ser um numero inteiro.");
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::unique_ptr<Dispositivo> novo = nullptr;
                if (tipo == 1)      novo = std::unique_ptr<Dispositivo>(new Luz());
                else if (tipo == 2) novo = std::unique_ptr<Dispositivo>(new Som());
                else if (tipo == 3) novo = std::unique_ptr<Dispositivo>(new ArCondicionado());
                else if (tipo == 4) novo = std::unique_ptr<Dispositivo>(new Portao());
                else {
                    throw std::runtime_error("Tipo de dispositivo invalido.");
                }

                if (novo != nullptr) {
                    int id = novo->getId();
                    comodoAtual->adicionarDispositivo(std::move(novo));
                    std::cout << "Dispositivo adicionado com ID: " << id << std::endl;
                }
                usuarioAtual->salvarDados(*sistema);
            }
        } catch (const std::exception& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erro: " << e.what() << std::endl;
        }

    }else if (Fcomando == "remover dispositivo") {
        if (comodoAtual != nullptr) {
            menuAtual = "COMODO";
            comodoAtual->removerDispositivo(dispositivoFocadoID);
        }
        usuarioAtual->salvarDados(*sistema);
    }else if (Fcomando == "ajuda"){
          exibirAjuda();
    }

      // comandos de usuario

      else if (Fcomando == "renomear") {
          if (usuarioAtual != nullptr) {
              std::string novoNome;
              std::cout << "Novo nome de usuario: ";
              std::cin >> novoNome;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              usuarioAtual->setNome(novoNome);
          }
          usuarioAtual->salvarDados(*sistema);
      }else if (Fcomando == "ver nome") {
          if (usuarioAtual != nullptr) {
              std::cout << "Usuario logado: " << usuarioAtual->getNome() << std::endl;
          }
      }else if (Fcomando == "excluir usuario") {
          std::string caminho = "data/" + usuarioAtual->getNome() + ".txt";
          
          if (std::remove(caminho.c_str()) != 0) {
              std::cout << "Erro: Nao foi possivel excluir o usuario.\n";
          } else {
              std::cout << "Usuario excluido com sucesso!\n";
              std::cout << "Pressione Enter para continuar...";
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              std::cin.get();

            iniciar();
          }
      }else if (Fcomando == "adicionar macro") {
          if (usuarioAtual != nullptr) {
              std::string evento;
              std::cout << "Evento da macro: ";
              std::cin >> evento;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

              
              Macro* macro = usuarioAtual->adicionarMacro(evento, *sistema);
              if(macro == nullptr){
                  return;
              }
              std::cout << "Macro criada com sucesso.\n";

              while(true){
                  std::string entrada;
                  sistema->listarDispositivos();
                  std::cout << "\nDigite o ID do dispositivo (ou 'fim' para terminar): ";
                  std::getline(std::cin, entrada);

                  if (entrada == "fim") {
                      break;
                  }

                  int id;

                  try {
                      id = std::stoi(entrada);
                  } catch (...) {
                      std::cout << "ID invalido.\n";
                      continue;
                  }

                  // Verifica se o dispositivo existe
                  if (sistema->getDispositivo(id) == nullptr) {
                      std::cout << "Dispositivo invalido.\n";
                      continue;
                  }   

                Dispositivo* disp = sistema->getDispositivo(id);

                // Descobre ações válidas
                std::vector<std::string> acoesValidas;

                if (dynamic_cast<Luz*>(disp)) {
                    acoesValidas = {"ligar", "desligar", "ajustar"};
                }
                else if (dynamic_cast<ArCondicionado*>(disp)) {
                    acoesValidas = {"ligar", "desligar", "ajustar"};
                }
                else if (dynamic_cast<Som*>(disp)) {
                    acoesValidas = {"ligar", "desligar", "ajustar"};
                }
                else if (dynamic_cast<Portao*>(disp)) {
                    acoesValidas = {"abrir", "fechar", "ajustar"};
                }
                else {
                    std::cout << "Tipo de dispositivo desconhecido.\n";
                                    continue;
                }

                // Mostra ações possíveis
                std::cout << "Acoes disponiveis:\n";
                for (const auto& a : acoesValidas) {
                    std::cout << " - " << a << "\n";
                }

                // Validação da ação
                std::string acao;

                while (true) {
                    std::cout << "Digite a acao: ";
                    std::getline(std::cin, acao);

                    bool valido = false;
                    for (const auto& a : acoesValidas) {
                        if (acao == a) {
                            valido = true;
                            break;
                        }
                    }

                    if (!valido) {
                        std::cout << "Acao invalida para este dispositivo. Tente novamente:\n";
                        continue;
                    }

                    break;
                }

                // Valor (caso ajuste)
                int valor = 0;

                if (acao == "ajustar") {
                    std::cout << "Digite o valor: ";
                    std::cin >> valor;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                macro->adicionarDispositivo(id, acao, valor);
                std::cout << "Comando adicionado a macro.\n";
              }
              std::cout << "\nMacro criada!\n";
              usuarioAtual->salvarDados(*sistema);
              limparTela();
          }else{
              std::cout << "Nenhum usuario logado. Nao e possivel adicionar macro.\n";
          }
      }else if (Fcomando == "remover macro") {
          if (usuarioAtual != nullptr) {
              std::string evento;
              usuarioAtual->listarMacros();
              std::cout << "Nome do evento da macro a remover: ";
              std::cin >> evento;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              try {
                  usuarioAtual->removerMacro(evento);
                  limparTela();
                  std::cout << "Macro removida com sucesso.\n";
              }
              catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
              }
          }
          usuarioAtual->salvarDados(*sistema);
    }else if (Fcomando == "executar macro") {
        if (usuarioAtual != nullptr) {
            usuarioAtual->listarMacros();

            std::string evento;
            std::cout << "Nome do evento para executar: ";
            std::cin >> evento;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            usuarioAtual->executarMacro(evento, *sistema);
        }
    }
    else if(Fcomando == "salvar"){
          usuarioAtual->salvarDados(*sistema);
    }
    else if(Fcomando == "carregar"){
        usuarioAtual->carregarDados(*sistema);
    }
      else if (Fcomando == "voltar") {
          if(menuAtual == "COMODO"){
              menuAtual = "PRINCIPAL";
              comodoFocado.clear();
              dispositivoFocadoID = -1;
          }else if(menuAtual == "DISPOSITIVO"){
              menuAtual = "COMODO";
              dispositivoFocadoID = -1;
          }
      }

      else {
          std::cout << "Comando invalido ou nao reconhecido.\n";
      } 
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

      std::cout << R"(
      ____  __  __    _    ____ _____   _   _  ___  __  __ _____
     / ___||  \/  |  / \  |  _ \_   _| | | | |/ _ \|  \/  | ____|
     \___ \| |\/| | / _ \ | |_) || |   | |_| | | | | |\/| |  _|
      ___) | |  | |/ ___ \|  _ < | |   | | | | |_| | |  | | |___
     |____/|_|  |_/_/   \_\_| \_\|_|   |_| |_|\___/|_|  |_|_____|

    )" << std::endl;

      std::cout << "Bem-vindo ao Sistema Smart Home (digite 'sair' para encerrar)" << std::endl;
      std::cout << "=== Menu Principal ===" << std::endl;
      exibirComodos();

      std::cout << "\nPara exibir comandos possiveis, execute \"ajuda\" \n";
      std::cout << "\nPara exercutar um comando, digite-o e pressione Enter \n ";
      std::cout << "> ";
      
}

void InterfaceTextual::exibirMenuComodo(const std::string &nomeComodo) {
    limparTela();
    if (sistema == nullptr) {
            std::cout << "Sistema nao inicializado." << std::endl;
            return;
      }

      if (nomeComodo == "") {
          std::cout << "Nenhum comodo focado" << std::endl;
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
            std::cout << "Comodo '" << nomeComodo << "' nao encontrado." << std::endl;
            return;
      }

      menuAtual = "COMODO";
      comodoFocado = nomeComodo;
      dispositivoFocadoID = -1;

      std::cout << "=== Comodo: " << nomeComodo << " ===" << std::endl;
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

      std::cout << "\nComandos disponiveis:" << std::endl;
      std::cout << "  adicionar dispositivo      - adicionar dispositivo" << std::endl;
      std::cout << "  focar <id>                 - foca em um dispositivo para executar comandos sobre ele" << std::endl;
      std::cout << "  remover comodo             - remove este comodo" << std::endl;
      std::cout << "  voltar                     - volta ao menu principal" << std::endl;
      std::cout << std::endl;
      std::cout << "> ";
      //adicionar mais comandos específicos.
}

void InterfaceTextual::exibirDispositivoFocado(int id) {
    limparTela();

    if (sistema == nullptr) {
        std::cout << "Sistema nao inicializado." << std::endl;
        return;
    }

    if (comodoFocado.empty()) {
        std::cout << "Nenhum comodo focado." << std::endl;
        return;
    }

    // Procura o cômodo atual
    Comodo* alvo = sistema->getComodo(comodoFocado);

    if (alvo == nullptr) {
        std::cout << "Comodo nao encontrado." << std::endl;
        return;
    }

    Dispositivo* disp = alvo->getDispositivo(id);

    if (disp == nullptr) {
        std::cout << "Dispositivo nao encontrado." << std::endl;
        return;
    }

    dispositivoFocadoID = id;
    menuAtual = "DISPOSITIVO";

    std::cout << "=== Dispositivo Focado ===" << std::endl;
    std::cout << disp->getEstadoFormatado() << std::endl;

    std::cout << "\nComandos disponiveis:\n";

    if (dynamic_cast<Luz*>(disp)) {
        std::cout << "  ligar luz\n";
        std::cout << "  desligar luz\n";
        std::cout << "  alterar intensidade\n";
    }
    else if (dynamic_cast<Som*>(disp)) {
        std::cout << "  ligar som\n";
        std::cout << "  desligar som\n";
        std::cout << "  tocar musica\n";
        std::cout << "  escolher musica\n";
        std::cout << "  alterar volume\n";
        std::cout << "  pausar som\n";
        std::cout << "  avancar musica\n";
        std::cout << "  voltar musica\n";
        std::cout << "  inserir musica\n";
        std::cout << "  remover musica\n";
    }
    else if (dynamic_cast<ArCondicionado*>(disp)) {
        std::cout << "  ligar ar condicionado\n";
        std::cout << "  desligar ar condicionado\n";
        std::cout << "  alterar temperatura\n";
    }
    else if (dynamic_cast<Portao*>(disp)) {
        std::cout << "  abrir portao\n";
        std::cout << "  alterar tempo\n";
    }

    std::cout << "\nComandos gerais:\n";
    std::cout << "  voltar                  - volta ao menu comodo\n";
    std::cout << "  remover dispositivo     - remove este dispositivo\n";
    std::cout << "\n> ";
}

void InterfaceTextual::exibirRelatorio() {
      if (sistema == nullptr) {
            std::cerr << "Sistema nao inicializado." << std::endl;
            return;
      }

      const std::string caminho = "src/relatorio.txt";
      sistema->gerarRelatorio(caminho);

      std::ifstream arq(caminho);
      if (!arq.is_open()) {
            std::cerr << "Nao foi possivel abrir o relatorio: " << caminho << std::endl;
            return;
      }
      std::cout << "\n===== RELATORIO DO SISTEMA =====\n";
      std::string linha;
      while (std::getline(arq, linha)) {
            std::cout << linha << std::endl;
      }
      std::cout << "===============================\n";
      std::cout << "\nPressione Enter para voltar ao menu.";
      std::cin.get();

      limparTela();
      arq.close();
}

void InterfaceTextual::exibirComodos() {
      if (sistema == nullptr) {
            std::cerr << "(Sistema nao inicializado)" << std::endl;
            return;
      }

      int qtd = sistema->getQtdComodos();
      std::cout << "Comodos cadastrados: " << qtd << std::endl;
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
    std::cout << "\n========== AJUDA - COMANDOS DISPONIVEIS ==========\n\n";

    std::cout << "  **COMANDOS DO SOM** (necessario ter um dispositivo Som focado):\n";
    std::cout << "  ligar som           - Liga o aparelho de som\n";
    std::cout << "  desligar som        - Desliga o aparelho de som\n";
    std::cout << "  tocar musica        - Toca a musica atual\n";
    std::cout << "  escolher musica     - Escolhe uma musica pelo indice\n";
    std::cout << "  alterar volume      - Altera o volume (0 a 100)\n";
    std::cout << "  pausar som          - Pausa/retoma a reproducao\n";
    std::cout << "  avancar musica      - Avanca para a proxima musica\n";
    std::cout << "  voltar musica       - Volta para a musica anterior\n";
    std::cout << "  inserir musica      - Adiciona uma musica a playlist\n";
    std::cout << "  remover musica      - Remove uma musica da playlist\n\n";

    std::cout << "  **COMANDOS DA ILUMINACAO** (necessario ter uma Luz focada):\n";
    std::cout << "  ligar luz          - Liga a luz\n";
    std::cout << "  desligar luz        - Desliga a luz\n";
    std::cout << "  alterar intensidade - Altera a intensidade (1 a 5)\n\n";

    std::cout << "  **COMANDOS DO PORTAO** (necessario ter um Portao focado):\n";
    std::cout << "  abrir portao         - Abre o portao\n";
    std::cout << "  alterar tempo        - Altera o tempo de fechamento automatico (segundos)\n\n";

    std::cout << "  **COMANDOS DO AR CONDICIONADO** (necessario ter um Ar focado):\n";
    std::cout << "  ligar ar condicionado    - Liga o ar-condicionado\n";
    std::cout << "  desligar ar condicionado - Desliga o ar-condicionado\n";
    std::cout << "  alterar temperatura      - Ajusta a temperatura (15 a 30)\n\n";

    std::cout << "  **COMANDOS DO SISTEMA** (gerais):\n";
    std::cout << "  relatorio             - Gera um relatorio do sistema\n";
    std::cout << "  adicionar comodo      - Adiciona um novo comodo\n";
    std::cout << "  focar <id>            - foca um dispositivo para comandos\n";
    std::cout << "  remover comodo        - Remove o comodo atual\n";
    std::cout << "  adicionar dispositivo - Adiciona um dispositivo ao comodo atual\n";
    std::cout << "  remover dispositivo   - Remove um dispositivo do comodo atual\n\n";

    std::cout << "  **COMANDOS DO USUARIO** (requer usuario logado):\n";
    std::cout << "  renomear            - Altera o nome do usuario\n";
    std::cout << "  ver nome            - Mostra o nome do usuario logado\n";
    std::cout << "  adicionar macro     - Cria uma nova macro\n";
    std::cout << "  remover macro       - Remove uma macro\n";
    std::cout << "  executar macro      - Executa uma macro\n\n";

    std::cout << "  **COMANDOS DE NAVEGACAO** (sempre disponiveis):\n";
    std::cout << "  entrar <nome>       - Entra em um comodo\n";
    std::cout << "  sair                - Encerra a interface\n";
    std::cout << "  excluir usuario     - remove o usuario logado e todos os dados relacionados a ele\n";
    std::cout << "  ajuda               - Exibe esta mensagem de ajuda\n\n";

    std::cout << "=====================================================\n";
    std::cout << "Pressione qualquer tecla para sair\n";
    std::cout << "> ";

    std::string info = " ";
    std::getline(std::cin, info);

    limparTela();
    exibirMenuPrincipal();

}
