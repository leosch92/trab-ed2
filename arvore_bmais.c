#include <stdio.h>
#include <string.h>

const int t = 2;

typedef struct arvbm{
    int nchaves, folha, *chave;
    struct aluno **aluno;
    struct arvbm **filho, *prox;
}TABM;

//chcs = Carga horária cursada com sucesso; npu = Número de períodos desde a entrada
//cht = Carga horária total; ntotper = Número total de períodos; tnc = Tempo nominal de curso
typedef struct aluno{
    int mat, num_trancs, chcs, npu, cht, ntotper, tnc;
    float cr;
    char nome[31];
}TAL;

TABM *cria(int t){
    TABM* novo = (TABM*)malloc(sizeof(TABM));
    novo->nchaves = 0;
    novo->chave =(int*)malloc(sizeof(int)*((t*2)-1));
    novo->folha = 1;
    novo->aluno = (TAL**)malloc(sizeof(TAL*) * ((t*2)-1));
    novo->filho = (TABM**)malloc(sizeof(TABM*)*t*2);
    novo->prox = NULL;
    int i;
    for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
    return novo;
}

TABM *inicializa(void){
    return NULL;
}

TABM *libera(TABM *a){
    if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) libera(a->filho[i]);
    }
    free(a->chave);
    free(a->filho);
    free(a->aluno);
    free(a->prox);
    free(a);
    return NULL;
    }
}

TABM *busca(TABM *a, int mat){
    if (!a) return NULL;
    int i = 0;
    while ((i < a->nchaves) && (mat > a->chave[i])) i++;
    if ((i < a->nchaves) && (a->folha) && (mat == a->chave[i])) return a;
    if (a-> folha) return NULL;
    if (a->chave[i] == mat) i++;
    return busca(a->filho[i], mat);
}

void imprime(TABM *a, int andar){
    if(a){
        int i,j;
        for(i=0; i<=a->nchaves-1; i++){
            imprime(a->filho[i],andar+1);
            for(j=0; j<=andar; j++) printf("   ");
            printf("%d\n", a->chave[i]);
        }
        imprime(a->filho[i],andar+1);
    }
}

TABM *divisao(TABM *x, int i, TABM* y, int t){
    TABM *z = cria(t);
    z->folha = y->folha;
    int j;
    if(!y->folha){
        z->nchaves = t-1;
        for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
        for(j=0;j<t;j++){
            z->filho[j] = y->filho[j+t];
            y->filho[j+t] = NULL;
        }
    }
    else {
        z->nchaves = t; //z possuirá uma chave a mais que y se for folha
        for(j=0;j < t;j++){
            z->chave[j] = y->chave[j+t-1];//Caso em que y é folha, temos q passar a info para o nó da direita
            z->aluno[j] = y->aluno[j+t-1];
        }
    }
    y->nchaves = t-1;
    for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
    x->chave[i-1] = y->chave[t-1];
    x->nchaves++;
    return x;
}

TABM *insere_nao_completo(TABM *x, TAL* k, int t){
    int i = x->nchaves-1;
    if(x->folha){
        while((i>=0) && (k->mat < x->chave[i])){
            x->chave[i+1] = x->chave[i];
            i--;
        }
        x->chave[i+1] = k->mat;
        x->aluno[i+1] = k;
        x->nchaves++;
        return x;
    }
    while((i>=0) && (k->mat < x->chave[i])) i--;
    i++;
    if(x->filho[i]->nchaves == ((2*t)-1)){
        x = divisao(x, (i+1), x->filho[i], t);
        if(k->mat > x->chave[i]) i++;
    }
    x->filho[i] = insere_nao_completo(x->filho[i], k, t);
    return x;
}

TABM *insere(TABM *T, TAL *k, int t){
    if(busca(T,k->mat)) return T;
    if(!T){
        T=cria(t);
        T->chave[0] = k->mat;
        T->aluno[0] = k;
        T->nchaves=1;
        return T;
    }
    if(T->nchaves == (2*t)-1){
        TABM *S = cria(t);
        S->nchaves=0;
        S->folha = 0;
        S->filho[0] = T;
        S = divisao(S,1,T,t);
        S = insere_nao_completo(S,k,t);
        return S;
    }
    T = insere_nao_completo(T,k,t);
    return T;
}

