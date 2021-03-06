#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct bot
{
    int chbot,chop,chdec; //checkagem do bot
    int x,y; //x=linha y=coluna / escolha da linha e coluna do bot
    int decisao,w,l;
};

struct tabuleiro
{
    int tab[3][3]; //tabuleiro matriz
    int chtab; //checks do tabuleiro
};

void buildT(struct tabuleiro* t);

int main()
{
    int i,j,l,c; //indices para percorrimento do tabuleiro
    struct tabuleiro t;
    struct bot IA;
    buildT(&t);           //montando tabuleiro
    while(1)
    {
        system("cls");
        printf("\nO tabuleiro e:\n");
        t.chtab=1;                      //ch1 so vai permanecer inalterado quando o tabuleiro nao tiver um 0.
        for(i=0; i<3; i++)
        {
            for(j=0; j<3; j++)
            {
                if(t.tab[i][j]==0)    //se tiver algum 0, o ch1 vai ser alterado.
                    t.chtab=0;
                printf("[%d] ",t.tab[i][j]);
            }
            printf("\n");
        }
        if(t.chtab==1)                  //chtab passa inalterado, fim da partida.
            break;
        t.chtab=1;                      //chtab serve para verificar se esta alterando uma peca ja colocada.
        do
        {
            if(t.chtab==0)
                printf("\nCampo ja preenchido!! Digite novamente!!\n");
            t.chtab=0;
            printf("\nDigite a linha em que quer posicionar sua peca (1): ");
            scanf("%d",&l);
            printf("\nDigite a coluna em que quer posicionar sua peca (c): ");
            scanf("%d",&c);
            if(t.tab[l-1][c-1]==0)     //so vai posicionar sua peca se for em um campo prenchido com 0.
            {
                t.tab[l-1][c-1]=1;
                t.chtab=1;
            }
        }
        while(t.chtab==0);
        //varifica�ao se h� algum vencedor.
        //verificando linhas
        for(i=0; i<3; i++)
        {
            IA.w=1; // w=1, bot vence.
            IA.l=1; // l=1, bot perde, usuario ganha.
            for(j=0; j<3; j++)
            {
                if(t.tab[i][j]!=-1)
                    IA.w=0;
                if(t.tab[i][j]!=1)
                    IA.l=0;
            }
            if(IA.w==1 || IA.l==1) //para sair do la�o.
                break;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
        //verificando colunas
        for(j=0; j<3; j++)
        {
            IA.w=1; // w=1, bot vence.
            IA.l=1; // l=1, bot perde, usuario ganha.
            for(i=0; i<3; i++)
            {
                if(t.tab[i][j]!=-1)
                    IA.w=0;
                if(t.tab[i][j]!=1)
                    IA.l=0;
            }
            if(IA.w==1 || IA.l==1) //para sair do la�o.
                break;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
        //verificando diagonal principal
        IA.w=1; // w=1, bot vence.
        IA.l=1; // l=1, bot perde, usuario ganha.
        for(i=0; i<3; i++)
        {
            if(t.tab[i][i]!=-1)
                IA.w=0;
            if(t.tab[i][i]!=1)
                IA.l=0;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
        //verificando diagonal secundaria
        IA.w=1; // w=1, bot vence.
        IA.l=1; // l=1, bot perde, usuario ganha.
        j=0;
        for(i=2; i>=0; i--)
        {
            if(t.tab[i][j]!=-1)
                IA.w=0;
            if(t.tab[i][j]!=1)
                IA.l=0;
            j++;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
        //---------------CHECK-----------------//
        printf("\nA I.A esta pensando...\n");
        Sleep(2000);
        //-----------------------------------------------------------------------------------------------------------------
        //verificando linhas
        for(i=0; i<3; i++)
        {
            IA.chbot=0; //verificador para marcar a pe�a do bot.
            IA.chop=0; //verificador para impedir que o adversario ganhe.
            for(j=0; j<3; j++)
            {
                if(t.tab[i][j]==-1)
                    IA.chbot++; //contando quantas pecas do bot se encontram na linha inspecionada.
                if(t.tab[i][j]==1)
                    IA.chop++; //contando quantas pecas do adversario se encontram na linha inspecionada.
            }
            IA.decisao=0;
            if(IA.chbot==2)  //caso em que o bot encontrou duas pe�as na linha, portanto colocara a ultima para sua vitoria, se tiver campo vazio.
            {
                for(j=0; j<3; j++)
                {
                    if(t.tab[i][j]==0)
                    {
                        IA.x=i;
                        IA.y=j;
                        IA.decisao=1; //decisao primaria.
                        break;
                    }
                }
            }
            if(IA.decisao==1) //bot ja decidiu, portanto pode parar o check nas linhas.
                break;
            if(IA.chop==2)  //bot procura o local que deve colocar a pe�a na linha para impedir que o adversario ganhe.
            {
                for(j=0; j<3; j++)
                {
                    if(t.tab[i][j]==0)
                    {
                        IA.x=i;
                        IA.y=j;
                        IA.decisao=2; //decisao secundaria.
                        break;
                    }
                }
            }
            if(IA.decisao==2) //bot ja decidiu, portanto pode parar o check nas linhas.
                break;
        }
        if(IA.decisao==1 || IA.decisao==2)
            goto decf; //bot ja decidiu, portanto pode ir colocar sua pe�a.
        //-----------------------------------------------------------------------------------------------------------------
        //verificando colunas
        for(j=0; j<3; j++)
        {
            IA.chbot=0; //verificador para marcar a pe�a do bot.
            IA.chop=0; //verificador para impedir que o adversario ganhe.
            for(i=0; i<3; i++)
            {
                if(t.tab[i][j]==-1)
                    IA.chbot++; //contando quantas pecas do bot se encontram na coluna inspecionada.
                if(t.tab[i][j]==1)
                    IA.chop++; //contando quantas pecas do adversario se encontram na coluna inspecionada.
            }
            IA.decisao=0;
            if(IA.chbot==2)  //caso em que o bot encontrou duas pe�as na linha, portanto colocara a ultima para sua vitoria, se tiver campo vazio.
            {
                for(i=0; i<3; i++)
                {
                    if(t.tab[i][j]==0)
                    {
                        IA.x=i;
                        IA.y=j;
                        IA.decisao=1; //decisao primaria.
                        break;
                    }
                }
            }
            if(IA.decisao==1) //bot ja decidiu, portanto pode parar o check nas colunas.
                break;
            if(IA.chop==2)  //bot procura o local que deve colocar a pe�a na coluna para impedir que o adversario ganhe.
            {
                for(i=0; i<3; i++)
                {
                    if(t.tab[i][j]==0)
                    {
                        IA.x=i;
                        IA.y=j;
                        IA.decisao=2; //decisao secundaria.
                        break;
                    }
                }
            }
            if(IA.decisao==2) //bot ja decidiu, portanto pode parar o check nas colunas.
                break;
        }
        if(IA.decisao==1 || IA.decisao==2)
            goto decf; //bot ja decidiu, portanto pode ir colocar sua pe�a.
        //-----------------------------------------------------------------------------------------------------------------
        //verificando diagonal principal
        IA.chbot=0; //verificador para marcar a pe�a do bot.
        IA.chop=0; //verificador para impedir que o adversario ganhe.
        for(i=0; i<3; i++)
        {
            if(t.tab[i][i]==-1)
                IA.chbot++; //contando quantas pecas do bot se encontram na diagonal principal.
            if(t.tab[i][i]==1)
                IA.chop++; //contando quantas pecas do adversario se encontram na diagoanl principal.
        }
        IA.decisao=0;
        if(IA.chbot==2)  //caso em que o bot encontrou duas pe�as na diagonal principal, portanto colocara a ultima para sua vitoria, se tiver campo vazio.
        {
            for(i=0; i<3; i++)
            {
                if(t.tab[i][i]==0)
                {
                    IA.x=i;
                    IA.y=i;
                    IA.decisao=1; //decisao primaria.
                    break;
                }
            }
        }
        if(IA.chop==2)  //bot procura o local que deve colocar a pe�a na linha para impedir que o adversario ganhe.
        {
            for(i=0; i<3; i++)
            {
                if(t.tab[i][i]==0)
                {
                    IA.x=i;
                    IA.y=i;
                    IA.decisao=2; //decisao secundaria.
                    break;
                }
            }
        }
        if(IA.decisao==1 || IA.decisao==2)
            goto decf; //bot ja decidiu, portanto pode ir colocar sua pe�a.
        //-----------------------------------------------------------------------------------------------------------------
        //verificando diagonal secundaria
        IA.chbot=0; //verificador para marcar a pe�a do bot.
        IA.chop=0; //verificador para impedir que o adversario ganhe.
        j=0;
        for(i=2; i>=0; i--)
        {
            if(t.tab[i][j]==-1)
                IA.chbot++; //contando quantas pecas do bot se encontram na diagonal secundaria.
            if(t.tab[i][j]==1)
                IA.chop++; //contando quantas pecas do adversario se encontram na diagoanal secundaria.
            j++;
        }
        IA.decisao=0;
        if(IA.chbot==2)  //caso em que o bot encontrou duas pe�as na diagonal secundaria, portanto colocara a ultima para sua vitoria, se tiver campo vazio.
        {
            j=0;
            for(i=2; i>=0; i--)
            {
                if(t.tab[i][j]==0)
                {
                    IA.x=i;
                    IA.y=j;
                    IA.decisao=1; //decisao primaria.
                    break;
                }
                j++;
            }
        }
        if(IA.chop==2)  //bot procura o local que deve colocar a pe�a na diagonal secundaria para impedir que o adversario ganhe.
        {
            j=0;
            for(i=2; i>=0; i--)
            {
                if(t.tab[i][j]==0)
                {
                    IA.x=i;
                    IA.y=j;
                    IA.decisao=2; //decisao secundaria.
                    break;
                }
                j++;
            }
        }
        //--------------------------------------------------------------------------------------------------------------------
        //BOT COLOCANDO A PE�A.
decf:
        if(IA.decisao==1)  //decisao primaria: marcar para ganhar.
        {
            t.tab[IA.x][IA.y]=-1;
        }
        else
        {
            if(IA.decisao==2) //decisao secundaria : marcar para nao perder.
            {
                t.tab[IA.x][IA.y]=-1;
            }
            else   //decisao final: marcar no no tabuleiro onde tiver o primeiro 0 achado
            {
                IA.chdec=0; //para dar break nos dois la�os.
                for(i=0; i<3; i++)
                {
                    for(j=0; j<3; j++)
                    {
                        if(t.tab[i][j]==0)
                        {
                            t.tab[i][j]=-1;
                            IA.chdec=1;
                            break;
                        }
                    }
                    if(IA.chdec==1)
                        break;
                }
            }
        }
        //varifica�ao se h� algum vencedor.
        //verificando linhas
        for(i=0; i<3; i++)
        {
            IA.w=1; // w=1, bot vence.
            IA.l=1; // l=1, bot perde, usuario ganha.
            for(j=0; j<3; j++)
            {
                if(t.tab[i][j]!=-1)
                    IA.w=0;
                if(t.tab[i][j]!=1)
                    IA.l=0;
            }
            if(IA.w==1 || IA.l==1) //para sair do la�o.
                break;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
        //verificando colunas
        for(j=0; j<3; j++)
        {
            IA.w=1; // w=1, bot vence.
            IA.l=1; // l=1, bot perde, usuario ganha.
            for(i=0; i<3; i++)
            {
                if(t.tab[i][j]!=-1)
                    IA.w=0;
                if(t.tab[i][j]!=1)
                    IA.l=0;
            }
            if(IA.w==1 || IA.l==1) //para sair do la�o.
                break;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
        //verificando diagonal principal
        IA.w=1; // w=1, bot vence.
        IA.l=1; // l=1, bot perde, usuario ganha.
        for(i=0; i<3; i++)
        {
            if(t.tab[i][i]!=-1)
                IA.w=0;
            if(t.tab[i][i]!=1)
                IA.l=0;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
        //verificando diagonal secundaria
        IA.w=1; // w=1, bot vence.
        IA.l=1; // l=1, bot perde, usuario ganha.
        j=0;
        for(i=2; i>=0; i--)
        {
            if(t.tab[i][j]!=-1)
                IA.w=0;
            if(t.tab[i][j]!=1)
                IA.l=0;
            j++;
        }
        if(IA.w==1 || IA.l==1) //h� um vencedor, fim de jogo.
            break;
    } //fim do escopo do loop infinito
    system("cls");
    printf("\nPartida finalizada, o tabuleiro  final e:\n\n");
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
            printf("[%d] ",t.tab[i][j]);
        printf("\n");
    }
    if(IA.w==1)
        printf("\n\nO bot venceu!!!!\n");
    else
    {
        if(IA.l==1)
            printf("\n\nVoce venceu!!!!\n");
        else
            printf("\n\nDeu velha, jogue novamente!!!!\n");
    }
    system("PAUSE");
    return 0;
}
//falta: corrigir problema da coluna, testar as respostas do bot.

//fun��es

void buildT(struct tabuleiro* t)
{
    int i,j;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
            t->tab[i][j]=0;             //montando tabuleiro
    }
}
