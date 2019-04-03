#include <stdio.h>

int Encryption(void);
int main() {
    char c;
    printf("Select an option: \na) Rotation Cypher\n");
    printf("b) Rotation Cypher Attack\nc) Substitution Cypher\n");
    printf("d) Substitution Cypher Attack\nSelection: ");
    scanf("%c", &c);
    switch(c) {
        case'a': Encryption();
            break;
        default: 
            printf("Unknown Selection\n");
    }  
    return 0;
}

int Encryption(void) {
    char str[500] = {"ABCDE fegh"};//Intiialising Word
    int i;
    int key = 1; //Rotational Factor
        //For loop to get every value of the string
        for(i=0; i < 500 && str[i] != 0; i++) {
            if(str[i] != 32) { //If whitespace no change occurs
                if(str[i] >= 97 && str[i] <= 122) { 
                    str[i] = str[i] - 32; //IF statement make Capital
                }
                str[i] = str[i]+ key; //Encrypting
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
