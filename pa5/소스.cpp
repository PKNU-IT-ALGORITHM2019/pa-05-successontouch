#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX 400000

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
	if (!root_tmp)
		return NULL;

	if (strcmp(tmp, root_tmp->word)==0) {

		printf("\n%s\n", root_tmp->explain);
		return 0;
	}
	 
	else if (tmp > root_tmp->word)
		BST_find(root_tmp->right, tmp); 

	else
		BST_find(root_tmp->left, tmp);
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
		if (root_tmp->word > word)
			root_tmp->left = BST_insert(root_tmp->left, word,type,explain);
		else
			root_tmp->right = BST_insert(root_tmp->right, word,type,explain);
	}
	return root_tmp;
}
Node* findMinNode(Node* root)
{
	Node* tmp = root;
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}
Node* BST_delete(Node* root, char* word)
{
	Node* tNode = NULL;
	if (root == NULL)
		return NULL;

	if (root->word > word)
		root->left = BST_delete(root->left, word);
	else if (root->word < word)
		root->right = BST_delete(root->right, word);
	else
	{
		// 자식 노드가 둘 다 있을 경우
		if (root->right != NULL && root->left != NULL)
		{
			tNode = findMinNode(root->right);
			root->word = tNode->word;
			root->right = BST_delete(root->right, tNode->word);
		}
		else
		{
			tNode = (root->left == NULL) ? root->right : root->left;
			free(root);
			return tNode;
		}
	}

	return root;
}
Node* BST_search(Node* root, char* word)
{
	if (root == NULL)
		return NULL;

	if (root->word == word)
		return root;
	else if (root->word > word)
		return BST_search(root->left, word);
	else
		return BST_search(root->right, word);
}
void BST_print(Node* root)
{
	if (root == NULL)
		return;

	printf("%s", root->word);
	BST_print(root->left);
	BST_print(root->right);
}

int main()
{
	FILE *fp = fopen("input2.txt","r");
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
			
			string = strtok(buffer, "(");
			save[0] = string;
			
			string = strtok(NULL, ")");
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
	//root = BST_insert(root, "worab");
	

	char a[MAX] = "Shellapple";
	//root = BST_delete(root, hh);
	BST_find(root, a);

	BST_print(root);
	printf("%d", entire_count);
	getchar();
	getchar();
}