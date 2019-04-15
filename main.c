#include <stdio.h>
#include <ctype.h>

int Encryption(void);
int Decryption(void);
int Sub_Cypher(void);
int Sub_Decryption(void);

int main() {
    FILE *input;
    input = fopen("input1", "r");
    if(input == NULL) {
        perror("fopen()"); 
        return 0; 
    } 
    int tmp = 0;
    char str[500];
    while(feof(input) == 0) {
        char c;
        
        fscanf(input, "%c", &c);
        str[tmp] = c;
        tmp++;
        
    }
    printf("The Encryption or Decrytption inputted:\n%s\n", str);
    //Above is putting input1 into string str
    char c;
    printf("Select an option: \na) Rotation Cypher\n");
    printf("b) Rotation Cypher Attack(known key)\nc) Substitution Cypher\n");
    printf("d) Substitution Cypher Attack(known key)\nSelection: ");
    scanf("%c", &c);
    switch(c) {
        case 'a': Encryption();
            break;
        case 'b': Decryption();
            break;
        case 'c': Sub_Cypher();
            break;
        case 'd': Sub_Decryption();
            break;
        default:
            printf("Unknown Selection\n");
    }  
    return 0;
}

int Encryption() {
    int key;
    int str[500];
    printf("\nKey of encryption:(Number) <enter>\n");
    scanf("%d", &key);
    int i;
    for(i=0; i < 500 && str[i] != 0; i++) {
        if(isupper(str[i]) || islower(str[i]) ) {
            if(islower(str[i])) { 
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
    char str[500];//Intiialising Decrytpion
    int key;
    printf("\nKey of decryption: <space> Phrase to be decrypted:\n");
    scanf("%d", &key);
    scanf("%[^\n]s", str);
    int i;
        //For loop to get every value of the string
    for(i=0; (i < 500) && (str[i] != 0); i++) {
        if(isupper(str[i])) {
            str[i] = str[i] - (key % 26);
            if(str[i] < 65) {
                str[i] = str[i] + 26;
            }
        }
    }
    printf("%s\n", str);
    return 0;
}

int Sub_Cypher(void) {
    char str[500];//Intiialising Word
    char key[26];
    int keysize;
    printf("\nKey of encryption:\n <enter> Size of key inputted:\n");
    printf("<Space> Phrase to be encrypted:\n");
    scanf("%s %d", key, &keysize);
    scanf("%[^\n]s", str);
    printf("\n");
    printf("sizeof of array: %d\n", (int) sizeof(key));
    int i;//variable used in for statement
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
    for(i=0; i < 500; i++) {
        if(islower(str[i])) {
            str[i] = str[i] - 32;
        }
        if(isupper(str[i])) { //only code not whitespace or grammar
            str[i] = str[i] - 65; // minus 65 to get number 0-25
            int p;
            p = str[i]; //make p equal this number
            str[i] = fullkey[p]; 
        }
    }
    printf("Encryption:\n");
    
    printf("%s\n", str);
    
    return 0;
}
 int Sub_Decryption(void) {
     
     return 0;
 }



