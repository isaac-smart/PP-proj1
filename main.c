/*ISAAC SMART C3329492
Programming Assignment 1 : ENGG1003
Encryption and Decryption of messages
The code below allows the user to use encrypt a message in input.txt file using rotation and substitution 
encryption. The encrypted message is printed to the terminal but also sent to output.txt file. It can also
decrypt messages from input.txt with a known key for both encryption types. A rotation decryption can also
be done without a known key through a brute force attack which checks the spelling of the first couple words. 
A day one substitution decryption is also found through hard coding the key used. These different tasks can be
completed through a menu which allows the user to select each given task and then exits out of main. 

The message is inputted by changing input.txt to the message wanting to be encrypted or decrypted.
All other inputs other than the message are inputted through scanf in the terminal.
 */
#include <stdio.h>
#include <ctype.h>

//The different functions used within the code
char Encryption(int key, char c);
char Decryption(int key, char c);
int Sub_Cypher(void);
int Sub_Decryption(void);
int Rotation_Decryption(void);
int Day_1_Sub_Decryption(void);


int main() {
    /* 
    FILE.IO is used below and pops up an error message if there is no file available. Read is the the list
    of 10 000 most common words used in the rotation decryption.
     */
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
    if(read == NULL) {
        perror("fopen()"); 
        return 0; 
    } 
    /*
    The menu and selection is below and includes the all the given functions in each section. The rotation 
    encryption and decryption functions uses the key and each given char to return the changed char. The other 
    functions need to do the whole task within the functions because it is impractical to pass whole arrays of 
    chars into a function.
    */
    int key;
    char menu;
    printf("Select an option: \na) Rotation Cypher\n");
    printf("b) Rotation Cypher Attack(known key)\nc) Substitution Cypher\n");
    printf("d) Substitution Cypher Attack(known key)\ne) Unknown Key Rotation Cypher");
    printf("\nf) Day 1 Substitution Cypher");
    printf("\nSelection: ");
    scanf("%c", &menu);
    switch(menu) {
        /*
        This case uses each character from the input and encrypts each character using the inputted key.
        The new character is printed to the terminal and output.txt. When the input.txt has nothing left to 
        read it exits the while loop.
         */
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
        //This case is the same as (a) just decrypts the message instead of encrypting
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
        Rotation_Decryption();
        break;
        
        case 'f':
        Day_1_Sub_Decryption();
        break;
        
        //If the input is not valid it prints the error message
        default:
            printf("ERROR: Unknown Selection\n");
    } 
    return 0;
}

//The rotational encryption function which changes char c into the encrypted message
char Encryption(int key, char c) {
//The while function changes a negative key to make it positive
    while(key <= 0) {
        key = key + 26;
    }
//The if statement only changes if the char character is a letter
    if( isalpha(c) ) {
        if(islower(c)) { //Changing lowercase to uppercase
            c = c - 32; 
        }
        c = c + (key % 26); //Encrypting, adds the key which is between 0-25
        if(c > 90) { 
            c = c - 26; //If ASCII number exceeds 90 minus 26 to make letter
        }        
    }
    return c; //Return c as char
}
//Similar to encryption function except minuses the key other 
char Decryption(int key, char c) {
    while(key <= 0) {
        key = key + 26;
    }
    if(isupper(c)) { //Encrypted message only uppercase
        c = c - (key % 26); //Minus the key from the encrypted message to decrypt
        if(c < 65) {
            c = c + 26; //If below 65 and not capital letter add 26 to make letter again
        }
    }
    return c; //Return c as char
}

/*
Substitution Encryption has two parts, initialising the array of the key and then changing the message according 
to the key. It along with the rest of the functions below have no arguments and returns zero at the end due to
the difficulty of passing whole arrays through functions.
 */
