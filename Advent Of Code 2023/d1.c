#include <stdio.h>
#include <string.h>
#include <ctype.h>


int threeChars(char list[]){
    char str1[] = "one";
    char str2[] = "two";
    char str3[] = "six";
    if (strncmp(list,str1, 3) == 0) {
        return 1;
    }
    if (strncmp(list,str2, 3) == 0) {
        return 2;
    }
    if (strncmp(list,str3, 3) == 0) {
        return 6;
    }
    return -1;
}

int fourChars(char list[]){
    char str1[] = "four";
    char str2[] = "five";
    char str3[] = "nine";
    if (strncmp(list,str1, 4) == 0) {
        return 4;
    } 
    if (strncmp(list,str2, 4) == 0) {
        return 5;
    }
    if (strncmp(list,str3, 4) == 0) {
        return 9;
    }
    return -1;
}

int fiveChars(char list[]){
    char str1[] = "three";
    char str2[] = "eight";
    char str3[] = "seven";
    if (strncmp(list,str1, 5) == 0) {
        return 3;
    } 
    if (strncmp(list,str2, 5) == 0) {
        return 8;
    }
    if (strncmp(list,str3, 5) == 0) {
        return 7;
    }
    return -1;
}

int main(){
    int i,j;
    FILE *file = fopen("inputs/day1.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    char line[256];
    int sum=0;
    int temp;
    while (!feof(file)) {
        if (fgets(line, sizeof(line), file)) {
            for(i=0;i<strlen(line);i=i+1){
                if (isdigit(line[i])) {
                    sum=sum+10*(line[i]-'0');
                    break;   
                }

                if (i<strlen(line)-2){
                    temp = threeChars(line+i);
                     if  (temp!=-1){
                         sum=sum+10*temp;
                         break;    
                    }
                }
                if (i<strlen(line)-3){
                    temp = fourChars(line+i);
                     if  (temp!=-1){
                         sum=sum+10*temp;
                         break;    
                    }
                }    
                if (i<strlen(line)-4){
                    temp = fiveChars(line+i);
                     if  (temp!=-1){
                         sum=sum+10*temp;
                         break;    
                    }
            }
            }
            for (j=strlen(line)-1;j>=0;j=j-1){
                if (isdigit(line[j])) {
                    sum=sum+(line[j]-'0');
                    break;
                }
                if (j<strlen(line)-2){
                    temp = threeChars(line+j);

                     if  (temp!=-1){
                         sum=sum+temp;
                         break;    
                    }
                }
                if (j<strlen(line)-3){
                    temp = fourChars(line+j);
                     
                     if  (temp!=-1){
                         sum=sum+temp;
                         break;    
                    }
                }    
                if (j<strlen(line)-4){
                    temp = fiveChars(line+j);

                     if  (temp!=-1){
                         sum=sum+temp;                         
                         break;    
                    }
                }
            }
        }
    }
    fclose(file);
    printf("%d",sum);

return 0;        
}