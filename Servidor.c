#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
//#include "ServerRule.h"
#include "server.h"
#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CLIENTS 4
//Ainda falta criar acenario e as bibliotecas Jogador e Info_Inimigo Info_payer
//Ainda falta a parte da diagonal
//e parimoraar o jogo caso vcs queiram
// e mais algumas coisas

enum estado_do_server
{
  ESPERANDO,
  EM_JOGO,
  FIM_DE_JOGO
};

void morri(Jogador jogadores[], struct msg_ret_t recebido)
{
  //jogadores[recebido.client_id].mortes++;
  jogadores[recebido.client_id].posX = 1;
  jogadores[recebido.client_id].posY = 21; //mudar
  jogadores[recebido.client_id].score = 0;
}

void cair(char cenario[][224], Jogador jogadores[], struct msg_ret_t recebido, char *Mudanca)
{ //gravidade que nao sei fazer porem tentei
  while (cenario[jogadores[recebido.client_id].posY + 1][jogadores[recebido.client_id].posX] == 0 && recebido.status == NO_MESSAGE)
  {
    jogadores[recebido.client_id].posY++;
    broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
    recebido = recvMsg(Mudanca);
  }
  //recebido = recvMsg(Mudanca);
  while (cenario[jogadores[recebido.client_id].posY + 1][jogadores[recebido.client_id].posX] == 0 && recebido.status == MESSAGE_OK)
  {
    while ((*Mudanca) == DIREITA && cenario[jogadores[recebido.client_id].posY + 1][jogadores[recebido.client_id].posX + 1] == 0)
    {
      jogadores[recebido.client_id].posY++;
      jogadores[recebido.client_id].posX++;
      broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
      recebido = recvMsg(Mudanca);
    }
    while ((*Mudanca) == ESQUERDA && cenario[jogadores[recebido.client_id].posY + 1][jogadores[recebido.client_id].posX - 1] == 0)
    {
      jogadores[recebido.client_id].posY++;
      jogadores[recebido.client_id].posX--;
      broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
      recebido = recvMsg(Mudanca);
    }
  }
  if (cenario[jogadores[recebido.client_id].posY + 1][jogadores[recebido.client_id].posX] == 2)
  {
    morri(jogadores, recebido);
  }
}

void pular(char cenario[][224], Jogador jogadores[], struct msg_ret_t recebido, char *Mudanca)
{
  char blocos = 2;
  while (blocos--)
  {
    recebido = recvMsg(Mudanca);
    if (cenario[jogadores[recebido.client_id].posY - 1][jogadores[recebido.client_id].posX] == 0 && recebido.status == NO_MESSAGE)
    {
      jogadores[recebido.client_id].posY--;
      broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
    }
    //recebido = recvMsg(Mudanca);
    if (cenario[jogadores[recebido.client_id].posY - 1][jogadores[recebido.client_id].posX] == 0 && recebido.status == MESSAGE_OK)
    {
      if ((*Mudanca) == DIREITA && cenario[jogadores[recebido.client_id].posY - 1][jogadores[recebido.client_id].posX + 1] == 0)
      {
        jogadores[recebido.client_id].posY--;
        jogadores[recebido.client_id].posX++;
        broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
      }
      if ((*Mudanca) == ESQUERDA && cenario[jogadores[recebido.client_id].posY - 1][jogadores[recebido.client_id].posX - 1] == 0)
      {
        jogadores[recebido.client_id].posY--;
        jogadores[recebido.client_id].posX--;
        broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
      }
    }
  }
}

void ganhei_Coracao(Jogador jogadores[], struct msg_ret_t recebido)
{
  jogadores[recebido.client_id].coracao = COM_CORACAO;
  jogadores[recebido.client_id].score += 200;
}

void testandoServidor(Jogador jogadores[], struct msg_ret_t recebido)
{
  printf("\nPosicao = [%d,%d]\nCoracao = %d\n Score = %d\n", jogadores[recebido.client_id].posX, jogadores[recebido.client_id].posY, jogadores[recebido.client_id].coracao, jogadores[recebido.client_id].score);
}

