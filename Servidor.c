#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Player.h"
//#include "ServerRule.h"
#include "server.h"
#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CLIENTS 3
//Ainda falta criar a matriz e as bibliotecas Info_player e Info_Inimigo Info_payer
//Ainda falta a parte da diagonal 
//e parimoraar o jogo caso vcs queiram 
// e mais algumas coisas
char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
Info_player jogadores[3];
char nicknames[3][LOGIN_MAX_SIZE];
char skins[3];
char estadodoserver = "Esperando";
char qtd_players=0;
while(estadodoserver!="perdeu"){
  while(estadodoserver=="Esperando"){
    int Identificador= acceptConnection();
    if(Identificador==NO_CONNECTION) puts("Erro");
    else{
      //start
      if(qtd_players+1<MAX_CLIENTS){
        recvMsgFromClient(nicknames[id],id,WAIT_FOR_IT);
        recvMsgFromClient(&skins[id],id,WAIT_FOR_IT);
        jogadores[Identificador].Estado="Nenhum";
        jogadores[Identificador].ID=Identificador; 
        jogadores[Identificador].HP=100;
        jogadores[Identificador].estamina=100;
        jogadores[Identificador].posicaox=;
        jogadores[Identificador].posicaoy=;
        int i;
        for(i=0;i<3;i++) jogadores[Identificador].item[i]=empty;
        sendMsgToClient((Info_player *)&jogadores[Identificador],sizeof(Info_player),Identificador);
      }
      struct msg_ret_t MensagemRecebida = recvMsg(aux_buffer);
      if(qtd_players==3){
        for(i=0;i<3;i++){
          adversarios.posicaoy=jogadores[i].posicaoy;
          adversarios.posicaox=jogadores[i].posicaox;
          adversarios.skins=skins[i];
          adversarios.HP=jogadores[i].HP;
          strcpy(adversario.nome,nicknames[i]);
          sendMsgToClient((Info_Inimigo*)&adversario,sizeof(Info_Inimigo),i);
        }
        estadodoserver="Rodando";
        broadcast((char*)&Jogo_Começou,1);
      }
    }
    char Mudanca;
    puts("Rodando");
    while(estadodoserver=="Rodando"){
      struct msg_ret_t recebido=recvMsg(&Mudanca);
      if(recebido.status==MESSAGE_OK){
        matriz[jogadores[0].posicaox][jogadores[0].posicaoy]=0;
        matriz[jogadores[1].posicaox][jogadores[1].posicaoy]=0;
        matriz[jogadores[2].posicaox][jogadores[2].posicaoy]=0;
      }
      if(Mudanca=='w'){
        jogadores[recebido.client_id].Estado=POSICAO;
        //mostra qual imagem sera mostrada do personagem
        jogadores[recebido.client_id].face=cima;
        //condicional para ver se haverá conflito com blocos no pulo pra cima
        /*if(Matriz[jogadores[recebido.client_id].posicaoy-1!=1){
          jogadores[recebido.client_id].posicaoy--;
        if(Matriz[jogadores[recebido.client_id].posicaoy-1!=1;
          jogadores[recebido.client_id].posicaoy--;      
        }*/
        //validação de POSICAO
        if(matriz[jogadores[recebido.client_id].posicaoy++][jogadores[recebido.client_id].posicaox]!=1){
          if(matriz[jogadores[recebido.client_id].posicaoy+2][jogadores[recebido.client_id].posicaox]){
            jogadores[recebido.client_id].posicaoy--;
          }
        }
        //gravidade
        while(Matriz[jogadores[recebido.client_id].posicaoy+1][jogadores[recebido.client_id].posicaox]!=1){
          jogadores[recebido.client_id].posicaoy++;
        }
        //atualiza a tela
        broadcast((Info_player *)&jogadores[recebido.client_id],sizeof(Info_player));
      }
      else if(Mudanca =='s'){
        jogadores[recebido.client_id].Estado=POSICAO;
        jogadores[recebido.client_id].face=baixo;
        while(Matriz[jogadores[recebido.client_id].posicaoy+1][jogadores[recebido.client_id].posicaox]!=1){
          jogadores[recebido.client_id].posicaoy++;
        }
        broadcast((Info_player *)&jogadores[recebido.client_id],sizeof(Info_player));
      }
      else if(Mudanca == 'd'){
        jogadores[recebido.client_id].Estado=POSICAO;
        jogadores[recebido.client_id].face=direita;
        if(matriz[jogadores[recebido.client_id].posicaoy+1][jogadores[recebido.client_id].posicaox+1]==1){
          if(matriz[jogadores[recebido.client_id].posicaoy][jogadores[recebido.client_id].posicaox+1]==Item1){
            //adiciona o item 1 no vetor da estrutura
          }
          else if (matriz[jogadores[recebido.client_id].posicaoy][jogadores[recebido.client_id].posicaox+1]==Item2){
            //adciona o item 2 no vetor da estrutura
          }
          else if (matriz[jogadores[recebido.client_id].posicaoy][jogadores[recebido.client_id].posicaox+1]==Item3){
            //adiciona o item 3 no vetor de estrutura 
          }
          jogadores[recebido.client_id].posicaox++;
        }
        else{
          while(Matriz[jogadores[recebido.client_id].posicaoy+1][jogadores[recebido.client_id].posicaox]!=1){
          jogadores[recebido.client_id].posicaoy++;
        }
        }
        broadcast((Info_player *)&jogadores[recebido.client_id],sizeof(Info_player));
      }
      else if(Mudanca == 'a'){
        jogadores[recebido.client_id].Estado=POSICAO;
        jogadores[recebido.client_id].face=esquerda;
        if(matriz[jogadores[recebido.client_id].posicaoy++][jogadores[recebido.client_id].posicaox--]!=1){
          if(matriz[jogadores[recebido.client_id].posicaoy][jogadores[recebido.client_id].posicaox--]==Item1){              
            //adiciona o item 1 no vetor da estrutura
          }
          else if(matriz[jogadores[recebido.client_id].posicaoy][jogadores[recebido.client_id].posicaox--]==Item2){              
            //adiciona o item 2 no vetor da estrutura
          }
          else if(matriz[jogadores[recebido.client_id].posicaoy][jogadores[recebido.client_id].posicaox--]==Item3){              
            //adiciona o item 3 no vetor da estrutura
          }
        }
        broadcast((Info_player *))&jogadores[recebido.client_id],sizeof(Info_player));
      }
  }
}
}