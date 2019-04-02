#include <stdio.h>



int main() {
    char str[500] = {"abcde"};//Intiialising Word
    int i;
    int key = 1; //Roational Factor
        for(i=0; i < 500 && str[i] != 0; i++) {
            //For loop to get every value of the array
            if(str[i] >= 97 && str[i] <= 122) { 
                str[i] = str[i] - 32; //IF statement make Capital
            }
            str[i] = str[i]+ key; //Rotational Factor
            if(str[i] > 90) {
                str[i] = str[i] - 26;
            }
        }
    printf("%s\n", str);
    
    
    return 0;
}
