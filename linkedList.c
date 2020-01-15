typedef struct node 
{
    unsigned short int number;
    struct node *next;
} node_t;

void print_list(node_t *head) 
{
    node_t *current = head;

    while (current != NULL) {
        printf("%d\n", current->number);
        current = current->next;
    }
}

void push(node_t **head, int val) 
{
    node_t *new_node;
    new_node = malloc(sizeof(node_t));

    new_node->number = val;
    new_node->next = *head;
    *head = new_node;
}

int pop(node_t **head) 
{
    int retval = -1;
    node_t *next_node = NULL;

    if (*head == NULL) 
    {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->number;
    free(*head);
    *head = next_node;

    return retval;
}

void deleteNode(node_t **head_ref, int position) 
{
    if (*head_ref == NULL)
        return;

    node_t *temp = *head_ref;

    if (position == 0) 
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return;

    node_t *next = temp->next->next;

    free(temp->next);

    temp->next = next;
}

void delete_by_value(node_t **head_ref, int key) 
{
    node_t *temp = *head_ref, *prev;

    if (temp != NULL && temp->number == key) 
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->number != key) 
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;

    free(temp);
}