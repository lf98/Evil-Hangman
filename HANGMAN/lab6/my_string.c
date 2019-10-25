#include "my_string.h"
#include "status.h"
#include "generic.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node{
  MY_STRING data;
  MY_STRING key;
  struct node* left;
  struct node* right;
  struct node* parent;

};

typedef struct node Node;





struct my_string{
  int size;
  int capacity;
  char*  data;
};
typedef struct my_string My_string;

typedef void* GENERIC_VECTOR;



struct generic_vector
{
  int size;
  int capacity;
  Item* data;
  Status(*Item_assignment)(Item* left, Item Right);
  void(*item_destroy)(Item* phItem);
  
  
};

typedef struct generic_vector Generic_vector;

MY_STRING my_string_init_default(void)
{
  My_string* pstring;
  
  pstring  =(My_string*) malloc(sizeof(My_string));
  if (pstring != NULL)
    {
      pstring->size = 0;
      pstring->capacity = 7;
      pstring->data = (char*)malloc(sizeof(char) * pstring->capacity + 1);
      if (pstring == NULL)
	{
	  free(pstring);
	  return NULL;
	 }
    }
  
  return(MY_STRING)pstring;
}

void my_string_destroy(Item* pItem)
{
  
  My_string* pstring = (My_string*)*pItem;
  if(pstring != NULL)
    {
      
      free(pstring->data);
      free(pstring);
      *pItem = NULL;
    }
}

MY_STRING my_string_init_c_string(const char*c_string)
{
  My_string* string;
  int i, size;
  size = 0;
  for(i = 0; c_string[i] != '\0'; i++)
    size++;
  string  = (My_string*)malloc(sizeof(My_string));
  if (string != NULL)
    {
      string->size = size;
      string->capacity = (string->size)+1;
      string->data = (char*)malloc(sizeof(char) * (string->capacity));
      if(string->data == NULL)
	return NULL;
      for(i = 0; i < string->size; i++)
	{
	  string->data[i] = c_string[i];
	}
      string->data[i] = '\0';
      return(MY_STRING)string;
      
    }
  return NULL; 
}

int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* string = (My_string*)hMy_string;
  return string->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string* string = (My_string*)hMy_string;
  return string->size;
}
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  int i;
  My_string* stringL = (My_string*)hLeft_string;
  My_string* stringR = (My_string*)hRight_string;
  for(i= 0;stringL->data[i] != '\0' && stringR->data[i]!= '\0'; i++)
    {
      if(stringL->data[i] - stringR->data[i] != 0)
	{
	  
	  return stringL->data[i]- stringR->data[i];
	}
      
	
    }
  
  
    return 0;

}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
 
  My_string* string = (My_string*)hMy_string;
  
  int i, j = 0;
  
  char* temp;
  char c;
  int noc;
  int size = 0;
  noc = fscanf(fp, " %c", &c);
  if(noc != 1)
    return FAILURE;
  else if(string->data == NULL)
    {
      string = my_string_init_default();
    }
  else if(fp == NULL)
    {
      fclose(fp);
      return FAILURE;
    }
  for(i = 0; i < string->capacity-1; i++)
    {
      string->data[i] = '\0';
      
    }
  
  string->size = 0;
  
  while(noc == 1 && !isspace(c))
    {
      
      for(j = size; j < string->capacity && noc != -1 && !isspace(c) ;j++)
    	{
	  string->data[j] = c;
	  noc = fscanf(fp, "%c", &c);
	  string->size++;
	  size++; 
	}
      if(j >= string->capacity)
	{
	  
	  temp = (char*)malloc(sizeof(char) * (string->capacity * 2)+1);
	      if(temp == NULL)
		{
		  
		  free(temp);
		  temp = NULL;
		  return FAILURE;
		}
	    
	      else
		{
		  for(i = 0; i <= string->size-1; i++)
		    {
		      temp[i] = string->data[i];
		    }
		  
		  
		  free(string->data);
		  string->data = NULL;
		  string->data = temp;
		  string->capacity*=2;
		  
		}
          }
	
    }
  
  if(isspace(c))
    { ungetc(c, fp);
      return SUCCESS;
      }
  return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  My_string* string = (My_string*)hMy_string;
  int i;
  for(i=0; i<=string->size; i++)
    {
      if(string->data[i] == ' ')
	{
	  
	  return FAILURE;

	}
      else
      fprintf(fp, "%c",  string->data[i]);
      
    }
  return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
  My_string* string = (My_string*)hMy_string;
  char* temp;
  int i;
  if(string == NULL)
    return FAILURE;
  if(string->size >= string->capacity)
    {
      temp = (char*)malloc(sizeof(char) *  (string->capacity * 2));
			   if(temp == NULL)
			     {
			       return FAILURE;
			     }
			   for(i = 0; i <= string->size; i++)
			     {
			       temp[i] = string->data[i];
			     }
			   free(string->data);
			   //string->data = NULL;
			   string->data = temp;
			   string->capacity *= 2;       
    }
  
  string->data[string->size] = item;
  string->size++;
  return SUCCESS;
    
 
			    

}

