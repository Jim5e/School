int insertClist(ArrayList AL, VHeap VH, CursorList *head){
    int ctr = 0;
    CursorList *trav;
    for(int i = 0; i < AL->studCtr; i++){
      for(trav = head; *trav != -1 && strcmp(VH->heap[*trav].stud.ID, AL->data[i].ID) < 0; trav = &VH->heap[*trav].link){}//traverse CB to CHECK

    
        if(*trav != -1){
            if(strcmp(VH->heap[*trav].stud.ID, AL->data[i].ID) != 0){
                int index = allocSpace(VH);
                if(index != -1){
                    VH->heap[index].stud = AL->data[i];
                    VH->heap[index].link = *trav;
                    *trav = index;
                    ctr++;
                }
            }
        }
    }
    return ctr;
}