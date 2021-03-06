#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 20

struct node {
	int frequency;
	char word[WORD_SIZE];
	struct node *left, *right;
};

struct node* newNode(int fre, char str[]){
	
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	
	strcpy(temp->word, str);
	temp->frequency = fre;
	
	temp->left = temp->right = NULL;
	return temp;
}

struct node* insert(struct node* node, int fre, char str[]){
	
	if (node == NULL)
		return newNode(fre, str);
		
	int res = strcmp(node->word, str);

	if (res > 0)
		node->left = insert(node->left, fre, str);
		
	else
		node->right = insert(node->right, fre, str);

	return node;
}

int findWord(struct node* node, char str[]){ 
  
  struct node* current = node;  
  int sum_frequency = 0;
  int step = 1; 
  
  while(1){
  	
	  int compare = strcmp(current->word, str);
	  sum_frequency += current->frequency;
	  
	  printf("compare : %12s, word frequency : %3d,  sum_frequency : %3d\n",current->word, current->frequency ,sum_frequency);
	  
	  if(compare == 0){
	  	printf("\n   Words found %d steps...\n", step);
	  	return sum_frequency;
	  }
	
	  else if(compare <= 0){
	  	
	  	if(current->right != NULL)
	  		current = current->right;
	  	
	  	else
	  		return -1;
	  }
	
	  else{
	  	
	  	if(current->left != NULL)
	  		current = current->left;
	  	
	  	else
	  		return -1;	
	  }
	  step++;
   } 
  
  return -1; 
}

void inorder(struct node* root){
	
	if (root != NULL) {
		
		inorder(root->left);
		printf("%15s %3d\n", root->word,root->frequency);
		inorder(root->right);
	}
}

int calculate_frequency(char *str, int size){
	
	int x;
	int i = 0;
	int number = 0;
	int j = 1;
	
	for(i = size - 2; i > 0; i--){
		if(str[i] == ',')
			break;
		
		x = str[i] - '0';
		number += j * x;
		j *= 10; 
	}
	
	return number;
}

size_t getline(char **lineptr, size_t *n, FILE *stream) {
	
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if(lineptr == NULL)
        return -1;
    
    if(stream == NULL)
        return -1;
    
    if(n == NULL)
        return -1;
    
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    
    if (c == EOF)
        return -1;
    
    if (bufptr == NULL){
    	
        bufptr = malloc(128);
        
        if (bufptr == NULL)
            return -1;
        
        size = 128;
    }
    
    p = bufptr;
    
    while(c != EOF){
    	
        if ((p - bufptr) > (size - 1)) {
        	
            size = size + 128;
            bufptr = realloc(bufptr, size);
            
            if (bufptr == NULL)
                return -1;  
        }
        
        *p++ = c;
        
        if (c == '\n')
            break;

        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

int main(){
	
	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	
	fp = fopen("input.txt", "r");
	
	if(fp == NULL)
		exit(EXIT_FAILURE);
		
	struct node* root = NULL;
	int i = 0;
	
	printf("\n   READ FILE START!\n\n");
	while((read = getline(&line, &len, fp)) != -1){
		
        //printf("%s", line);
        
        int word_size = (int)read;
        int frequency = calculate_frequency(line, word_size);
        
        char* word = strtok(line, ",");
		word = strtok(NULL, ",");
        printf(" word : %12s %3s frequency : %3d\n", word, " " ,frequency); 
        
        if(i == 0)
        	root = insert(root, frequency, word);
        	
		else
			insert(root, frequency, word);
	}
	fclose(fp);

	printf("\n\n   READ FILE FINISH!\n\n");

	printf("   INORDER: \n\n");
	inorder(root);
	
	printf("\n\n");
	
	char str[WORD_SIZE];
	printf(" Enter the word : ");
	gets(str);
	
	int res_fre = findWord(root, str);
	
	if(res_fre == -1){
		printf("\n   Word not be found...\n", str);
	}
	else{
		printf("\n   Word found! Access Time : %d\n", res_fre);
	}
	
	return 0;
}