TAL *le_curriculo(TAL* aln, int ncur){
    if (ncur == 1){
        aln->cht = 2955;
        aln->tnc = 8;
        aln->ntotper = 16;
    }
    else if (ncur == 2){
        aln->cht = 3524;
        aln->tnc = 8;
        aln->ntotper = 12;
    }
    else if (ncur == 3){
        aln->cht = 3200;
        aln->tnc = 8;
        aln->ntotper = 12;
    }
    return aln;
}

void imprime_menu(void){
    printf("\nMENU\n");
    printf("1.Imprimir arvore atual\n");
    printf("2.Imprimir as informacoes de um determinado aluno\n");
    printf("3.Inserir arquivo de alunos\n");
    printf("4.Inserir um aluno\n");
    printf("5.Remover um aluno\n");
    printf("6.Alterar informacao de aluno\n");
    printf("7.Remover formandos\n");
    printf("8.Remover discentes que violam a regra de 50%% do curso nao concluido no tempo nominal\n");
    printf("9.Remover discentes que violam a regra de tempo maximo sem concluir a graduacao\n");
    printf("10.Sair\n\n");
    return;
}

void imprime_menu_altera(void){
    printf("Qual informacao deseja alterar?\n\n");
    printf("1.CR\n");
    printf("2.Numero de trancamentos\n");
    printf("3.Carga horaria cursada com aprovacao\n");
    printf("4.Numero de periodos que o discente esta na universidade\n\n");
    return;
}

void imprime_aluno(TABM* a, int mat){
    TABM *aux = busca(a, mat);
    if (!aux){
        printf("Aluno nao encontrado.\n");
        return;
    }
    int i;
    for (i = 0; i < aux->nchaves; i++){
        if (aux->chave[i] == mat){
            printf("\nMatricula: %d\n", aux->aluno[i]->mat);
            printf("Nome: %s\n", aux->aluno[i]->nome);
            printf("CR: %f\n", aux->aluno[i]->cr);
            printf("Numero de trancamentos: %d\n", aux->aluno[i]->num_trancs);
            printf("Carga horaria cursada com aprovacao: %d\n", aux->aluno[i]->chcs);
            printf("Carga horaria total do curso: %d\n", aux->aluno[i]->cht);
            printf("Numero de periodos desde a entrada na universidade: %d\n", aux->aluno[i]->npu);
            printf("Tempo de curso nominal (em periodos): %d\n", aux->aluno[i]->tnc);
            printf("Tempo maximo de periodos no curriculo: %d\n\n", aux->aluno[i]->ntotper);
            break;
        }
    }
    return;
}

TABM *le_arq_arvore(char* nm_arq, TABM* arv, int t){
    FILE *fp = fopen(nm_arq, "rt");
    if(!fp) exit(1);
    int num_cur, r;
    TAL* aluno = (TAL*)malloc(sizeof(TAL));
    r = fscanf(fp, "%d %f %d %d %d %d %30[^\n]", &aluno->mat, &aluno->cr, &aluno->num_trancs, &aluno->chcs, &aluno->npu,
               &num_cur, &aluno->nome);
    while (r == 7) { //7 é o número de informações por linha no arquivo
            aluno = le_curriculo(aluno, num_cur);
            arv = insere(arv, aluno, t);
            aluno = (TAL*)malloc(sizeof(TAL));
            r = fscanf(fp, "%d %f %d %d %d %d %30[^\n]", &aluno->mat, &aluno->cr, &aluno->num_trancs, &aluno->chcs, &aluno->npu,
               &num_cur, &aluno->nome);
    }
    fclose(fp);
    return arv;
}

