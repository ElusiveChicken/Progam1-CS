//Name: Gavin Schmidt
//Dr. Steinberg
//COP3502C Spring 2022
//Programming Assignment 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 20

char ** doubleIt(char **arr, int *maxsize); 
char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize);
char* generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize); //write sentence to console window
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr); //write story to txt file
void displaySentence(char * sentence);
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize);

int main()
{
	//setup randomness
	int x;
	printf("Enter seed: ");
	scanf("%d", &x);
	srand(x); //set seed
	
	//declare necessary variables
	int nounsize = 0;
	int verbsize = 0;
	int adjsize = 0;
	int prepositionsize = 0;
	
	int nounmaxsize = 5;
	int verbmaxsize = 5;
	int adjmaxsize = 5;
	int prepositionmaxsize = 5;
	const int articlemaxsize = 3; //there are only 3 articles in the english language a, an, and the. that is why const is applied
	
	printf("Welcome to the random sentence generator.\n");
	
	//double pointers
	char ** nouns = NULL;
	char ** verbs = NULL;
	char ** adjectives = NULL;
	char ** preposition = NULL;
	char ** articles = NULL;
	
	nouns = (char **) malloc(sizeof(char *) * nounmaxsize); 
	verbs = (char **) malloc(sizeof(char *) * verbmaxsize);
	adjectives = (char **) malloc(sizeof(char *) * adjmaxsize); 
	preposition = (char **) malloc(sizeof(char *) * prepositionmaxsize); 
	articles = (char **) malloc(sizeof(char *) * articlemaxsize); 
	
	//make sure malloc was able to allocate memory
	if(nouns == NULL || verbs == NULL || adjectives == NULL || preposition == NULL || articles == NULL) 
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}
	
	//populate articles using strcpy. numbers represent how many characters are needed. this includes \0 character
	articles[0] = (char *) malloc(sizeof(char) * 2);
	strcpy(articles[0], "A");
	articles[1] = (char *) malloc(sizeof(char) * 3);
	strcpy(articles[1], "An");
	articles[2] = (char *) malloc(sizeof(char) * 4);
	strcpy(articles[2], "The");
	
	//open the file of words
	FILE *fptr = fopen("nouns.txt", "r");
	FILE *fptr2 = fopen("verbs.txt", "r");
	FILE *fptr3 = fopen("adjectives.txt", "r");
	FILE *fptr4 = fopen("preposition.txt", "r");
	
	//make sure the files were opened properly
	if(fptr == NULL || fptr2 == NULL || fptr3 == NULL || fptr4 == NULL)
	{
		printf("file was not successful in opening.");
		printf("Program will now terminate.\n");
		exit(1);
	}
	
	//populate the dynamic array
	nouns = populate(nouns, fptr, &nounsize, &nounmaxsize); //populate nouns
	verbs = populate(verbs, fptr2, &verbsize, &verbmaxsize); //populate verbs
	adjectives = populate(adjectives, fptr3, &adjsize, &adjmaxsize); //populate adjectives
	preposition = populate(preposition, fptr4, &prepositionsize, &prepositionmaxsize); //populate prepositions
	
	//close the files
	fclose(fptr);
	fclose(fptr2);
	fclose(fptr3);
	fclose(fptr4);

	//now lets generate 5 sentences and write them to the console window
	
	printf("Let's generate some random sentences that don't make sense.\n");
	
	for(int x = 0; x < 5; ++x)
	{
		char * sentence = generateSentence(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize);
		displaySentence(sentence);
		free(sentence);
	}
	
	printf("Now let's create three stories that just don't make sense.\n");
	fptr = fopen("story1.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 1
	fclose(fptr);
	
	fptr = fopen("story2.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 2
	fclose(fptr);

	fptr = fopen("story3.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 3
	fclose(fptr);

	cleanUp(nouns, verbs, adjectives, preposition, articles, nounmaxsize, verbmaxsize, adjmaxsize, prepositionmaxsize, 3);

	
	printf("The stories were generated successfully and stored in their respective text files.\n");
	printf("Check them out!\n");
	
	return 0;
}




char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize)
{
	//allocates for array words
	words = malloc(sizeof(char *) * (*maxsize));
	if(words == NULL) 
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}
	//freed

	for(/**currentsize*/ int i = 0; /**currentsize*/ i < *maxsize; ++i/*(*currentsize)*/)
	{
		//allocates for each index in array words
		words[i/**currentsize*/] = malloc(sizeof(char) * LIMIT);
		if(words[i/**currentsize*/] == NULL) 
		{
			printf("malloc was not successful\n");
			printf("Program will now terminate.\n");
			exit(1);
		}
		//freed

		int end = fscanf(fptr, "%s", words[i/**currentsize*/]);
		++(*currentsize);
		
		if(*currentsize == (i/**maxsize*/ - 1) && end != EOF)
		{
			words = doubleIt(words, maxsize);
			continue;
		}
		else if (end == EOF)
		{
			i = *maxsize;
			break;
		}
	}
	return words;
}
char ** doubleIt(char **arr, int *maxsize)
{
	//allocates new array with double size
    char** arr2 = malloc(sizeof (char*) * (*maxsize * 2));
    if(arr2 == NULL) 
    {
        printf("malloc was not successful\n");
        printf("Program will now terminate.\n");
        exit(1);
    }
	//freed


    for(int i = 0; i < *maxsize; ++i)
    {
        arr2[i] = malloc(sizeof(char*) * LIMIT);
        if(arr2[i] == NULL) 
        {
            printf("malloc was not successful\n");
            printf("Program will now terminate.\n");
            exit(1);
        }

        strcpy(arr2[i], arr[i]);
    }
	//frees old array
    for(int j = 0; j < *maxsize; j++)
    {
        free(arr[j]);
    }
    free(arr);
    *maxsize = *maxsize * 2;
    return arr2;
}
char* generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize) //write sentence to console window
{
	//allocate for sentence
	char* sentence = malloc(sizeof(char) * 100);
	if(sentence == NULL)
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}
	//freed after main and generatesentence calls

	//copy random words into sentence
	strcpy(sentence, article[(rand() % (articlesize + 1))]);
	strcat(sentence, " ");
	strcat(sentence, adjective[(rand() % (adjsize + 1))]);
	strcat(sentence, " ");
	strcat(sentence, noun[(rand() % (nounsize + 1))]);
	strcat(sentence, " ");
	strcat(sentence, verb[(rand() % (verbsize + 1))]);
	strcat(sentence, " ");
	strcat(sentence, preposition[(rand() % (prepositionsize + 1))]);
	strcat(sentence, " ");
	strcat(sentence, article[(rand() % (articlesize + 1))]);
	strcat(sentence, " ");
	strcat(sentence, adjective[(rand() % (adjsize + 1))]);
	strcat(sentence, " ");
	strcat(sentence, noun[(rand() % (nounsize +1))]);
	strcat(sentence, ".\n");

	return sentence;
}
void displaySentence(char * sentence)
{
	printf("%s", sentence);
}
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr) //write story to txt file
{
	int numSent = (rand() % 401) + 100;

	for (int i = 0; i <= numSent; ++i)
	{
		char* sentence = generateSentence(noun, verb, adjective, preposition, article, nounsize, verbsize, adjsize, prepositionsize, articlesize);
		fputs(sentence, fptr);
		free(sentence);
	}
}
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize)
{
	//frees all char** words
	for(int a = 0; a < (nounsize); ++a)
		free(nouns[a]);
	free(nouns);
	for(int b = 0; b < verbsize; ++b)
		free(verbs[b]);
	free(verbs);
	for(int c = 0; c < adjsize; ++c)
		free(adjectives[c]);
	free(adjectives);
	for(int d = 0; d < prepositionsize; ++d)
		free(prepositions[d]);
	free(prepositions);
	for(int e = 0; e < articlesize; ++e)
		free(articles[e]);
	free(articles);
}