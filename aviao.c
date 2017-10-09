#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_VOO 5
#define MAX_PASSAGEIROS 5

struct voo {
    char nome[20];
    char sobrenome[20];
    char rg[9];
    struct voo *anterior;
    struct voo *proximo;
};

struct voo *atual = NULL;
struct voo *inicio[5];

int voo;
FILE *p_arq = NULL;

void PosicionarNoFinal()
{
	if(inicio[voo-1] != NULL)
	{
		if(inicio[voo-1]->proximo != NULL)
			atual = inicio[voo-1]->proximo;
		else
			atual = inicio[voo-1];

		while((atual->proximo != NULL) && (atual->proximo != inicio[voo-1]))
			atual = atual->proximo;
	}
}

void CriarArquivo()
{
	switch(voo)
	{
		case 1: p_arq = fopen("voo_1.txt", "a");
				break;

		case 2: p_arq = fopen("voo_2.txt", "a");
				break;

		case 3: p_arq = fopen("voo_3.txt", "a");
				break;
	
		case 4: p_arq = fopen("voo_4.txt", "a");
				break;

		case 5: p_arq = fopen("voo_5.txt", "a");
				break;

		default: break;
	}
}

void AbrirArquivoLeitura()
{
	switch(voo)
	{
		case 1: p_arq = fopen("voo_1.txt", "r");
				break;

		case 2: p_arq = fopen("voo_2.txt", "r");
				break;

		case 3: p_arq = fopen("voo_3.txt", "r");
				break;

		case 4: p_arq = fopen("voo_4.txt", "r");
				break;

		case 5: p_arq = fopen("voo_5.txt", "r");
				break;

		default: break;
	}
}

void AbrirArquivoEscrita()
{
	switch(voo)
	{
		case 1: p_arq = fopen("voo_1.txt", "w");
				break;

		case 2:	p_arq = fopen("voo_2.txt", "w");
				break;

		case 3: p_arq = fopen("voo_3.txt", "w");
				break;

		case 4: p_arq = fopen("voo_4.txt", "w");
				break;

		case 5: p_arq = fopen("voo_5.txt", "w");
				break;

		default: break;
	}
}

void GravarInclusao()
{
	if(inicio[voo-1] != NULL)
	{
		atual = inicio[voo-1];
		do
		{
			fprintf(p_arq, "%s %s %s\n", atual->sobrenome, atual->nome, atual->rg);
			if((atual->proximo != NULL) && (atual->proximo != inicio[voo-1]))
				atual = atual->proximo;
			else
				break;
		}while(1);
	}
	fclose(p_arq);
	p_arq = NULL;
}

void LimparBuffer()
{
	#ifdef _WIN32
	    fflush(stdin);
	#else
	    setbuf(stdin, NULL);
	#endif
}

void MyToUpper(char *string)
{
    while(*string != '\0')
    {
        if(*string >= 'a' && *string <= 'z')
            *string = (*string - 'a') + 'A';
        string++;
    }
             
}

int CountLista()
{
	int i = 0;
	
	if(inicio[voo-1] != NULL)
	{
		atual = inicio[voo-1];
		do
		{
			i++;
			if((atual->proximo != NULL) && (atual->proximo != inicio[voo-1]))
				atual = atual->proximo;
			else
				break;
		}while(1);
	}

	return(i);
}

int EncontrarOrdem(char *sobrenome)
{
	atual = inicio[voo-1];
        
    while(strcmp(sobrenome, atual->sobrenome) > 0)
        if(atual->proximo != NULL && atual->proximo != inicio[voo-1])
            atual = atual->proximo;
        else
			return(1);

	return(0);
}

void StartLista(char *sobrenome, char *nome, char *rg)
{
    struct voo *novo = NULL;
    novo = (struct voo *) malloc(sizeof(struct voo));
    strcpy(novo->nome, nome);
    strcpy(novo->sobrenome, sobrenome);
    strcpy(novo->rg, rg);
    novo->anterior = novo;
    novo->proximo = novo;
	inicio[voo-1] = novo;
    atual = novo;
}

