import tkinter as tk
import ctypes
import os
import platform
from tkinter import messagebox

if platform.system() == "Windows":
    lib = ctypes.CDLL(os.path.abspath("jogo.dll"))
else:
    lib = ctypes.CDLL("./libjogo.so")


lib.Iniciar_Jogo.restype = ctypes.POINTER(ctypes.c_int)
score = ctypes.c_int(0)
lib.Mover.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
lib.Mover.restype = ctypes.c_int
matriz = None

def on_enter(e):
    e.widget["background"] = "#ffa048"
def on_leave(e):
    e.widget["background"] = "#f5f5f5"

def Iniciar():
    global matriz
    for widget in janela.winfo_children():
        widget.destroy()
    global score
    score = ctypes.c_int(0)
    ptr = lib.Iniciar_Jogo()
    ArrayType = ctypes.c_int * 16
    matriz = ctypes.cast(ptr, ctypes.POINTER(ArrayType)).contents
    Desenhar_Tabuleiro()

def Cor_Para_Valor(valor):
    cores = {
        0:     ("white", "white"),       
        2:     ("#eee4da", "black"),
        4:     ("#ede0c8", "black"),
        8:     ("#f2b179", "white"),
        16:    ("#f59563", "white"),
        32:    ("#f67c5f", "white"),
        64:    ("#f65e3b", "white"),
        128:   ("#edcf72", "black"),
        256:   ("#edcc61", "black"),
        512:   ("#edc850", "black"),
        1024:  ("#edc53f", "black"),
        2048:  ("#edc22e", "black"),
    }
    return cores.get(valor, ("#3c3a32", "white"))

def Desenhar_Tabuleiro():
    global matriz

    for widget in janela.winfo_children():
        widget.destroy()

    frame_matriz = tk.Frame(janela, bg="#fff1d2")
    frame_matriz.grid(row=0, column=0, padx=150, pady=20) 
    frame_matriz.grid_propagate(False) 

    TAMANHO_CELULA = 100
    frame_matriz.config(width=TAMANHO_CELULA * 4, height=TAMANHO_CELULA * 4)

    for i in range(4):
        frame_matriz.grid_rowconfigure(i, weight=1, uniform="linha")
        frame_matriz.grid_columnconfigure(i, weight=1, uniform="coluna")
        for j in range(4):
            valor = matriz[i * 4 + j]
            bg_color, fg_color = Cor_Para_Valor(valor)
            texto = "" if valor == 0 else str(valor)
            cell = tk.Label(
                frame_matriz, text=texto, font=("Helvetica", 16),
                bg=bg_color, fg=fg_color, borderwidth=2, relief="groove"
            )
            cell.grid(row=i, column=j, sticky="nsew", padx=1, pady=1) 

    frame_botoes = tk.Frame(janela, bg="#fff1d2")
    frame_botoes.grid(row=1, column=0, pady=10)
    for texto, comando, pos in [("↑", 0, (0, 1)), ("←", 2, (1, 0)), ("↓", 1, (1, 1)), ("→", 3, (1, 2))]:
        btn = tk.Button(frame_botoes, text=texto, width=6, height=3, command=lambda d=comando: Mover(d), relief="ridge")
        btn.grid(row=pos[0], column=pos[1], padx=5, pady=5)
        btn.bind("<Enter>", on_enter)
        btn.bind("<Leave>", on_leave)

    label_score = tk.Label(janela, text=f"Score: {score.value}", font=("Helvetica", 14), bg="#fff1d2")
    label_score.grid(row=2, column=0, pady=20)

def Mover(direcao):
    global matriz, highscore
    resultado = lib.Mover(direcao, matriz, ctypes.byref(score))
    Desenhar_Tabuleiro()
    if resultado == 0:
        messagebox.showinfo("Fim de Jogo", "Não há mais movimentos possíveis.")
        if score.value > highscore:
            highscore = score.value
            messagebox.showinfo("NOVO RECORDE!", f"Novo Highscore: {highscore}")
        Mostrar_Tela_Inicial()

