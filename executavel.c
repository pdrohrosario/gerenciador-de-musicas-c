#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ERRO_LISTA_VAZIA	-1
#define ERRO_POS_INVALIDA	-2

void validaArquivo(){
	FILE *f = fopen("playlist.txt", "rt");
	if( f == NULL ){
		f = fopen("playlist.txt","wt");
	}
}

void inicializa_lista( Playlist *p, int t ){
	p->lista = NULL;
	p->qtdMusicas = 0;
}

void mostra_menu() {
  printf("\tMENU\n");
  printf("[1] | Cadastrar musica\n");
  printf("[2] | Mostrar musicas\n");
  printf("[3] | Buscar musica pelo nome\n");
  printf("[4] | Buscar musica pelo artista\n");
  printf("[5] | Buscar musica pelo estilo\n");
  printf("[6] | Remover msica\n");
  printf("[0] | Sair do programa\n");

  printf("\nDIGITE SUA ESCOLHA: \n");

}

Musica *aloca_elemento( void *info, int tam ) {
	Musica *p = malloc( sizeof(Musica) );
	if( p == NULL )
		return NULL; // Erro, falta de mem?ria!
	memcpy(p, info, tam);
	return p; // Sucesso!
}
//Musica *aloca_elemento() {
//	Musica *m = malloc( sizeof(Musica *)*2 );
//	if( m == NULL )
//		return NULL; // Erro, falta de mem?ria!

//	return m; // Sucesso!
//}


int playlist_vazia(Playlist p){
	return p.lista == NULL;
}

void inicializa_playlist(Playlist *p, int tam){
	p->tamInfo = tam;
	p->qtdMusicas = 0;
	p->lista = NULL;
}


int cadastrar_musica(Playlist *p, int  (*compara)(void*, void*)){
	
	Musica *novaMusica = malloc(sizeof(Musica));
	
	Artista *novoArtista = malloc(sizeof(Artista));
    Data *novaData = malloc(sizeof(Data));
	
	time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("Digite o nome da musica: ");
    scanf(" %[^\n]", novaMusica->nome);
  
    printf("Digite o duracao da musica: ");
    scanf("%d", &novaMusica->duracao);
  
    printf("Digite o estilo da musica: ");
    scanf(" %[^\n]", novaMusica->estilo);
    
  
    printf("Digite o nome do artista: ");
    scanf(" %[^\n]", novoArtista->nome);
    
    printf("Digite a nacionalidade do artista: ");
    scanf(" %[^\n]", novoArtista->nacionalidade);
		
    novaData->dia = tm.tm_mday;
    novaData->mes = tm.tm_mon + 1;
    novaData->ano = tm.tm_year + 1900;

    novaMusica->artista = novoArtista;
    novaMusica->data = novaData;
    
    
    if(musica_ja_cadastrada(p, novaMusica, compara_nome_musica) == 0){
		insere_ordem(p, novaMusica, compara_nome_musica);
	}
	else{
		printf("Essa musica j� foi cadastrada ...\n");
		cadastrar_musica(p,compara_nome_musica);
	}  
  
}

int musica_ja_cadastrada( Playlist *p, void *info , int (*compara_nome_musica)(void*, void*)){
	Musica *aux = p->lista;
	int cont = 0;

	while( aux != NULL){
		if(compara_nome_musica( info, aux->nome) == 0 && compara_artista(info, aux->artista->nome) == 0){
			cont = 1;
			break;
			
		}
		
		aux = aux->proximo;
	}

	return cont;
}

int inserir_inicio(Playlist *p, Musica *m){
	if( m == NULL )
		return 0; // Erro, falta de mem?ria!

	m->proximo = p->lista;
	p->lista = m;
	p->qtdMusicas++;
	return 1; // Sucesso!
}

void mostra_musica(Musica m){
	printf("\nNome da musica: %s\n",m.nome);
	printf("Duracao: %d\n",m.duracao);
	printf("Estilo: %s\n",m.estilo);
	printf("Nome do artista: %s\n", m.artista->nome);
	printf("Nacionalidade do artista: %s\n",m.artista->nacionalidade);
	printf("Data: %d/%d/%d\n", m.data->dia, m.data->mes, m.data->ano);
}

