void insertCar(BST *BSTptr, Vheap VH, Car Elem){
    if(VH.avail == -1){
        printf("Cannot insert. Heap is full.");

    }else{
        //find location to insert
        BST *trav;
        for(trav = BSTptr; *trav != NULL && strcmp(Elem, VH->heap(*trav).car.model) != 0; ){
            trav = (strcmp(Elem, VH->heap[*trav].car.model) > 0) ? &(VH->heap[*trav].RC) : &(VH->heap[*trav].LC);
        }        

        //allocate mem and insert
        if(*trav == -1){
            //alocate
            int temp = VH->avail;
            VH->avail = VH.heap[temp].LC;

            //insert
            *trav = temp;
            VH->heap[temp].car = Elem;
            VH->heap[temp].LC = -1;
            VH->heap[temp].RC = -1;
        }
    }

}

//10:51pm start
//11:05 fin