void altera_aluno(TABM* arv, int m, void* nova_info, int t, int num_opalt){
    TABM* aux = busca(arv, m);
    if (!aux){
        printf("Matricula nao encontrada.\n");
        return;
    }
    int i = 0;
    for (i = 0; i < aux->nchaves; i++){
        if (aux->chave[i] == m){
            if (num_opalt == 1){
                float *novo_cr = (float*)nova_info;
                aux->aluno[i]->cr = *novo_cr;
            }
            else if (num_opalt == 2){
                int *novo_ntrancs = (int*)nova_info;
                aux->aluno[i]->num_trancs = *novo_ntrancs;
            }
            else if (num_opalt == 3){
                int *nova_chcs = (int*)nova_info;
                aux->aluno[i]->chcs = *nova_chcs;
            }
            else if (num_opalt == 4){
                int *novo_npu = (int*)nova_info;
                aux->aluno[i]->npu = *novo_npu;
            }
            break;
        }
    }
    return;
}

int main(){
    TABM *arvore = inicializa();
    printf("Bem vinda, Rosseti! Digite a operacao que deseja realizar:\n");
    imprime_menu();
    int num_op;
    scanf("%d", &num_op);
    while (num_op != 10){
        if (num_op == 1){
            printf("\n\n----------------- Arvore atual -----------------\n");
            imprime(arvore, 0);
        }
        else if (num_op == 2){
            printf("Digite a matricula do aluno a ser procurado:\n");
            int mat_imp;
            scanf("%d", &mat_imp);
            imprime_aluno(arvore, mat_imp);
        }
        else if (num_op == 3){
            printf("Digite o nome do arquivo:\n");
            char nome_arq[31];
            scanf("%s", nome_arq);
            arvore = le_arq_arvore(nome_arq, arvore, t);
        }
        else if (num_op == 4){
            printf("Digite as informacoes do aluno:\n");
            TAL* aln_ins = (TAL*)malloc(sizeof(TAL));
            int ncur;
            scanf("%d %f %d %d %d %d %30[^\n]", &aln_ins->mat, &aln_ins->cr, &aln_ins->num_trancs,
                  &aln_ins->chcs, &aln_ins->npu, &ncur, aln_ins->nome);
            aln_ins = le_curriculo(aln_ins, ncur);
            arvore = insere(arvore, aln_ins, t);
        }
        else if (num_op == 5){
            printf("Insira a matricula do aluno a ser removido:\n");
            int mat_removida;
            scanf("%d", &mat_removida);
            //retira(arvore, mat_removida, t);
            imprime(arvore, 0);
        }
        else if (num_op == 6){
            printf("Digite a matricula do aluno a ser alterado:\n");
            int mat_alterado;
            scanf("%d", &mat_alterado);
            printf("\n");
            imprime_menu_altera();
            int num_op_altera;
            scanf("%d", &num_op_altera);
            if (num_op_altera == 1){
                printf("Digite o novo CR:\n");
                float *novo_cr = malloc(sizeof(float));
                scanf("%f", novo_cr);
                altera_aluno(arvore, mat_alterado, novo_cr, t, num_op_altera);
            }
            else if (num_op_altera == 2){
                printf("Digite o numero de trancamentos desejado:\n");
                int *novo_num_trancs = malloc(sizeof(int));
                scanf("%d", novo_num_trancs);
                altera_aluno(arvore, mat_alterado, novo_num_trancs, t, num_op_altera);
            }
            else if (num_op_altera == 3){
                printf("Digite a nova CHCS:\n");
                int *nova_chcs = malloc(sizeof(int));
                scanf("%d", nova_chcs);
                altera_aluno(arvore, mat_alterado, nova_chcs, t, num_op_altera);
            }
            else if (num_op_altera == 4){
                printf("Digite o novo NPU:\n");
                int *novo_npu = malloc(sizeof(int));
                scanf("%d", novo_npu);
                altera_aluno(arvore, mat_alterado, novo_npu, t, num_op_altera);
            }
        }
        else if (num_op == 7){
            //remove_formandos(arvore, t);
            imprime(arvore, 0);
        }
        else if (num_op == 8){
            //remove_regra_cinquenta(arvore, t);
            imprime(arvore, 0);
        }
        else if (num_op == 9){
            //remove_regra_maximo(arvore, t);
            imprime(arvore, 0);
        }

        imprime_menu();
        scanf("%d", &num_op);
    }
    libera(arvore);
    return 0;
}
