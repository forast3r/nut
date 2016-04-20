//TODO: not in final
#include <malamute.h>

/*
 *      HEADER FILE
 *
 */
typedef struct {
	int oid_value;			/* OID value */
	const char *info_value;	/* INFO_* value */
} info_lkp_t;

typedef struct {
	void **values;
	int size;
	int capacity;
	char *name;
} alist_t;

typedef enum {
    ERR = -1,
    OK
} state_t;

// Create and initialize info_lkp_t
info_lkp_t *
    info_lkp_new (int oid, const char *value);

// Destroy and NULLify the reference to info_lkp_t
void
    info_lkp_destroy (void **self_p);

/*
 *
 *  C FILE
 *
 */

info_lkp_t *
info_lkp_new (int oid, const char *value)
{
    info_lkp_t *self = (info_lkp_t*) malloc (sizeof (info_lkp_t));
    assert (self);
    memset (self, 0, sizeof (info_lkp_t));
    self->oid_value = oid;
    self->info_value = strdup (value);
    return self;
}

void
info_lkp_destroy (void **self_p)
{
    if (*self_p) {
        info_lkp_t *self =(info_lkp_t*) *self_p;

        if (self->info_value) {
            free ((char*)self->info_value);
            self->info_value = NULL;
        }
        free (self);
        *self_p = NULL;
    }
}

void alist_append(alist_t *self,void *element){
/*  if(self->values==NULL){
    self->values=(void**)malloc(sizeof(void*));
    assert(self->values);
    self->values[self->size]=NULL;
  }else{
    self->values=realloc(self->values,self->size*sizeof());
  }*/
/*TODO Check when allocatd memory get full for reallocate more*/
  if(self->size<self->capacity){
  self->values[self->size]=element;
  self->size++;
  }
}

void alist_delete_allvalues(alist_t *self){
  do{
    info_lkp_destroy((void**)&self->values[self->size]);
    self->size--;
  }while(self->size>0);
  free(self->values);
}

/*  Use common API ad info_lkp_t*/
// step #1
alist_t *alist_new (const char *name){
  alist_t *index=(alist_t*)malloc(sizeof(alist_t));
  assert(index);
  memset(index, 0, sizeof(alist_t));
  index->name=strdup(name);
  index->size=0;
  index->values=(void**)malloc(16*sizeof(void*));
  assert(index->values);
  index->capacity=16;
  index->values[index->size]=NULL;
  return index;
}

// step #2
//alist_append (alist_t *self, void *item);

// step #3
//alist_destroy (alist_t **self_p);

// step #4
//alist_set_destructor (alist_t *);


int main ()
{
    //info_lkp_t * lkp = info_lkp_new (1, "one");
    const char *attrs[]={"Sensitivity","1","","OK",""};
    alist_t *index=alist_new(attrs[0]);
    info_lkp_t *element=info_lkp_new(atoi(attrs[1]),attrs[3]);
    alist_append(index,element);
    
    alist_delete_allvalues(index);
    //index_add(index,0,attrs);
    //index_del(index,0);
    free(index->name);
    
    free(index);
    

}
