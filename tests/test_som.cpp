#include "doctest.h"
#include "Som.hpp"
#include <string>
#include <vector>

TEST_CASE("Testes de Unidade - Classe Som") {
    // Cenário inicial: Um dispositivo de som instalado na sala
    Som aparelhoSom(105, "Sala");

    SUBCASE("Inicialização Padrão e Herança de Dispositivo") {
        // Testando atributos herdados da classe base Dispositivo
        CHECK(aparelhoSom.getId() == 105);
        CHECK(aparelhoSom.getComodo() == "Sala");
        CHECK(aparelhoSom.getEstado() == false); // Deve iniciar desligado

        // Testando estado inicial dos atributos específicos da classe Som
        CHECK(aparelhoSom.getVolume() >= 0);     // Volume não pode ser lixo de memória
        CHECK(aparelhoSom.getVolume() <= 100);   // Volume deve respeitar o limite (0 a 100)
    }

    SUBCASE("Controle de Reprodução e Toggle Pause") {
        // Simulando o estado padrão inicial (por exemplo: pausado/parado)
        // Se _pause inicia como true (pausado), togglePause() deve mudá-lo para false (tocando)
        bool estadoInicialPause = true; 
        
        aparelhoSom.togglePause();
        // O teste assume que o comportamento esperado é a inversão do estado anterior
        // Como não temos um método getPause público, testamos a execução estável do método:
        aparelhoSom.togglePause(); 
    }

    SUBCASE("Gerenciamento de Playlist (Overloads de Adição e Remoção)") {
        // Testando Overload 1: Adicionar ao final da lista
        aparelhoSom.adicionarMusica("Musica Alfa");
        aparelhoSom.adicionarMusica("Musica Beta");

        // Testando Overload 2: Adicionar em uma posição específica (índice)
        // Inserindo na posição 1 (entre Alfa e Beta)
        aparelhoSom.adicionarMusica("Musica Meio", 1);

        // Testando a remoção de uma música existente
        aparelhoSom.removerMusica("Musica Alfa");

        // Testando robustez: tentar remover uma música que não existe na playlist
        // A regra de negócio exige que o sistema ignore ou trate sem crashar o software
        aparelhoSom.removerMusica("Musica Inexistente Qualquer");
    }

    SUBCASE("Navegação de Faixas (Próxima e Anterior) e Limites Críticos") {
        // Populando a playlist para testar os ponteiros de _indice
        aparelhoSom.adicionarMusica("Track 1");
        aparelhoSom.adicionarMusica("Track 2");
        aparelhoSom.adicionarMusica("Track 3");

        // Cenário: Estamos na primeira música (_indice = 0)
        // O que acontece se tentarmos voltar antes da primeira? (Testando limite inferior)
        // Regra de negócio ideal: Ou mantém no índice 0 ou vai para o fim da playlist (circular)
        aparelhoSom.anterior(); 
        
        // Testando avanço normal
        aparelhoSom.proxima(); // Vai para a Track 2
        aparelhoSom.proxima(); // Vai para a Track 3

        // Cenário: Chegamos na última música da playlist
        // Testando limite superior: avançar além do tamanho do vector
        aparelhoSom.proxima(); 
    }

    SUBCASE("Overloads do Método Tocar") {
        aparelhoSom.adicionarMusica("Song A");
        aparelhoSom.adicionarMusica("Song B");

        // Testando Overload 1: Tocar faixa atual/padrão
        aparelhoSom.tocar();

        // Testando Overload 2: Forçar reprodução de um índice específico
        aparelhoSom.tocar(1);

        // Testando robustez do Overload 2: Passar índice inválido/fora do escopo da playlist
        // O TDD força o código a validar se o índice passado está dentro do tamanho do vector
        aparelhoSom.tocar(-5);
        aparelhoSom.tocar(999);
    }

    SUBCASE("Manipulação de Arquivos Externos") {
        // Testa se o método lida com o parser sem quebrar, caso o arquivo não exista
        // (Tratamento de exceções com blocos try/catch ou validação de ifstream)
        aparelhoSom.carregarMusicas("playlist_fantasma_que_nao_existe.txt");
    }
}