void mostra_playlist(Playlist p, void (*mostra)(void *) ){

		//printf("Dados da lista (%d elementos):\n", p.qtd );
		Musica *m = p.lista;
		int cont = 0; // cont ? o ?ndice do elemento dentro da lista.
		while( m != NULL ){
			printf("\n[%d] \n", cont);
			mostra(m); // Invoca??o por callback
			m = m->proximo;
			cont++;
		}
		
	printf("\n--------------------------------\n");
}

void busca_musica( Playlist p,void (*mostra)(void *), int *filtro_busca){
	Musica *m = p.lista; 
	char nome[15] = "nome";
	char artista[15] = "artista"; 
	char musica_buscada[30];
	int encontrado=0;
	
		printf("\nDigite o nome da musica buscada: \n");
		scanf(" %[^\n]", musica_buscada);
				
		while( m != NULL ){
			int cmp;
			if((*filtro_busca) == 3){
				cmp=strcmp(m->nome, musica_buscada);
			}
			else if((*filtro_busca) == 4){
				cmp=strcmp(m->artista->nome, musica_buscada);
			}
			else{
				cmp=strcmp(m->estilo, musica_buscada);
			}
			if(cmp==0){
				mostra(m);
				encontrado = 1;		
			}
			m = m->proximo;
		}
		if(encontrado==0)
		 printf("Musica nao encontrada!!\n");
}
int insere_pos( Playlist *p, void *info , int pos ){
	
	
	if( pos < 0 || pos > p->qtdMusicas )
		return ERRO_POS_INVALIDA;
		
	if( pos == 0 )
		return inserir_inicio( p, info );
	
	Musica *aux = p->lista;
	int cont;
	for( cont = 0 ; cont < pos-1 ; cont++ )
		aux = aux->proximo; // Vai at? elemento em pos-1
	
	Musica *novo = info;
	
	novo->proximo = aux->proximo;
	aux->proximo = novo;
	p->qtdMusicas++;
	return 1; // Sucesso!
	
}


int insere_ordem( Playlist *p, void *info , int (*compara_nome_musica)(void*, void*)){
	Musica *aux = p->lista;
	int cont = 0;

	while( aux != NULL && compara_nome_musica( info, aux->nome) > 0){
		aux = aux->proximo;
		cont++;
	}

	return insere_pos( p, info, cont );
}

//void busca_musica( Playlist *p , int (*compara)(void*, void*) ){
	
//	Playlist musicas_encontradas;
	
//	inicializa_playlist(&musicas_encontradas, sizeof(Playlist));
	
//	char musica_buscada[30];
	
//	printf("\nDigite o nome da musica buscada: \n");
//	scanf(" %[^\n]", musica_buscada);
	
//	Musica *aux = p->lista;
//	int cont=0;
	
//	while(aux != NULL ){
//		if(compara( musica_buscada, aux->nome ) != 0 ){
//			aux = aux->proximo;		
//		}
//		else{
//			printf("Encontrado!\n");
//			int i = inserir_inicio(&musicas_encontradas,*aux);
//			aux = aux->proximo;
//		}cont++;
//	}
	
//	mostra_playlist(musicas_encontradas, mostra_mc);
//}

/*
void iniciaALeita(){
	printf("Deseja carregar os produtos do arquivo (s/n)? ");
	scanf("%c", &resp);
	
	if(resp != NULL){
		if( resp == 's'){
			int n;
	    	FILE *f = fopen("playlist.txt", "rt");
	    	//cen?rio arquivo em branco
			fscanf(f, "%d", &n);
			p = malloc( sizeof(struct Playlist) * n );
			
			for( i = 0 ; i < n ; i++ ){
				char nomeMusica[30];
				int duracao;
				char estilo[20];
				char nomeArtista[30];
				char nacionalidade[30];
				int dia;
				int mes;
				int ano;
				
				fscanf(f, "%s", &nomeMusica);
				fscanf(f, "%d", &duracao);
				fscanf(f, "%s", &estilo);
				fscanf(f, "%s", &nomeArtista);
				fscanf(f, "%d", &dia);
				fscanf(f, "%d", &mes);
				fscanf(f, "%d", &ano);
				
				carregarMusicaArquivo(p, nomeMusica, duracao, estilo, nomeArtista, dia, mes, ano);
			}
			fclose( f );
		}
		else{
			insereMusica(p,info);
			scanf("%d", &n);	
			v = malloc( sizeof(struct Produto) * n );
			for( i = 0 ; i < n ; i++ ){
				printf("Produto %d:\n", i+1);
				le_produto( &v[i] );
			}
		}
	}
}
*/


