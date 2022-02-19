// Constantes de erro
#define ERRO_LISTA_VAZIA	-1
#define ERRO_POS_INVALIDA	-2
#define NOME_DO_ARQUIVO "playlist"

typedef struct {
	char nome[30];
	char nacionalidade[20];
} Artista;

typedef struct {
	int dia;
	int mes;
	int ano;
} Data;


// Elemento de lista
typedef struct ele {
	struct ele *proximo;
	char nome[30];
	int duracao;
	char estilo[20];
	Artista *artista;
	Data *data;
} Musica;


// Cabe?alho de lista
typedef struct {
	Musica *lista;
	int tamInfo;
	int qtdMusicas;
} Playlist;


void carrega_musicas_arq(Playlist *p,int  (*compara_nome_musica)(void*, void*));
int valida_arquivo();
int cadastrar_musica( Playlist *p, int  (*compara_nome_musica)(void*, void*));
void exibe_menu();
void mostraPlaylist( Playlist p);
int playlistVazia(Playlist p);
void mostraMusica(Musica m, int nrMusica);
void mostra_playlist(Playlist  m, void(*mostra)(void *));
void busca_musica( Playlist p , void (*mostra)(void *), int *filtro_busca );
void inicializa_playlist( Playlist *p, int tam);
int inserir_inicio(Playlist *p, Musica *m);
void mostra_mc( void *x );
int insere_ordem( Playlist *p, void *info , int (*compara_nome_musica)(void*, void*) );
int insere_pos( Playlist *p, void *info , int pos );
Playlist busca_varios(Playlist p, void *info, int  (*compara)(void*, void*) );
int compara_artista( void *x, void *y );
int musica_ja_cadastrada( Playlist *p, void *info , int (*compara_nome_musica)(void*, void*));
int compara_nome_musica( void *x, void *y );
void remover_musica(Playlist *p, void (*mostra)(void *));
void salva_arquivo(Playlist p);
