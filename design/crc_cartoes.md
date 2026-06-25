# Cartões CRC 
 
--- 
 
## Classe: Casa 
 
| Responsabilidades                     | Colaborações | 
|---------------------------------------|--------------| 
| Armazenar dispositivos                | Dispositivo  | 
| Organizar dispositivos por cômodo     | Sistema      | 
| Armazenar macros globais              | Sensor       | 
| Salvar estado atual                   |              | 
| Adicionar e remover dispositivos      |              | 
 
--- 
 
## Classe: Sistema 
 
| Responsabilidades                             | Colaborações     | 
|-----------------------------------------------|------------------| 
| Controlar execução do sistema                 | Casa             | 
| Identificar comandos                          | Macro            | 
| Enviar comandos para dispositivos             | Dispositivo      | 
| Monitorar estado geral                        | Sensor           | 
| Gerenciar automações                          | InterfaceTextual | 
| Informar estado                               |                  | 
| Registrar alertas e falhas                    |                  | 
 
--- 
 
## Classe: Dispositivo 
 
| Responsabilidades                             | Colaborações | 
|-----------------------------------------------|--------------| 
| Armazenar ID                                  | Casa         | 
| Definir cômodo                                | Sistema      | 
| Atualizar estado                              | Macro        | 
| Receber comandos do sistema                   | Sensor       | 
| Detectar falhas                               |              | 
 
Subclasses: Luz, Ar condicionado, Portão, Som   
 
--- 
 
## Classe: Luz 
 
| Responsabilidades            | Colaborações | 
|------------------------------|--------------| 
| Ligar luz                    | Dispositivo  | 
| Desligar luz                 | Macro        | 
| Ajustar intensidade          | Sistema      | 
| Atualizar estado             | Sensor       | 
| Responder a comandos         |              | 
| Integrar com macros          |              | 
 
---

## Classe: Som

| Responsabilidades                    | Colaborações |
|--------------------------------------|--------------|
| Ligar som                            | Dispositivo  |
| Desligar som                         | Macro        |
| Ajustar volume                       | Sistema      |
| Atualizar estado                     | Sensor       |
| Responder a comandos                 |              |
| Integrar com macros                  |              |
| Iniciar, pausar e pular música       |              |

---

## Classe: Ar condicionado

| Responsabilidades                    | Colaborações |
|--------------------------------------|--------------|
| Ligar ar condicionado                | Dispositivo  |
| Desligar ar condicionado             | Macro        |
| Ajustar temperatura                  | Sistema      |
| Atualizar estado                     | Sensor       |
| Responder a comandos                 |              |
| Integrar com macros                  |              |
| Alterar modos de operação            |              |

---

## Classe: Portão

| Responsabilidades                | Colaborações |
|----------------------------------|--------------|
| Abrir portão                     | Dispositivo  |
| Fechar portão                    | Macro        |
| Atualizar estado                 | Sistema      |
| Fechar depois de certo tempo     | Sensor       |
| Responder a comandos             |              |
| Integrar com macros              |              |

---

## Classe: Macro

| Responsabilidades                   | Colaborações |
|-------------------------------------|--------------|
| Armazenar lista de ações            | Dispositivo  |
| Executar sequência de comandos      | Sistema      |
| Editar lista de ações               | Sensor       |
| Nomear macro                        |              |
| Associar a eventos                  |              |

---

## Classe: Usuário

| Responsabilidades                   |    Colaborações   |
|-------------------------------------|-------------------|
| Enviar comandos ao sistema          | InterfaceTextual  |
| Receber informações do sistema      |                   |
| Autenticar-se no sistema            |                   |
| Ativar e desativar macros           |                   |
| Cadastrar novos dispositivos        |                   |
| Consultar o estado da casa          |                   |

---

## Classe: InterfaceTextual

| Responsabilidades                   | Colaborações |
|-------------------------------------|--------------|
| Receber comandos do usuário         | Usuário      |
| Interpretar comandos de texto       | Sistema      |
| Encaminhar comandos ao sistema      |              |
| Exibir respostas ao usuário         |              |
| Exibir alertas                      |              |

---