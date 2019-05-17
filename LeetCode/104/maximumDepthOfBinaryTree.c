/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    if(root == NULL) return 0;
    int h1, h2;
    h1 = maxDepth(root->left);
    h2 = maxDepth(root->right);
    return h1>h2?h1+1:h2+1;
}