#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265358979323846

typedef struct pilhaFuncoes {
    char str[6];
    struct pilhaFuncoes* next;
} PilhaFuncoes;

typedef struct pilhaOperador {
    char operador;
    struct pilhaOperador* next;
} PilhaOperador;

typedef struct pilhaExpressoes {
    char *str;
    struct pilhaExpressoes* next;
} PilhaExpressoes;

void operadorInserir(PilhaOperador **top, char operador) {
    PilhaOperador* new = malloc(sizeof(PilhaOperador));
    new->operador = operador;
    new->next = *top;
    *top = new;
}

char operadorRetirar(PilhaOperador **top) {
    if (*top == NULL) return '\0';
    PilhaOperador* temp = *top;
    char operador = temp->operador;
    *top = temp->next;
    free(temp);
    return operador;
}

void expressaoInserir(PilhaExpressoes **top, char* val) {
    PilhaExpressoes* new = malloc(sizeof(PilhaExpressoes));
    new->str = strdup(val);
    new->next = *top;
    *top = new;
}

void expressaoRetirar(PilhaExpressoes **top, char* remover) {
    if (*top == NULL) {
        return;
    }
    PilhaExpressoes* temp = *top;
    strcpy(remover, temp->str);
    *top = temp->next;
    free(temp->str);
    free(temp);
}

void funcoesInserir(PilhaFuncoes **top, const char* val) {
    PilhaFuncoes* new = malloc(sizeof(PilhaFuncoes));
    strncpy(new->str, val, 5);
    new->str[5] = '\0';
    new->next = *top;
    *top = new;
}

char* funcoesRetirar(PilhaFuncoes **top, char* remover) {
    if (*top == NULL) return NULL;
    PilhaFuncoes* temp = *top;
    strcpy(remover, temp->str);
    *top = temp->next;
    free(temp);
    return remover;
}

// Verifica se substring a partir de str[i] bate com func, retorna 1 se sim
int ehFuncao(const char* str, int i, const char* func) {
    unsigned long int n = strlen(func);
    return strncmp(&str[i], func, n) == 0;
}

int ehOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Retorna 1 se válido, 0 se inválido
int validaInfixa(char* str) {
    int i = 0, par = 0;
    int elementoAnterior = 0; // 0: início/parenteses aberto, 1: número, 2: operador, 3: função, 4: fecha parênteses

    while (str[i]) {
        
        if (str[i] == ' ') {
            i++;
            continue;
        }

        // Funções
        if (ehFuncao(str, i, "sen")) {
            if (elementoAnterior == 1 || elementoAnterior == 4){
                return 0;
            }
            i += 3;
            elementoAnterior = 3;
            continue;
        }
        
        if (ehFuncao(str, i, "cos")) {
            if (elementoAnterior == 1 || elementoAnterior == 4){
                return 0;
            }
            i += 3;
            elementoAnterior = 3;
            continue;
        }
        
        if (ehFuncao(str, i, "tg")) {
            if (elementoAnterior == 1 || elementoAnterior == 4){
                return 0;
            }
            i += 2;
            elementoAnterior = 3;
            continue;
        }
        if (ehFuncao(str, i, "log")) {
            if (elementoAnterior == 1 || elementoAnterior == 4){
                return 0;
            }
            i += 3;
            elementoAnterior = 3;
            continue;
        }

        // Parênteses
        if (str[i] == '(') {
            par++;
            if (elementoAnterior == 1 || elementoAnterior == 4){
                return 0;
            }
            i++;
            elementoAnterior = 0;
            continue;
        }
        if (str[i] == ')') {
            par--;
            if (par < 0) {
                return 0;
            }
            if (elementoAnterior == 2 || elementoAnterior == 0 || elementoAnterior == 3) {
                return 0;
            }
            i++;
            elementoAnterior = 4;
            continue;
        }

        // Número
        if (isdigit(str[i])) {
            if (elementoAnterior == 1 || elementoAnterior == 4){
                return 0;
            }
            int virgulaSeparador = 0;
            while (isdigit(str[i]) || ((str[i] == ',' || str[i] == '.') && !virgulaSeparador)) {
                if (str[i] == ',' || str[i] == '.'){
                    virgulaSeparador = 1;
                }
                i++;
            }
            elementoAnterior = 1;
            continue;
        }

        // Operador
        if (ehOperator(str[i])) {
            if (elementoAnterior != 1 && elementoAnterior != 4){
                return 0;
            }
            i++;
            elementoAnterior = 2;
            continue;
        }

        // Caractere inválido
        return 0;
    }

    // Último não pode ser operador ou função ou parêntese aberto
    if (elementoAnterior == 2 || elementoAnterior == 3 || elementoAnterior == 0) return 0;
    if (par != 0) return 0;

    return 1;
}

