#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

void mostra_mc( void *x ){
	Musica *musica = x;
	mostra_musica( *musica );
}

int compara_artista( void *x, void *y ){
    Musica *a = x;
    char *b = y;
    return strcmp(a->artista->nome, b);
}

int compara_nome_musica( void *x, void *y ){
    Musica *a = x;
    char *b = y;
    return strcmp(a->nome, b);
    
}
int compara( void *x, void *y ){
	char *musica_buscada = x;
	char *musica_atual = y;
	int eh_igual;
	
	eh_igual = strcmp(musica_buscada,musica_atual);

	if(eh_igual == 0){
		return 0;
	}

	return 1;
}


int main() {
  
  Playlist p;
  
  inicializa_playlist(&p, sizeof(Playlist *));
  int escolha_usuario = 1000;
    while (escolha_usuario != 0) {
    	system("cls");
	    mostra_menu();
	    scanf(" %i", &escolha_usuario);
	
	    switch (escolha_usuario) {
	        case 1:
	          cadastrar_musica(&p, compara_nome_musica);
	          break;
		    case 2:
			   mostra_playlist(p,mostra_mc); 
			   system("pause");
			   break;
			case 3:
			   busca_musica(p , mostra_mc, &escolha_usuario);
			   system("pause");
			   break;
			case 4:
				busca_musica(p , mostra_mc, &escolha_usuario);
				system("pause");
				break; 
			case 5:
			   busca_musica(p , mostra_mc, &escolha_usuario);
			   system("pause");
			   break;
			case 6:
				remover_musica(&p, mostra_mc );
				system("pause");
				break;
			case 0:
				 salva_arquivo(p);
				
		    default:
			  	printf("Opcao invalida"); 
	    }
 	}
  
  return 0;
}


