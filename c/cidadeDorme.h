#ifndef _cidadeDorme_h
#define _cidadeDorme_h

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Clause SETS */
typedef enum
{
    cidadeDorme__p1,
    cidadeDorme__p2,
    cidadeDorme__p3,
    cidadeDorme__p4,
    cidadeDorme__p5,
    cidadeDorme__p6,
    cidadeDorme__p7,
    cidadeDorme__p8,
    cidadeDorme__p9,
    cidadeDorme__p10
    
} cidadeDorme__Participantes;
#define cidadeDorme__Participantes__max 10
typedef enum
{
    cidadeDorme__fora,
    cidadeDorme__vivo,
    cidadeDorme__morto,
    cidadeDorme__atacado
    
} cidadeDorme__Status_participante;
#define cidadeDorme__Status_participante__max 4
typedef enum
{
    cidadeDorme__aguardando,
    cidadeDorme__cadastro,
    cidadeDorme__distribuicao_papeis,
    cidadeDorme__ataque,
    cidadeDorme__cura,
    cidadeDorme__relatorio_noite,
    cidadeDorme__investigacao,
    cidadeDorme__votacao,
    cidadeDorme__apuracao_votos,
    cidadeDorme__reinicio
    
} cidadeDorme__Status_jogo;
#define cidadeDorme__Status_jogo__max 10
typedef enum
{
    cidadeDorme__lobisomem,
    cidadeDorme__detetive,
    cidadeDorme__curandeiro,
    cidadeDorme__comum,
    cidadeDorme__nenhum
    
} cidadeDorme__Papeis;
#define cidadeDorme__Papeis__max 5
typedef enum
{
    cidadeDorme__sim,
    cidadeDorme__nao
    
} cidadeDorme__Relatorio;
#define cidadeDorme__Relatorio__max 2
typedef enum
{
    cidadeDorme__morreu_lobisomem,
    cidadeDorme__morreu_nao_lobisomem,
    cidadeDorme__ninguem_morreu,
    cidadeDorme__lobisomem_venceu
    
} cidadeDorme__Relatorio_votacao;
#define cidadeDorme__Relatorio_votacao__max 4

/* Clause CONCRETE_VARIABLES */


/* Clause CONCRETE_CONSTANTS */
/* Basic constants */
/* Array and record constants */
extern void cidadeDorme__INITIALISATION(void);

/* Clause OPERATIONS */

extern void cidadeDorme__cadastrar(cidadeDorme__Participantes nn);
extern void cidadeDorme__terminar_cadastro(void);
extern void cidadeDorme__distribuir_papeis(void);
extern void cidadeDorme__atacar(cidadeDorme__Participantes pp, cidadeDorme__Status_participante *ss);
extern void cidadeDorme__curar(cidadeDorme__Participantes pp);
extern void cidadeDorme__relatar_noite(cidadeDorme__Relatorio *resp, cidadeDorme__Participantes *mm);
extern void cidadeDorme__investigar(cidadeDorme__Participantes pp, cidadeDorme__Relatorio *resp);
extern void cidadeDorme__votar_nulo(cidadeDorme__Participantes pp);
extern void cidadeDorme__votar(cidadeDorme__Participantes pp, cidadeDorme__Participantes qq);
extern void cidadeDorme__apurar_votos(cidadeDorme__Relatorio_votacao *resp);
extern void cidadeDorme__reiniciar(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _cidadeDorme_h */
