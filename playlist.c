#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 100

/* Declaração de estruturas */
typedef struct{
    int min;
    int seg;
} TTempo; // Struct tempo

typedef struct{
    char *titulo;
    char **artista;
    char *album;
    char **genero;
    int  num_artista;
    int  num_genero;
    TTempo duracao;
} TMusica; // Struct musica

/* Declaração de funções */
void menu(); // Exibe o menu
void op_menu(int option); // Executa a escolha do usuario
void op_listar(); // Dispara a opção para listar as musicas
void listarMusica(); // Exibe a playlist
void exibeMusica(TMusica playlist); // Exibe uma musica
void incluirMusica(); // Dispara a função de criar musica
TMusica criarMusica(); // Cria uma musica e adciona a playlist
void alterar_musica(); // Altera uma musica
int op_alterar(int op, int indice); // Dispara a opção de alteração
void alterar_artista(int indice); // Altera o artista
void alterar_genero(int indice); // Altera o genero
void excluir_musica(); // Exclui uma musica
int validarTempo(int min, int seg); // Valida o tempo
void limparMemoria(); // Limpa a memória alocada
void limparMusica(TMusica *music); // Limpa a memória das músicas
void valida_alocacao(void *v); // Valida a alocação de memória

TMusica *_playList;
int _numMusicas = 0;