Status my_string_pop_back(MY_STRING hMy_string)
{
  My_string* string = (My_string*)hMy_string;
  
  if(string->size <= 0)
    {
      return FAILURE;
    }
  else
    {
      
      //string->size--;
      if(string->size > 0)
	string->data[string->size] = '\0';
      string->size--;
      return SUCCESS;
    }
  
  
}

char* my_string_at(MY_STRING hMy_string, int index)
{
  My_string* string = (My_string*)hMy_string;
  if(index <= string->size)
  {
    return &(string->data[index]);
  }
  else
    {
      return NULL;
    }
}

char* my_string_c_str(MY_STRING hMy_string)
{
  My_string* string = (My_string*)hMy_string;
  my_string_push_back(hMy_string, '\0');
  string->size--;
  return string->data;
  
  
     
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* original = (My_string*)hResult;
  My_string* append = (My_string*)hAppend;
  char* temp;
  int i;
  int j;

  if(original->data != NULL && append->data != NULL)
    {
      temp = (char*)malloc(sizeof(char) * ((original->size) + (append->size) +2));
      if(temp == NULL)
        {
          free(temp);
          temp = NULL;
          return FAILURE;
        }
      for(i = 0; i <= original->size; i++)
        {
          temp[i] = original->data[i];
        }
      j = i;
      for(i = 0; i <= append->size; i++, j++)
	{
	  temp[j] = append->data[i];
	}
    }
  else
    {
      free(original);
      original = NULL;
      free(append);
      append = NULL;
      return FAILURE;
    }
  free(original->data);
  original->data = NULL;
  original->data = temp;
  original->size += append->size;
  original->capacity += append->capacity - 1;
  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* string = (My_string*)hMy_string;
  if(string->size > 0)
    return FALSE;
  else
    return TRUE;

}

Status my_string_assignment(Item* pLeft, Item Right)
{
  
  if(*pLeft == NULL)
    {
      *pLeft = my_string_init_c_string(my_string_c_str(Right));
      
      
      return SUCCESS;
    }
  else
    {
      my_string_destroy(pLeft);
      *pLeft = my_string_init_c_string(my_string_c_str(Right));
      
      
      return SUCCESS;
      }
  return FAILURE;

  
}



