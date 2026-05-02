# Cartões CRC 
 
--- 
 
## Classe: Casa 
 
| Responsabilidades                     | Colaborações | 
|---------------------------------------|--------------| 
| Armazenar dispositivos                | Dispositivo  | 
| Organizar dispositivos por cômodo     | Sistema      | 
| Executar macros globais               |              | 
| Salvar estado atual                   |              | 
| Adicionar e remover dispositivos      |              | 
| Gerenciar funcionamento geral         |              | 
 
--- 
 
## Classe: Sistema 
 
| Responsabilidades                             | Colaborações | 
|-----------------------------------------------|--------------| 
| Controlar execução do sistema                 | Casa         | 
| Identificar comandos                          | Dispositivo  | 
| Enviar comandos para dispositivos             | Macro        | 
| Monitorar estado geral                        |              | 
| Gerenciar automações                          |              | 
| Informar estado                               |              | 
| Registrar alertas e falhas                    |              | 
 
--- 
 
## Classe: Dispositivo 
 
| Responsabilidades                             | Colaborações | 
|-----------------------------------------------|--------------| 
| Armazenar ID e nome                           | Casa         | 
| Definir tipo (luz, som, etc.)                 | Sistema      | 
| Atualizar estado                              | Macro        | 
| Receber comandos do sistema                   |              | 
| Definir cômodo                                |              | 
| Detectar falhas                               |              | 
 
Subclasses: Luz, Ar condicionado, Portão, Som   
 
--- 
 
## Classe: Luz 
 
| Responsabilidades            | Colaborações | 
|------------------------------|--------------| 
| Ligar luz                    | Dispositivo  | 
| Desligar luz                 | Macro        | 
| Ajustar intensidade          | Sistema      | 
| Atualizar estado             |              | 
| Responder a comandos         |              | 
| Integrar com macros          |              | 
 
---
## Classe: Som

| Responsabilidades                    | Colaborações |
|--------------------------------------|--------------|
| Ligar som                            | Dispositivo  |
| Desligar som                         | Macro        |
| Ajustar volume                       | Sistema      |
| Atualizar estado                     |              |
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
| Atualizar estado                     |              |
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
| Fechar depois de certo tempo     |              |
| Responder a comandos             |              |
| Integrar com macros              |              |

---

## Classe: Macro

| Responsabilidades                   | Colaborações |
|-------------------------------------|--------------|
| Armazenar lista de ações            | Dispositivo  |
| Executar sequência de comandos      | Sistema      |
| Editar lista de ações               |              |
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

| Responsabilidades                   |    Colaborações   |
|-------------------------------------|-------------------|
| Receber comandos do usuário         | Usuário           |
| Interpretar comandos de texto       | Sistema           |
| Encaminhar comandos ao sistema      |                   |
| Exibir respostas ao usuário         |                   |
| Exibir alertas                      |                   |

---

## Classe: Sensor

| Responsabilidades                   |    Colaborações   |
|-------------------------------------|-------------------|
| Monitorar o estado de dispositivos  | Dispositivo       |
| Coletar dados dos dispositivos      | Sistema           |
| Detectar erros                      |                   |
| Gerar alertas                       |                   |
| Notificar o sistema sobre problemas |                   |

