//
//  main.c
//  CalculadoraPosfixa
//
//  Created by Caio Mandarino on 03/06/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

int main(void) {
    Expressao expr;
    int opcao = 0;
    char entrada[512];

    do {
        system("clear || cls");

        printf("\nAVALIADOR DE EXPRESSOES NUMERICAS\n");
        printf("1- Infixa para Pos-fixa e Calcular\n");
        printf("2- Pos-fixa para Infixa e Calcular\n");
        printf("3- Sair\n");
        printf("Escolha uma opcao: \n");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0; // Força a opção inválida
        }
        
        while(getchar() != '\n'); // Limpa o buffer após a leitura
        
        switch (opcao) {
            case 1:
                printf("Digite a expressao Infixa: \n");
                scanf("%[^\n]", entrada);
                
                strcpy(expr.inFixa, entrada);
                char* posFixaResultado = getFormaPosFixa(expr.inFixa);
                if (posFixaResultado != NULL) {
                    strcpy(expr.posFixa, posFixaResultado);
                    printf("Expressao Pos-fixa: %s\n", expr.posFixa);
                    printf("Valor da Expressao: %.2f", getValorPosFixa(expr.posFixa));
                    free(posFixaResultado);
                } else {
                    printf("Erro: Expressao infixa invalida.\n");
                }
                break;

            case 2:
                printf("Digite a expressao Pos-fixa: \n");
                scanf("%[^\n]", entrada);

                strcpy(expr.posFixa, entrada);
                char* inFixaResultado = getFormaInFixa(expr.posFixa);
                 if (inFixaResultado != NULL) {
                    strcpy(expr.inFixa, inFixaResultado);
                    printf("Expressao Infixa: %s\n", expr.inFixa);
                     printf("Valor da Expressao: %.2f", getValorInFixa(expr.inFixa));
                    free(inFixaResultado);
                } else {
                    printf("Erro: Expressao pos-fixa invalida.\n");
                }
                break;

            case 3:
                printf("Finalizando o programa.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        if (opcao != 3) {
             printf("\nPressione ENTER para continuar...\n");
             getchar();
        }
        
        while(getchar() != '\n'); // Limpa o buffer após a leitura
        

    } while (opcao != 3);

    return 0;
}
