#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "goods.h"
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
int main()
{
    int opc;
    do
    {
        printf("---- MENU ----\n");
        printf("1. Produtos\n");
        printf("2. Vendas\n");
        printf("3. Sair\n");
        printf("--------------\n");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            Produtos();
            break;
        case 2:
            Vendas();
            break;
        case 3:
            printf("\nSaindo do programa...\n");
            return 0;
        default:
            printf("\nOpção inválida! Digite novamente.\n");
            break;
        }
    }
    while (opc < 1 || opc > 3 || opc != 3);
    return 0;
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