void IncluirNaLista(char *sobrenome, char *nome, char *rg)
{
	int posicao, continua = 0;
    struct voo *novo = NULL;
    novo = (struct voo *) malloc(sizeof(struct voo));
    strcpy(novo->nome, nome);
    strcpy(novo->sobrenome, sobrenome);
    strcpy(novo->rg, rg);
	posicao = EncontrarOrdem(sobrenome);

	if(atual == inicio[voo-1] && inicio[voo-1]->proximo == inicio[voo-1])
	{
		if(!posicao)
			inicio[voo-1] = novo;

		novo->proximo = novo->anterior = atual;
		atual->proximo = atual->anterior = novo;
	}
	else
	{
		if(!posicao)
		{
			novo->proximo = atual;
			novo->anterior = atual->anterior;
			atual->anterior = atual->anterior->proximo = novo;
		}
		else
		{
			novo->anterior = atual;
			novo->proximo = atual->proximo;
			atual->proximo = atual->proximo->anterior = novo;
		}

	}
}

void IniciarInclusao()
{
    char nome[20], sobrenome[20], rg[9];
    
    LimparBuffer();

    printf("Informe o sobrenome do passageiro: ");
    gets(sobrenome);
    printf("Informe o nome do passageiro: ");
    gets(nome);
    printf("Informe o RG do passageiro: ");
    gets(rg);
    
    MyToUpper(nome);
    MyToUpper(sobrenome);
    
    if(inicio[voo-1] == NULL)
        StartLista(sobrenome, nome, rg);
    else
        IncluirNaLista(sobrenome, nome, rg);
}

void ListarPassageiros()
{ 
	atual = inicio[voo-1];
	printf("=====================================================\n");
	printf("|                    PASSAGEIROS                    |\n");
	printf("-----------------------------------------------------\n");
	printf("|\t    Sobrenome|\t\t      Nome|\t  RG|\n");
	printf("-----------------------------------------------------\n");
    do
    {
        printf("|%20s|%20s|%9s|\n", atual->sobrenome, atual->nome, atual->rg);
       
		if((atual->proximo != NULL) && (atual->proximo != inicio[voo-1])) 
	        atual = atual->proximo;
		else
			break;
    }while(1);
	printf("=====================================================\n");
}

int CancelarPassagem(char *sobrenome, char *nome)
{
	int mudarInicio = 0;
	atual = inicio[voo-1];
	do
	{
		if((strcmp(sobrenome, atual->sobrenome) == 0) && (strcmp(nome, atual->nome) == 0))
		{	
			if(atual == inicio[voo-1])
				mudarInicio = 1;

			if(atual == inicio[voo-1] && inicio[voo-1] == inicio[voo-1]->proximo)
				inicio[voo-1] = NULL;
			else
			{
				atual->proximo->anterior = atual->anterior;
				atual->anterior->proximo = atual->proximo;
			}

			if(mudarInicio && inicio[voo-1] != NULL)
				inicio[voo-1] = atual->proximo;
			else
				atual = NULL;
			return(1);
		}

		if((atual->proximo != NULL) && (atual->proximo != inicio[voo-1]))
			atual = atual->proximo;	
		else
			return(0);
	}while(1);
}

int IniciarCancelamento()
{
	char nome[20], sobrenome[20];

	LimparBuffer();

	printf("Informe o sobrenome do passageiro: ");
	gets(sobrenome);
    printf("Informe o nome do passageiro: ");
    gets(nome);

	MyToUpper(sobrenome);
	MyToUpper(nome);

	return(CancelarPassagem(sobrenome, nome));
}

void BuscarPassageiro(char *sobrenome, char *nome)
{
	int i = 0;
	atual = inicio[i];	
	do
	{
		if(inicio[i] == NULL)
		{
			if(i < 5)
			{
				i++;
				atual = inicio[i];
				continue;	
			}
			else
			{
				printf("O passageiro solicitado não foi encontrado em nenhum dos vôos disponíveis\n");
				break;
			}
		}

		if((strcmp(sobrenome, atual->sobrenome) == 0) && (strcmp(nome, atual->nome) == 0))
		{
			printf("O passageiro foi encontrado no vôo %d\n", (i + 1));
			break;
		}		

		if((atual->proximo != NULL) && (atual->proximo != inicio[i]))
			atual = atual->proximo;
		else
		{
			if(i < 5)
			{
				i++;
				atual = inicio[i];
			}
			else
			{	
				printf("O passageiro solicitado não foi encontrado em nenhum dos vôos disponíveis\n");
				break;
			}
		}
	}while(1);
}

