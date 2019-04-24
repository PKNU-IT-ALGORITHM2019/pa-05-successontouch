#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX 400000
#define MINI_MAX 100

int entire_count = 0;

typedef struct NodeStruct
{
	char* word;
	char* explain;
	char* type;
	struct NodeStruct* left;
	struct NodeStruct* right;
}Node;

Node* root = NULL;

Node* BST_find(Node *root_tmp,char* tmp)
{
	if (!root_tmp) {
		printf("같은 값 없음\n");
		return NULL;
	}

	if (strcmp(tmp, root_tmp->word)==0) {
		
		printf("\n%s\n", root_tmp->explain);
		return 0;
	}
	 
	else if (strcmp(root_tmp->word,tmp)>0)
		BST_find(root_tmp->left, tmp); 

	else
		BST_find(root_tmp->right, tmp);
}

Node* BST_insert(Node* root_tmp, char* word, char* type,char* explain )
{

	if (root_tmp == NULL)
	{
		root_tmp = (Node*)malloc(sizeof(Node));
		
		root_tmp->left =root_tmp->right = NULL;
		root_tmp->word = strdup(word);
		root_tmp->type = strdup(type);
		root_tmp->explain = strdup(explain);
		return root_tmp;
	}
	else
	{
		if (strcmp(root_tmp->word,word) > 0)
			root_tmp->left = BST_insert(root_tmp->left, word,type,explain);
		else
			root_tmp->right = BST_insert(root_tmp->right, word,type,explain);
	}
	return root_tmp;
}
Node* findMinNode(Node* root_tmp)
{
	Node* tmp = root_tmp;
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}
Node* BST_delete(Node* root_tmp, char* tmp)
{
	Node* tNode = NULL;
	if (root_tmp == NULL)
		return NULL;

	if (strcmp(root_tmp->word, tmp) > 0)
		root_tmp->left = BST_delete(root_tmp->left, tmp);
	else if (strcmp(root_tmp->word, tmp) < 0)
		root_tmp->right = BST_delete(root_tmp->right, tmp);
	else{  //(strcmp(root_tmp->word, tmp) == 0)
		if (root_tmp->right != NULL && root_tmp->left != NULL)
		{
			tNode = findMinNode(root_tmp->right);
			root_tmp->word = tNode->word;
			root_tmp->right = BST_delete(root_tmp->right, tNode->word);
		}
		else
		{
			tNode = (root_tmp->left == NULL) ? root_tmp->right : root_tmp->left;
			free(root_tmp);
			return tNode;
		}
	}
	return root_tmp;
}
Node* BST_search(Node* root_tmp, char* word)
{
	if (root_tmp == NULL)
		return NULL;

	if (strcmp(root_tmp->word , word)==0)
		return root_tmp;
	else if (strcmp(root_tmp->word,word) > 0)
		return BST_search(root_tmp->left, word);
	else
		return BST_search(root_tmp->right, word);
}

void BST_print(Node* root_tmp)
{
	if (root_tmp == NULL)
		return;

	printf("%s\n", root_tmp->word);
	BST_print(root_tmp->left);
	BST_print(root_tmp->right);
}

int main()
{
	printf("&실행\n");
	FILE *fp = fopen("input.txt","r");
	int state = 0;
	if (fp == NULL) 
		return 0;
	
	else {
		while (!feof(fp)) {
			entire_count++;
			char buffer[MAX];
			char *save[3];
			char* string;

			fgets(buffer, sizeof(buffer), fp);
			
			string = strtok(buffer, " (");
			save[0] = string;
			
			string = strtok(NULL, ") ");
			save[1] = string;
		
			
			string = strtok(NULL, "\n");
			save[2] = string;

			if (state == 0) {
				state++;
				root = BST_insert(root, save[0], save[1], save[2]);
			}
			else
				BST_insert(root, save[0], save[1], save[2]);
		}
	}

	fclose(fp);	
	char just[MINI_MAX];
	while (1) {
		printf("1.size 2.find word 3.add word class meaning 4.delete 5.deleteall 6.print 7.end\n");
		scanf("%s", &just);
		if (strcmp(just, "size") == 0) {
			printf("%d\n", entire_count);
		}
		else if (strcmp(just, "find") == 0) {

			char what[MINI_MAX];
			scanf("%s", what);
			BST_find(root, what);
		}
		else if (strcmp(just, "add") == 0) {
			char save0[MINI_MAX];
			char save1[MINI_MAX];
			char save2[MINI_MAX];
			printf("word: ");
			scanf("%s", save0);

			printf("class: ");
			scanf("%s", save1);

			printf("meaning ");
			scanf("%s", save2);

			BST_insert(root, save0, save1, save2);
			entire_count++;
		}
		else if (strcmp(just, "delete") == 0) {
			char what[MINI_MAX];
			scanf("%s", what);
			BST_delete(root, what);
			entire_count--;
		}
		else if (strcmp(just, "deleteall") == 0) {
			FILE *fp2 = fopen("input3.txt", "r");

			if (fp2 == NULL)
				return 0;

			while (!feof(fp2)) {
				char b[MINI_MAX];
				fgets(b, sizeof(b), fp2);
				for (int i = 0; i < MINI_MAX; i++) {
					if (b[i] == '\n') {
						b[i] = NULL;
						break;
					}
				}
				BST_delete(root, b);
				entire_count--;
			}
		}
		else if (strcmp(just, "print") == 0)
			BST_print(root);
		else if (strcmp(just, "end") == 0)
			return 0;
	}
	getchar();
	getchar();
}