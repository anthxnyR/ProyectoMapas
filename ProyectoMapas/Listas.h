#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED
#include "JIC2.h"

//Funcion para quitar espacios en blanco, se usa muchas veces en el programa.
void RemoveBlanks (char *str){
    char straux[strlen(str)];
    int i=0,j=0;
    while(str[i]!='\0'){
        if(!(str[i]==' ')){
            straux[j] = str[i];
            j++;
        }
        i++;
    }
    if(straux[j-1]=='\n')
        straux[j-1]='\0';
    else straux[j]='\0';
    strcpy(str,straux);
}

//Verifica si el Lugar Existe
int Existe(char str[], Lugares *places){
    while(places){
        if(strcmp(places->Name,str)==0) return 1;
        places=places->Next;
    }
    return 0;
}

//Verifica la longitud de la cadena
int checklen(char str[]){
    int cont=0;
    for(int i=0;str[i]!='\0';i++)
        cont++;
    return cont;
}

//Verifica si el Texto cumple con los caracteres debidos (alfanumericos y '_')
int VerificarTxt(char str[]){
    int len=checklen(str);
    for(int i=0;i<len;i++)
        if(!isalnum(str[i]) && str[i]!='_')
            return 0;
    return 1;
}


// ************************ VERIFICAR ENTRADA DE CLIMA ****************************

void CambioClima(Camino *path,float P,float B,float C,char name[]){
    if(path==NULL) return;
    for(;path;path=path->Next){
        if(strcmp(path->Name,name)==0){
            path->Peso[0]=path->Peso[0]*P;
            path->Peso[1]=path->Peso[1]*B;
            path->Peso[2]=path->Peso[2]*C;
        }
    }
}

char MakeStringClima(char name[],char cP[6],char cB[6], char cC[6],char stringcompare[]){
    strcat(stringcompare,name);
    strcat(stringcompare,"=P:");
    strcat(stringcompare,cP);
    strcat(stringcompare,";B:");
    strcat(stringcompare,cB);
    strcat(stringcompare,";C:");
    strcat(stringcompare,cC);
    return *stringcompare;
}

int CheckCharClima(char str[]){
    int semcol=0,col=0,eq=0;
    for(int i=0;i<checklen(str);i++){
        switch(str[i]){
            case ';':
                semcol++;
                break;
            case ':':
                col++;
                break;
            case '=':
                eq++;
                break;
        }
    }
    if(semcol==2 && col==3 && eq==1)
            return 1;
    else return 0;
}

//Funcion para eliminar una cadena hasta un caracter dado.
void DeleteChar(char str[],char const delim){
    int i;
    for(i=0;str[i]!=delim;i++){
        str[i]=' ';
    }
    str[i]=' ';
    RemoveBlanks(str);
    return;
}

int ObtainData(char ogstr[]){
    char str[100],str_aux[100],nombre[50],num,comp[100],cP[6],cB[6],cC[6];
    float P,B,C;
    if(!CheckCharClima(ogstr)) return 0;
    comp[0]='\0';
    strcpy(str,ogstr);
    strcpy(str_aux,str);

    strtok(str_aux,"=");
    strcpy(nombre,str_aux);
    DeleteChar(str,'=');
    strcpy(str_aux,str);

    int i=0;
    while(i<3){
        strtok(str_aux,":");
        num=str_aux[0];
        switch(num){
            case 'P':
                DeleteChar(str,':');
                strcpy(str_aux,str);
                strtok(str_aux,";");
                strcpy(cP,str_aux);
                P=atof(str_aux);
                DeleteChar(str,';');
                strcpy(str_aux,str);
                i++;
                break;

            case 'B':
                DeleteChar(str,':');
                strcpy(str_aux,str);
                strtok(str_aux,";");
                strcpy(cB,str_aux);
                B=atof(str_aux);
                DeleteChar(str,';');
                strcpy(str_aux,str);
                i++;
                break;

            case 'C':
                DeleteChar(str,':');
                strcpy(cC,str);
                C=atof(str);
                i++;
                break;
        }
    }
    MakeStringClima(nombre,cP,cB,cC,comp);
    if(strcasecmp(ogstr,comp)==0)
        return 1;
    else return 0;
}

