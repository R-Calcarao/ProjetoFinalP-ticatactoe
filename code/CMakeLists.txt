cmake_minimum_required(VERSION 3.21)
project(code C)

set(CMAKE_C_STANDARD 99)


set(Headers jogo.h utils.h matdin.h estruturas.h)

add_executable(TextManipulation ${PROJECT_SOURCE_DIR}/ main.c jogo.c utils.c estruturas.c matdin.c)

add_executable(code main.c jogo.c utils.c matdin.c estruturas.c)
