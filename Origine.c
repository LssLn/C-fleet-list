/*
Sviluppo di applicazione in ANSI C per gestire i viaggi di una flotta aziendale di veicoli

In un archivio memorizzato su un file di testo (allegato "viaggi.txt") è memorizzato
l'elenco dei viaggi effettuati dai diversi veicoli.
Ogni viaggio è memorizzato su una riga del file, con i campi: id viaggio, targa veicolo,
km percorsi, costo viaggio.

Implementare le seguenti funzioni:

1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file) in una lista di viaggi.
2. AggiungiViaggio: dato un id viaggio, km e costo, se l'id esiste già in lista si sommano ai valori già presenti in lista, in caso contrario inserisce un nuovo viaggio nella lista (fornendo da tastiera in tal caso anche la targa)
3. Data una targa, stampa il totale dei km percorsi ed il costo medio per km di tutti i viaggi ad essa associati

*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "elenco.txt"

typedef struct Viaggio
{
	char  id_viaggio[5]; //4+\0
	char  targa[9];		 //8+\0
	int   km;
	float costo;
} TViaggio;

typedef struct NodoLista
{
	TViaggio viaggio;
	struct NodoLista* succ;
} TNodoLista;

typedef TNodoLista* PNodoLista;

/* ListaAggiungi inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int ListaAggiungi(PNodoLista* plista, TViaggio viaggio){
	PNodoLista aux;
	aux = (PNodoLista)malloc(sizeof(TNodoLista));
	if (aux == 0)
		return 0;
	aux->viaggio = viaggio;
	aux->succ = *plista;
	*plista = aux;
	return 1;
}

/*
1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; 
	ogni id viaggio è presente solo una volta nel file) in una lista di viaggi
  Restituisce 1 se l'operazione va a buon fine, 0    altrimenti.
*/
int CaricaViaggi(PNodoLista* plista, char* nome_file){
	FILE* f;
	TViaggio v;
	int cont = 0;

	f = fopen(nome_file, "r");
	if (f == NULL) return 0;
	while (fscanf(f, "%s%s%d%f", v.id_viaggio, v.targa, &v.km, &v.costo) == 4) {
		ListaAggiungi(plista, v);
		cont++;
	}
	fclose(f);
	return cont;
}

/*
 2. AggiungiViaggio: dato un id viaggio, km e costo, se l'id esiste già in lista si sommano ai valori già presenti in lista,
	in caso contrario inserisce un nuovo viaggio nella lista (fornendo da tastiera in tal caso la targa)
*/
void AggiungiViaggio(PNodoLista* lista,char* id_viaggio, int km, float costo){
	TViaggio v;
	PNodoLista aux; //non malloc perchè copia lista 
	aux = *lista;
	//while (*lista != NULL) {
	//	if (strcmp((*lista)->viaggio.id_viaggio, id_viaggio) == 0) { //il viaggio già esiste, aggiorno km e costi
	//		(*lista)->viaggio.km = (*lista)->viaggio.km + km;
	//		(*lista)->viaggio.costo = (*lista)->viaggio.costo + costo;
	//		return NULL;
	//	}
	//	*lista = (*lista)->succ;
	//}

	while (aux != NULL) {//il viaggio già esiste, aggiorno km e costi
		if (strcmp((aux)->viaggio.id_viaggio, id_viaggio) == 0) { 
			aux->viaggio.km = (aux)->viaggio.km + km;
			(aux)->viaggio.costo = (aux)->viaggio.costo + costo;
			return NULL;
			}
		aux=aux->succ;
	}
	//caso in cui non sono entrato nel primo ciclo while aka id nuovo
	printf("Inserire targa per il nuovo elemento : ");
	scanf("%s", v.targa);
	strcpy(v.id_viaggio, id_viaggio);
	v.km = km;
	v.costo = costo;
	ListaAggiungi(lista, v);
}

/*
3. Data una targa, stampa il totale dei km percorsi ed il costo medio per km di tutti i viaggi ad essa associati
*/
void TotaleVeicolo(PNodoLista lista,char* targa, float* totkm, float* costomedio){
	// ... da completare a cura dello studente ...
	*totkm = 0.0;
	*costomedio = 0.0;
	int cont = 0;

	while (lista != NULL) {
		if (strcmp(lista->viaggio.targa, targa) == 0) {
			*totkm = *totkm + lista->viaggio.km;
			*costomedio = *costomedio + lista->viaggio.costo;
			cont++;
		}
		lista = lista->succ;
	}
	*costomedio = (float)*costomedio / *totkm;
}



int Menu(){
	int scelta;

	printf("*** M E N U ***\n"
		"1 - CaricaViaggi\n"
		"2 - AggiungiViaggio\n"
		"3 - TotaleVeicolo\n"
		"4 - Stampa\n"
		"0 - Uscita\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

void DisallocaLista(PNodoLista lista){
	PNodoLista p;

	while (lista != NULL){
		p = lista;
		lista = lista->succ;
		free(p);
	}
}

void stampa(PNodoLista lista) {
	while (lista != NULL) {
		printf("\nViaggio : %s  targa : %s  km : %d  costo : %.2f", lista->viaggio.id_viaggio, lista->viaggio.targa, lista->viaggio.km, lista->viaggio.costo);
		lista = lista->succ;
	}
}

int main(void){
	//PNodoLista lista;
	PNodoLista lista=NULL;
	int        scelta;
	// allocare le variabili necessarie...
	int es;
	//TViaggio v;
	char id[5];
	float costo;
	int km;
	float costomedio;
	float totkm;
	char targa[9];

	do {
		scelta = Menu();

		switch (scelta)
		{
		case 1:
			// Invocare la funzione CaricaViaggi e visualizzare un messaggio in caso di errore
			es = CaricaViaggi(&lista, NOME_FILE);
			printf("Caricati %d elementi\n", es);
			break;
		case 2:
			// Invocare la funzione AggiungiViaggio, caricando prima da tastiera i valori da passare come parametri
			printf("\nInserire il codice: ");
			scanf("%s",id);
			printf("Inserire i km: ");
			scanf("%d",&km);
			printf("Inserire il costo: ");
			scanf("%f", &costo);
			AggiungiViaggio(&lista, id, km, costo);

			break;

		case 3:
			// Invocare la funzione TotaleVeicolo, acquisendo preventivamente la targa da tastiera
			printf("\nTarga per cui visualizzare totkm e costomedio : ");
			scanf("%s", targa);
			TotaleVeicolo(lista, targa, &totkm, &costomedio); //& in totkm e costom perchè la funzione chiama i puntatori, 
			// ma in main sono definiti come float semplici. dunque &  => passo puntatore (Come con le liste)
			// Visualizzare km totali e costo medio per km
			printf("\n %s : %.2f km con costo medio %.2f", targa, totkm, costomedio);
			break;
		case 4:
			stampa(lista);
		}

	} while (scelta != 0);

	//DisallocaLista(...); // passare il parametro opportuno

	return 0;
}

