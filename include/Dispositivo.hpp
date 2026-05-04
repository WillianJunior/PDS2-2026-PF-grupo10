#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <string>
using namespace std;

class Dispositivo{
    private:
    int id;
    string comodo;
    bool estado;
    bool erro;

    public:
    static int qtdDispositivos;

    Dispositivo(int id, string comodo); //construtor incrementa 1 em qtdDispositivos
    ~Dispositivo(); //destrutor

    //getters
    int getId();
    string getComodo();
    virtual string getEstado(); //especificar: portao "aberto" para estado true, ar "ligado" para estado true, etc
    bool temErro(); //getErro
    //setters
    void alterarEstado(bool estado); //alterar para o estado pedido caso não estiver nele
    virtual void detectarErro() = 0; //erro = true se for detectado alguma falha

};

#endif