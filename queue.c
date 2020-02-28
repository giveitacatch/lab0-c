#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    while (q_remove_head(q, NULL, 0))
        ;

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    if (!newh)
        return false;

    newh->value = malloc((strlen(s) + 1) * sizeof(char));

    if (!newh->value) {
        free(newh);
        return false;
    }

    // strcpy is not safe. strncpy does not guarantee '\n'-termination. Since we
    // just did malloc according to the length of s, we should be fine.
    strncpy(newh->value, s, strlen(s) + 1);
    newh->next = q->head;
    q->head = newh;

    // Increment size
    q->size++;

    if (q->size == 1) {
        // Point tail to head
        q->tail = q->head;
    }
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;

    if (q->size == 0)
        return q_insert_head(q, s);

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));

    if (!newt)
        return false;

    newt->value = malloc((strlen(s) + 1) * sizeof(char));

    if (!newt->value) {
        free(newt);
        return false;
    }

    // strcpy is not safe. strncpy does not guarantee '\n'-termination. Since we
    // just did malloc according to the length of s, we should be fine.
    strncpy(newt->value, s, strlen(s) + 1);
    newt->next = NULL;

    // Update tail
    q->tail->next = newt;
    q->tail = newt;


    //
    q->size++;

    if (q->size == 1) {
        // Point head to tail
        q->head = q->tail;
    }
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return false;

    list_ele_t *tmp = q->head;

    if (sp) {
        strncpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    q->head = q->head->next;

    if (q->size == 1) {
        // Point tail to head
        q->tail = q->head;
    }

    q->size--;
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (!q || !q->head)
        return;

    list_ele_t *tmp = NULL;
    list_ele_t *preNode = NULL;

    q->tail = q->head;

    while (q->head->next) {
        tmp = q->head->next;
        q->head->next = preNode;
        preNode = q->head;
        q->head = tmp;
    }

    q->head->next = preNode;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (!q || !q->head)
        return;

    // Merge sort, recursive
    q->head = mergeSortList(q->head);


    /*
    // Selection Sort
    //    list_ele_t *lastSorted, *nextIsMin;
    list_ele_t *curr, *prev;
    list_ele_t *min, *min_prev;


    for (int i = 0; i < q->size; i++) {
        curr = q->head;
        prev = q->head;
        min = q->head;
        min_prev = q->head;

        for (int j = i; j < q->size; j++) {
            if (strcmp(min->value, curr->value) > 0) {
                min = curr;
                min_prev = prev;
            }
            curr = curr->next;
            if (j != i)
                prev = prev->next;
        }

        if (min == q->head) {
            // head is the min
            q->tail->next = q->head;
            q->head = q->head->next;
            q->tail = q->tail->next;
            q->tail->next = NULL;
        } else {
            q->tail->next = min;
            min_prev->next = min->next;
            q->tail = q->tail->next;
            min->next = NULL;
        }
    }
    */


    /* Not working
        node = q->head;
        nextIsMin = q->head;

        while (node->next) {
            if (strcmp(nextIsMin->next->value, node->next->value) > 0) {
                nextIsMin = node;


        }

        for (int i = 1; i < q->size; i++) {
            node = lastSorted->next;
            nextIsMin = lastSorted;

            while (node->next) {
                printf("node value %s\n", node->value);
                if (strcmp(nextIsMin->next->value, node->next->value) > 0) {
                    nextIsMin = node;
                }
                node = node->next;
            }
            printf("finish while %d\n", i);
            if (nextIsMin != lastSorted) {
                list_ele_t *tmp = lastSorted->next;
                lastSorted->next = nextIsMin->next;
                nextIsMin->next = nextIsMin->next->next;
                lastSorted->next->next = tmp;
            }

            lastSorted = lastSorted->next;
        }

        q->tail = lastSorted;
        q->head = dummy->next;
    */


    return;
}

// mergeSort_nonRecursive(queue_t *q) {}


list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    if (!l1)
        return l2;

    if (!l2)
        return l1;

    if (strcmp(l1->value, l2->value) < 0) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}

list_ele_t *mergeSortList(list_ele_t *head)
{
    // Merge sort, recursive
    if (!head || !head->next)
        return head;

    // Split list
    list_ele_t *fast, *slow;
    fast = head->next;
    slow = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = NULL;

    // Sort
    list_ele_t *l1 = mergeSortList(head);
    list_ele_t *l2 = mergeSortList(fast);

    // merge
    return merge(l1, l2);
}
