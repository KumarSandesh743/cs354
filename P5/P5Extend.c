node_t *head;
void * heap;
int allocation=0;

void * my_malloc(int size){
	node_t* check = head;
	bool flag=false;
	bool f2 = false;
	do
	{
		if (check->length>=size+sizeof(occupied_t)){
			flag=true;
			break;
		}
		check=check->next;
	} while (check->next!=NULL);

	if (flag==true){
		if (check==head){
			f2 = true;
		}
		void* temp_return=NULL;
		node_t *p=check;

		int initial_length=check->length;
		
		occupied_t* temp = (occupied_t *)p;
		temp->length_2=size;
		temp->magic=magicNumber;
		check=(node_t*)((char*)check+size+sizeof(occupied_t));
		check->length=initial_length-size-sizeof(occupied_t);
		if (f2==true){
			head = check;
			head->next == NULL;
		}
		temp_return=(void*)((char*)p+sizeof(occupied_t));
		printf("in malloc:pointer returned:%p\n",temp_return);
		allocation++;
		return temp_return;
	}
	else{
		printf("Sorry, Sufficient space not found");
		return NULL;
		}
}

void * my_free(void * ptr){
	printf("free called\n");
	occupied_t* temp =(occupied_t*)((char*)ptr - 8);
	if (temp->magic == magicNumber){
		int retain = temp->length_2 + sizeof(occupied_t);
		void * address = temp;
		node_t * a = head->next;
		node_t * free_node = address;
		free_node->length=temp->length_2;
		head->next=free_node;
		free_node->next = a;
	}
	else{
		printf("INVALID PTR   \n");
		exit(1);
	}
}