int Sub_Cypher(void) {
//First Part - creation of the key
    char key[26];
    int keysize;
    keysize = 0; 
    printf("\nKey of encryption:(singular phrase with only letters) <enter>\n");
    scanf("%s", key); //Getting the string(key) to build a full 26 character key from(fullkey)
    int i;//variable used in for statements
    for(i=0; key[i] != 0; i++) {
        if(isalpha(key[i])) { //If the key is a letter
            keysize++; //Finding the size of the inputted key used when making the fullkey
        }
        else { //If string contains any non-letter character it becomes a zero
            printf("Incorrect Key/n");
            return 0;
        }
    }
    int a = 65, z = 90; //variables used to create fullkey
    char fullkey[26]; //the string used to hold the whole 26 letter key for substitution
    int p;
    
    //for statement to create a full key(all individual 26 letters) from inputted string
    for( i = 0; i < 26; i++) { 
        if(islower(key[i])) { //if key is lowecase make uppercase
            key[i] = key[i] - 32;
        }
        if(keysize > i) { //if i is lower than the size of the key
            fullkey[i] = key[i]; // makes key equal new key
            for(p=0; p < i; p++) { //use another for statement to check all previous letters
                if(key[p] == fullkey[i]) { //checks for repetition of letters
                    fullkey[i] = z; //assigns to z to first repeated number
                    z--; //makes z equal 89 so for second iteration is replaced with y and is continued
                }
            }
        }
        else { //to intialise key outside the input
            fullkey[i] = a; //Full key equal a for if statement
            for(p = 0; (p < keysize); p++) { //for statement to check
                if(fullkey[p] == fullkey[i]) { //if letter being made equals any previous letter in fullkey
                    a++; //go to the next available number
                    fullkey[i] = a; //make fullkey equal new number
                    p = -1; //restart the for loop
                }
            }
            fullkey[i] = a; //make fullkey equal a again
            a++; //next available number
        }
    }  
    
    //Second Part: Substituting the fullkey created into phrase that needs to be encrypted
    printf("Substitution Encryption:\n");
    //Files need to be reopened within functions
    FILE *input; 
    FILE *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    while(feof(input) == 0) { 
        char c;
        fscanf(input, "%c", &c); //Gets 
        
        if(islower(c)) { //If lowercase make uppercase
            c = c - 32;
        }
        if(isupper(c)) { //only includes message and no whitespace or grammar included
            c = c - 65; // The char becomes a number 0-25 indicating A-Z
            int position;
            position = c; //Make p equal c and is not a char
            c = fullkey[position]; 
            //The position indicates 0-25 in the fullkey and makes c equal the new substituted letter
        }
        printf("%c", c);
        fprintf(output, "%c", c);
        //C is printed to both the terminal and to output.txt till the while loop terminates
    }
    return 0;
}

/*
The Substitution decryption has two parts: the intialising of the key (similar to substitution encrypting) 
but also has the decrypting of the message using the key.
 */
int Sub_Decryption(void) {
//First Part: The same as substitution encryption so not commented
    char key[26];
    int keysize;
    keysize = 0;
    printf("\nKey used to encrypt:(singular phrase with only letters) <enter>\n");
    scanf("%s", key);
    int i;
    for(i=0; key[i] != 0; i++) {
        if(isalpha(key[i])) {
            keysize++;
        }
        else {
            printf("Incorrect Key/n");
            return 0;
        }
    }
    int a = 65, z = 90;
    char fullkey[26];
    int p;
    
    for( i = 0; i < 26; i++) { 
        if(islower(key[i])) {
            key[i] = key[i] - 32;
        }
        if(keysize > i) { 
            fullkey[i] = key[i]; 
            for(p=0; p < i; p++) { 
                if(key[p] == fullkey[i]) { 
                    fullkey[i] = z;
                    z--;
                }
            }
        }
        else {
            fullkey[i] = a; 
            for(p = 0; (p < keysize); p++) { 
                    if(fullkey[p] == fullkey[i]) {
                    a++;
                    fullkey[i] = a;
                    p = -1;
                }
            }
            fullkey[i] = a; 
            a++;
        }
    }
//Second Part: Decryption of the message using the fullkey created
    printf("Substituition Decryption:\n");
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    while(feof(input) == 0) {
        char c;
        fscanf(input, "%c", &c); //get char from input
        
        if(isupper(c)) { //only message is changed not whitespace or grammar
             //make p equal this number
            int p = 0;
            while(c != fullkey[p]) { //tests whether c is equal to fullkey[p] and when it does exit
                p++;
            }
            p = p + 65; //add 65 to p to put in ASCII character range for uppercase letters
            c = p; //make p a char c
        }
        printf("%c", c);
        fprintf(output, "%c", c); //print c to the terminal and output.txt
    }
    return 0;
 }

