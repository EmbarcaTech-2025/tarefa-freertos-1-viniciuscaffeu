
# Tarefa: Roteiro de FreeRTOS #1 - EmbarcaTech 2025

Autor: **Vinicius de Souza Caffeu**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, junho de 2025

---

## 🚀 Sobre o Projeto

Este projeto consiste no desenvolvimento de um sistema embarcado multitarefa para a placa **BitDogLab** (baseada no Raspberry Pi Pico). Utilizando o sistema operacional de tempo real **FreeRTOS** e a linguagem **C**, o sistema gerencia tarefas concorrentes para controlar periféricos da placa, demonstrando conceitos essenciais de escalonamento, suspensão e retomada de tarefas.

O sistema controla três funcionalidades principais de forma simultânea:
1.  Um **LED RGB** que alterna ciclicamente entre as cores vermelho, verde e azul.
2.  Um **buzzer** que emite bipes sonoros em intervalos periódicos.
3.  Dois **botões** de entrada que permitem ao usuário suspender e retomar as tarefas do LED e do buzzer de forma independente.

---
## 🎯 Objetivos de Aprendizagem


* **Criar e gerenciar múltiplas tarefas** com FreeRTOS.
* Compreender os conceitos de **escalonamento e prioridades** em um RTOS.
* Utilizar as funções essenciais da API do FreeRTOS, como `vTaskCreate()`, `vTaskDelay()`, `vTaskSuspend()` e `vTaskResume()`.
* **Controlar periféricos de hardware** (GPIOs) em um ambiente multitarefa.
* Estruturar e organizar um projeto embarcado no VSCode integrando o **pico-sdk** e o kernel do **FreeRTOS**.

---
## 🛠️ Materiais e Pré-requisitos

### Hardware
* Placa de desenvolvimento **BitDogLab** com Raspberry Pi Pico W ou Pico 2.
* Cabo de dados micro-USB ou USB-C.

### Software
* **Visual Studio Code** com as extensões C/C++ e CMake Tools.
* **ARM GCC Toolchain** (`arm-none-eabi-gcc`).
* **CMake**.
* **Pico SDK** configurado no ambiente.

---
## 📂 Estrutura do Projeto

O projeto está organizado na seguinte estrutura de diretórios para garantir modularidade e clareza:

meu_projeto_freertos/
├── CMakeLists.txt          # Arquivo de configuração principal do CMake
├── pico_sdk_import.cmake   # Script de importação do SDK do Pico
├── FreeRTOS/               # Clone do kernel do FreeRTOS
├── src/
│   └── main.c              # Código-fonte principal com a lógica das tarefas
└── include/
└── FreeRTOSConfig.h    # Arquivo de configuração do FreeRTOS


---
## ⚙️ Como Compilar e Gravar

Siga os passos abaixo para compilar o projeto e gravar o firmware na sua BitDogLab.

1.  **Clone o repositório:**
    ```bash
    git clone [[URL_DO_SEU_REPOSITÓRIO_AQUI](https://github.com/EmbarcaTech-2025/tarefa-freertos-1-viniciuscaffeu)]
    cd meu_projeto_freertos
    ```

2.  **Clone o Kernel do FreeRTOS** (se ainda não estiver presente):
    ```bash
    git clone [https://github.com/FreeRTOS/FreeRTOS-Kernel.git](https://github.com/FreeRTOS/FreeRTOS-Kernel.git) FreeRTOS
    ```

3.  **Crie a pasta de build:**
    ```bash
    mkdir build
    cd build
    ```

4.  **Gere os arquivos de compilação com o CMake:**
    ```bash
    cmake ..
    ```

5.  **Compile o projeto:**
    ```bash
    make -j4
    ```

6.  **Grave na Placa:**
    * Conecte a BitDogLab ao computador mantendo o botão `BOOTSEL` pressionado para entrar no modo de gravação.
    * A placa será montada como um dispositivo de armazenamento USB (`RPI-RP2`).
    * Arraste o arquivo `meu_projeto_freertos.uf2` (ou o nome do seu executável) da pasta `build` para dentro do dispositivo.
    * A placa reiniciará automaticamente com o novo firmware.

---
## 🕹️ Teste e Validação

Após gravar o firmware, o sistema deverá se comportar da seguinte maneira:

* O **LED RGB** alterna entre vermelho, verde e azul, com cada cor permanecendo acesa por 500ms.
* O **Buzzer** emite um "beep" curto a cada 1 segundo.
* Ao pressionar o **Botão A**, a tarefa do LED é suspensa, e o LED para de piscar. Ao pressionar novamente, a tarefa é retomada.
* Ao pressionar o **Botão B**, a tarefa do buzzer é suspensa, e os bipes param. Ao pressionar novamente, a tarefa é retomada.

---

---

## 📜 Licença
GNU GPL-3.0.
