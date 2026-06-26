#include "doctest.h"
#include "Som.hpp"
#include <string>
#include <vector>
#include <fstream>

TEST_CASE("Som - alterar volume para valor valido") {
    Som som;

    som.setVolume(80);

    CHECK(som.getVolume() == 80);
}

TEST_CASE("Som - alterar volume invalido mantem valor anterior") {
    Som som;

    int volumeOriginal = som.getVolume();

    som.setVolume(-10);

    CHECK(som.getVolume() == volumeOriginal);

    som.setVolume(500);

    CHECK(som.getVolume() == volumeOriginal);
}

TEST_CASE("Som - tocar playlist vazia nao altera pausa") {
    Som som;

    CHECK_NOTHROW(som.carregarMusicas("arquivo_inexistente.txt"));

    CHECK_NOTHROW(som.tocar());
}

TEST_CASE("Som - remover musica por indice invalido") {
    Som som;

    som.adicionarMusica("Rock");

    CHECK_NOTHROW(som.removerMusica(-1));
    CHECK_NOTHROW(som.removerMusica(500));
}

TEST_CASE("Som - remover musica por indice deixa playlist vazia") {
    Som som;

    som.adicionarMusica("Unica");

    CHECK_NOTHROW(som.removerMusica(0));
}

TEST_CASE("Som - estado formatado ligado") {
    Som som;

    som.alterarEstado(true);

    std::string texto =
        som.getEstadoFormatado();

    CHECK(texto.find("Ligado") != std::string::npos);
}

TEST_CASE("Som - estado formatado desligado") {
    Som som;

    std::string texto = som.getEstadoFormatado();

    CHECK(texto.find("Som") != std::string::npos);

    CHECK(texto.find("Desligado") != std::string::npos);
}

TEST_CASE("Testes de Unidade - Classe Som") {
    // Cenário inicial: Um dispositivo de som instalado na sala
    Som aparelhoSom;

    SUBCASE("Inicialização Padrão e Herança de Dispositivo") {
        CHECK(aparelhoSom.getId() > 0);
        CHECK(aparelhoSom.getEstado() == false); // Deve iniciar desligado

        // Testando estado inicial dos atributos específicos da classe Som
        CHECK(aparelhoSom.getVolume() >= 0);     // Volume não pode ser lixo de memória
        CHECK(aparelhoSom.getVolume() <= 100);   // Volume deve respeitar o limite (0 a 100)
    }

    SUBCASE("Controle de Reprodução e Toggle Pause") {
        CHECK(aparelhoSom.getPause() == true);
        aparelhoSom.togglePause();
        CHECK(aparelhoSom.getPause() == false);

    }

    SUBCASE("Gerenciamento de Playlist (Overloads de Adição e Remoção)") {
        CHECK_NOTHROW(aparelhoSom.adicionarMusica("Musica Alfa"));
        CHECK_NOTHROW(aparelhoSom.adicionarMusica("Musica Beta"));

        CHECK_NOTHROW(aparelhoSom.adicionarMusica("Musica Meio", 1));
        CHECK_NOTHROW(aparelhoSom.removerMusica("Musica Alfa"));

        CHECK_NOTHROW(aparelhoSom.removerMusica("Musica Inexistente Qualquer"));

        CHECK(aparelhoSom.getVolume() == 50);
    }

    SUBCASE("Navegação de Faixas (Próxima e Anterior) e Limites Críticos") {
        
        aparelhoSom.adicionarMusica("Track 1");
        aparelhoSom.adicionarMusica("Track 2");
        aparelhoSom.adicionarMusica("Track 3");

        CHECK_NOTHROW(aparelhoSom.anterior());

        CHECK_NOTHROW(aparelhoSom.proxima());
        CHECK_NOTHROW(aparelhoSom.proxima());
        CHECK_NOTHROW(aparelhoSom.proxima());

        CHECK(aparelhoSom.getPause() == true);
    }

    SUBCASE("Overloads do Método Tocar") {
        aparelhoSom.adicionarMusica("Song A");
        aparelhoSom.adicionarMusica("Song B");

        CHECK_NOTHROW(aparelhoSom.tocar());

        CHECK_NOTHROW(aparelhoSom.tocar(1));
        CHECK_NOTHROW(aparelhoSom.tocar(-5));
        CHECK_NOTHROW(aparelhoSom.tocar(999));

        CHECK(aparelhoSom.getVolume() >= 0);
        CHECK(aparelhoSom.getVolume() <= 100);
    }

    SUBCASE("Manipulação de Arquivos Externos") {
        CHECK_NOTHROW(aparelhoSom.carregarMusicas("playlist_fantasma_que_nao_existe.txt"));

        CHECK(aparelhoSom.getVolume() == 50);
    }
}