def Mostrar_Tela_Inicial():
    for widget in janela.winfo_children():
        widget.destroy()
    tk.Label(janela, text="2048", font=("Helvetica", 40, "bold"), bg="#fff1d2", fg="#462D1F").pack(pady=20)
    botao_jogar = tk.Button(janela, text="Jogar", font=("Helvetica", 12,) , command=Iniciar, relief="groove", width=20, height=3)
    botao_jogar.pack(pady=10)
    botao_jogar.bind("<Enter>", on_enter)
    botao_jogar.bind("<Leave>", on_leave)

    botao_instrucoes = tk.Button(janela, text="Instruções", font=("Helvetica", 12,) , command=Ler_Instrucoes, relief="groove", width=20, height=3)
    botao_instrucoes.pack(pady=10)
    botao_instrucoes.bind("<Enter>", on_enter)
    botao_instrucoes.bind("<Leave>", on_leave)

    label_highscore = tk.Label(janela, text=f"Highscore: {highscore}", font=("Helvetica", 14), bg="#fff1d2", fg="#6B3719")
    label_highscore.pack(pady=20)

    label_creditos = tk.Label(janela, text=f"Trabalho desenvolvido por Eduarda Pereira Medeiros \npara a disciplina de Conceitos de Linguagem de Programação.", font=("Helvetica", 10), bg="#fff1d2", fg="#000000")
    label_creditos.pack(pady=20)

def Ler_Instrucoes():
    for widget in janela.winfo_children():
        widget.destroy()

    def Titulo(texto):
        return tk.Label(
            janela,
            text=texto,
            font=("Helvetica", 16, "bold"),
            fg="#5a3825",  
            bg="#fff1d2",
            justify="left",
            anchor="w"
        )

    def Paragrafo(texto):
        return tk.Label(
            janela,
            text=texto,
            font=("Helvetica", 13),
            bg="#fff1d2",
            justify="left",
            anchor="w",
            wraplength=700
        )

    Titulo("OBJETIVO DO JOGO 2048:").pack(anchor="w", padx=30, pady=(20, 5))
    Paragrafo("Combine blocos com os mesmos números para somá-los e alcançar o número 2048.").pack(anchor="w", padx=40)
    Paragrafo("Todas as peças têm valor múltiplo de 2. Ao chegar em 2048, o jogo continua até \nnão haver mais movimentos possíveis.").pack(anchor="w", padx=40)
    Paragrafo("A quantidade de peças combinadas e o valor delas aumentam a pontuação do jogo. \nTente alcançar o maior score possível!").pack(anchor="w", padx=40)

    Titulo("COMO JOGAR:").pack(anchor="w", padx=30, pady=(25, 5))
    Paragrafo("-> Clique nos botões de direção para mover todos os blocos no sentido escolhido.").pack(anchor="w", padx=40)
    Paragrafo("-> Quando dois blocos com o mesmo número se encostam, eles se combinam.").pack(anchor="w", padx=40)
    Paragrafo("-> O jogo termina quando não houver mais movimentos que modifiquem a matriz.").pack(anchor="w", padx=40)

    Titulo("\nBom jogo! :)").pack(anchor="w", padx=40, pady=(20, 10))

    botao_voltar = tk.Button(janela, text="Voltar", font=("Helvetica", 13), command=Mostrar_Tela_Inicial, relief="groove", width=20, height=2)
    botao_voltar.pack(pady=10)
    botao_voltar.bind("<Enter>", on_enter)
    botao_voltar.bind("<Leave>", on_leave)


global highscore
highscore = 0
janela = tk.Tk()
janela.configure(bg="#fff1d2") 
janela.bind("<Up>", lambda e: Mover(0))
janela.bind("<Down>", lambda e: Mover(1))
janela.bind("<Left>", lambda e: Mover(2))
janela.bind("<Right>", lambda e: Mover(3))
janela.title("Trabalho de CLP - Eduarda Pereira Medeiros")
janela.geometry("700x670")

Mostrar_Tela_Inicial()
janela.mainloop()

