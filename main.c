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
    printf("\nThe key of decryption:\n");
    scanf("%d", &key);
    printf("\nPhrase to be encrypted:\n");
    scanf("%[^\n]s", str);
    int i;
        //For loop to get every value of the string
        for(i=0; i < 500 && str[i] != 0; i++) {
            if(str[i] != 32) { //If whitespace no change occurs
                if(str[i] >= 97 && str[i] <= 122) { 
                    str[i] = str[i] - 32; //IF statement make Capital
                }
                str[i] = str[i] + key; //Encrypting
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
    printf("\nThe key of decryption:\n");
    scanf("%d", &key);
    printf("\nPhrase to be decrypted:\n");
    scanf("%[^\n]s", str1);
    int i;
        //For loop to get every value of the string
    for(i=0; (i < 26) && (str1[i] != 0); i++) {
        if(str1[i] != 32) {
            str1[i] = str1[i] - key;
            if(str1[i] < 65) {
                str1[i] = str1[i] + 26;
            }
        }

    }
    printf("%s\n", str1);
    return 0;
}

int Sub_Cypher(void) {
    
}
