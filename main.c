#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "linkedList.c"
#include "data-structs.h"
#include "makeFs.h"
#include "utils.h"

int main(int argc, char **argv) 
{
	FILE *FILE_FS, *save;
	node_t *start = NULL;

	int RESERVED_CLUSTERS = 512 * 9;

	//65527
	int FREE_CLUSTERS = 65527;
	for (int i = FREE_CLUSTERS - 1; i >= 0; i--) 
	{
		push(&start, i + 9);
	}

	if (exists("fs.img") == 0) 
	{
		int fssize = 65536 * 512;
		FILE_FS = fopen("fs.img", "wb+");

		fseek(FILE_FS, fssize, SEEK_SET);
		fputc('\0', FILE_FS);
		rewind(FILE_FS);

		if (FILE_FS == NULL) 
		{
			printf("Erro!");
			exit(1);
		}
		boot_sec(FILE_FS);
		make_dir(FILE_FS);
		fclose(FILE_FS);
	}
	FILE_FS = fopen("fs.img", "rb+");

	make_list(FILE_FS, &start, 544);

	while (1) 
	{
		char choose[100];
		printf("> ");
		scanf("%100s", choose);
		fflush(stdin);

		if (strstr(choose, "add") != NULL) 
		{
			char filepath[100], filename[100];
			FILE *SAVE;

			printf("Digite o arquivo: ");

			scanf("%100s", filepath);
			fflush(stdin);

			printf("%s\n", filepath);
			SAVE = fopen(filepath, "rb");
			if (SAVE == NULL) 
			{
				printf("file cannot be open\n");
				exit(-1);
			}
			strcpy(filename, get_name(filepath, '/'));
			save_file(filename, SAVE, FILE_FS, &start, 512);

			fclose(SAVE);
		}
		else if (strstr(choose, "ls") != NULL)
		{
			list_files(FILE_FS, 512, 0);
		}
		else if (strstr(choose, "mkdir") != NULL)
		{
			char nome[25];

			printf("Digite o subdiretório: ");

			scanf("%100s", nome);
			fflush(stdin);

			make_subdir(FILE_FS, nome, &start, 512);
		}
		else if (strstr(choose, "remover") != NULL)
		{
			char nome[25];

			printf("Digite o arquivo ou subdiretório a ser removido: ");

			scanf("%100s", nome);
			fflush(stdin);

			//dir/dir1/arq.txt -> ["dir", "dir1", "arq.txt"]
			char **subdir_names = str_split(nome, '/');

			if (subdir_names)
			{
				int array_size = 0;
				//incrementa end de memoria, pq tamanho dinamico
				for (int i = 0; *(subdir_names + i); i++)
				{
					array_size++;
				}

				remove_file(FILE_FS, subdir_names, &start, 544, 0, subdir_names[0], array_size);
			}
			else
			{
				printf("error");
			}
		}
		else if (strstr(choose, "filesb") != NULL)
		{
			char filepath[100], filename[25], subdirname[25];
			FILE *SAVE;

			printf("Digite o arquivo: ");

			scanf("%100s", filepath);
			fflush(stdin);

			SAVE = fopen(filepath, "rb");
			if (SAVE == NULL)
			{
				printf("file cannot be open\n");
				exit(-1);
			}
			strcpy(filename, get_name(filepath, '/'));

			printf("Digite o subdiretório: ");

			scanf("%s", subdirname);
			fflush(stdin);

			verify_subdir(FILE_FS, SAVE, subdirname, filename, &start);
			//save_file(filename, SAVE, FILE_FS, &start, RESERVED_CLUSTERS);

			fclose(SAVE);
		}
		else if (strstr(choose, "sair") != NULL)
		{
			printf("Saiu!!!\n");
			exit(0);
		}
		else if (strstr(choose, "formatar") != NULL)
		{
			int numsector;

			printf("Número de setores: ");
			scanf("%d", &numsector);

			format(FILE_FS, numsector);
		}
		else if (strstr(choose, "exportar") != NULL)
		{
			char filepath[100], filename[25];
			FILE *SAVE;

			printf("Digite o arquivo: ");

			scanf("%100s", filepath);
			fflush(stdin);

			SAVE = fopen(filepath, "wb");
			if (SAVE == NULL)
			{
				printf("file cannot be open\n");
				exit(-1);
			}

			strcpy(filename, get_name(filepath, '/'));

			fflush(stdin);

			export_dir(FILE_FS, SAVE, filename);

			fclose(SAVE);
		}
		else if (strstr(choose, "ajuda") != NULL)
		{
			printf("add - Adiciona arquivo ao root.\n");
			printf("remover - Remove um arquivo ou subdiretório.\n");
			printf("ls - Listar arquivos.\n");
			printf("mkdir - Criar diretórios de n niveis.\n");
			printf("filesb - Adiciona arquivo em um subdiretório.\n");
			printf("exportar - Exporta um arquivo\n");
		}
		else
		{
			printf("Opção inválida!\n");
		}
	}

	fclose(FILE_FS);
}