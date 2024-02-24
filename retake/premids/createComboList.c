ComboList createComboList(StudLink *L){
    ComboList combolist = (ComboList) malloc (sizeof(struct List));
    if(combolist != NULL){
        //initialize the comboList
        combolist->IT = NULL;
        combolist->CS.count = 0;
        //add rear to IT so we can skip traversal
        StudLink *rear = &combolist->IT;

        //traverse and decide
        Studlink *trav;
        for(trav = L; *trav != NULL;){
            //check course then decide
            if(strcmp((*trav)->stud.course, "BSIT") == 0){
                StudLink newNode = (StudLink) malloc (sizeof(struct node));
                if(newNode != NULL){
                    newNode->stud = (*trav)->stud;
                    newNode->link = NULL;

                    *rear = newNode;
                    rear = &(*rear).link;
                }
                
                //delete node in the given sorted list
                StudLink temp = *trav
                (*trav) = temp->link;
                free(temp);
            }else if(strcmp((*trav)->stud.course, "BSCS") == 0){
                if(combolist->CS.count < MAX){ // check for space
                    combolist->CS[count].stud = (*trav)->stud;
                    count++;                
                }

                //delete node in the given sorted list
                StudLink temp = *trav
                (*trav) = temp->link;
                free(temp);
            }else{
                trav = &(*trav).link;
            }
        }
    }

    return combolist;
}