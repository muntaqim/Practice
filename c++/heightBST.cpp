int heightBST(Node *head)
{
    if (head == NULL)
        return 0;

    return (1 + max(heightBST(head->left),
                    heightBST(head->right)));
}
