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

int main(int argc, const char * argv[]) {
//    char infixa[100] = "(3 + 4) * 5";
//    char posfixa[100] = "";
//    
//    //strcpy(postfix, getFormaPosFixa(infix));
//    const char* temp = getFormaPosFixa(infixa);
//    //const char* temp = getFormaInFixa(postfix);
//    
//    if(temp != NULL){
//        strcpy(posfixa, temp);
//    }
//    
//    
//    const char* temp2 = getFormaInFixa(posfixa);
//    
//    if(temp2 != NULL){
//        strcpy(infixa, temp2);
//    }
//    
//    
//    printf("Infixa: %s\n", infixa); //Isso é a função
//    printf("%.2f\n", getValorInFixa(infixa));
//    
//    printf("Posfixa: %s\n", posfixa);
//    printf("%.2f\n", getValorPosFixa(posfixa));
    Expressao a;
    strcpy(a.inFixa, "sen(45) ^2 + 0,5");
    strcpy(a.posFixa, getFormaPosFixa(a.inFixa));
    a.Valor = getValorInFixa(a.inFixa);
    
    Expressao b;
    strcpy(b.posFixa, "45 sen 2 ^ 0.5 +");
    strcpy(b.inFixa, getFormaInFixa(b.posFixa));
    b.Valor = getValorPosFixa(b.posFixa);
    
    printf("%s\n%s\n", b.inFixa, b.posFixa);
//    printf("%.2f\n", getValorPosFixa(b.posFixa));
//    printf("%.2f\n", getValorInFixa(b.inFixa));
    printf("%.2f\n", b.Valor);
    
    return 0;
}
