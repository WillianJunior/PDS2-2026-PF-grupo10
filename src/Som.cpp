#include "Som.hpp"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

/*
Assume-se que:
    não há tempo de reprodução das músicas
    imprimir o nome da musica na tela da SmartHome faz com que ela seja tocada no aparelho físico

*/

Som::Som() : Dispositivo(), _volume(50), _indice(0), _pause(true) {
    this->nome = "Som";
    carregarMusicas("src/playlist.txt");
}

Som::~Som() {
    supplArq("src/playlist.txt");
}

void Som::supplArq(const string& nomeArquivo){
    if(playlist.empty()){
        std::cerr << "Nada para salvar" << std::endl;
        return;
    }

    std::cout << "Salvando músicas..." << std::endl;

    std::fstream playArq(nomeArquivo, std::ios::trunc);
    if(!playArq.is_open()){
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return;
    }else{
            for(const auto& a : playlist){
                playArq << a << std::endl;
            }
        }
    playArq.close();
}

int Som::getVolume() const {
    return _volume;
}

void Som::setVolume(int nVol){
    try {
        if (nVol < 0 || nVol > 100) {
            throw std::out_of_range("Volume inválido.");
        }

        _volume = nVol;
    }
    catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

bool Som::getPause() const{
    return _pause;
}

void Som::carregarMusicas(const string& nomeArquivo) {
    std::cout << "Carregando músicas salvas..." << std::endl;
    std::ifstream playArq(nomeArquivo);
    if(!playArq.is_open()){
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        return;
    }

    while(getline(playArq, _musica)){
        if(!_musica.empty()){playlist.push_back(_musica);}
    }
    std::cout << "Músicas carregadas!"<<std::endl;

    playArq.close();
}

void Som::togglePause() {
    /* Pause true:  pausado
     * Pause false: tocando
     * */
    std::cout << (_pause ? "Reprodução pausada" : "Reprodução retomada" ) <<std::endl;
    _pause = !_pause;
}

void Som::tocar() {
    if(playlist.empty()){
        std::cerr << "Nada para tocar" << std::endl;
        return;
    }else{
        std::cout << "Reprodução iniciada" <<std::endl;
        _indice = 0;
        _musica = playlist[0];
    }
}

void Som::tocar(int indice){
    if(playlist.empty()){
        std::cerr << "Nada para tocar" << std::endl;
        return;
    }

    if(indice < 0 || indice >= playlist.size()){
        std::cerr << "Erro: Índice inválido" << std::endl;
        return;
    }else{
        _indice = indice;
        _musica = playlist[indice - 1];
        std::cout << "Tocando música escolhida: "<< _musica << std::endl;
    }
}

void Som::proxima() {
    if(playlist.empty()){
        std::cerr << "Nada para tocar" << std::endl;
        return;
    }
    int prox = (_indice + 1) % playlist.size();
    tocar(prox);
}

void Som::anterior() {
    if(playlist.empty()){
        std::cerr << "Nada para tocar" << std::endl;
        return;
    }

    int ant = _indice - 1;

    if(ant < 0){
        ant = playlist.size() - 1;
    }
    tocar(ant);
}

void Som::printPlaylist() {
    if(playlist.empty()){
        std::cerr << "Nada para tocar" << std::endl;
        return;
    }

    std::cout << "Lista de reprodução atual:" << std::endl << std::endl;
    for(auto a : playlist){
        std::cout << a << std::endl;
    }
}

void Som::adicionarMusica(const string& nome){
        std::cout << "Adicionando " << nome << "no final da lista de reprodução" << std::endl;
        playlist.push_back(nome);
}

void Som::adicionarMusica(const string& nome, int pos) {
    std::cout << "Adicionando " << nome << "na posição " << pos << " da lista de reprodução" << std::endl;

    if(pos < 0) {
        pos = 0;
    }

    if(pos > static_cast<int>(playlist.size())){
        pos = playlist.size();
    }

    auto it = playlist.begin() + pos;
    playlist.insert(it, nome);

    if(pos <= _indice) _indice++;
}

void Som::removerMusica(const string& nome) {
    if(playlist.empty()){
        std::cerr << "Não há nada para remover" << std::endl;
        return;
    }

    auto it = std::find(playlist.begin(), playlist.end(), nome);

    if(it != playlist.end()){
        int pos = std::distance(playlist.begin(), it);
        playlist.erase(it);
        std::cout << "Removendo " << nome << " da lista de reprodução" << std::endl;

        if(playlist.empty()){
            _indice = 0;
            _musica = " ";
        }else if (pos < _indice) {
            _indice--;
        }else if (pos == _indice) {
            if(_indice >= playlist.size()){
                _indice = 0;
            }
            _musica = playlist[_indice];
        }
    }else{
        std::cerr << "Música não encontrada" << std::endl;
    }

}

void Som::removerMusica(int pos) {
    if(playlist.empty()){
        std::cerr << "Não há nada para remover" << std::endl;
    }

    if (pos < 0 || pos >= static_cast<int>(playlist.size())) {
        std::cerr << "Índice inválido!" << std::endl;
        return;
    }

    auto it = playlist.begin() + pos;
    playlist.erase(it);

    std::cout << "Removendo da lista de reprodução a musica na posição "<< pos << std::endl;

    if(playlist.empty()){
        _indice = 0;
        _musica = " ";
    }else if (pos < _indice) {
        _indice--;
    }else if (pos == _indice) {
        if(_indice >= playlist.size()){
            _indice = 0;
        }
        _musica = playlist[_indice];
    }
}

void Som::detectarErro() {
    std::ifstream teste("playlist.txt");
    if(!teste.is_open()) {
        std::cerr << "Arquivo de leitura ausente ou corrompido" << std::endl;
    }
    teste.close();
}

std::string Som::getEstadoFormatado() const {
    std::string estado_str = this->estado ? "Ligado" : "Desligado";
    std::string resposta = std::to_string(this->getId()) + " " + this->nome + " " + estado_str + " Volume: " + std::to_string(this->_volume) + "    Tocando agora: " + this->_musica;
    if (this->erro) {
        resposta += " erro";
    }
    return resposta;
}
