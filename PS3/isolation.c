#include <stdio.h>
#include <stdlib.h>

struct BinaryTree {
    int value;
    struct BinaryTree* left;
    struct BinaryTree* right;
};

void removeTreeNode(struct BinaryTree **Tree, int *size, int index);
void releaseBinaryTree(struct BinaryTree *root);
int compareTrees(struct BinaryTree *root1, struct BinaryTree *root2);

int main(void) {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);
    
    if (n >= 1 && n <= 50 && k >= 1 && k <= 20) {
        struct BinaryTree **Tree = (struct BinaryTree**)calloc(n, sizeof(struct BinaryTree*));
        if (Tree == NULL) {
            return -1; 
        }
        int i=0;
        while (i<n)
        {
            Tree[i] = NULL;
            for (int j = 0; j < k; j++) {
                int value;
                scanf("%d", &value);
                
                if (Tree[i] == NULL) {
                    Tree[i] = (struct BinaryTree*)calloc(1, sizeof(struct BinaryTree));
                    if (Tree[i] != NULL) {
                        Tree[i]->value = value;
                    }
                } else {
                    struct BinaryTree *current = Tree[i];
                    while (1) {
                        if (value > current->value) {
                            if (current->right == NULL) {
                                current->right = (struct BinaryTree*)calloc(1, sizeof(struct BinaryTree));
                                if (current->right != NULL) {
                                    current->right->value = value;
                                }
                                break;
                            } else {
                                current = current->right;
                            }
                        } else {
                            if (current->left == NULL) {
                                current->left = (struct BinaryTree*)calloc(1, sizeof(struct BinaryTree));
                                if (current->left != NULL) {
                                    current->left->value = value;
                                }
                                break;
                            } else {
                                current = current->left;
                            }
                        }
                    }
                }
            }
            i++;
        }
        int con=0;
        while (con<n-1)
        {
            for (int j = con + 1; j < n; j++) {
                if (Tree[j] != NULL && compareTrees(Tree[con], Tree[j]) == 1) {
                    removeTreeNode(Tree, &n, j--);
                }
            }
            con++;
        }
        

        
        int unique_trees = 0;
        for (int i = 0; i < n; i++) {
            if (Tree[i] != NULL) {
                unique_trees++;
            }
            releaseBinaryTree(Tree[i]);
        }
        
        free(Tree);
        
        printf("%d\n", unique_trees);
    }
    
    return 0;
}

void removeTreeNode(struct BinaryTree **Tree, int *size, int index) {
    if (Tree == NULL || *size <= 0 || index < 0 || index >= *size) {
        return;
    }
    releaseBinaryTree(Tree[index]); 
    for (int i = index; i < *size - 1; i++) {
        Tree[i] = Tree[i + 1];
    }
    Tree[*size - 1] = NULL; 
    (*size)--; 
}

void releaseBinaryTree(struct BinaryTree *root) {
    if (root == NULL) {
        return;
    }
    releaseBinaryTree(root->left);
    releaseBinaryTree(root->right);
    free(root);
}

int compareTrees(struct BinaryTree *root1, struct BinaryTree *root2) {
   if ((root1 == NULL && root2 == NULL))
	{
		return 1;
	}
	if ((root1 == NULL && root2 != NULL) || (root1 != NULL && root2 == NULL))
	{
		return -1;
	}
	if ((compareTrees(root1->left, root2->left) == -1)
		|| (compareTrees(root1->right, root2->right) == -1))
	{
		return -1;
	}
	return 1;
}
