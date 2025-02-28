# TSP
TSP - Análise de Desempenho do Algoritmo TSP

Desenvolvida durante o Curso de Pós-Doutoramento em Engenharia Elétrica com Ênfase em Engenharia de Sistemas e Computação (COPPE/UFRJ entre 2020-2022).

Disciplina: Arquiteturas Avançadas 

Professores:

Claudio Luis Amorim (https://www.cos.ufrj.br/index.php/pt-BR/pessoas/details/18/1007-amorim)

Diego Leonel Cadette Dutra (https://www.cos.ufrj.br/index.php/pt-BR/telefones-do-pesc/details/3/2784)

Autor(100%): Luiz Marcio Faria de Aquino Viana, Pós-D.Sc. Prazo de dezenvolvimento da Biblioteca: 1 dia (= 1 sabado!)

Trabalho individual, que analisou o desempenho dos algoritmos paralelos de solução do Problema Simétrico do Caixeiro Viajante (TSP) usando as bibliotecas OpenMP e OpenMPI em ambientes multiprocessados.

O Problema Simétrico do Caxeiro Viajante (TSP) ocorre com frequência no nosso cotidiano, e possui diversos algorítimos determinísticas conhecidos. 

Estes algoritmos avaliam todas as permutações dos N nós do grafo, isto é, avaliam o custo dos N! diferentes caminhos possíveis de visita aos nós.

Este problema possui complexidade O(N 2 x Log 2 N), e existem algoritmos determinísticos que resolvem este problema com complexidade O(N 3 ).

Nesta pesquisa, analisamos este problema usando um algorítimo de Força Bruta (FB) de complexidade O(N 3 ) que avalia o custo de todos os caminhos possíveis e seleciona o de menor custo.

Em seguida, implementamos um algoritmo que utiliza uma Heurística Míope de complexidade O(N 2 ), e comparamos o desempenho deste algoritmo em ambientes multiprocessados.

Referência:

OpenMP - URL: https://www.openmp.org/

OpenMPI - URL: https://www.open-mpi.org/

LNCC - Programa de Verão 2021 - URL: https://www.youtube.com/playlist?list=PL1JkuXNrkXKwSyYollJaUefFqP5AjdZRw

# CONTATO

CONTACT ME, IF YOU NEED HELP OR HAVE ANY QUESTIONS ABOUT THIS ACADEMIC WORK!

Luiz Marcio Faria de Aquino Viana,Pós-D.Sc.
E-mail: luiz.marcio.viana@gmail.com
Phone/WhatsApp: +55-21-99983-7207