void IniciarBuscaDePassageiro()
{
	char nome[20], sobrenome[20];
	printf("Informe o sobrenome do passageiro: ");
	gets(sobrenome);
    printf("Informe o nome do passageiro: ");
    gets(nome);

	MyToUpper(sobrenome);
	MyToUpper(nome);

	BuscarPassageiro(sobrenome, nome);	
}

void CarregarVoos()
{
	int inicio = 1;
	char nome[20], sobrenome[20], rg[9];
	while((fscanf(p_arq, "%s %s %s\n", sobrenome, nome, rg)) != EOF)
	{
		if(inicio)
		{
			StartLista(sobrenome, nome, rg);			
			inicio = 0;
		}
		else
			IncluirNaLista(sobrenome, nome, rg);
	} 
}

void ListarVoos()
{	
	printf("==================================\n");
	printf("          Vôos disponíveis        \n");
	printf("----------------------------------\n");
	printf("1)Brasília\n");
	printf("2)Campinas\n");
	printf("3)Guarulhos\n");
	printf("4)Rio de Janeiro\n");
	printf("5)Belo Horizonte\n");
	printf("==================================\n");
}

void Menu()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

	printf("==================================\n");
	printf("          Viação LAVaJATO         \n");
	printf("----------------------------------\n");
	printf("1) Abrir lista\n");
	printf("2) Incluir passageiro\n");
	printf("3) Buscar passageiro\n");
	printf("4) Listar passageiros\n");
	printf("5) Cancelar passagem\n");
	printf("6) Salvar\n");
	printf("7) Recuperar\n");
	printf("8) Sair\n");
	printf("==================================\n");
}

int main()
{
    int opcao;
    do
    {
        Menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
		LimparBuffer();
        
        switch(opcao)
        {
			case 1: ListarVoos();
					printf("Informe o número do vôo: ");
					scanf("%d", &voo);
					if((voo > 0) && (voo <= MAX_VOO))
						CriarArquivo();
					else
						printf("O vôo informado é inválido\n");
					break;

            case 2: ListarVoos();	
					printf("Informe o número do vôo: ");
					scanf("%d", &voo);
					if((voo > 0) && (voo <= MAX_VOO))
					{
						if(CountLista() < MAX_PASSAGEIROS)
							IniciarInclusao();
						else
							printf("Não é possível adicionar mais passageiros neste vôo, excesso de passageiros.\n");
					}
					else
						printf("O vôo informado é inválido\n");
                    break;

			case 3: IniciarBuscaDePassageiro();
					break;
                   
            case 4: ListarVoos();
					printf("Informe o número do vôo: ");
					scanf("%d", &voo);
					if((voo > 0) && (voo <= MAX_VOO))
					{
						if(inicio[voo-1] != NULL)
							ListarPassageiros();
						else
							printf("Não há nenhum passageiro neste vôo.\n");
					}
					else
						printf("O vôo informado é inválido\n");
                    break;

			case 5: ListarVoos();
					printf("Informe o número do vôo: ");
					scanf("%d", &voo);
					if((voo > 0) && (voo <= MAX_VOO))
					{
						if(inicio[voo-1] != NULL)
						{
							if(IniciarCancelamento())
								printf("Usuário removido com sucesso\n");
							else
								printf("O usuário informado não foi encontrado\n");
						}
						else
							printf("Não há nenhum passageiro neste vôo.\n");
					}
					else
						printf("O vôo informado é inválido\n");
					break;

			case 6: AbrirArquivoEscrita();
					GravarInclusao();					
					break;

			case 7: if(p_arq != NULL)
					{
						fclose(p_arq);
						p_arq = NULL;
					}

					ListarVoos();
					printf("Informe o número do vôo: ");
					scanf("%d", &voo);
					if((voo > 0) && (voo <= MAX_VOO))
					{
						AbrirArquivoLeitura();
						if(p_arq != NULL)
							CarregarVoos();
						else
							printf("Não foi possível recarregar este arquivo pois ele não foi encontrado\n");
					}
					else	
						printf("O vôo informado é inválido\n");

					break;
            
            default: break;
        }

		if(p_arq != NULL)
		{
			fclose(p_arq);
			p_arq = NULL;
		}
        
        LimparBuffer();
        printf("Pressione enter para continuar...");
        getchar();
    }while(opcao != 8);
    return 0;
}
