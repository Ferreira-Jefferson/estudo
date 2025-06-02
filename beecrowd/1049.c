#include <stdio.h>
#include <string.h>

#define QT_ANIMAL_TYPES 8

enum type {
	VERTEBRADO 		= 0b0,
	INVERTEBRADO 	= 0b1
};

enum food {
	CARNIVORO 	= 0b000,
	ONIVORO 	= 0b010,
	HERBIVORO	= 0b100,
	HEMATOFAGO	= 0b110
};

enum group {
	AVE			= 0b00000,
	MAMIFERO 	= 0b01000,
	INSETO		= 0b10000,
	ANELIDEO	= 0b11000
};

typedef struct {
	char identifier;
	char name[20];
} Animal_kingdom;

typedef char Category;

Animal_kingdom* define_animal_types()
{
	static Animal_kingdom animal_types[QT_ANIMAL_TYPES] = {
		{VERTEBRADO | AVE | CARNIVORO , "aguia"},
		{VERTEBRADO | AVE | ONIVORO , "pomba"},
		{VERTEBRADO | MAMIFERO | ONIVORO , "homem"},
		{VERTEBRADO | MAMIFERO | HERBIVORO , "vaca"},
		{INVERTEBRADO | INSETO | HEMATOFAGO , "pulga"},
		{INVERTEBRADO | INSETO | HERBIVORO , "lagarta"},
		{INVERTEBRADO | ANELIDEO | HEMATOFAGO , "sanguessuga"},
		{INVERTEBRADO | ANELIDEO | ONIVORO , "minhoca"}
	};

	return (animal_types);
}

Category categorize(char *animal_category, char *animal_group, char *food_group)
{
	Category category = 0;

	if(strcmp(animal_category, "vertebrado") == 0)
		category |= VERTEBRADO;
	else
		category |= INVERTEBRADO;
	
	if(strcmp(animal_group, "ave") == 0)
		category |= AVE;
	else if(strcmp(animal_group, "mamifero") == 0)
		category |= MAMIFERO;
	else if(strcmp(animal_group, "inseto") == 0)
		category |= INSETO;
	else
		category |= ANELIDEO;

	if(strcmp(food_group, "carnivoro") == 0)
		category |= CARNIVORO;
	else if(strcmp(food_group, "onivoro") == 0)
		category |= ONIVORO;
	else if(strcmp(food_group, "herbivoro") == 0)
		category |= HERBIVORO;
	else
		category |= HEMATOFAGO;

	return (category);
}

void define_animal(Category category)
{
	Animal_kingdom *animal_types = define_animal_types();
	int i = 0;

	while(i < QT_ANIMAL_TYPES)
	{
		if(animal_types[i].identifier == category)
		{
			printf("%s\n", animal_types[i].name);
			break ;
		}
		i++;
	}
}

int main()
{
    char animal_category[20];
    char animal_group[20];
    char food_group[20];

	scanf("%19s", animal_category);
	scanf("%19s", animal_group);
	scanf("%19s", food_group);
	
	Category category = categorize(animal_category, animal_group, food_group);
	
	define_animal(category);
 
    return 0;
}