int main(){
    int op;
    do{
        menu();

        printf("** Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        op_menu(op);
    } while(op != 0);

    limparMemoria();
    return 0;
}

void menu(){
    system("cls");
    printf("- (1) Incluir musica\n");
    printf("- (2) Listar musicas\n");
    printf("- (3) Alterar musica\n");
    printf("- (4) Excluir musica\n");
    printf("- (0) Sair\n\n");
}

void op_menu(int option){
    switch(option){
    case 1:
        incluirMusica();
        break;
    case 2:
        op_listar();
        break;
    case 3:
        alterar_musica();
        break;
    case 4:
        excluir_musica();
        break;
    case 0:
        printf("Saindo...");
        break;
    default:
        printf("**ERRO! Opcao invalida!!!**");
        break;
    }
}

void excluir_musica(){
    int indice;
    char opSn = 'x';

    if(_numMusicas == 0){
        printf("**Nao ha musicas na playlist!!!**\n");
        system("pause");
        return;
    }

    if(_numMusicas > 1){
        listarMusica();
        printf("** Qual musica deseja excluir [%d-%d]? ", 1, _numMusicas);
        scanf("%d", &indice);
        fflush(stdin);
    } else{
        indice = 1;
    }
    system("cls");

    indice--;
    printf("*** Musica [%d] ***\n", indice + 1);
    exibeMusica(_playList[indice]);
    while(opSn != 's' && opSn != 'n'){
        printf("Confirma a exclusao da musica [%d] (S/N)? ", indice+1);
        scanf("%c", &opSn);
        opSn = tolower(opSn);

        if(opSn != 's' && opSn != 'n'){
            printf("**Erro! Opcao invalida!**\n\n");
            continue;
        }

        if(opSn == 's'){
            if(indice >= 1 && indice <= _numMusicas){
                for(int i = indice - 1; i < _numMusicas - 1; i++){
                    _playList[i] = _playList[i + 1];
                }
                _numMusicas--;
                _playList = (TMusica*)realloc(_playList, _numMusicas * sizeof(TMusica));
                system("cls");
                printf("Musica exluida com sucesso!\n\n");
            } else{
                printf("**Musica inexistente!**\n");
                return;
            }
            system("pause");
        } else{
            return;
        }
    }
}

void op_listar(){
    int indice, op;

    if(_numMusicas <= 0){
        printf("***Nao ha musicas na playlist***\n");
        system("pause");
        return;
    }

    if(_numMusicas == 1){
        exibeMusica(_playList[0]);
        system("pause");
        return;
    }

    printf("- (1) Exibir TODAS as musicas\n");
    printf("- (2) Exibir APENAS UMA musica\n");
    printf("- (3) Voltar para o menu anterior\n\n");
    printf("** Digite a opcao: ");
    scanf("%d", &op);
    system("cls");

    if(op == 1){
        listarMusica();
    } else if(op == 2){
        do{
            printf("Qual musica deseja exibir [%d-%d]: ", 1, _numMusicas);
            scanf("%d", &indice);
            if(indice <= _numMusicas && indice >= 1){
                system("cls");
                printf("*** Musica [%d] ***\n", indice);
                exibeMusica(_playList[indice - 1]);
            } else{
                printf("***MUSICA INVALIDA***\n\n");
            }
        } while(indice > _numMusicas || indice < 1);
    } else if(op == 3){
        return;
    }else{
        printf("***MUSICA INVALIDA***\n\n");
    }

    system("pause");
}

void listarMusica(){
    for(int i = 0; i < _numMusicas; i++){
        printf("*** Musica [%d] ***\n", i+1);
        exibeMusica(_playList[i]);
    }
}

void exibeMusica(TMusica playList){
    if(_numMusicas <= 0){
        printf("***Nao ha musicas na playlist!!!***\n");
        system("pause");
        return;
    }

    printf("- Titulo: %s\n", playList.titulo);
    printf("- Album: %s\n", playList.album);

    printf("- Artista: ");
    for(int i = 0; i < playList.num_artista; i++){
        if(i < (playList.num_artista - 1)){
            printf("%s, ", playList.artista[i]);
        } else{
            printf("%s\n", playList.artista[i]);
        }
    }

    printf("- Genero: ");
    for(int i = 0; i < playList.num_genero; i++){
        if(i < (playList.num_genero - 1)){
            printf("%s, ", playList.genero[i]);
        } else{
            printf("%s\n", playList.genero[i]);
        }
    }

    printf("- Duracao: %d:%d\n\n", playList.duracao.min, playList.duracao.seg);
}

void incluirMusica(){
    if(_numMusicas == 0){
        _playList = (TMusica *)malloc(1 * sizeof(TMusica));
    }
    else{
        _playList = (TMusica *)realloc(_playList, (_numMusicas + 1) * sizeof(TMusica));
    }
    valida_alocacao(&_playList[_numMusicas]);
    _playList[_numMusicas] = criarMusica();
    _numMusicas++;
}

TMusica criarMusica(){
    TMusica musica;
    char strAux[100], opSn;

    printf("- Titulo: ");
    gets(strAux);
    musica.titulo = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    valida_alocacao(musica.titulo);
    strcpy(musica.titulo, strAux);

    printf("- Album: ");
    gets(strAux);
    musica.album = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    valida_alocacao(musica.album);
    strcpy(musica.album, strAux);

    musica.num_artista = 0;
    while(1){
        printf("- Autor: ");
        gets(strAux);      

        if(musica.num_artista == 0){
            musica.artista = (char**)malloc(1 * sizeof(char*));
        } else{
            musica.artista = (char**)realloc(musica.artista, (musica.num_artista + 1) * sizeof(char*));
        }
        valida_alocacao(musica.artista);

        musica.artista[musica.num_artista] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(musica.artista[musica.num_artista], strAux);
        valida_alocacao(musica.artista[musica.num_artista]);
        musica.num_artista++;

        do{
            printf("** Deseja adcionar mais um artista (S/N)? ");
            scanf("%c", &opSn);
            fflush(stdin);
            opSn = tolower(opSn);

            if(opSn != 's' && opSn != 'n'){
                printf("**Erro! Opcao inexistente!**\n\n");
            }

            printf("\n");
        } while(opSn != 's' && opSn != 'n');

        if(opSn == 'N' || opSn == 'n'){
            break;
        }
    }

    musica.num_genero = 0;
    while(1){
        printf("- Genero: ");
        gets(strAux);

        if(musica.num_genero == 0){
            musica.genero = (char**)malloc(1 * sizeof(char*));
        } else{
            musica.genero = (char**)realloc(musica.genero, (musica.num_genero + 1) * sizeof(char*));
        }
        valida_alocacao(musica.genero);

        musica.genero[musica.num_genero] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(musica.genero[musica.num_genero], strAux);
        valida_alocacao(musica.genero[musica.num_genero]);
        musica.num_genero++;

        do{
            printf("** Deseja adcionar mais um genero (S/N)? ");
            scanf("%c", &opSn);
            fflush(stdin);
            opSn = tolower(opSn);

            if(opSn != 's' && opSn != 'n'){
                printf("**Erro! Opcao inexistente!**\n\n");
            }

            printf("\n");
        } while(opSn != 's' && opSn != 'n');

        if(opSn == 'N' || opSn == 'n'){
            break;
        }
    }

    do{
        printf("- Tempo (Min/Seg): ");
        scanf("%d%d", &musica.duracao.min, &musica.duracao.seg);
        fflush(stdin);
    } while(validarTempo(musica.duracao.min, musica.duracao.seg) == 0);

    return musica;
}

void alterar_musica(){
    int indice, op, aux;

    if(_numMusicas == 0){
        printf("***Nao ha musicas na playlist!!!***\n");
        system("pause");
        return;
    }

    if(_numMusicas > 1){
        do{
            listarMusica();
            printf("** Digite o numero da musica a ser alterada [%d-%d]: ", 1, _numMusicas);
            scanf("%d", &indice);
            fflush(stdin);

            if(indice < 1 || indice > _numMusicas){
                printf("**Numero invalido!**\n");
                system("pause");
            }
            system("cls");
        } while(indice < 1 || indice > _numMusicas);
    } else{
        indice = 1;
    }
    indice--;

    printf("*** Musica [%d] ***\n", indice + 1);
    exibeMusica(_playList[indice]);

    printf("Digite o atributo a alterar\n");
    printf("- (1) Titulo\n");
    printf("- (2) Album\n");
    printf("- (3) Artista\n");
    printf("- (4) Genero\n");
    printf("- (5) Duracao\n");
    printf("- (0) Voltar ao menu inicial\n\n");
    printf("** Digite a opcao: ");
    scanf("%d", &op);
    fflush(stdin);
    system("cls");

    aux = op_alterar(op, indice);

    if(aux == 1){
        printf("\nMusica alterada com sucesso!\n");
        system("pause");
    } else{
        return;
    }
}

int op_alterar(int op, int indice){
    char strAux[100];

    printf("***Musica [%d]***\n", indice+1);
    switch(op){
    case 0:
        return -1;
        break;
    case 1:
        printf("- Titulo: %s\n\n", _playList[indice].titulo);
        printf("Digite o novo titulo da musica: ");
        gets(strAux);
        _playList[indice].titulo = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        valida_alocacao(_playList[indice].titulo);
        strcpy(_playList[indice].titulo, strAux);
        fflush(stdin);
        break;
    case 2:
        printf("- Album: %s\n\n", _playList[indice].album);
        printf("Digite o novo album da musica: ");
        gets(strAux);
        _playList[indice].album = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        valida_alocacao(_playList[indice].album);
        strcpy(_playList[indice].album, strAux);
        fflush(stdin);
        break;
    case 3:
        printf("- Artista: ");
        for(int i = 0; i < _playList[indice].num_artista; i++){
            if(i < (_playList[indice].num_artista - 1)){
                printf("%s, ", _playList[indice].artista[i]);
            } else{
                printf("%s\n\n", _playList[indice].artista[i]);
            }
        }
        alterar_artista(indice);
        break;
    case 4:
        printf("- Genero: ");
        for(int i = 0; i < _playList[indice].num_genero; i++){
            if(i < (_playList[indice].num_genero - 1)){
                printf("%s, ", _playList[indice].genero[i]);
            } else{
                printf("%s\n\n", _playList[indice].genero[i]);
            }
        }
        alterar_genero(indice);
        break;
    case 5:
        printf("- Duracao: %d:%d\n\n", _playList[indice].duracao.min, _playList[indice].duracao.seg);
        do{
            printf("Digite a nova duracao da musica: ");
            scanf("%d%d", &_playList[indice].duracao.min, &_playList[indice].duracao.seg);
            fflush(stdin);
        } while(validarTempo(_playList[indice].duracao.min, _playList[indice].duracao.seg) == 0);
        break;
    default:
        printf("**Opcao invalida!**\n");
        system("pause");
        return -1;
    }

    return 1;
}

void alterar_artista(int indice){
    char strAux[100], opSn;

    _playList[indice].num_artista = 0;
    while(1){
        printf("Digite o novo artista: ");
        gets(strAux);

        if(_playList[indice].num_artista == 0){
            _playList[indice].artista = (char**)malloc(1 * sizeof(char*));
        } else{
            _playList[indice].artista = (char**)realloc(_playList[indice].artista, (_playList[indice].num_artista + 1) * sizeof(char*));
        }
        valida_alocacao(_playList[indice].artista);

        _playList[indice].artista[_playList[indice].num_artista] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_playList[indice].artista[_playList[indice].num_artista], strAux);
        valida_alocacao(_playList[indice].artista[_playList[indice].num_artista]);
        _playList[indice].num_artista++;

        do{
            printf("** Deseja adcionar mais um artista (S/N)? ");
            scanf("%c", &opSn);
            fflush(stdin);
            opSn = tolower(opSn);

            if(opSn != 's' && opSn != 'n'){
                printf("**Erro! Opcao inexistente!**\n\n");
            }

            printf("\n");
        } while(opSn != 's' && opSn != 'n');

        if(opSn == 'N' || opSn == 'n'){
            break;
        }
    }
}

