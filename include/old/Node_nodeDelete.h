/*
 Given a binary search tree
   and a key, this function
   deletes the key and
   returns the new root
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minValueNode(root->right);

        // Copy the inorder
        // successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
*/

void nodeDelete(Node **node) {
    if (!node || !(*node))
        return;
    if (!((*node)->left)) {

    } else if (!((*node)->right)) {

    } else {

    }
//     if ((*node)->left == NULL) {
//         // Node *temp = *node;
//         // *node = (*node)->right;
//         // free(temp);
//     } else if ((*node)->right == NULL) {
//         // Node *temp = *node;
//         // *node = (*node)->left;
//         // free(temp);
//     } else {
// //         Node *temp = (*node)->right;
// //         while (temp && temp->left)
// //             temp = temp->left;
// //
// //         strcpy((*node)->word, temp->word);
// //         strcpy((*node)->translation, temp->translation);
// //
// //         nodeDelete(&(*node)->right);
//     }
//     tree_count--;
}
