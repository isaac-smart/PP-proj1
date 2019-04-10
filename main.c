#include <stdio.h>

int Encryption(void);
int Decryption(void);
int Sub_Cypher(void);

int main() {
    char c;
    printf("Select an option: \na) Rotation Cypher\n");
    printf("b) Rotation Cypher Attack(known key\nc) Substitution Cypher\n");
    printf("d) Substitution Cypher Attack(known key)\nSelection: ");
    scanf("%c", &c);
    switch(c) {
        case 'a': Encryption();
            break;
        case 'b': Decryption();
            break;
        case 'c': Sub_Cypher();
            break;
        default: 
            printf("Unknown Selection\n");
    }  
    return 0;
}

int Encryption(void) {
    char str[500];//Intiialising Word
    int key;
    printf("\nKey of encryption:<space> Phrase to be encrypted:\n");
    scanf("%d", &key);
    scanf("%[^\n]s", str);
    int i;
        //For loop to get every value of the string
        for(i=0; i < 500 && str[i] != 0; i++) {
            if(str[i] < 65);
            else { //If whitespace no change occurs
                if(str[i] >= 97 && str[i] <= 122) { 
                    str[i] = str[i] - 32; //IF statement make Capital
                }
                str[i] = str[i] + (key % 26); //Encrypting
                if(str[i] > 90) {
                    /*If ASCII number exceeds 90 and is not going to 
                    produce letter minus 26 to get letter*/
                    str[i] = str[i] - 26;
                }
            }
        }
    printf("%s\n", str);
    return 0;
}

int Decryption() {
    char str1[500];//Intiialising Decrytpion
    int key;
    printf("\nKey of decryption: <space> Phrase to be decrypted:\n");
    scanf("%d", &key);
    scanf("%[^\n]s", str1);
    int i;
        //For loop to get every value of the string
    for(i=0; (i < 500) && (str1[i] != 0); i++) {
        if(str1[i] < 65);
        else {
            str1[i] = str1[i] - (key % 26);
            if(str1[i] < 65) {
                str1[i] = str1[i] + 26;
            }
        }

    }
    printf("%s\n", str1);
    return 0;
}

int Sub_Cypher(void) {
    char str[500];//Intiialising Word
    char key[26];
    int keysize;
    printf("\nKey of encryption:(only lowercase letters)\n <enter> Size of key inputted:\n");
    scanf("%s %d", key, &keysize);
    printf("Phrase to be encrypted:");
    scanf("%[^\n]s", str);
    printf("\n");
    int i;//key into code
    int a = 97, z = 122, t; //a is the start usuallly a, z is the end
    char fullkey[26];
    int p;
    for( i = 0; i < 26; i++) { //for statement to intialise fullkey
        if(keysize > i) { //if part of word at code beginning
            fullkey[i] = key[i]; // makes it eqaul new key
            for(p=0; p < i; p++) { //unless already addressed(double letter)
                if(key[p] == fullkey[i]) { //assigns to lowest available number
                    fullkey[i] = z;
                    z--;
                }
            }
        }
        else {
            t = 0;
            fullkey[i] = a; //Full key eqauls a
            for(p = 0; p <= keysize; p++) { //to intialise key outside the input
                if(fullkey[p] == fullkey[i] ) { //however if equals something already in key
                    a++;
                }
                
            }
            fullkey[i] = a;
            a++;

        }

    }
    printf("%s", fullkey);
    return 0;
}
