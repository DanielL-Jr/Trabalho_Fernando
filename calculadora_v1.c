#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double bin_to_dec(const char *binStr);
char* dec_to_bin(double num);
void evaluate_expression();
void limpar_console();

int main() {
    int option;
    do {
        printf("Menu:\n");
        printf("1. Binario -> Decimal\n");
        printf("2. Decimal -> Binario\n");
        printf("3. Calcular expressao\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        switch(option) {
            case 1: {
                char binStr[100];
                printf("Digite um numero binario: ");
                scanf("%s", binStr);
                int valid = 1;
                int has_point = 0;
                int i = 0;
                if (binStr[0] == '-') i = 1;
                for (; binStr[i] != '\0'; i++) {
                    if (binStr[i] == '.') {
                        if (has_point) { valid = 0; break; }
                        has_point = 1;
                    } else if (binStr[i] != '0' && binStr[i] != '1') {
                        valid = 0; break;
                    }
                }
                if (!valid) {
                    printf("Numero binario INVALIDO.\n");
                    break;
                }
                double dec = bin_to_dec(binStr);
                printf("Valor decimal: %f\n", dec);
                limpar_console();
                break;
            }
            case 2: {
                double num;
                printf("Digite um numero decimal: ");
                scanf("%lf", &num);
                char *bin = dec_to_bin(num);
                printf("Valor binario: %s\n", bin);
                free(bin);
                limpar_console();
                break;
            }
            case 3:
                evaluate_expression();
                limpar_console();
                break;
            case 4:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcao invalida.\n");
                limpar_console();
        }
    } while (1);
    return 0;
}

double bin_to_dec(const char *binStr) {
    int is_negative = 0;
    int i = 0;
    if (binStr[0] == '-') {
        is_negative = 1;
        i++;
    }
    double int_value = 0.0;
    while (binStr[i] != '\0' && binStr[i] != '.') {
        int_value = int_value * 2 + (binStr[i] - '0');
        i++;
    }
    double frac_value = 0.0;
    double factor = 0.5;
    if (binStr[i] == '.') {
        i++;
        while (binStr[i] != '\0') {
            frac_value += (binStr[i] - '0') * factor;
            factor /= 2;
            i++;
        }
    }
    double total = int_value + frac_value;
    return is_negative ? -total : total;
}

char* dec_to_bin(double num) {
    if (num == 0.0) {
        char *result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    int int_part = (int)num;
    double frac_part = num - int_part;
    char int_bin[32] = {0};
    int i = 0;
    if (int_part == 0) {
        int_bin[i++] = '0';
    } else {
        while (int_part > 0) {
            int_bin[i++] = (int_part % 2) + '0';
            int_part /= 2;
        }
    }
    for (int j = 0; j < i/2; j++) {
        char temp = int_bin[j];
        int_bin[j] = int_bin[i - j - 1];
        int_bin[i - j - 1] = temp;
    }
    int_bin[i] = '\0';
    char frac_bin[9] = {0};
    int f = 0;
    while (frac_part > 0 && f < 8) {
        frac_part *= 2;
        int bit = (int)frac_part;
        frac_bin[f++] = '0' + bit;
        frac_part -= bit;
    }
    frac_bin[f] = '\0';
    int total_length = is_negative + strlen(int_bin) + (f ? 1 + f : 0) + 1;
    char *result = malloc(total_length);
    int pos = 0;
    if (is_negative) result[pos++] = '-';
    strcpy(result + pos, int_bin);
    pos += strlen(int_bin);
    if (f > 0) {
        result[pos++] = '.';
        strcpy(result + pos, frac_bin);
    }
    return result;
}

void evaluate_expression() {
    printf("\n1. Adicao (+)\n2. Subtracao (-)\n3. Multiplicacao (*)\n");
    printf("4. Divisao fracionaria (/)\n5. Divisao inteira (div)\n6. Potencia (^)\n");
    char choice, str[4];
    double a, b;
    do{        
        printf("Digite a expressao numerica:\n");
        scanf("%lf %s %lf", &a, str, &b);
        choice = str[0];
    } while (choice != '+' && choice != '-'  && choice != '*'  && choice != '/'  && strcmp(str, "div") != 0 && choice != '^');
    
    double result;
    switch(choice) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) { 
                printf("Erro: Division by zero.\n"); 
                return; 
            }
            result = a / b; break;
        case 'd': 
            if ((int)b == 0) { 
                printf("Erro: Divisao por zero.\n"); 
                return; 
            }
            result = (int)a / (int)b; break;
        case '^': result = pow(a, b); break;
    }
    printf("Resultado: %lf\n", result);
}

void limpar_console(){
    printf("Pressione Enter para continuar...\n");
    system("pause > nul");
    system("cls");
}