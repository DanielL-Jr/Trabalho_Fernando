#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double bin_to_dec(const char *binStr);
char* dec_to_bin(double num);
void evaluate_expression();

int main() {
    int option;
    char another;
    do {
        printf("\nMain Menu:\n");
        printf("1. Binary to Decimal\n");
        printf("2. Decimal to Binary\n");
        printf("3. Evaluate Expression\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        switch(option) {
            case 1: {
                char binStr[100];
                printf("Enter a binary number: ");
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
                    printf("Invalid binary number.\n");
                    break;
                }
                double dec = bin_to_dec(binStr);
                printf("Decimal value: %f\n", dec);
                break;
            }
            case 2: {
                double num;
                printf("Enter a decimal number: ");
                scanf("%lf", &num);
                char *bin = dec_to_bin(num);
                printf("Binary value: %s\n", bin);
                free(bin);
                break;
            }
            case 3:
                evaluate_expression();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid option.\n");
        }
        printf("Do you want to perform another operation? (S/N): ");
        scanf(" %c", &another);
    } while (another == 'S' || another == 's');
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
    printf("Select operation:\n");
    printf("1. Addition (+)\n2. Subtraction (-)\n3. Multiplication (*)\n");
    printf("4. Division fracionária (/)\n5. Division inteira (div)\n6. Potência (^)\n");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 6) {
        printf("Invalid choice.\n");
        return;
    }
    double a, b;
    printf("Enter first number: ");
    scanf("%lf", &a);
    printf("Enter second number: ");
    scanf("%lf", &b);
    double result;
    switch(choice) {
        case 1: result = a + b; break;
        case 2: result = a - b; break;
        case 3: result = a * b; break;
        case 4: 
            if (b == 0) { printf("Error: Division by zero.\n"); return; }
            result = a / b; break;
        case 5: 
            if ((int)b == 0) { printf("Error: Division by zero.\n"); return; }
            result = (int)a / (int)b; break;
        case 6: result = pow(a, b); break;
    }
    printf("Result: %lf\n", result);
}