1.) 
int HundredsHash(int num){
    return num % 1000;
}

2.)
int Hash19(int num){
    int sum = 0;
    int i = 10;
    while(num % i == 0){
        sum = sum + (num % i);
        i = i * 10;
    }

    return sum % 19;
}

3.)
int HashName(char *name){
    for(int sum = 0, int i = 0; char[i] != '\0'; i++){
        sum = sum + char[i];
    }

    return sum % 49;
}