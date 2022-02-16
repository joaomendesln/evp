/* WARNING if type checker is not performed, translation could contain errors ! */

#include "cidadeDorme.h"

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */

/* Array and record constants */
/* Clause CONCRETE_VARIABLES */

static int32_t cidadeDorme__qtd_vivos_i;
static cidadeDorme__Status_jogo cidadeDorme__status_j;
static cidadeDorme__Status_participante cidadeDorme__status_p[10];
static cidadeDorme__Papeis cidadeDorme__papel[10];
static cidadeDorme__Participantes cidadeDorme__lobisomem_p;
static cidadeDorme__Participantes cidadeDorme__detetive_p;
static cidadeDorme__Participantes cidadeDorme__curandeiro_p;
static bool cidadeDorme__ja_votou[10];
static int32_t cidadeDorme__qtd_votos_i;
static int32_t cidadeDorme__votos_recebidos_i[10];
static cidadeDorme__Participantes cidadeDorme__participante_mais_votado;
/* Clause INITIALISATION */
void cidadeDorme__INITIALISATION(void)
{
    
    unsigned int i = 0;
    cidadeDorme__qtd_vivos_i = 0;
    cidadeDorme__status_j = cidadeDorme__aguardando;
    for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        cidadeDorme__status_p[i] = cidadeDorme__fora;
    }
    for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        cidadeDorme__papel[i] = cidadeDorme__nenhum;
    }
    cidadeDorme__lobisomem_p = cidadeDorme__p1;
    cidadeDorme__detetive_p = cidadeDorme__p1;
    cidadeDorme__curandeiro_p = cidadeDorme__p1;
    for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        cidadeDorme__ja_votou[i] = false;
    }
    cidadeDorme__qtd_votos_i = 0;
    for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        cidadeDorme__votos_recebidos_i[i] = 0;
    }
    cidadeDorme__participante_mais_votado = cidadeDorme__p1;
}

/* Clause OPERATIONS */

void cidadeDorme__cadastrar(cidadeDorme__Participantes nn)
{
    cidadeDorme__status_p[nn] = cidadeDorme__vivo;
    if(cidadeDorme__qtd_vivos_i == 0)
    {
        cidadeDorme__papel[nn] = cidadeDorme__lobisomem;
        cidadeDorme__lobisomem_p = nn;
    }
    if(cidadeDorme__qtd_vivos_i == 1)
    {
        cidadeDorme__papel[nn] = cidadeDorme__detetive;
        cidadeDorme__detetive_p = nn;
    }
    if(cidadeDorme__qtd_vivos_i == 2)
    {
        cidadeDorme__papel[nn] = cidadeDorme__curandeiro;
        cidadeDorme__curandeiro_p = nn;
    }
    if((cidadeDorme__qtd_vivos_i) > (2))
    {
        cidadeDorme__papel[nn] = cidadeDorme__comum;
    }
    cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i+1;
    if(cidadeDorme__qtd_vivos_i == 6)
    {
        cidadeDorme__status_j = cidadeDorme__cadastro;
    }
}

void cidadeDorme__terminar_cadastro(void)
{
    cidadeDorme__status_j = cidadeDorme__distribuicao_papeis;
}

void cidadeDorme__distribuir_papeis(void)
{
    cidadeDorme__status_j = cidadeDorme__ataque;
}

void cidadeDorme__atacar(cidadeDorme__Participantes pp, cidadeDorme__Status_participante *ss)
{
    cidadeDorme__status_p[pp] = cidadeDorme__atacado;
    {
        cidadeDorme__Status_participante cc;
        
        cc = cidadeDorme__status_p[cidadeDorme__curandeiro_p];
        if(cc == cidadeDorme__vivo)
        {
            cidadeDorme__status_j = cidadeDorme__cura;
        }
        else
        {
            cidadeDorme__status_j = cidadeDorme__relatorio_noite;
        }
    }
    (*ss) = cidadeDorme__status_p[pp];
}

void cidadeDorme__curar(cidadeDorme__Participantes pp)
{
    {
        cidadeDorme__Status_participante cc;
        
        cc = cidadeDorme__status_p[pp];
        if(cc == cidadeDorme__atacado)
        {
            cidadeDorme__status_p[pp] = cidadeDorme__vivo;
        }
    }
    cidadeDorme__status_j = cidadeDorme__relatorio_noite;
}

void cidadeDorme__relatar_noite(cidadeDorme__Relatorio *resp, cidadeDorme__Participantes *mm)
{
    {
        cidadeDorme__Status_participante cc;
        
        cc = cidadeDorme__status_p[cidadeDorme__p1];
        (*resp) = cidadeDorme__nao;
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p1;
            cidadeDorme__status_p[cidadeDorme__p1] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p2];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p2;
            cidadeDorme__status_p[cidadeDorme__p2] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p3];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p3;
            cidadeDorme__status_p[cidadeDorme__p3] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p4];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p4;
            cidadeDorme__status_p[cidadeDorme__p4] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p5];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p5;
            cidadeDorme__status_p[cidadeDorme__p5] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p6];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p6;
            cidadeDorme__status_p[cidadeDorme__p6] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p7];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p7;
            cidadeDorme__status_p[cidadeDorme__p7] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p8];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p8;
            cidadeDorme__status_p[cidadeDorme__p8] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p9];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p9;
            cidadeDorme__status_p[cidadeDorme__p9] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__p10];
        if(cc == cidadeDorme__atacado)
        {
            (*mm) = cidadeDorme__p10;
            cidadeDorme__status_p[cidadeDorme__p10] = cidadeDorme__morto;
            (*resp) = cidadeDorme__sim;
            cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
        }
        cc = cidadeDorme__status_p[cidadeDorme__detetive_p];
        if(cc == cidadeDorme__vivo)
        {
            cidadeDorme__status_j = cidadeDorme__investigacao;
        }
        else
        {
            cidadeDorme__status_j = cidadeDorme__votacao;
        }
    }
}

