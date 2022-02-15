#include "stdio.h"
#include "cidadeDorme_i.c"

int main(int argc, char** argv){
    const char* participantes[] = {"p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "p10"};
    const char* status_participantes[] = {"fora", "vivo", "morto", "atacado"};
    const char* status_jogo[] = {"aguardando", "cadastro", "distribuicao_papeis", "ataque", "cura", "relatorio_noite", "investigacao", "votacao", "apuracao_votos", "reinicio"};
    const char* papeis[] = {"lobisomem", "detetive", "curandeiro", "comum", "nenhum"};
    const char* relatiorio[] = {"sim", "nao"};
    const char* relatiorio_votacao[] = {"morreu_lobisomem", "morreu_nao_lobisomem", "ninguem_morreu", "lobisomem_venceu"};

    printf("Iniciando...\n");

    cidadeDorme__INITIALISATION();

    printf("%d\n", cidadeDorme__qtd_vivos_i);

    cidadeDorme__cadastrar(cidadeDorme__p1);
    cidadeDorme__cadastrar(cidadeDorme__p4);
    cidadeDorme__cadastrar(cidadeDorme__p5);
    cidadeDorme__cadastrar(cidadeDorme__p6);
    cidadeDorme__cadastrar(cidadeDorme__p7);
    printf("%s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__cadastrar(cidadeDorme__p8);
    cidadeDorme__cadastrar(cidadeDorme__p9);

    printf("%s\n", status_jogo[cidadeDorme__status_j]);
    cidadeDorme__terminar_cadastro();
    printf("%s\n", status_jogo[cidadeDorme__status_j]);
    printf("%s\n", participantes[cidadeDorme__lobisomem_p]);
    printf("%d\n", cidadeDorme__qtd_vivos_i);

    return (0);
}