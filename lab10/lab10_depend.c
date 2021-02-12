#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

struct bin_tree {
    int data;
    struct bin_tree * right, * left;
};
typedef struct bin_tree node;
int found;

void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data)
    {
        insert(&(*tree)->right, val);
    }

}

void printer_task(int data)
{
    printf("Found value in tree: %d\n", data);
}

void search(node ** tree, int val)
{
        if((*tree)->data == val)
        {
            found = val;
            #pragma omp depend(in: found)
            printer_task((*tree)->data);
            return;
        }
        if(val < (*tree)->data)
        {
            #pragma omp task
            search(&((*tree)->left), val);
        }
        else
        {
            #pragma omp task
            search(&((*tree)->right), val);
        }
}

int main(int argc, char *argv[])
{
    node *root;
    node *tmp;
    root = NULL;

    // Inserting nodes into the tree
    insert(&root, 400);
    for(int i=0; i < 5000000; i++){
        insert(&root, rand()%500000);
    }

    double start = omp_get_wtime();

    omp_set_num_threads(atoi(argv[1]));
    // Parallel search
    #pragma omp parallel
    #pragma omp single
    search(&root, 400);

    double end = omp_get_wtime();
    printf("start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);

    return 0;
}