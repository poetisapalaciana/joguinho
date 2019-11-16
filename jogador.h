#include <stdio.h>
#include <stdlib.h>

#define PULAR 'w'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define NOME 13

enum personagem{
    ACRUCHA,
    JONGA,
    MALUZINHA,
    TAIRONE,
    TALES,
    YAS
};

enum mensagem_recebida{
    VACUO,
    POSICAO,
    GANHEI,
    PERDI
};

enum playerFace{
    PULO,
    FRENTE,
    TRAS
};

enum flag{
    SIM,
    NAO
};

enum coracoes{
    SEM_CORACAO,
    INVERNO,
    VERAO,
    OUTONO,
    PRIMAVERA
};

enum itens{
    FOLHA=3,
    FLOR,
    CAFE,
    AGUA
};

//struct do jogador
typedef struct{
    unsigned char ID, vida, estamina, coracao, mortes, flores, folhas, cafe, agua, posX, posY, estado, face;
}Jogador;