void cidadeDorme__investigar(cidadeDorme__Participantes pp, cidadeDorme__Relatorio *resp)
{
    {
        cidadeDorme__Papeis cc;
        
        cc = cidadeDorme__papel[pp];
        if(cc == cidadeDorme__comum)
        {
            (*resp) = cidadeDorme__sim;
        }
        else
        {
            (*resp) = cidadeDorme__nao;
        }
    }
    cidadeDorme__status_j = cidadeDorme__votacao;
}

void cidadeDorme__votar_nulo(cidadeDorme__Participantes pp)
{
    cidadeDorme__ja_votou[pp] = true;
    cidadeDorme__qtd_votos_i = cidadeDorme__qtd_votos_i+1;
    if(cidadeDorme__qtd_votos_i == cidadeDorme__qtd_vivos_i)
    {
        cidadeDorme__status_j = cidadeDorme__apuracao_votos;
    }
}

void cidadeDorme__votar(cidadeDorme__Participantes pp, cidadeDorme__Participantes qq)
{
    cidadeDorme__ja_votou[pp] = true;
    cidadeDorme__votos_recebidos_i[qq] = cidadeDorme__votos_recebidos_i[qq]+1;
    cidadeDorme__qtd_votos_i = cidadeDorme__qtd_votos_i+1;
    if(cidadeDorme__qtd_votos_i == 0)
    {
        cidadeDorme__participante_mais_votado = qq;
    }
    else
    {
        {
            int32_t cc;
            int32_t dd;
            
            cc = cidadeDorme__votos_recebidos_i[qq];
            dd = cidadeDorme__votos_recebidos_i[cidadeDorme__participante_mais_votado];
            if((cc) > (dd))
            {
                cidadeDorme__participante_mais_votado = qq;
            }
        }
    }
    if(cidadeDorme__qtd_votos_i == cidadeDorme__qtd_vivos_i)
    {
        cidadeDorme__status_j = cidadeDorme__apuracao_votos;
    }
}

void cidadeDorme__apurar_votos(cidadeDorme__Relatorio_votacao *resp)
{
    unsigned int i = 0;
    {
        {
            int32_t cc;
            cidadeDorme__Papeis dd;
            int32_t ee;
            
            cc = cidadeDorme__votos_recebidos_i[cidadeDorme__participante_mais_votado];
            dd = cidadeDorme__papel[cidadeDorme__participante_mais_votado];
            ee = (cidadeDorme__qtd_vivos_i / 2)+1;
            if((cc) >= (ee))
            {
                cidadeDorme__qtd_vivos_i = cidadeDorme__qtd_vivos_i-1;
                cidadeDorme__status_p[cidadeDorme__participante_mais_votado] = cidadeDorme__morto;
                if(dd == cidadeDorme__lobisomem)
                {
                    (*resp) = cidadeDorme__morreu_lobisomem;
                    cidadeDorme__status_j = cidadeDorme__reinicio;
                }
                else
                {
                    if((cidadeDorme__qtd_vivos_i) <= (3))
                    {
                        cidadeDorme__status_j = cidadeDorme__reinicio;
                        (*resp) = cidadeDorme__lobisomem_venceu;
                    }
                    else
                    {
                        cidadeDorme__status_j = cidadeDorme__ataque;
                        (*resp) = cidadeDorme__morreu_nao_lobisomem;
                    }
                }
            }
            else
            {
                if((cidadeDorme__qtd_vivos_i) <= (3))
                {
                    cidadeDorme__status_j = cidadeDorme__reinicio;
                    (*resp) = cidadeDorme__lobisomem_venceu;
                }
                else
                {
                    cidadeDorme__status_j = cidadeDorme__ataque;
                    (*resp) = cidadeDorme__ninguem_morreu;
                }
            }
        }
        cidadeDorme__qtd_votos_i = 0;
        for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
        {
            cidadeDorme__ja_votou[i] = false;
        }
        for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
        {
            cidadeDorme__votos_recebidos_i[i] = 0;
        }
    }
}

void cidadeDorme__reiniciar(void)
{
    unsigned int i = 0;
    {
        cidadeDorme__status_j = cidadeDorme__aguardando;
        for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
        {
            cidadeDorme__papel[i] = cidadeDorme__nenhum;
        }
        for(i = 0; i <= cidadeDorme__Participantes__max-1;i++)
        {
            cidadeDorme__status_p[i] = cidadeDorme__fora;
        }
        cidadeDorme__qtd_vivos_i = 0;
    }
}