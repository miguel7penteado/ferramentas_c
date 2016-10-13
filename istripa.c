/*
 ============================================================================
 Name        : istripa.c
 Author      : Miguel Suez Xve Penteado
 Version     :
 Copyright   : Isto eh um software livre.
 Description : Formata nomeação de arquivos.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inplace_reverse(char * str)
{
    if (str)
    {
    char * end = str + strlen(str) - 1;

    #define XOR_SWAP(a,b) do\
    {\
    a ^= b;\
    b ^= a;\
    a ^= b;\
    } while (0)

    while (str < end)
    {
        XOR_SWAP(*str, *end);
        str++;
        end--;
    }
    #undef XOR_SWAP
    }
}


int main(int argc, char *argv[])
{
    FILE *fp;
    char estringue_saida[500];
    int tamanho_saida=0;


    int tamanho=0;
    int sequencia=0;
    char entrada[500];
    int contador=0;
    char login[200];
    char maquina[200];
    char data[200];
    char hora[200];
    char data_final[200];
    char municipio[200];
    char agencia[200];

    int contador_login=0;
    int contador_maquina=0;
    int contador_data=0;
    int contador_municipio=0;
    int contador_agencia=0;

        memset(estringue_saida, '\0', sizeof(estringue_saida));
        memset(data_final, '\0', sizeof(data_final));


        memset(login, '\0', sizeof(login));
        memset(maquina, '\0', sizeof(maquina));
        memset(data, '\0', sizeof(data));
        memset(hora, '\0', sizeof(hora));
        memset(municipio, '\0', sizeof(municipio));
        memset(agencia, '\0', sizeof(agencia));

        memset(entrada, '\0', sizeof(entrada));
        strcpy(entrada,argv[1]);
//        printf("\n tamanho da string de entrada é %d \n",(unsigned)strlen(argv[1]));
        tamanho=(unsigned)strlen(argv[1]);
//        tamanho++;
//        entrada[tamanho]= '\n';
//        printf(entrada);

        contador=tamanho;

        while (contador >= 0 )
        {
            if( entrada[contador] != '+' )
            {
                if (sequencia == 0)
                {
                    if (entrada[contador] == '.')
                        goto ALTERA_SEQUENCIA;
                }
                if (sequencia == 1)
                {
                    login[(contador_login)] = entrada[contador];
                    contador_login++;
                }
                if (sequencia == 2)
                {
                    maquina[(contador_maquina)] = entrada[contador];
                    contador_maquina++;
                }
                if (sequencia == 3)
                {
                    data[(contador_data)] = entrada[contador];
                    contador_data++;
                }
                if (sequencia == 4)
                {
                    municipio[(contador_municipio)] = entrada[contador];
                    contador_municipio++;
                }
                if (sequencia == 5)
                {
                    agencia[(contador_agencia)] = entrada[contador];
                    contador_agencia++;
                }
                if (sequencia > 5)
                {
                    //municipio[(contador_municipio)] = entrada[contador];
                    //contador_municipio++;
                    contador=0;
                }


            }
            else
            {

                ALTERA_SEQUENCIA: sequencia++;
            }
            contador--;
        }

        inplace_reverse(login);
        inplace_reverse(maquina);
        inplace_reverse(data);
        inplace_reverse(municipio);
        inplace_reverse(agencia);

        contador=0;
        contador_data=0;
        tamanho_saida=0;
        memset(data_final, '\0', sizeof(data_final));
        tamanho_saida=strlen(estringue_saida);

        if(strlen(data) == 8)
        {
            while(contador <= 9)
            {
                if((contador == 4) ||(contador == 6) )
                {data_final[contador_data]= '-';contador_data++;}

                data_final[contador_data]=data[contador];contador_data++;
                contador++;
            }
            strncpy(hora,"00:00:00",sizeof(hora));
        }
        else
        {
            if(strlen(data) == 12)
            {
                while(contador <= 11)
                {
                    if (contador <= 7)
                    {
                        if((contador == 4) ||(contador == 6) )
                        {data_final[contador_data]= '-';contador_data++;}

                        data_final[contador_data]=data[contador];contador_data++;

                    }
                    else
                    {
                        if (contador == 8) {contador_data = 0;}

                        if((contador == 10) ||(contador == 12) )
                        {hora[contador_data]= ':';contador_data++;}

                        hora[contador_data]=data[contador];contador_data++;

                    }
                    contador++;
                }
                strcat(hora,":00");


            }
            else
            {
                strncpy(data,"00-00-00",sizeof(data));
                strncpy(hora,"00:00:00",sizeof(hora));
            }
        }

        strncpy(data,data_final,sizeof(data));

        setenv("USUARIO", login, 1);
        setenv("MAQUINA", maquina, 1);
        setenv("DATA_IMPORTACAO", data, 1);
        setenv("MUNICIPIO", municipio, 1);
		setenv("AGENCIA", agencia, 1);


        (fp = fopen("saida.txt","w"));

        if ( fp == NULL  )
        {
            printf("\nErro de abertura de arquivo\n");
            exit(1);
        }
        else
        {        fflush(fp);

                contador=0;
                tamanho_saida=0;
                memset(estringue_saida, '\0', sizeof(estringue_saida));
                strncpy(estringue_saida,"USUARIO=",sizeof(estringue_saida));
                strcat(estringue_saida,login);
                estringue_saida[strlen(estringue_saida)] = '\n';
                tamanho_saida=strlen(estringue_saida);
                while(contador <= tamanho_saida)
                {
                    fprintf(fp,"%c",estringue_saida[contador]);
                    contador++;
                }

                contador=0;
                tamanho_saida=0;
                memset(estringue_saida, '\0', sizeof(estringue_saida));
                strncpy(estringue_saida,"MAQUINA=",sizeof(estringue_saida));
                strcat(estringue_saida,maquina);
                estringue_saida[strlen(estringue_saida)] = '\n';
                tamanho_saida=strlen(estringue_saida);
                while(contador <= tamanho_saida)
                {
                    fprintf(fp,"%c",estringue_saida[contador]);
                    contador++;
                }

                contador=0;
                tamanho_saida=0;
                memset(estringue_saida, '\0', sizeof(estringue_saida));
                strncpy(estringue_saida,"DATA_IMPORTACAO=",sizeof(estringue_saida));
                strcat(estringue_saida,data);
                estringue_saida[strlen(estringue_saida)] = '\n';
                tamanho_saida=strlen(estringue_saida);
                while(contador <= tamanho_saida)
                {
                    fprintf(fp,"%c",estringue_saida[contador]);
                    contador++;
                }

                contador=0;
                tamanho_saida=0;
                memset(estringue_saida, '\0', sizeof(estringue_saida));
                strncpy(estringue_saida,"HORA_IMPORTACAO=",sizeof(estringue_saida));
                strcat(estringue_saida,hora);
                estringue_saida[strlen(estringue_saida)] = '\n';
                tamanho_saida=strlen(estringue_saida);
                while(contador <= tamanho_saida)
                {
                    fprintf(fp,"%c",estringue_saida[contador]);
                    contador++;
                }

                contador=0;
                tamanho_saida=0;
                memset(estringue_saida, '\0', sizeof(estringue_saida));
                strncpy(estringue_saida,"MUNICIPIO=",sizeof(estringue_saida));
                strcat(estringue_saida,municipio);
                estringue_saida[strlen(estringue_saida)] = '\n';
                tamanho_saida=strlen(estringue_saida);
                while(contador <= tamanho_saida)
                {
                    fprintf(fp,"%c",estringue_saida[contador]);
                    contador++;
                }

                contador=0;
                tamanho_saida=0;
                memset(estringue_saida, '\0', sizeof(estringue_saida));
                strncpy(estringue_saida,"AGENCIA=",sizeof(estringue_saida));
                strcat(estringue_saida,agencia);
                estringue_saida[strlen(estringue_saida)] = '\n';
                tamanho_saida=strlen(estringue_saida);
                while(contador <= tamanho_saida)
                {
                    fprintf(fp,"%c",estringue_saida[contador]);
                    contador++;
                }
                fclose(fp);
        };

//        memset(estringue_saida, '\0', sizeof(estringue_saida));

    return EXIT_SUCCESS;

}
