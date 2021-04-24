typedef struct pqueue *pqueue;
pqueue allocate_pqueue(heap h, boolean(*)(void *, void *));
void deallocate_pqueue(pqueue q);
void pqueue_insert(pqueue q, void *v);
void *pqueue_peek(pqueue q);
void *pqueue_pop(pqueue q);
void pqueue_reorder(pqueue q);
typedef closure_type(pqueue_element_handler, boolean, void *);
boolean pqueue_walk(pqueue q, pqueue_element_handler h);