void ligaServidor()
{
  char cenario[][224] = {};
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  Jogador jogadores[4];
  char nicknames[4][LOGIN_MAX_SIZE];
  char skins[4];
  char estadodoserver = ESPERANDO;
  char qtd_players = 0;
  puts("meuuuuuuuu o joguinho nao kitou k k k k\n");
  ////ALLEGRO :
  /*if (!al_init())
    puts("Falha ao iniciar allegro\n");

  timer = al_create_timer(8.0); //bota sempre .0 nos numeros inteiros, pra ele interpretar como double
  if (!timer)
  {
    puts("timer == NULL");
    exit(-1);
  }
  else
    puts("Timer funfou");
  decrementTimer = al_create_timer(1.0);
  if (!decrementTimer)
  {
    puts("decrementTimer == NULL");
    exit(-1);
  }
  else
    puts("decrementTimer funfou");
  eventQueue = al_create_event_queue() while (estadodoserver != FIM_DE_JOGO)
  {*/
  while (estadodoserver == ESPERANDO)
  {
    int id = acceptConnection();
    if (id == NO_CONNECTION)
      puts("Erro");
    else
    {
      //start
      if (qtd_players++ < MAX_CLIENTS)
      {
        recvMsgFromClient(nicknames[id], id, WAIT_FOR_IT);
        recvMsgFromClient(&skins[id], id, WAIT_FOR_IT);
        printf("%s se conectou com id = %d e escolheu o personagem %d \n qtd_players=%d\n", nicknames[id], id, skins[id], qtd_players);
        jogadores[id].estado = VACUO;
        jogadores[id].ID = id;
        jogadores[id].posX = 1; //onde o jogador inicia!!
        jogadores[id].posY = 21;
        jogadores[id].score = 0;
        jogadores[id].coracao = SEM_CORACAO;
        sendMsgToClient((Jogador *)&jogadores[id], sizeof(Jogador), id);
      }
      struct msg_ret_t MensagemRecebida = recvMsg(aux_buffer);
      if (MensagemRecebida.status == DISCONNECT_MSG)
      {
        --qtd_players;
        printf("%s disconnected id: %d is free\n", nicknames[MensagemRecebida.client_id], MensagemRecebida.client_id);
        printf("players_connected: %d\n", qtd_players);
      }
      if (qtd_players == 3)
      {
        estadodoserver = EM_JOGO;
        broadcast(&estadodoserver, 1);
      }
    }
    char Mudanca;
    puts("Rodando");
    struct msg_ret_t recebido;
    while (estadodoserver == EM_JOGO)
    {
      recebido = recvMsg(&Mudanca);
      if (recebido.status == MESSAGE_OK)
      {
        cenario[jogadores[0].posX][jogadores[0].posY] = 0;
        cenario[jogadores[1].posX][jogadores[1].posY] = 0;
        cenario[jogadores[2].posX][jogadores[2].posY] = 0;
        if (Mudanca == PULAR)
        {
          jogadores[recebido.client_id].estado = POSICAO;
          //mostra qual imagem sera mostrada do personagem
          jogadores[recebido.client_id].face = PULO;
          pular(cenario, jogadores, recebido, &Mudanca);
          cair(cenario, jogadores, recebido, &Mudanca);
          broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
        }
        else if (Mudanca == DIREITA)
        {
          jogadores[recebido.client_id].estado = POSICAO;
          jogadores[recebido.client_id].face = FRENTE;
          if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX + 1] == 0)
          {
            if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == FOLHA) //folha vale
            {
              cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
              jogadores[recebido.client_id].score += 50;
              if (jogadores[recebido.client_id].score >= 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
              {
                ganhei_Coracao(jogadores, recebido);
              }
            }
            else if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == FLOR)
            {
              cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
              jogadores[recebido.client_id].score += 50;
              if (jogadores[recebido.client_id].score >= 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
              {
                ganhei_Coracao(jogadores, recebido);
              }
            }
            else if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == CAFE)
            {
              cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
              jogadores[recebido.client_id].score += 50;
              if (jogadores[recebido.client_id].score == 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
              {
                ganhei_Coracao(jogadores, recebido);
              }
            }
            else if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == AGUA)
            {
              cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
              jogadores[recebido.client_id].score += 50;
              if (jogadores[recebido.client_id].score == 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
              {
                ganhei_Coracao(jogadores, recebido);
              }
            }
            jogadores[recebido.client_id].posX++;

            broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
            if (cenario[jogadores[recebido.client_id].posY + 1][jogadores[recebido.client_id].posX] == 0)
              ;
            {
              cair(cenario, jogadores, recebido, &Mudanca);
            }
          }
        }
        else if (Mudanca == ESQUERDA)
        {
          jogadores[recebido.client_id].estado = POSICAO;
          jogadores[recebido.client_id].face = TRAS;
          if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] != 1)
          {
            if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == FOLHA)
            {
              cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
              jogadores[recebido.client_id].score += 50;
              if (jogadores[recebido.client_id].score >= 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
              {
                ganhei_Coracao(jogadores, recebido);
              }
            }
          }
          else if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == FLOR)
          {
            cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
            jogadores[recebido.client_id].score += 50;
            if (jogadores[recebido.client_id].score >= 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
            {
              ganhei_Coracao(jogadores, recebido);
            }
          }
        }
        else if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == CAFE)
        {
          cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
          jogadores[recebido.client_id].score += 50;
          if (jogadores[recebido.client_id].score >= 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
          {
            ganhei_Coracao(jogadores, recebido);
          }
        }
        else if (cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] == AGUA)
        {
          cenario[jogadores[recebido.client_id].posY][jogadores[recebido.client_id].posX - 1] = 0;
          jogadores[recebido.client_id].score += 50;
          if (jogadores[recebido.client_id].score >= 200 && jogadores[recebido.client_id].coracao == SEM_CORACAO)
          {
            ganhei_Coracao(jogadores, recebido);
          }
        }
        jogadores[recebido.client_id].posX--;
        //parte da gravidade
        broadcast((Jogador *)&jogadores[recebido.client_id], sizeof(Jogador));
        if (cenario[jogadores[recebido.client_id].posY + 1][jogadores[recebido.client_id].posX] == 0)
        {
          cair(cenario, jogadores, recebido, &Mudanca);
        }
      }
      testandoServidor(jogadores, recebido);
    }
  }
}

int main()
{
  serverInit(MAX_CLIENTS);
  puts("Servidor ta pegando!!\n");
  //int res = 'y';
  while (1)
  {
    ligaServidor();
  }
  puts("KITEI");

  return EXIT_SUCCESS;
}
/*else if(ret.status==DISCONNECT_MSG){
                --players_connected;
                printf("PLAYER(%d) DESCONECTOU\n",ret.client_id);
                if(players_connected == 0) serverState = ENDGAME;
            }
*/
