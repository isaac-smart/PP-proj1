#include <stdio.h>
#include <ctype.h>

char Encryption(int key, char c);
char Decryption(int key, char c);
int Sub_Cypher(void);
int Sub_Decryption(void);

int main() {
    FILE *input;
    input = fopen("input1", "r");
    if(input == NULL) {
        perror("fopen()"); 
        return 0; 
    } 

    //Menu key below
    int key;
    char menu;
    printf("Select an option: \na) Rotation Cypher\n");
    printf("b) Rotation Cypher Attack(known key)\nc) Substitution Cypher\n");
    printf("d) Substitution Cypher Attack(known key)\nSelection: ");
    scanf("%c", &menu);
    switch(menu) {
        case 'a': 
        printf("\nKey of encryption:(Number) <enter>\n");
        scanf("%d", &key);
        while(feof(input) == 0) {
            char c;
            fscanf(input, "%c", &c);
            c = Encryption(key, c);
            printf("%c", c);
        }
            break;
        case 'b': 
        printf("\nKey used to encrypt:(Number) <enter>\n");
        scanf("%d", &key);
        while(feof(input) == 0) {
            char c;
            fscanf(input, "%c", &c);
            c = Decryption(key, c);
            printf("%c", c);
        }
            break;
        case 'c': 
            Sub_Cypher();
            break;
        case 'd': Sub_Decryption();
            break;
        default:
            printf("Unknown Selection\n");
    } 
    return 0;
}

char Encryption(int key, char c) {
        if(isupper(c) || islower(c) ) {
            if(islower(c)) { 
                c = c - 32; //IF statement make Capital
            }
            c = c + (key % 26); //Encrypting
            if(c > 90) {
                /*If ASCII number exceeds 90 and is not going to 
                produce letter minus 26 to get letter*/
                c = c - 26;
            }        
        }
    return c;
}

char Decryption(int key, char c) {
        if(isupper(c)) {
            c = c - (key % 26);
            if(c < 65) {
                c = c + 26;
            }
        }
    return c;
}

int Sub_Cypher(void) {
    char key[26];
    int keysize;
    keysize = 0;
    printf("\nKey of encryption:\n");
    scanf("%s", key);
    int i;//variable used in for statement
    for(i=0; key[i] != 0; i++) {
        keysize++;
    }
    int a = 65, z = 90; //variables used to create key
    char fullkey[26]; //the string used to hold the whole 26 letter key
    int p;
    /*for statement to create a full key(all individual 26 letters)
    from inputted key*/
    for( i = 0; i < 26; i++) { 
        if(islower(key[i])) {
            key[i] = key[i] - 32;
        }
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
            fullkey[i] = a; //Full key equal a for if statement
            for(p = 0; (p < keysize); p++) { //to intialise key outside the input
                    if(fullkey[p] == fullkey[i]) {
                    a++;
                    fullkey[i] = a;
                    p = -1;
//If any value in key equals the next desired number the number next in 
//the alphabet is subbed into the key and the loop begins again
                }
            }
            fullkey[i] = a; //make fullkey equal a again
            a++;//add for next number
        }
    }  
    // Substituting fullkey created into phrase that needs to be decrytpted
    printf("Encryption:\n");
    FILE *input;
    input = fopen("input1", "r");
    if(input == NULL) {
        perror("fopen()"); 
        return 0; 
    }
    while(feof(input) == 0) {
        char c;
        fscanf(input, "%c", &c);
            
        if(islower(c)) {
            c = c - 32;
        }
        if(isupper(c)) { //only code not whitespace or grammar
            c = c - 65; // minus 65 to get number 0-25
            int p;
            p = c; //make p equal this number
            c = fullkey[p]; 
        }
        printf("%c", c);
    }
    return 0;
}
 int Sub_Decryption(void) {
     
     return 0;
 }

