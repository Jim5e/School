studHeap createInfoHeap(StudList *LL, char *course){
    //init Heap
    studHeap retval;
    retval.studCnt = 0;

    //locate and REMOVE 2nd years that are given COURSE from L.list
    studList *trav;
    for(trav = LL; *trav != NULL; ){

        //find 2nd yrs && same course
        if((*trav)->stud.yrLevel = 2 && strcmp((*trav)->stud.course, course)){
            //save linkedlist location & adjust link
            studList temp = *trav;
            *trav = temp->slink;

            //insert in maxHeap arranged by ID
            if(retval.studCnt < MAX){ //if theres still space in heap
                retval.data.[studCnt].sName = temp->stud.name; //NAME
                strcpy(retval.data.[studCnt].ID, temp->stud.ID); //ID
                
                //bubble up to fix POT
                for(int childNdx = retval.studCnt; childNdx != 0;){
                    int parentNdx = (childNdx-1)/2;

                    if(strcmp(retval.data[childNdx].ID, retval.data[parentNdx].ID) > 0){ //if child > parent, swap
                        swapStudInfo(&(retval.data[childNdx]), &(retval.data[parentNdx]));
                    }

                    childNdx = parentNdx;
                }

                studCnt++;
            }

            free(temp);
        }else{
            trav = &(*trav)->slink
        }

    }
    return retval;
}

//11:14pm
//11:50pm