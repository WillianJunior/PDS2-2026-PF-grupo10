#include "doctest.h"
#include "Sistema.hpp"
#include "Comodo.hpp"
#include "Luz.hpp"
#include <fstream>

TEST_CASE("Sistema - quantidade de comodos") {
    Sistema sistema;

    CHECK(sistema.getQtdComodos() == 0);

    sistema.adicionarComodo(
        std::unique_ptr<Comodo>(new Comodo("Sala"))
    );

    CHECK(sistema.getQtdComodos() == 1);

    sistema.adicionarComodo(
        std::unique_ptr<Comodo>(new Comodo("Quarto"))
    );

    CHECK(sistema.getQtdComodos() == 2);
}

TEST_CASE("Sistema - buscar dispositivo inexistente") {
    Sistema sistema;

    CHECK(sistema.getDispositivo(1) == nullptr);

    sistema.adicionarComodo(
        std::unique_ptr<Comodo>(new Comodo("Sala"))
    );

    CHECK(sistema.getDispositivo(9999) == nullptr);
}

TEST_CASE("Sistema - buscar dispositivo existente") {
    Sistema sistema;

    std::unique_ptr<Comodo> comodo(new Comodo("Sala"));

    std::unique_ptr<Luz> luz(new Luz());

    int id = luz->getId();

    comodo->adicionarDispositivo(std::move(luz));

    sistema.adicionarComodo(std::move(comodo));

    CHECK(sistema.getDispositivo(id) != nullptr);
}

TEST_CASE("Sistema - remover comodo inexistente nao altera estado") {
    Sistema sistema;

    sistema.adicionarComodo(
        std::unique_ptr<Comodo>(new Comodo("Sala"))
    );

    Comodo outro("Banheiro");

    sistema.removerComodo(&outro);

    CHECK(sistema.getQtdComodos() == 1);
}

TEST_CASE("Sistema - limpar sistema remove todos os comodos") {
    Sistema sistema;

    sistema.adicionarComodo(
        std::unique_ptr<Comodo>(new Comodo("Sala"))
    );

    sistema.adicionarComodo(
        std::unique_ptr<Comodo>(new Comodo("Quarto"))
    );

    REQUIRE(sistema.getQtdComodos() == 2);

    sistema.limparSistema();

    CHECK(sistema.getQtdComodos() == 0);
    CHECK(sistema.getComodo(0) == nullptr);
}

TEST_CASE("Sistema - gerar relatorio cria arquivo") {
    Sistema sistema;

    sistema.adicionarComodo(
        std::unique_ptr<Comodo>(new Comodo("Sala"))
    );

    CHECK_NOTHROW(
        sistema.gerarRelatorio("teste_relatorio.txt")
    );

    std::ifstream arq("teste_relatorio.txt");

    CHECK(arq.is_open());

    std::string conteudo;
    std::getline(arq, conteudo);

    CHECK(arq.good());

    arq.close();

    std::remove("teste_relatorio.txt");
}

TEST_CASE("Sistema - gerar relatorio com caminho invalido") {
#ifdef _WIN32
    std::string caminho = "?:/arquivo.txt";
#else
    std::string caminho = "/arquivo_sem_permissao.txt";
#endif

    Sistema sistema;

    CHECK_THROWS_AS(
        sistema.gerarRelatorio(caminho),
        std::runtime_error
    );
}


TEST_CASE("Sistema - listar dispositivos nao deve falhar") {
    Sistema sistema;

    CHECK_NOTHROW(
        sistema.listarDispositivos()
    );

    std::unique_ptr<Comodo> c(
        new Comodo("Sala")
    );

    c->adicionarDispositivo(
        std::unique_ptr<Dispositivo>(new Luz())
    );

    sistema.adicionarComodo(std::move(c));

    CHECK_NOTHROW(
        sistema.listarDispositivos()
    );
}

TEST_CASE("Sistema - receber comando nao altera estado") {
    Sistema sistema;

    CHECK_FALSE(sistema.estaAtivo());

    sistema.receberComando("ligar");

    CHECK_FALSE(sistema.estaAtivo());
}

TEST_CASE("Testes de Unidade - Classe Sistema") {

    Sistema sistemaHome;

    SUBCASE("Inicialização Padrão e Ciclo de Vida dos Atributos") {

        CHECK(sistemaHome.estaAtivo() == false);

        CHECK(sistemaHome.getComodo(static_cast<int>(0)) == nullptr);
        CHECK(sistemaHome.getComodo(-1) == nullptr);
        CHECK(sistemaHome.getComodo("") == nullptr);
    }

    SUBCASE("Controle de Ativação e Execução") {

        sistemaHome.executarSistema();

        CHECK(sistemaHome.estaAtivo() == true);
    }

    SUBCASE("Gerenciamento de Cômodos (Adicionar, Consultar e Tratar Limites)") {
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Sala de Estar")));
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Cozinha")));
        
        CHECK(sistemaHome.getComodo(static_cast<int>(0)) != nullptr);
        CHECK(sistemaHome.getComodo(1) != nullptr);
        CHECK(sistemaHome.getComodo("Sala de Estar") != nullptr);

        CHECK(sistemaHome.getComodo(-1) == nullptr);
        CHECK(sistemaHome.getComodo(2) == nullptr);
        CHECK(sistemaHome.getComodo("Banheiro") == nullptr);
    }

    SUBCASE("Remoção de Cômodos e Validação de Ponteiros") {
        sistemaHome.adicionarComodo(std::unique_ptr<Comodo>(new Comodo("Quarto")));

        const Comodo* cAntes = sistemaHome.getComodo(static_cast<int>(0));

        REQUIRE(cAntes != nullptr);

        sistemaHome.removerComodo(cAntes);

        CHECK(sistemaHome.getComodo(static_cast<int>(0)) == nullptr);
    }

    SUBCASE("Processamento e Parser de Comandos Textuais (CLI)") {

        sistemaHome.executarSistema();

        sistemaHome.receberComando("");

        sistemaHome.receberComando(
            "PROXIMA_MUSICA_DO_MUNDO_INTEIRO_SINAL_INVALIDO 12345"
        );

        sistemaHome.receberComando("ligar 101");

        sistemaHome.receberComando("ajustar_temperatura 22");
    }
}