GENERIC_VECTOR generic_vector_init_default(
	   Status (*assignment)(Item* phleft, Item Right), void(*destroy)(Item* phItem)
)
{
  Generic_vector* pVector;
  pVector = (Generic_vector*)malloc(sizeof(Generic_vector));
  int i;
  if(pVector != NULL)
    {
      pVector->size = 0;
      pVector->capacity = 1;
      pVector->data = (Item*)malloc(sizeof(Item) * pVector->capacity);
      if(pVector->data == NULL)
	{
	  free(pVector);
	  return NULL;
	}
      
      pVector->Item_assignment = assignment;
      pVector->item_destroy = destroy;
      for(i = 0; i < pVector->capacity; i++)
	{
	  pVector->data[i] = NULL;
	}
    }
  return (GENERIC_VECTOR)pVector;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, Item item)
{
  Generic_vector* pVector = (Generic_vector*)hVector;
  Item* temp;
  int i;

  if(pVector->size >= pVector->capacity)
    {
      temp = (Item*)malloc(sizeof(Item) * 2 * pVector->capacity);
      if(temp == NULL)
	{
	  return FAILURE;
	}
      for(i = 0; i < pVector->size; i++)
	{
	  temp[i] = pVector->data[i];
	}
      pVector->capacity *=2;
      for(;i<pVector->capacity; i++)
	{
	  temp[i] = NULL;
	}
      free(pVector->data);
      pVector->data = temp;
    }
  if (pVector->Item_assignment(&(pVector->data[pVector->size]), item) == SUCCESS)
    {
      pVector->size++;
      return SUCCESS;
    }
  return FAILURE;
}

int generic_vector_get_size(GENERIC_VECTOR hVector)
{
  Generic_vector* pVector = (Generic_vector*)hVector;
  return pVector->size;


}
int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
  Generic_vector* pVector = (Generic_vector*)hVector;
  return pVector->capacity;


}
Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
  Generic_vector* pVector = (Generic_vector*)hVector;

  if (pVector->size <= 0)
    {
      return FAILURE;
    }
    else
      {
      
	pVector->item_destroy(&pVector->data[pVector->size-1]);
	pVector->size--;
	return SUCCESS;
      }

}

Boolean generic_vector_empty(GENERIC_VECTOR hVector, int index)
{
  Generic_vector* pVector = (Generic_vector*)hVector;
  return (Boolean)(pVector->size == 0);


}

Item generic_vector_at(GENERIC_VECTOR hVector, int index)
{
  Generic_vector* pVector = (Generic_vector*)hVector;
  if (index < 0 || index >= pVector->size)
    {
      return NULL;
    }
  return pVector->data[index];

}

void generic_vector_destroy(GENERIC_VECTOR* hVector)
{
  Generic_vector* pVector = (Generic_vector*)*hVector;
  if(pVector->data != NULL && pVector != NULL)
    {
      int i;
      for(i = 0; i < pVector->size; i++)
	pVector->item_destroy(&pVector->data[i]);
      free(pVector->data);
  
      free(pVector);
      *hVector = NULL;
      
    }
  return;
  

}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
  
  int i = 0;
  if(isupper(guess) )
    {
      guess = toupper(guess);
    }
  my_string_assignment((Item*)&new_key, (Item)current_word_family);
  
  for(i = 0; i < my_string_get_size(word); i++)
    {
      if(*(my_string_at(word, i)) == guess)
	{
	  *my_string_at(new_key, i) = guess;
	 
	}
    }
  
  return SUCCESS;
  if(new_key == NULL || current_word_family == NULL)
    {    
      return FAILURE;
    }
  
  

}

MY_STRING key_init_default(MY_STRING key, int word_length)
{
  int i  = 0;
  if(key == NULL)
    {  
      key = my_string_init_default();
    }
  else
    {
      while(!my_string_empty(key))
	{
	  my_string_pop_back(key);
	}
    }
    while( i < word_length)
	{
	  my_string_push_back(key, '-');
	  i++;
	}
    return key;
    
  

}





void insert(Node** proot, MY_STRING string)
{
  if(*proot == NULL)
    {
      *proot = (Node*)malloc(sizeof(Node));
      if(*proot == NULL)
	{
	  return;
	 
	}
    }
      (*proot)->data = string;
      (*proot)->left = NULL;
      (*proot)->right = NULL;
      if(my_string_compare((*proot)->data, string) < 0)
	insert((&(*proot)->left), string);
 

      else if(my_string_compare((*proot)->data, string) > 0)
        insert((&(*proot)->left), string);
}
Node* init_tree(GENERIC_VECTOR* vector, int word_length)
{
  
    return NULL;
}

Node* search_tree(Node* tree)
{
  return NULL;
}

void destroy_tree(Node* tree)
{
  return;
}
