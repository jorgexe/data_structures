#include "Customlib.h"


void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

//captura_cadena(1,"\n\r Captura cadena: ",&cadena,&tam);
void captura_cadena(int p_min_size,char *string_indicacion,char **cadena,int *p_size)
{
    int flag_captura,i,length=0;
    char temp_array[MAX_SIZE];
    char c;
    printf("%s",string_indicacion);
    fflush(stdin);
    fflush(stdin);
        for(i=0;i<MAX_SIZE;i++)
        {
            flag_captura=0;
            do{
                fflush(stdin);
                c=_getch();
                if(c==3)
                {
                    exit(0);
                    return;
                }
                if((isalpha(c)))
                {
                    temp_array[i]=c;
                    printf("%c",temp_array[i]);
                    length++;
                    flag_captura=1;
                }
                if(c==32){
                    temp_array[i]=c;
                    printf("%c",temp_array[i]);
                    length++;
                    flag_captura=1;
                }
                fflush(stdin);
                if(c=='\b')
                {
                    if(i>0)
                    {
                        temp_array[i-1]='\0';
                        printf("\b");
                        printf(" ");
                        printf("\b");
                        i=i-2;
                        length--;
                        flag_captura=1;
                    }
                }
                fflush(stdin);
                if(c=='\r')
                {
                    if(i>=p_min_size)
                    {
                        temp_array[i]='\0';
                        length++;
                        flag_captura=1;
                        i=1000;
                    }
                }
                fflush(stdin);
            }while(flag_captura!=1);
        }
        fflush(stdin);
        char *tmp= malloc((length)*sizeof(char*));
        *cadena=tmp;
        for(i=0;i<length;i++)
        {
            (*cadena)[i]=temp_array[i];// De un arreglo parcialmente llenado, lo guarda a un arreglo definido
        }
        *p_size=length;
}



void captura_int(int p_min,int p_max,char *string_indicacion,int *p_entero)
{
    int flag_captura,i,length=0;
    char temp_array[MAX_SIZE];
    char c;
    printf("%s",string_indicacion);
    fflush(stdin);
        for(i=0;i<MAX_SIZE;i++)
        {
            flag_captura=0;
            do{
                fflush(stdin);
                c=_getch();
                if(c==3)
                {
                    exit(0);
                    return;
                }
                if((isdigit(c)) && length<p_max)
                {
                    temp_array[i]=c;
                    printf("%c",temp_array[i]);
                    flag_captura=1;
                    length++;
                }
                fflush(stdin);
                if(c=='\b')
                {
                    if(i>0)
                    {
                        temp_array[i-1]='\0';
                        printf("\b");
                        printf(" ");
                        printf("\b");
                        i=i-2;
                        length--;
                        flag_captura=1;
                    }
                }
                fflush(stdin);
                if(c=='\r')
                {
                    if(i>=p_min)
                    {
                        temp_array[i]='\0';
                        length++;
                        i=1000;
                        flag_captura=1;
                    }
                }
                fflush(stdin);
            }while(flag_captura!=1);
        }
        sscanf(temp_array,"%d",p_entero);
        fflush(stdin);
}


void esperar_enter(void)
{
    char c;
    int espera=1;
    printf("\n\r PRESIONA ENTER PARA CONTINUAR...");
    while(espera)
    {
        fflush(stdin);
        c=_getch();
        if(c==3)
        {
            espera=0;
            exit(0);
            return;
        }
        if(c=='\r')
        {
            espera=0;
        }
    }
}


void display_options(Cadenas *opciones)
{
    int i;
    for(i=0;i<CANTIDAD_OPCIONES;i++)
    {
        gotoxy(0,i+4);
        printf("[%d] %s",i,opciones[i].cadena);
    }
}