#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define home "/home/joaops95/Desktop/MyProjects/explicacoesgui/projecty/dados.txt"
#define MAXINT 8
#define MAXFILE 100
char input[5];

//estrutura de dados para guaradar ocorrencias de resultados num1 op num2 
struct data {                           
    int num1;
    int num2;
    char op; 
};  


//declaracao de funcoes

int my_isdigit(int ch);
void showCalcFor(char, int , struct data[MAXFILE]);
int makeCalc(char, int, int);
void showHeader(void);

int main(){
    char value;
    //declaracao do ficheiro

    FILE *fptr;
    //Verificar se o ficheiro existe

    if ((fptr = fopen(home,"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    //Vou buscar o primeiro caracter do ficheiro

    value = getc(fptr);
    char endofline =  10;
    int counter = 0;

    struct data arr_data[MAXFILE];
    //crio um array de estruturas num1 op num2 
    // para poder guardar todas as contas

    // enquanto o ficheiro nao chegar ao fim

     while (value != EOF)
    {
        int num1found = 0;
        int num1firstfound = 0;
        int num2found = 0;
        int num2firstfound = 0;
        int opfound = 0;
        int opfirstfound = 0;
        char num1[MAXINT]  = "";
        char num2[MAXINT]  = "";
        char op;
        // enquanto nao existir uma nova linha
        while (value != endofline)
        {    
            // se nao encontrou o 1 numero
            if(!num1found){

                if(!num1firstfound && (my_isplusorless(value))){
                    strncat(num1, &value, 1);
                }
                if(my_isdigit(value)){
                    num1firstfound = 1;
                    strncat(num1, &value, 1); 
                }
                if(num1firstfound && (!my_isdigit(value))){
                    num1found = 1;
                    arr_data[counter].num1 = atoi(num1);
                }
            }
            // se encontrou o 1 numero, nao encontrou o operador

            if(num1found && !opfound){
                if(value == 42 || my_isplusorless(value) || value == 47 || value == 37){
                    opfound = 1;
                    arr_data[counter].op = value;
                    value = getc(fptr);

                }
            }
            // se encontrou o 1 numero, o opeardor e nao encontrou o segundo

            if(num1found && opfound && !num2found){

                if(!num2firstfound && (my_isplusorless(value))){
                    strncat(num2, &value, 1);
                }
                if(my_isdigit(value)){
                    num2firstfound = 1;
                    strncat(num2, &value, 1);
                    arr_data[counter].num2 = atoi(num2);

                }
                if(num2firstfound && (!my_isdigit(value))){
                    num2found = 1;
                    arr_data[counter].num2 = atoi(num2);
                }
            }
            
            value = getc(fptr);
            if(value == EOF) break;
        }
        counter++;
        value = getc(fptr);
    }
    if (feof(fptr)){
        fclose(fptr); 
    }
    // chamar o menu

    showHeader();

    if(strcmp("none",input) != 0){
        if(strcmp("all",input) == 0){
            char newinput[5] =  "+-*/%";
            for (int i = 0; i < strlen(newinput); i++){
                showCalcFor(newinput[i], counter, arr_data);
            }
        }else{
            for (int i = 0; i < strlen(input); i++){
                showCalcFor(input[i], counter, arr_data);
            }
        }
    }


    return 0;
}



void showCalcFor(char op, int maxdata, struct data items[MAXFILE])
{
    //mostrar a conta para operador

    for (int i = 0; i < maxdata; i++)
    {
        if(op == items[i].op){
            printf("\n%d %c %d = %d",items[i].num1,items[i].op,items[i].num2, makeCalc(items[i].op, items[i].num1 ,items[i].num2));
        }
    }
    
}

int makeCalc(char c, int num1, int num2){
    //fazer a conta com os numeros e operadores

    int sum = 0;
    switch(c) {
        case '+': sum = num1 + num2; return sum;
        case '-': sum = num1 - num2; return sum;
        case '*': sum = num1 * num2; return sum;
        case '/': sum = num1 / num2; return sum;
        case '%': sum = num1 % num2; return sum;
        default: break;
    }
}

int my_isdigit(int ch){
    if(ch >= 48 && ch <= 57) return 1;
    return 0;
}

int my_isplusorless(int ch){
    if(ch == 43 || ch == 45) return 1;
    return 0;
}


void showHeader(void){
    // se encontrou o 1 numero, nao encontrou o operador
    char possible[10][5] = { "+", "-", "*", "/", "%", "+-", "+-*/%", "all", "none", "error"};
    int valid = 0;
    do{
        printf("Calculadora LTGI\n\n");
        printf("Opções válidas:\n");
        printf("+\t - Soma\n");
        printf("-\t - Subtração\n");
        printf("*\t - Multiplicação\n");
        printf("/\t - Divisão\n");
        printf("%%\t - Modulo\n");
        printf("all\t - Mostra todas as operações válidas (+ - * / %%)\n");
        printf("none\t - Não mostra qualquer operação\n");
        printf("error\t - Mostra linhas com operações inválidas\n");
        printf("Exemplos de opções de execução:\n\n");
        printf("+\t : Mostra apenas as somas\n");
        printf("+-\t : Mostra apenas as somas e subtrações\n");
        printf("%%+-*/\t : Mostra todas as operações aritméticas\n");
        printf("all\t : Igual à opção anterior\n");
        printf("none\t : Não mostra qualquer operação\n");
        printf("error\t : Mostra todas as operações com operadores inválidos\n");
        printf("Introduza uma das opcoes:\n");
        scanf("%s", input);
        for(int i = 0; input[i]; i++){
            input[i] = tolower(input[i]);
        }
        //passar o input para lowercase
        for (int j = 0; j < 10; j++)
        {
            //ir a cada opcao possivel e comparar se e igual ao input

            int i = 0;
            while(possible[j][i] != '\0' && input[i] != '\0') // until atleast one string ends
            {
                if(possible[j][i] != input[i]) 
                {
                    valid = 1;
                    break;
                }
                i++;
            }
        }
    }while (!valid);
}