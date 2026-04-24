# Cartões CRC 
 
--- 
 
## Classe: Casa 
 
| Responsabilidades                      | Colaborações | 
|---------------------------------------|-------------| 
| Armazenar dispositivos                | Dispositivo | 
| Organizar dispositivos por cômodo     | Sistema     | 
| Executar macros globais               |             | 
| Salvar estado atual                   |             | 
| Gerenciar funcionamento geral         |             | 
 
--- 
 
## Classe: Sistema 
 
| Responsabilidades                              | Colaborações | 
|-----------------------------------------------|-------------| 
| Controlar execução do sistema                 | Casa        | 
| Identificar comandos                          | Dispositivo | 
| Enviar comandos para dispositivos             | Macro       | 
| Monitorar estado geral                        |             | 
| Gerenciar automações                          |             | 
| Informar estado                               |             | 
| Registrar alertas e falhas                    |             | 
 
--- 
 
## Classe: Dispositivo 
 
| Responsabilidades                              | Colaborações | 
|-----------------------------------------------|-------------| 
| Armazenar ID e nome                           | Casa        | 
| Definir tipo (luz, som, etc.)                 | Sistema     | 
| Atualizar estado                              | Macro       | 
| Receber comandos do sistema                   |             | 
| Detectar falhas                               |             | 
 
Subclasses: Luz, Ar condicionado, Portão, Som   
 
--- 
 
## Classe: Luz 
 
| Responsabilidades              | Colaborações | 
|------------------------------|-------------| 
| Ligar luz                    | Dispositivo | 
| Desligar luz                 | Macro       | 
| Ajustar intensidade          | Sistema     | 
| Atualizar estado             |             | 
| Responder a comandos         |             | 
| Integrar com macros          |             | 
 
---