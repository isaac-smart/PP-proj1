#include <stdio.h>
#include <ctype.h>

char Encryption(int key, char c);
char Decryption(int key, char c);
int Sub_Cypher(void);
int Sub_Decryption(void);
int Day_1_Sub_Decrytpion(void);


int main() {
    FILE *input;
    FILE *output;
    FILE *read;
    input = fopen("input.txt", "r");
    if(input == NULL) {
        perror("fopen()"); 
        return 0; 
    } 
    output = fopen("output.txt", "w+");
    read = fopen("google-10000-english.txt", "r");
    //Menu key below
    int key;
    char menu;
    printf("Select an option: \na) Rotation Cypher\n");
    printf("b) Rotation Cypher Attack(known key)\nc) Substitution Cypher\n");
    printf("d) Substitution Cypher Attack(known key)\ne) Unknown Key Rotation Cypher");
    printf("\nf) Day 1 Substitution Cypher(1)");
    printf("\nSelection: ");
    scanf("%c", &menu);
    switch(menu) {
        case 'a': 
        printf("\nKey of encryption:(Number) <enter>\n");
        scanf("%d", &key);
        printf("Rotation Encryption:\n");
        while(feof(input) == 0) {
            char c;
            fscanf(input, "%c", &c);
            c = Encryption(key, c);
            printf("%c", c);
            fprintf(output, "%c", c);
        }
            break;
            
        case 'b': 
        printf("\nKey used to encrypt:(Number) <enter>\n");
        scanf("%d", &key);
        printf("Rotation Decryption:\n");
        while(feof(input) == 0) {
            char c;
            fscanf(input, "%c", &c);
            c = Decryption(key, c);
            printf("%c", c);
            fprintf(output, "%c", c);
        }
            break;
            
        case 'c': 
        Sub_Cypher();
        break;
            
        case 'd': 
        Sub_Decryption();
        break;
        
        case 'e':
        for(key = 0; key < 26; key++) {
            char c; 
            int t;
            int words = 0;
            while(feof(input) == 0) {
                fscanf(input, "%c", &c);
                c = Encryption(key, c);
                c = tolower(c);
                printf("%c", c);
                fprintf(output, "%c", c);
            }
            fseek(output, 0, SEEK_SET);
            //Testing the similarity first 5 words against the most common 10 000 words
            char testing[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', '\0'};
            fscanf(output, "%s", testing);
            char testing1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', '\0'};
            fscanf(output, "%s", testing1);
            char testing2[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', '\0'};
            fscanf(output, "%s", testing2);
            char testing3[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', '\0'};
            fscanf(output, "%s", testing3);
            char testing4[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', '\0'};
            fscanf(output, "%s", testing4);
            for(t=0; t < 10000; t++) {
                char dictionary[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', '\0'};
                fscanf(read, "%s", dictionary);    
                if(strcmp(testing, dictionary) == 0) {
                words++;
                }
                if(strcmp(testing1, dictionary) == 0) {
                words++;
                }
                if(strcmp(testing2, dictionary) == 0) {
                words++;
                }
                if(strcmp(testing3, dictionary) == 0) {
                words++;
                }
                if(strcmp(testing4, dictionary) == 0) {
                words++;
                }
                if(words >= 2) { //if two words
                    t = 10000;
                    key = 26;
                }
            }
                  
            /*if first word in the output.txt aligns with the first 1000 words of dictionary
            then it keeps that key in output*/
                fseek(input, 0, SEEK_SET);
                fseek(output, 0, SEEK_SET);
                fseek(read, 0, SEEK_SET);
        }
        if(key == 26) {
            printf("NO PHRASE FOUND\n");
        }
        if(key == 27) {
            printf("THE PHRASE IS FOUND\n");
        }
        break;
        case 'f':
        Day_1_Sub_Decryption();
        break;
        default:
            printf("Unknown Selection\n");
    } 
    return 0;
}

char Encryption(int key, char c) {
    while(key <= 0) {
        key = key + 26;
    }
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
    while(key <= 0) {
        key = key + 26;
    }
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
    printf("\nKey of encryption:(singular phrase with only letters) <enter>\n");
    scanf("%s", key);
    int i;//variable used in for statement
    for(i=0; key[i] != 0; i++) {
        if(isalpha(key[i])) {
            keysize++;
        }
        else {
            printf("Incorrect Key/n");
            return 0;
        }
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
    printf("Substitution Encryption:\n");
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    if(input == NULL) {
        perror("fopen()"); 
        return 0; 
    }
    output = fopen("output.txt", "w");
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
        fprintf(output, "%c", c);
    }
    return 0;
}
 int Sub_Decryption(void) {
    char key[26];
    int keysize;
    keysize = 0;
    printf("\nKey used to encrypt:(singular phrase with only letters) <enter>\n");
    scanf("%s", key);
    int i;//variable used in for statement
    for(i=0; key[i] != 0; i++) {
        if(isalpha(key[i])) {
            keysize++;
        }
        else {
            printf("Incorrect Key/n");
            return 0;
        }
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
    printf("Substituition Decryption:\n");
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    if(input == NULL) {
        perror("fopen()"); 
        return 0; 
    }
    output = fopen("output.txt", "w");
    while(feof(input) == 0) {
        char c;
        fscanf(input, "%c", &c);
        
        if(isupper(c)) { //only code not whitespace or grammar
             //make p equal this number
            int p = 0;
            while(c != fullkey[p]) {
                p++;
            }
            p = p + 65;
            c = p;
        }
        printf("%c", c);
        fprintf(output, "%c", c);
    }
    return 0;
 }
 
 int Day_1_Sub_Decryption(void) {
    char fullkey[] = {'N', 'W', 'L', 'R', 'B', 'M', 'Q', 'H', 'C', 'D', 'A', 'Z', 'O', 'K', 'Y', 'I', 'Q', 'X', 'J', 'F', 'E', 'G', 'P', 'X', 'V', 'Z', '\0'};
    printf("Substituition Decryption:\n");
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    if(input == NULL) {
        perror("fopen()"); 
        return 0; 
    }
    output = fopen("output.txt", "w");
    while(feof(input) == 0) {
        char c;
        fscanf(input, "%c", &c);
        
        if(isupper(c)) { //only code not whitespace or grammar
             //make p equal this number
            int p = 0;
            while(c != fullkey[p]) {
                p++;
            }
            p = p + 65;
            c = p;
        }
        printf("%c", c);
        fprintf(output, "%c", c);
    }
    return 0;
 }
 
