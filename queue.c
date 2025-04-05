#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define reverse_list_for_each_safe(node, safe, head)             \
    for (node = (head)->prev, safe = node->prev; node != (head); \
         node = safe, safe = node->prev)

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head)
        return NULL;

    INIT_LIST_HEAD(head);

    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;

    element_t *iter = NULL;
    element_t *safe = NULL;
    list_for_each_entry_safe(iter, safe, head, list) {
        list_del(&iter->list);
        q_release_element(iter);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *element = malloc(sizeof(element_t));
    if (!element)
        return false;

    element->value = strdup(s);
    if (!element->value) {
        free(element);
        return false;
    }
    list_add(&element->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *element = malloc(sizeof(element_t));
    if (!element)
        return false;

    element->value = strdup(s);
    if (!element->value) {
        free(element);
        return false;
    }
    list_add_tail(&element->list, head);

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *element = list_first_entry(head, element_t, list);
    if (sp && element->value) {
        strncpy(sp, element->value, bufsize);
    }
    list_del(&element->list);

    return element;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *element = list_last_entry(head, element_t, list);
    if (sp && element->value) {
        strncpy(sp, element->value, bufsize);
    }
    list_del(&element->list);

    return element;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each(li, head)
        len++;

    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || !head->next)
        return false;

    struct list_head *prev = NULL;
    struct list_head *slow = head;
    struct list_head *fast = head->next;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = slow->next;
    list_del(slow);

    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head))
        return false;

    element_t *iter = NULL;
    element_t *next = NULL;
    bool dup = false;

    list_for_each_entry_safe(iter, next, head, list) {
        if (&next->list != head && !strcmp(iter->value, next->value)) {
            list_del(&iter->list);
            dup = true;
        } else if (dup) {
            list_del(&iter->list);
            dup = false;
        }
    }

    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head || list_empty(head))
        return;

    struct list_head *iter;
    struct list_head *next;

    list_for_each_safe(iter, next, head) {
        if (next != head) {
            list_del(iter);
            list_add(iter, next);
            next = iter->next;
        }
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    struct list_head *iter;
    struct list_head *safe;

    reverse_list_for_each_safe(iter, safe, head)
    {
        if (safe != head->prev)
            list_move_tail(iter, head);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
