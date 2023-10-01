#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct Arquivo {
    char arquivo[50];
    char pasta[50];
    char pasta2[50];
};

void menuExibicao() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
        printf("\e[8;30;120t");
    #endif

    printf("========================================================================================================================\n");
    printf("\n");
    printf("                                              O que você deseja fazer\n");
    printf("\n");
    printf("                                     [ 1 ] Criar arquivo   |   [ 2 ] Criar pasta\n");
    printf("                                     [ 3 ] Mover arquivo   |   [ 4 ] Mover pasta\n");
    printf("                                     [ 5 ] Deletar arquivo |   [ 6 ] Deletar pasta\n");
    printf("                                                    [ 7 ] Sair\n");
    printf("\n");
    printf("========================================================================================================================\n");
}

void funcFolder2(struct Arquivo *fileStruct) {
    char folderName[100];
    printf("Nome da pasta: ");
    scanf("%s", folderName);

    strcpy(fileStruct->pasta, folderName);
}

void funcFolder(struct Arquivo *fileStruct) {
    char folderName[100];
    printf("Nome da pasta: ");
    scanf("%s", folderName);

    strcpy(fileStruct->pasta, folderName);
}

void funcFile(struct Arquivo *fileStruct) {
    char fileName[100];
    printf("Nome do arquivo: ");
    scanf("%s", fileName);

    strcpy(fileStruct->arquivo, fileName);
}

int main() {
    int escolha;
    struct Arquivo fcf;

    while (1) {
        menuExibicao();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                FILE *arquivo;
                funcFile(&fcf);

                arquivo = fopen(fcf.arquivo, "w"); // Modo de escrita

                if (arquivo != NULL) {
                    fclose(arquivo);
                    printf("[INFO] Arquivo %s foi criado com sucesso.\n", fcf.arquivo);
                    sleep(3);
                } else {
                    printf("[ERRO] Não foi possível criar o arquivo %s.\n", fcf.arquivo);
                }

                break;
            }

           case 2: {
                funcFolder(&fcf);

                if (mkdir(fcf.pasta, 0777) == 0) {
                    printf("[INFO] A pasta %s foi criada com sucesso.\n", fcf.pasta);
                    sleep(3);
                } else {
                    printf("[ERRO] Não foi possível criar a pasta %s.\n", fcf.pasta);
                }

                break;
            }


            case 3: {
                funcFile(&fcf);
                funcFolder(&fcf);
                char comando[120];

                sprintf(comando, "mv %s %s", fcf.arquivo, fcf.pasta);
                int status = system(comando);

                if (status == 0) {
                    printf("[INFO] O arquivo %s foi movido com sucesso para a pasta %s\n", fcf.arquivo, fcf.pasta);
                    sleep(3);
                } else {
                    printf("[ERRO] Não foi possível mover o arquivo %s para a pasta %s\n", fcf.arquivo, fcf.pasta);
                }

                break;
            }


            case 4: {
                funcFolder(&fcf);
                funcFolder2(&fcf)
                char comando[120];

                sprintf(comando, "mv %s %s", fcf.pasta, fcf.pasta2);
                int status = system(comando);

                if (status == 0) {
                    printf("[INFO] O arquivo %s foi movido com sucesso para a pasta %s\n", fcf.arquivo, fcf.pasta);
                    sleep(3);
                } else {
                    printf("[ERRO] Não foi possível mover o arquivo %s para a pasta %s\n", fcf.arquivo, fcf.pasta);
                }

                break;
            }

            case 5: {
                funcFile(&fcf);

                if (remove(fcf.arquivo) == 0) {
                    printf("[INFO] O arquivo %s foi deletado com sucesso.\n", fcf.arquivo);
                    sleep(3);
                } else {
                    printf("[ERRO] Não foi possível deletar o arquivo %s\n", fcf.arquivo);
                }

                break;
            }

            case 6: {
                funcFolder(&fcf);

                if (remove(fcf.pasta) == 0) {
                    printf("[INFO] A pasta %s foi deletado com sucesso", fcf.pasta);
                    sleep(3);
                } else {
                    printf("[ERRO] Não foi possível deletar a pasta %s\n", fcf.pasta);
                }

                break;
            }
            case 7:
                printf("Saindo do programa.\n");
                exit(0);

            default:
                printf("Escolha inválida.\n");
        }
    }

    return 0;
}
