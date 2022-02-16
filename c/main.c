#include "stdio.h"
#include "cidadeDorme_i.c"

int main(int argc, char** argv){
    const char* participantes[] = {"p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "p10"};
    const char* status_participantes[] = {"fora", "vivo", "morto", "atacado"};
    const char* status_jogo[] = {"aguardando", "cadastro", "distribuicao_papeis", "ataque", "cura", "relatorio_noite", "investigacao", "votacao", "apuracao_votos", "reinicio"};
    const char* papeis[] = {"lobisomem", "detetive", "curandeiro", "comum", "nenhum"};
    const char* relatorio[] = {"sim", "nao"};
    const char* relatorio_votacao[] = {"morreu_lobisomem", "morreu_nao_lobisomem", "ninguem_morreu", "lobisomem_venceu"};

    int ss, resp, mm;

    cidadeDorme__INITIALISATION();

    printf("\nestado do jogo -  %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__cadastrar(cidadeDorme__p1);
    cidadeDorme__cadastrar(cidadeDorme__p4);
    cidadeDorme__cadastrar(cidadeDorme__p5);
    cidadeDorme__cadastrar(cidadeDorme__p6);
    cidadeDorme__cadastrar(cidadeDorme__p7);
    cidadeDorme__cadastrar(cidadeDorme__p8);
    cidadeDorme__cadastrar(cidadeDorme__p9);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__terminar_cadastro();

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__distribuir_papeis();

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__atacar(cidadeDorme__p4, &ss);
    printf("estado de %s - %s\n", participantes[cidadeDorme__p4], status_participantes[cidadeDorme__status_p[cidadeDorme__p4]]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__curar(cidadeDorme__p4);
    printf("estado de %s - %s\n", participantes[cidadeDorme__p4], status_participantes[cidadeDorme__status_p[cidadeDorme__p4]]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__relatar_noite(&resp, &mm);
    printf("morreu alguém? %s; s", relatorio[resp]);
    if (resp == 0) printf("quem? %s", participantes[mm]);
    printf("\n");
    
    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__investigar(cidadeDorme__p7, &resp);
    printf("%s é comum? %s\n", participantes[cidadeDorme__p7], relatorio[resp]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__votar(cidadeDorme__p1, cidadeDorme__p8);
    cidadeDorme__votar(cidadeDorme__p4, cidadeDorme__p1);
    cidadeDorme__votar_nulo(cidadeDorme__p5);
    cidadeDorme__votar_nulo(cidadeDorme__p6);
    cidadeDorme__votar(cidadeDorme__p7, cidadeDorme__p1);
    cidadeDorme__votar(cidadeDorme__p8, cidadeDorme__p1);
    cidadeDorme__votar(cidadeDorme__p9, cidadeDorme__p1);
    for(int i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        if (cidadeDorme__status_p[i] == 1){
            printf("%s recebeu %d votos\n", participantes[i], cidadeDorme__votos_recebidos_i[i]);
        }
    }

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__apurar_votos(&resp);
    printf("resultado da apuração: %s\n", relatorio_votacao[resp]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__reiniciar();

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__cadastrar(cidadeDorme__p2);
    cidadeDorme__cadastrar(cidadeDorme__p3);
    cidadeDorme__cadastrar(cidadeDorme__p4);
    cidadeDorme__cadastrar(cidadeDorme__p6);
    cidadeDorme__cadastrar(cidadeDorme__p7);
    cidadeDorme__cadastrar(cidadeDorme__p8);
    cidadeDorme__cadastrar(cidadeDorme__p9);
    cidadeDorme__cadastrar(cidadeDorme__p10);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__terminar_cadastro();

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__distribuir_papeis();
    
    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__atacar(cidadeDorme__p8, &ss);
    printf("estado de %s - %s\n", participantes[cidadeDorme__p8], status_participantes[cidadeDorme__status_p[cidadeDorme__p8]]);
    
    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__curar(cidadeDorme__p4);
    printf("estado de %s - %s\n", participantes[cidadeDorme__p8], status_participantes[cidadeDorme__status_p[cidadeDorme__p8]]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__relatar_noite(&resp, &mm);
    printf("morreu alguém? %s; ", relatorio[resp]);
    if (resp == 0) printf("quem? %s", participantes[mm]);
    printf("\n");
    
    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__investigar(cidadeDorme__p2, &resp);
    printf("%s é comum? %s\n", participantes[cidadeDorme__p2], relatorio[resp]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__votar(cidadeDorme__p2, cidadeDorme__p4);
    cidadeDorme__votar(cidadeDorme__p3, cidadeDorme__p4);
    cidadeDorme__votar(cidadeDorme__p4, cidadeDorme__p2);
    cidadeDorme__votar(cidadeDorme__p6, cidadeDorme__p4);
    cidadeDorme__votar_nulo(cidadeDorme__p7);
    cidadeDorme__votar(cidadeDorme__p9, cidadeDorme__p4);
    cidadeDorme__votar(cidadeDorme__p10, cidadeDorme__p4);
    for(int i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        if (cidadeDorme__status_p[i] == 1){
            printf("%s recebeu %d votos\n", participantes[i], cidadeDorme__votos_recebidos_i[i]);
        }
    }

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__apurar_votos(&resp);
    printf("resultado da apuração: %s\n", relatorio_votacao[resp]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__atacar(cidadeDorme__p3, &ss);
    printf("estado de %s - %s\n", participantes[cidadeDorme__p3], status_participantes[cidadeDorme__status_p[cidadeDorme__p3]]);
    
    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__relatar_noite(&resp, &mm);
    printf("morreu alguém? %s; ", relatorio[resp]);
    if (resp == 0) printf("quem? %s", participantes[mm]);
    printf("\n");

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__votar(cidadeDorme__p2, cidadeDorme__p6);
    cidadeDorme__votar(cidadeDorme__p6, cidadeDorme__p9);
    cidadeDorme__votar(cidadeDorme__p7, cidadeDorme__p6);
    cidadeDorme__votar(cidadeDorme__p9, cidadeDorme__p6);
    cidadeDorme__votar(cidadeDorme__p10, cidadeDorme__p6);
    for(int i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        if (cidadeDorme__status_p[i] == 1){
            printf("%s recebeu %d votos\n", participantes[i], cidadeDorme__votos_recebidos_i[i]);
        }
    }

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__apurar_votos(&resp);
    printf("resultado da apuração: %s\n", relatorio_votacao[resp]);

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__atacar(cidadeDorme__p10, &ss);
    printf("estado de %s - %s\n", participantes[cidadeDorme__p10], status_participantes[cidadeDorme__status_p[cidadeDorme__p10]]);
    
    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__relatar_noite(&resp, &mm);
    printf("morreu alguém? %s; ", relatorio[resp]);
    if (resp == 0) printf("quem? %s", participantes[mm]);
    printf("\n");

    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__votar(cidadeDorme__p2, cidadeDorme__p9);
    cidadeDorme__votar(cidadeDorme__p7, cidadeDorme__p9);
    cidadeDorme__votar(cidadeDorme__p9, cidadeDorme__p2);
    for(int i = 0; i <= cidadeDorme__Participantes__max-1;i++)
    {
        if (cidadeDorme__status_p[i] == 1){
            printf("%s recebeu %d votos\n", participantes[i], cidadeDorme__votos_recebidos_i[i]);
        }
    }
    
    printf("\nestado do jogo - %s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__apurar_votos(&resp);
    printf("resultado da apuração: %s\n", relatorio_votacao[resp]);

    return (0);
}