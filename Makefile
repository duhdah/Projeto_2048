# Comandos disponíveis no Makefile:
# make: compila o código em C em uma biblioteca compartilhada
# make run: compila (se necessário) e executa a interface gráfica
# make clean: remove a biblioteca compilada (.so ou .dll)
# make install-deps: instala a biblioteca Tkinter

CC=gcc
CFLAGS=-fPIC -shared -O2
TARGET=libjogo.so
PYTHON=python3
PIP=pip3
SRCS=jogo.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: all
	$(PYTHON) interface.py

install-deps:
	$(PIP) sudo apt-get install python3-tk

clean:
	rm -f $(TARGET)

.PHONY: all run clean install-deps