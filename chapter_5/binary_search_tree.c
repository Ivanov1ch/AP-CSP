#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct bst_node
{
    int value;
    struct bst_node *left_child;
    struct bst_node *right_child;
} node;

node *root = NULL;

node *create_node(int node_value)
{
    node *new_node = malloc(sizeof(node));

    if (new_node)
    {
        new_node->value = node_value;
        new_node->left_child = NULL;
        new_node->right_child = NULL;

        return new_node;
    }
    else
    {
        printf("Heap Overflow\n");
        exit(-1);
    }
}

void insert(int value_to_insert)
{
    node *new_node = create_node(value_to_insert);

    int has_found_place = 0;
    node *current_node = root;

    if (!root)
    {
        root = new_node;
    }
    else
    {
        while (!has_found_place)
        {
            if (current_node->value > new_node->value)
            {
                // Go left
                if (!current_node->left_child)
                {
                    current_node->left_child = new_node;
                    has_found_place = 1;
                }
                else
                {
                    // Dive into the left level
                    current_node = current_node->left_child;
                }
            }
            else if (current_node->value < new_node->value)
            {
                // Go right
                if (!current_node->right_child)
                {
                    current_node->right_child = new_node;
                    has_found_place = 1;
                }
                else
                {
                    // Dive into the right level
                    current_node = current_node->right_child;
                }
            }
            else
            {
                printf("Value already exists in tree!");
                return;
            }
        }
    }
}

node *search(node *current_root, int value_to_search_for)
{
    if (!current_root || current_root->value == value_to_search_for)
    {
        return current_root;
    }
    else if (current_root->value < value_to_search_for)
    {
        return search(current_root->right_child, value_to_search_for);
    }
    else
    {
        return search(current_root->left_child, value_to_search_for);
    }
}

// Used to find inorder successor
node *find_minimum(node *current_root)
{
    if (!current_root)
    {
        return NULL;
    }
    else if (current_root->left_child) // node with minimum value will have no left child
    {
        return find_minimum(current_root->left_child);
    }
    return current_root;
}

node *delete(node *current_root, int node_value)
{
    if (!current_root)
    {
        return current_root;
    }

    if (node_value > current_root->value)
    {
        // Go right
        current_root->right_child = delete(current_root->right_child, node_value);
    }
    else if (node_value < current_root->value)
    {
        // Go left
        current_root->left_child = delete(current_root->left_child, node_value);
    }
    else
    {
        // Take action according to the type of node

        // Leaf
        if (!current_root->left_child && !current_root->right_child)
        {
            free(current_root);
            return NULL; // Recurse up (sets the left or right child pointer to this element to NULL)
        }

            // One child
        else if (!current_root->left_child || !current_root->right_child)
        {
            node *temp;

            if (!current_root->left_child)
            {
                temp = current_root->right_child;
            }
            else
            {
                temp = current_root->left_child;
            }

            free(current_root);
            return temp; // Recurse up
        }

            // Two children, find inorder successor on right-side subtree
        else
        {
            node *temp = find_minimum(current_root->right_child);
            current_root->value = temp->value;
            // Remove the node of the inorder successor
            current_root->right_child = delete(root->right_child, temp->value);
        }
    }
}

void print_tree(node *current_root, int current_layer)
{
    if (current_root)
    {
        printf("%d (layer %d)\n", current_root->value, current_layer);
    }

    if (current_root->left_child)
    {
        print_tree(current_root->left_child, current_layer + 1);
    }
    if(current_root->right_child)
    {
        print_tree(current_root->right_child, current_layer + 1);
    }
}

int main(void)
{
    for (int i = 10; i > 0; i--)
    {
        insert(i);
    }

    delete(root, 5);

    print_tree(root, 0);
}