void alterar_genero(int indice){
    char strAux[100], opSn;

    _playList[indice].num_genero = 0;
    while(1){
        printf("Digite o novo genero: ");
        gets(strAux);

        if(_playList[indice].num_genero == 0){
            _playList[indice].genero = (char**)malloc(1 * sizeof(char*));
        } else{
            _playList[indice].genero = (char**)realloc(_playList[indice].genero, (_playList[indice].num_genero + 1) * sizeof(char*));
        }
        valida_alocacao(_playList[indice].genero);

        _playList[indice].genero[_playList[indice].num_genero] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_playList[indice].genero[_playList[indice].num_genero], strAux);
        valida_alocacao(_playList[indice].genero[_playList[indice].num_genero]);
        _playList[indice].num_genero++;

        do{
            printf("** Deseja adcionar mais um genero (S/N)? ");
            scanf("%c", &opSn);
            fflush(stdin);
            opSn = tolower(opSn);

            if(opSn != 's' && opSn != 'n'){
                printf("**Erro! Opcao inexistente!**\n\n");
            }

            printf("\n");
        } while(opSn != 's' && opSn != 'n');

        if(opSn == 'N' || opSn == 'n'){
            break;
        }
    }
}

int validarTempo(int min, int seg){
    int x = 1;

    if(min < 0){
        printf("**Erro ao inserir duracao!**\n\n");
        x = 0;
    } else if(seg >= 60 || seg < 0){
        printf("**Erro ao inserir duracao!**\n\n");
        x = 0;
    } else if(seg == 0 && min == 0){
        printf("**Erro ao inserir duracao!**\n\n");
        x = 0;
    }

    return x;
}

void limparMemoria(){
    for(int i = 0; i < _numMusicas; i++){
        limparMusica(&_playList[i]);
    }
    free(_playList);
}

void limparMusica(TMusica *music){
    free(music->titulo);
    free(music->album);
    for(int i = 0; i < music->num_artista; i++){
        free(music->artista[i]);
    }
    free(music->artista);
    
    for(int i = 0; i < music->num_genero; i++){
        free(music->genero[i]);
    }
    free(music->genero);
}

void valida_alocacao(void *v){
    if(!v){
        printf("***ERRO AO ALOCAR MEMORIA!!!***\n");
        exit(1);
    }
}