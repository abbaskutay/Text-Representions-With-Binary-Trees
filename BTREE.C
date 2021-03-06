#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>

#define WORD_SIZE 20

struct node {
	int frequency;
	char word[WORD_SIZE];
	struct node *left, *right;
};
  
struct node* newNode(int frequency, char str[]);
  
struct node* sortedArrayToBST(struct node arr[], int start, int end){ 

    if(start > end) 
      return NULL; 
  
    int mid = (start + end)/2; 
    
    struct node *root = newNode(arr[mid].frequency, arr[mid].word); 
    
    root->left =  sortedArrayToBST(arr, start, mid-1); 
    root->right = sortedArrayToBST(arr, mid+1, end); 
  
    return root; 
}  

struct node* newNode(int frequency, char str[]){
 
    struct node* node = (struct node*) malloc(sizeof(struct node));
	 
    node->frequency = frequency; 
    strcpy(node->word, str);
    node->left = NULL; 
    node->right = NULL; 
  
    return node; 
}
  
void preOrder(struct node* node){
 
    if (node == NULL) 
        return; 
        
    printf("%5d %12s\n", node->frequency, node->word); 
    preOrder(node->left); 
    preOrder(node->right); 
}

void sortArray(struct node arr[]){
	
	int j, i = 0;
	
	for(i = 0; i < 50; i++){
		for(j = 0; j < 50 - i - 1; j++){
			
			int compare = strcmp(arr[j].word, arr[j+1].word);
			
			if(compare > 0){
				struct node temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int findWord(struct node* node, char str[]){ 
  
  struct node* current = node;  
  int sum_frequency = 0; 
  int step = 1;
  
  while(1){
  	
	  int compare = strcmp(str, current->word);
	  sum_frequency += current->frequency;
	  
	  printf("compare : %12s, word frequency : %3d,  sum_frequency : %3d\n",current->word, current->frequency ,sum_frequency);
	  
	  if(compare == 0){
	  	printf("\n   Words found %d steps...\n", step);
	  	return sum_frequency;
	  }
	
	  else if(compare <= 0){
	  	
	  	if(current->left != NULL)
	  		current = current->left;
	  	
	  	else
	  		return -1;
	  }
	
	  else{
	  	
	  	if(current->right != NULL)
	  		current = current->right;
	  	
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
		
	struct node arr[50];
	int i = 0;
	int j = 0;
	
	struct node* temp = NULL;
	
	printf("\n   READ FILE START!\n\n");
	while((read = getline(&line, &len, fp)) != -1){
		
        //printf("%s", line);
        
        int word_size = (int)read;
        int frequency = calculate_frequency(line, word_size);
        
        char* word = strtok(line, ",");
		word = strtok(NULL, ",");
        printf("j = %3d    word : %10s %3s frequency : %3d\n", j, word, " " ,frequency); 	
        
        arr[j].frequency = frequency;
        strcpy(arr[j].word, word);
		
		j++;
	}
	fclose(fp);
	
	sortArray(arr);
	struct node *root = sortedArrayToBST(arr, 0, 49);

	printf("\n\n   READ FILE FINISH!\n\n");
	printf("   INORDER: \n\n");
	inorder(root);
	//preOrder(root);
	printf("\n\n");
	
	char str[WORD_SIZE];
	printf(" Enter the word : ");
	gets(str);
	
	printf("\n");
	
	int res_fre = findWord(root, str);
	
	if(res_fre == -1){
		printf("\n   Word not be found...\n", str);
	}
	else{
		printf("\n   Word found! Access Time : %d\n", res_fre);
	}
	
    return 0; 
} 
