🛠️ Guia de Execução — VirtOnto Spatial Engine
1. Pré-requisitos Necessários
Garante que tens as seguintes ferramentas instaladas no sistema:

Compilador C++ (C++17): MinGW (GCC/G++) ou MSVC (Visual Studio).

CMake: Versão 3.20 ou superior.

Python: 3.x (utilizado apenas para subir o servidor local HTTP).

Navegador Web: Chrome, Edge ou Firefox.

2. Estrutura de Pastas e Ficheiros de Origem
A pasta raiz do projeto (VirtOnto/) deve conter rigorosamente a seguinte estrutura antes de criar ou gerar a build:

Plaintext
VirtOnto/
├── CMakeLists.txt
├── index.html
├── mock_ontology.json
├── ontology mock test.cpp
└── CPP/
    ├── include/       (ficheiros .hpp)
    └── src/           (ficheiros .cpp do motor)
Aviso Importante: Nada deve ser adicionado na pasta build de forma não automática!
Obs: Se já tens o CMake instalado no sistema, podes avançar para o Passo seguinte.

3. instalação do CMake
Windows (PowerShell) em computadores com restrição de Admin:
Baixe o binario disponivel em https://github.com/Kitware/CMake/releases/download/v4.4.3/cmake-4.4.3-windows-x86_64.zip
Extrai o ficheiro .zip completo para dentro da raiz do projeto (VirtOnto/).

Abre o terminal (PowerShell) na pasta raiz do projeto e adiciona temporariamente a pasta do CMake ao teu ambiente com o seguinte comando:
$env:PATH += ";$PWD\cmake-4.4.3-windows-x86_64\bin"
Valida se a instalação temporária funcionou executando o comando:
cmake --version

Linux / macOS (Terminal):
sudo apt update && sudo apt install -y cmake

4. Cria pasta de construção (na pasta VirtOnto).
mkdir build
cd build

5. Configurar o Projeto com o CMake
Este comando lê o CMakeLists.txt da raiz (..) e copia automaticamente o index.html e o mock_ontology.json para dentro do build/.

PowerShell
# Se usas MinGW:
cmake .. -G "MinGW Makefiles"

# Caso utilizador de Visual Studio/MSVC/Codespace:
# cmake ..

6. Compilar o Motor e o Teste C++
cmake --build .

7. Executar o Processamento Espacial da Ontologia
Este executável lê o mock_ontology.json, aplica o algoritmo espacial e gera o ficheiro de cena renderable.json dentro da pasta build/.
.\ontology_mock_test.exe - Windows
./ontology_mock_test - Linux

8. Iniciar o Servidor Web Local
Garante que ficas posicionado dentro da pasta build ao rodar este comando.
python -m http.server 8000

9. Visualização no Navegador
Abre o navegador em: http://localhost:8000

10. Quando quiser encerrar o grafo, limpar e destruir a pasta de construção direto dela.
cmake --build . --target clean-build