int VerifyTxtClima(char namefile[]){
    FILE *archivo=NULL;
    char str[100];
    archivo=fopen(namefile,"r");

    while(!feof(archivo)){
        fgets(str,100,archivo);
        RemoveBlanks(str);
        if(strlen(str)>1)
            if(!CheckCharClima(str)){
                printf("\n\n\t\tERROR: FORMATO NO VALIDO\n");
                printf("EN LA SIGUIENTE ENTRADA: %s\n",str);
                fclose(archivo);
                return 0;
            }

    }
    fclose(archivo);
    return 1;
}

// ************************* FIN DE VERIFICACION DE CLIMA *****************

//Se verifican que todos los caracteres que componen el formato de ruta existan
int CheckChars(char str[]){
    int guion=0,flecha=0,semcol=0,col=0,eq=0;
    for(int i=0;i<checklen(str);i++){
        switch(str[i]){
            case '-':
                guion++;
                break;
            case '>':
                flecha++;
                break;
            case ';':
                semcol++;
                break;
            case ':':
                col++;
                break;
            case '=':
                eq++;
                break;
        }
    }
    if(guion==1 && flecha==1 && semcol==2 && col==4 && eq==1)
        return 1;
    else return 0;
}


//Esta funcion arma un formato adecuado que despues se comparara con el string dado
char MakeString(char Name[],char Origen[],char Destino[],char cP[6], char cB[6], char cC[6],char stringcompare[]){
    strcat(stringcompare,Name);
    strcat(stringcompare,"->");
    strcat(stringcompare,Origen);
    strcat(stringcompare,":");
    strcat(stringcompare,Destino);
    strcat(stringcompare,"=P:");
    strcat(stringcompare,cP);
    strcat(stringcompare,";B:");
    strcat(stringcompare,cB);
    strcat(stringcompare,";C:");
    strcat(stringcompare,cC);
    return *stringcompare;
}

//Lee la ruta y la Almacena en Memoria
Camino *LeerRuta(char ogstr[], Lugares *Mapa, Camino *path){
    char Nombre[50],Origen[50],Dest[50],num,cP[6],cB[6],cC[6];
    char str_aux[100],str[100],comp[100];
    float P,B,C;
    comp[0]='\0';
    if(!CheckChars(ogstr)){                         //A partir de esta funcion se verifica el formato de Ruta
        printf("\n\t\tERROR: FORMATO NO VALIDO\n");
        return NULL;
    }
    strcpy(str,ogstr);
    strcpy(str_aux,str);

    strtok(str_aux,"->");
    strcpy(Nombre,str_aux);
    DeleteChar(str,'>');
    strcpy(str_aux,str);

    strtok(str_aux,":");
    strcpy(Origen,str_aux);
    DeleteChar(str,':');
    strcpy(str_aux,str);

    strtok(str_aux,"=");
    strcpy(Dest,str_aux);
    DeleteChar(str,'=');
    strcpy(str_aux,str);

    int i=0;
    while(i<3){
        strtok(str_aux,":");
        num=str_aux[0];
        switch(num){
            case 'P':
                DeleteChar(str,':');
                strcpy(str_aux,str);
                strtok(str_aux,";");
                strcpy(cP,str_aux);
                P=atof(str_aux);
                DeleteChar(str,';');
                strcpy(str_aux,str);
                i++;
                break;

            case 'B':
                DeleteChar(str,':');
                strcpy(str_aux,str);
                strtok(str_aux,";");
                strcpy(cB,str_aux);
                B=atof(str_aux);
                DeleteChar(str,';');
                strcpy(str_aux,str);
                i++;
                break;

            case 'C':
                DeleteChar(str,':');
                strcpy(cC,str);
                C=atof(str);
                i++;
                break;
        }
    }
    MakeString(Nombre,Origen,Dest,cP,cB,cC,comp);
    if(strcmp(comp,ogstr)!=0){
        printf("\n\t\tERROR: FORMATO NO VALIDO!\n");
        return NULL;
    }
    comp[0]='\0';
    path=AddCamino(CaminoNuevo(Nombre,P,B,C),Origen,Dest,Mapa,path);
    if(!path) return NULL;
    return path;

}

#endif // LISTAS_H_INCLUDED
