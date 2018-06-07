#include <stdio.h>
#include <time.h>
#include <cstdlib>

typedef struct BSTnode{
    int val;
    struct BSTnode* right;
    struct BSTnode* left;
    struct BSTnode* parent;
} BSTnode;

void add_node(BSTnode* &root, int value){
    BSTnode* tmp = new BSTnode;
    tmp->val=value;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;

    if(root == NULL){
        root=tmp;
        return;
    }

    BSTnode* tmpRoot = root;
    BSTnode* prevRoot = NULL;

    // Find the father of a new node
    while(tmpRoot != NULL){
        prevRoot=tmpRoot;
        
        if(tmpRoot->val<value){
        	tmpRoot=tmpRoot->right;
		}
		else{
			tmpRoot=tmpRoot->left;
		}
    }

    // Insert the new node
    if(prevRoot->val < value)
        prevRoot->right=tmp;
    else{
        prevRoot->left=tmp;
    }
    tmp->parent=prevRoot;
}

void free_BST(BSTnode* root){
    if(root == NULL){
        return;
    }
    if(root->left != NULL){
        free_BST(root->left);
    }
    if(root->right != NULL){
        free_BST(root->right);
    }
    delete root;
    return;
}

BSTnode* min(BSTnode* root){
    
    if(root==NULL){
    	return NULL;
	}
	
	while(root->left!=NULL){
		root=root->left;
	}
	
	return root;
}

BSTnode* max(BSTnode* root){
    if(root==NULL){
    	return NULL;
	}
	
	while(root->right!=NULL){
		root=root->right;
	}
	
	return root;
}


BSTnode* succ(BSTnode* node){
    if(node->right != NULL){
        return min(node->right);
    }else{
		BSTnode* prev=node->parent;
		
		while(prev!=NULL && prev->left!=node){
			node=prev;
			prev=prev->parent;
		}
		return prev;
    }
}

BSTnode* search(BSTnode* root, int val){
    // Base Cases: root is null or key is present at root
    if(root == NULL || root->val == val){
       return root;
    }
    // Key is greater than root's key
    if(root->val < val){
        return search(root->right,val);
    }
    // Key is smaller than root's key
    return search(root->left,val);
}

int sum_in_range(BSTnode* node, int min_value, int max_value){
    BSTnode* left = search(node,min_value);
    BSTnode* right = search(node,max_value);
    int sum = 0;
    while(left != right){
        sum+=left->val;
        left=succ(left);
    }
    sum += right->val; //suming the last element
    return sum;
}

int main(){
    /*
     * test data:
     * Z - number of test cases
     * N, MIN, MAX - number of insert values, min range, max range
     * N values to insert
     * Output:
     * sum
    */
    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    for(int i = 0 ; i < Z ; i++){
        int N, MI, MA;
        scanf("%d %d %d", &N, &MI, &MA);

        BSTnode* tree = NULL;

        int x;
        // insert
        for(int j = 0 ; j < N ; j++) {
            scanf("%d", &x);
            add_node(tree, x);
        }

        int sum = sum_in_range(tree, MI, MA);
        printf("%d\n", sum);

        // cleanup
        free_BST(tree);
    }
}
