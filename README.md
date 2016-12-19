# trab-ed2
Trabalho de Estrutura de Dados II - Árvore B+

----- ENUNCIADO DO TRABALHO ------

Trabalho Computacional

Manipulação de árvores B+ em memória principal

Seja uma universidade hipotética que tenha num, mesmo curso de graduação,
alunos de 3 currículos diferentes, represente os referidos discentes 
numa árvore B+.

As informações referentes às folhas são as seguintes:

A) Carga horária cursada com sucesso (CHCS);

B) Carga horária total (CHT);

C) Número máximo de períodos do currículo (NTOTPER);

D) Número de períodos desde a entrada na universidade (NPU);

E) CR, matrícula e número de trancamentos; e

F) Tempo nominal do curso (TNC);

Exemplos de currículos:

- Currículo 1:
	2955h (CHT)
	16 (NOTOTPER)
	8 (TNC)

- Currículo 2:
	3524h
	12
	8

- Currículo 3:
	3200h
	12
	8

Implemente as seguintes operações:

1) Manipulação em árvore B+:
- Inicializa;
- Libera;
- Imprime;
- Insere;
- Retira;
- Busca;
- Cria nó de árvore B+;
- Modifica CHCS;
- Altera CR;
- Modifica NPU;
- Altera número de trancamentos.

2) Limpeza da árvore B+: (Uma operação para cada)
- Retirada dos formandos;
- Retirada dos alunos que chegaram ao tnc e não atingiram 50% do CHT;
- Retirada dos alunos que chegaram ao NTOTPER e não atingiram 100% do CHT.

Imprimir na retirada para ver o que está acontecendo.

Grupos de, no mínimo, dois alunos e, no máximo, três discentes.

== DATA DE ENTREGA: 18/12 às 23:59h ==

Apresentação do trabalho:
21/12 - Qua
20/12 - Ter
19/12 - Seg

Arquivo:
MAT CR NTRANCAMENTOS CHCS NPU NCURRICULO(COMO DEFINIDO ANTERIORMENTE) NOME

NOTAS IMPORTANTES PARA RETIRADA:

- C3A:
	* Nós internos: uso a mesma info que vem do nó emprestado
	* Nó interno e folha: uso a info da folha que vem p/ nó destino
- C3B:
	* Nós internos: a info do nó interno se mantém
	* Nó interno e folha: perco a informação do nó interno
  
  ------------- FIM DO ENUNCIADO ----------
Bugs:
- Caso 3B da remoção
