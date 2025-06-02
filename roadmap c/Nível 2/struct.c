#include <stdio.h>

struct struct_name {
	int x;
	char c;
};

struct {
	int x;
	char c;
} struct_name_down; // Apesar de não dar erro de compilação, esse tipo de declaração é inválida

typedef struct struct_def {
	int x;
	char c;
} struct_def;

typedef struct {
	int x;
	char c;
} anonymous_struct_def;

typedef struct {
	struct struct_name s1;
	struct struct_def s2;
	anonymous_struct_def s3;
} internal_struct;

int	main(void)
{
	struct struct_name my_struct;
	my_struct.x = 10;
	my_struct.c = 'a';

	printf("struct_name: x: %d c: %c \n\n", my_struct.x, my_struct.c); 

	/* Erro na criação da struct
 	struct struct_name_down my_struct_name_down;
	my_struct_name_down.x = 10;
	my_struct_name_down.c = 'a';
	
	printf("struct_name_down: x: %d c: %c \n\n", my_struct_name_down.x, my_struct_name_down.c); 
	*/

	struct_def my_struct_def;
	my_struct_def.x = 20;
	my_struct_def.c = 'b';

	printf("struct_def: x: %d c: %c \n\n", my_struct_def.x, my_struct_def.c);

	anonymous_struct_def my_anonymous_struct_def;
	my_anonymous_struct_def.x = 30;
	my_anonymous_struct_def.c = 'c';

	printf("anonymous_struct_def: x: %d c: %c \n\n", my_anonymous_struct_def.x, my_anonymous_struct_def.c);

	internal_struct my_internal_struct;
	
	my_internal_struct.s1.x = 1;
	my_internal_struct.s1.c = 'a';

	my_internal_struct.s2.x = 2;
	my_internal_struct.s2.c = 'b';

	my_internal_struct.s3.x = 3;
	my_internal_struct.s3.c = 'c';

	printf("internal_struct.s1: x: %d c: %c \n", my_internal_struct.s1.x,my_internal_struct.s1.c);

	printf("internal_struct.s2: x: %d c: %c \n", my_internal_struct.s2.x,my_internal_struct.s2.c);

	printf("internal_struct.s3: x: %d c: %c \n", my_internal_struct.s3.x,my_internal_struct.s3.c);

	return (0);
}