char valorTop(PilhaOperador *top) {
    return top ? top->operador : '\0';
}

int isFunction(const char* str, unsigned long int i, char* nomeFunc) {
    
    if (strncmp(&str[i], "sen", 3) == 0) {
        strcpy(nomeFunc, "sen");
        return 3;
    }
    
    if (strncmp(&str[i], "cos", 3) == 0) {
        strcpy(nomeFunc, "cos");
        return 3;
    }
    
    if (strncmp(&str[i], "tg", 2) == 0)  {
        strcpy(nomeFunc, "tg");
        return 2;
    }
    
    if (strncmp(&str[i], "log", 3) == 0) {
        strcpy(nomeFunc, "log");
        return 3;
    }
    
    return 0;
}

int precedencia(char op) {
    switch(op) {
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        default: return 0;
    }
}

int diferenteDeElevado(char op) {
    return (op != '^');
}

char *getFormaPosFixa(char *Str) {
    if (validaInfixa(Str) == 0) {
        return NULL;
    }
    PilhaOperador* pilhaOp = NULL;
    PilhaFuncoes* pilhaFunc = NULL;   // Funções
    unsigned long int len = strlen(Str);
    char* posfixa = malloc(5 * len);
    int i = 0, k = 0;
    char funcNome[6];

    while (Str[i] != '\0') {
        if (Str[i] == ' ') {
            i++;
            continue;
        }

        // Função
        int funcTam = isFunction(Str, i, funcNome);
        if (funcTam != 0) {
            funcoesInserir(&pilhaFunc, funcNome);
            i += funcTam;
            continue;
        }

        // Número
        if (isdigit(Str[i])) {
            while ( isdigit(Str[i]) || ((Str[i] == ',' || Str[i] == '.')) ) {
                posfixa[k] = Str[i];
                k++;
                i++;
            }
            posfixa[k] = ' ';
            k++;
            continue;
        }

        // Parêntese de abertura
        if (Str[i] == '(') {
            operadorInserir(&pilhaOp, Str[i]);
            i++;
            continue;
        }

        // Parêntese de fechamento
        if (Str[i] == ')') {
            while (pilhaOp && valorTop(pilhaOp) != '(') {
                posfixa[k] = operadorRetirar(&pilhaOp);
                k++;
                posfixa[k] = ' ';
                k++;
            }
            operadorRetirar(&pilhaOp); // Remove '('
            
            // Se havia função no topo, move para saída
            if (pilhaFunc != NULL) {
                char funcName[6];
                funcoesRetirar(&pilhaFunc, funcName);
                int j;
                for (j = 0; funcName[j]; j++){
                    posfixa[k] = funcName[j];
                    k++;
                }
                
                posfixa[k] = ' ';
                k++;
            }
            i++;
            continue;
        }

        // Operadores
        if (ehOperator(Str[i])) {
            while (pilhaOp && ehOperator(valorTop(pilhaOp)) &&
                ((diferenteDeElevado(Str[i]) && precedencia(Str[i]) <= precedencia(valorTop(pilhaOp))) ||
                (!diferenteDeElevado(Str[i]) && precedencia(Str[i]) < precedencia(valorTop(pilhaOp))))) {
                posfixa[k] = operadorRetirar(&pilhaOp);
                k++;
                posfixa[k] = ' ';
                k++;
            }
            operadorInserir(&pilhaOp, Str[i]);
            i++;
            continue;
        }

        // Se não reconhecido, ignora
        i++;
    }

    // Esvazia operadores restantes
    while (pilhaOp) {
        posfixa[k] = operadorRetirar(&pilhaOp);
        k++;
        posfixa[k] = ' ';
        k++;
    }
    
    // Esvazia funções restantes
    while (pilhaFunc) {
        char funcRestantes[6];
        funcoesRetirar(&pilhaFunc, funcRestantes);
        int j;
        for (j = 0; funcRestantes[j]; j++){
            posfixa[k] = funcRestantes[j];
            k++;
        }
        
        posfixa[k] = ' ';
        k++;
    }

    if (k > 0){
        k--; // Remove último espaço
    }
    
    posfixa[k] = '\0';
    
    return posfixa;
}

