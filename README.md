# Projeto_2048

2048 é um jogo de quebra-cabeça de um jogador onde o desafio é combinar blocos numerados para alcançar a maior pontuação possível.
O jogo acontece em uma grade 4x4 onde peças de valor 2 ou 4 surgem a cada movimento feito. 
Quando duas peças de mesmo valor são combinadas, elas se fundem em uma nova peça com a soma de seus valores.
O objetivo do jogo é criar uma peça de valor 2048, no entanto, o jogo só acaba quando o jogador não consegue fazer mais nenhum movimento válido.

## Como jogar?

Para jogar, você pode usar clicar nos botões da interface com o mouse ou usar as teclas do teclado.
Ao clicar em uma seta, todas as peças deslizam para a direção escolhida e as peças de mesmo valor são combinadas.
Tente combinar as peças para atingir valores cada vez maiores!
Se a grade ficar cheia e não houver mais peças que possam ser combinadas, o jogo termina.
Cada combinação feita acrescenta uma pontuação proporcional ao valor da peça formada ao score total.

## Dependências:
* Python 3: Interpretador utilizado para executar a aplicação.
* PIP: Gerenciador de pacotes de Python utilizado para instalar as bibliotecas necessárias.
* Tkinter: Biblioteca Python utilizada para elaborar a interface gráfica.

Se for necessário instalar o Tkinter separadamente, utilize o seguinte comando:
```bash
make install-deps
```

## Como compilar?
No Linux:
* A compilação do código C em uma biblioteca compartilhada (`.so`) é feita utilizando o `Makefile`. No terminal, basta executar o seguinte comando:
```bash
make
```  

No Windows:
* A compilação deve ser feita manualmente com o comando a seguir para gerar a biblioteca compartilhada:
```PowerShell
gcc -shared -o mandelbrot.dll mandelbrot.c -O2
```  

## Como executar?
No Linux:
```bash
make run
```  

No Windows:
```PowerShell
python interface.py
```

