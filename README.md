*Integrantes da Turma:42SIF01N3A

Carlos Victor da Cruz Santos Matrícula: 2250204407
Karolayne Silva Ramos Matrícula: 2250105638
Naralicia Mendes Silva Souza Matrícula: 2250101912

****************************************************

*Trabalho A: Playlist de Músicas-Listas Simples

Playlist de Músicas – NKC PLAYLIST!
Sua música, sua vibe, sua sintonia!

Este programa foi desenvolvido em linguagem C para gerenciar uma playlist de músicas utilizando a estrutura de dados Lista Simples. O sistema permite cadastrar, listar, buscar, editar e excluir músicas, além de salvar e carregar os dados em um arquivo CSV.
A estrutura de dados utilizada consiste em um vetor de estruturas do tipo Música, onde cada posição armazena as informações de uma música. Essa implementação permite realizar operações de inserção, consulta, atualização e remoção de registros.

Instruções para compilar:

Antes de executar o programa, é necessário ter instalado:
•	GCC (MinGW) para compilação em C;
•	Visual Studio Code;
•	Extensão C/C++ da Microsoft para Visual Studio Code.
Abra o terminal do VS Code e execute o comando:
gcc playlist.c -o playlist.exe

Instruções para executar:

Após a compilação, execute o programa utilizando o comando: .\playlist.exe

Observações sobre o Funcionamento:

Ao iniciar, o sistema exibe o menu principal:
--- NKC PLAYLIST 💃🕺 ---
Sua música, sua vibe, sua sintonia!
O que você quer fazer hoje?
1.	Cadastrar Música – Insere um novo registro na playlist.
2.	Listar Músicas – Exibe todos os registros armazenados.
3.	Buscar Música – Localiza uma música pelo ID.
4.	Editar Música – Permite alterar dados de uma música existente.
5.	Excluir Música – Remove um registro pelo ID.
6.	Salvar em CSV – Exporta os dados para playlist.csv.
7.	Carregar CSV – Importa dados previamente salvos.
0.	 Sair – Finaliza o programa exibindo a mensagem: "Encerrando a NKC PLAYLIST."

Armazenamento dos Dados:

Os dados são armazenados no arquivo: playlist.csv
Cada registro contém: ID-Título-Artista-Duração-Gênero.
Exemplo de Uso:
Cadastro de música:
ID: 1
Título: Eterno Aprendiz
Artista: Gonzaguinha
Duração (MM:SS): 05:12
Gênero: MPB
Após selecionar a opção "Salvar em CSV", os dados serão gravados no arquivo playlist.csv.
Para finalizar o programa, selecione:
0 - Sair
O sistema exibirá a mensagem:
Encerrando a NKC PLAYLIST.
A principal dificuldade encontrada durante o desenvolvimento foi a configuração do ambiente de programação no Visual Studio Code, incluindo a instalação do compilador GCC (MinGW), configuração do terminal e execução correta do programa.

*****************************************************

*Trabalho B: Chamadas de Emergência-Pilhas Simples

explicação breve de cada programa: 
Este programa foi desenvolvido em linguagem C com o objetivo de administrar um sistema de chamadas de emergência por meio da estrutura de dados Pilha Sequencial. O programa oferece as funcionalidades de inserir novas ocorrências, realizar o atendimento da chamada mais recente, visualizar o topo e listar os registros ativos, contando ainda com persistência de dados em um arquivo CSV.
A lógica computacional baseia-se em um vetor de estruturas (structs) do tipo chamada, cujo gerenciamento de entrada e saída adota o conceito LIFO (Last In, First Out). Dessa forma, todas as operações de escrita e remoção acontecem obrigatoriamente no topo do vetor, assegurando que o último chamado reportado seja o primeiro a ser processado pela equipe.

instruções para compilar:
Para realizar a compilação será necessário a instalação dos programas abaixo:
- Visual Studio Code.
- GCC (MINGW) para realizar a compilação em C.
- extensão C/C++ dentro do vs conde.

Com esse programas instalados execute o comando no terminal:
gcc sistema.c -o sistema.exe

instruções para executar: 
Cole o comando: .\sistema.exe para executar.

observações sobre o funcionamento:

Ao executar o programa esse será o menu exibido:

 SISTEMA DE CHAMADAS DE EMERGENCIA (PILHA)              