/*
The Rotation Decryption, decrypts a message without a key using a brute force attack by shifting the message 
by 1 and testing if the first few words of the phrase are within the file google-10000-english.txt. This file
contains the most common 10000 words in the english language.
 */
int Rotation_Decryption(void){
//Open the
    FILE *input;
    FILE *output;
    FILE *read;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w+");//NOTE: Output is w+ which writes and reads file which is important 
    read = fopen("google-10000-english.txt", "r");
    int foundkey; //The correct key is stored here when found
    int key; //intialising the key 
    for(key = 0; key < 26; key++) {
        char c; 
        int t;        
        int words = 0;
        while(feof(input) == 0) { //Below is similar to the rotational cypher however only prints to the output
            fscanf(input, "%c", &c);
            c = Encryption(key, c);//NOTE: Uses the rotational cypher function 
            c = tolower(c); //made lowercase as words being tested against are lowercase
            fprintf(output, "%c", c);
        }
        fseek(output, 0, SEEK_SET); //Resetting the position of the output so it can be read from the beginning
/*
Testing the similarity first 7 words of the message which has been decrypted to the most common 10 000 words
NOTE: A long similar initialisation is used for the tests and dictionary to create similar arrays 
so they can be seen if similar
*/
        char testing[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'}; 
        fscanf(output, "%s", testing); //writes over the top of intialisating
        char testing1[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
        fscanf(output, "%s", testing1);
        char testing2[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
        fscanf(output, "%s", testing2);
        char testing3[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
        fscanf(output, "%s", testing3);
        char testing4[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
        fscanf(output, "%s", testing4);
        char testing5[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
        fscanf(output, "%s", testing5);
        char testing6[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
        fscanf(output, "%s", testing6);
        for(t=0; t < 10000; t++) { //tests all the words in the file through for loop
            char dictionary[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
            fscanf(read, "%s", dictionary); //first word is read   
            if(strcmp(testing, dictionary) == 0) { //strcmp tests if words arrays are similar and outputs zero if are
                words++; //adds 1 to words if arrays are exactly the same
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
            if(strcmp(testing5, dictionary) == 0) {
                words++;
            }
            if(strcmp(testing6, dictionary) == 0) {
                words++;
            }
            if(words >= 5) { //If 5 words are correct out of the 7 tested, the message is believed to be correct
                t = 10000; //Exits out of loop
                foundkey = key; //Makes key equal foundkey
                key = 50; //Used to indicate whether phrase is found or not 
            }
        }

        fseek(input, 0, SEEK_SET); //Return all files to starting position to conclude loop
        fseek(output, 0, SEEK_SET);
        fseek(read, 0, SEEK_SET);
    }
    if( key != 51 ) {
        printf("NO PHRASE FOUND\n");
    }
    else {
        printf("THE PHRASE IS FOUND\n");
        char c;
        while(feof(input) == 0) { //Reprints the correct decryption into the terminal and output.txt
            fscanf(input, "%c", &c);
            c = Encryption(foundkey, c);
            printf("%c", c);
            fprintf(output, "%c", c);
        }
    }
    return 0;
}
 

int Day_1_Sub_Decryption(void) {
//Intialising the key manually as it is the correct substitution key for the Day 1 Substitution Cypher
    char fullkey[] = {'N', 'W', 'L', 'R', 'B', 'M', 'Q', 'H', 'C', 'D', 'A', 'Z', 'O', 'K', 'Y', 'I', 'S', 'X', 'J', 'F', 'E', 'G', 'P', 'U', 'V', 'T', '\0'};
//The code below was previously commented in the Sub_Decryption Function and is identical
    printf("Substituition Decryption:\n");
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    while(feof(input) == 0) {
        char c;
        fscanf(input, "%c", &c);
        
        if(isupper(c)) {
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
 