char *getFormaInFixa(char *Str) {
    PilhaExpressoes *exprPilha = NULL;
    unsigned long int len = strlen(Str);
    int i = 0;
    
    while (i < len) {
        if (Str[i] == ' ') {
            i++;
            continue;
        }

        // Função (sen, cos, tg, log)
        char nomeFunc[6];
        int funcTam = isFunction(Str, i, nomeFunc);
        
        if (funcTam != 0) {
            char tempExpr[256];
            char expr[300];
            expressaoRetirar(&exprPilha, tempExpr);
            snprintf(expr, sizeof(expr), "%s(%s)", nomeFunc, tempExpr);
            expressaoInserir(&exprPilha, expr);
            i += funcTam;
            continue;
        }

        // Número (inclui decimal)
        if (isdigit(Str[i])) {
            char num[64];
            int j = 0;
            while (isdigit(Str[i]) || Str[i] == '.' || Str[i] == ',') {
                num[j] = Str[i];
                j++;
                i++;
                if(j == 63){
                    break;
                }
            }
            num[j] = '\0';
            expressaoInserir(&exprPilha, num);
            continue;
        }

        // Operador binário (+ - * / ^)
        if (ehOperator(Str[i])) {
            char direita[256], esquerda[256];
            expressaoRetirar(&exprPilha, direita);
            expressaoRetirar(&exprPilha, esquerda);
            char expr[520];
            snprintf(expr, sizeof(expr), "(%s %c %s)", esquerda, Str[i], direita);
            expressaoInserir(&exprPilha, expr);
            i++;
            continue;
        }

        // Não reconhecido: volta
        return NULL;
    }

    // O resultado estará no topo da pilha
    char* result = malloc(1024);
    
    if (exprPilha != NULL) {
        expressaoRetirar(&exprPilha, result);
    } else {
        result[0] = '\0';
    }
    
    // Algo na pilha ainda, retorna erro
    if (exprPilha != NULL) {
        return NULL;
    }
    
    return result;
}

// Função para avaliar pós-fixa com operadores + - * / ^ e funções sen, cos, tg, log
float getValorPosFixa(char *StrPosFixa) {
    float pilha[128];
    int top = -1;
    unsigned long int len = strlen(StrPosFixa);
    int i = 0;

    while (i < len) {
        if (StrPosFixa[i] == ' ') {
            i++;
            continue;
        }

        // Função (sen, cos, tg, log)
        char funcNome[6];
        int funcTam = isFunction(StrPosFixa, i, funcNome);
        if (funcTam != 0) {
            float arg = pilha[top];
            top--;
            if (strcmp(funcNome, "sen") == 0){
                top++;
                pilha[top] = sinf(arg * PI / 180.0);
            }
            
            else if (strcmp(funcNome, "cos") == 0){
                top++;
                pilha[top] = cosf(arg * PI / 180.0);
            }
            
            else if (strcmp(funcNome, "tg") == 0){
                top++;
                pilha[top] = tanf(arg * PI / 180.0);
            }
            
            else if (strcmp(funcNome, "log") == 0){
                top++;
                pilha[top] = log10f(arg);
            }
            
            i += funcTam;
            continue;
        }

        // Número (decimal)
        if (isdigit(StrPosFixa[i])) {
            char num[64]; int j = 0;
            while (isdigit(StrPosFixa[i]) || StrPosFixa[i] == '.' || StrPosFixa[i] == ',') {
                num[j] = (StrPosFixa[i] == ',') ? '.' : StrPosFixa[i];
                j++;
                i++;
            }
            num[j] = '\0';
            top++;
            pilha[top] = atof(num);
            continue;
        }

        // Operador
        if (ehOperator(StrPosFixa[i])) {
            float b = pilha[top];
            top--;
            float a = pilha[top];
            top--;
            switch (StrPosFixa[i]) {
                case '+':
                    top++;
                    pilha[top] = a + b;
                    break;
                case '-':
                    top++;
                    pilha[top] = a - b;
                    break;
                case '*':
                    top++;
                    pilha[top] = a * b;
                    break;
                case '/':
                    top++;
                    pilha[top] = a / b;
                    break;
                case '^':
                    top++;
                    pilha[top] = powf(a, b);
                    break;
            }
            i++;
            continue;
        }
        // Caractere inválido: ignora
        i++;
    }
    return (top == 0) ? pilha[0] : 0.0f;
}

float getValorInFixa(char *StrInFixa) {
    char *posfixa = getFormaPosFixa(StrInFixa);
    if (!posfixa) return 0.0f; // Expressão infixa inválida
    float val = getValorPosFixa(posfixa); // Já considera trigonometria em graus
    free(posfixa);
    return val;
}