======================================================================
 GUIA RAPIDO DE REFERENCIA DE EMERGENCIAS:
  * POLICIA MILITAR (190): Roubo, perturbacao do sossego, agressao.
  * BOMBEIROS (193): Incendio, vazamento de gas, resgate de animais.
  * SAMU (192): Parada cardiorrespiratoria, atropelamento, acidentes graves.
----------------------------------------------------------------------
1. Registrar Chamada (Empilhar)
2. Atender Chamada (Desempilhar)
3. Consultar Ultima Chamada (Topo)
4. Listar Todas as Chamadas
5. Salvar Dados (CSV)
0. Sair do Programa

Dificuldades:
Tive dificuldades na preparação do ambiente, especialmente na instalação do gcc para poder executar o codigo corretamente.

********************************************************
*Trabalho C: Fila de Impressão-Filas Simples

explicação breve de cada programa:

Esse trabalho é um sistema de fila de impressão feito em C. A ideia é simular uma fila de impressão de verdade, igual tem em laboratório ou escritório. O diferencial é que ele tem duas filas: uma para trabalhos normais (capacidade 100) e uma fila circular para trabalhos prioritários (capacidade 50). A regra é simples: se tiver algo na fila prioritária, processa primeiro. Só vai para a fila normal se a prioritária estiver vazia.

O usuário pode enfileirar trabalhos informando ID, nome do arquivo, páginas e tipo (N ou P). Também dá para listar as filas, buscar por ID, cancelar um trabalho específico e ver relatórios com estatísticas. Tudo salvo em CSV pra não perder os dados quando fechar o programa.

O código foi dividido em módulos separados (.h e .c) para organizar melhor: fila, terminal (cores), persistência (CSV) e estatísticas.

-instruções para compilar:

Abra o terminal na pasta do projeto e execute:

gcc -std=c99 -Wall -pedantic main.c fila.c persistencia.c estatisticas.c terminal.c -o main.exe
Pré-requisito: Ter o GCC (MinGW) instalado no Windows.

Pelo VS Code: Pressione Ctrl+Shift+B — a task de compilação já está configurada no .vscode/tasks.json e compila todos os arquivos automaticamente.

-instruções para executar:

Após compilar, execute no terminal:      

.\main.exe

O programa mostra um menu com as opções:

Opção	Função
1	Enfileirar trabalho
2	Processar próximo
3	Listar filas
4	Buscar trabalho por ID
5	Cancelar trabalho por ID
6	Salvar dados (CSV)
7	Relatórios e Estatísticas
0	Sair
Basta digitar o número e pressionar Enter.

-observações sobre o funcionamento:

Duas filas separadas: O sistema mantém uma fila normal (capacidade: 100) e uma fila circular prioritária (capacidade: 50)
Prioridade: Trabalhos prioritários (tipo P) são sempre processados antes dos normais (tipo N). Só processa um normal se a fila prioritária estiver vazia
ID único: Cada trabalho tem um ID que não pode se repetir. O programa valida na hora de enfileirar
Validações: O programa verifica entradas inválidas (ID repetido, nome vazio, páginas negativas, tipo diferente de N/P)
Persistência: Os dados ficam salvos mesmo depois de fechar o programa. Ao abrir novamente, as filas são restauradas
Cores no terminal: O sistema usa cores para destacar mensagens (verde = sucesso, vermelho = erro, amarelo = aviso)
Relatórios: A opção 7 mostra estatísticas como total de trabalhos, total de páginas, média, maior/menor trabalho, ocupação das filas e distribuição por tipo

-Armazenamento dos Dados

Os dados são salvos no arquivo fila_impressao.csv no formato:

id;arquivo;paginas;tipo
1;relatorio.pdf;10;N
2;contrato.doc;3;P
O separador é ; (ponto e vírgula)
A primeira linha é o cabeçalho com os nomes dos campos
Cada trabalho vira uma linha no arquivo
O CSV pode ser aberto no Excel ou bloco de notas
O programa carrega automaticamente ao iniciar e salva automaticamente ao sair (opção 0)
Também é possível salvar manualmente pela opção 6 do menu

-dificuldades encontradas:

A maior dificuldade foi entender a fila circular com o operador %. No começo parecia confuso porque quando o fim chega na última posição ele volta pro início, e eu não conseguia visualizar isso direito.
E com o CSV, a primeira execução o arquivo não existe e o programa precisa tratar isso sem fechar com erro. E se alguém editar o CSV manualmente e colocar dados errados, o programa precisa pular a linha inválida e continuar com as próximas.

