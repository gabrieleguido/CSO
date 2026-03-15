#include <stdio.h>

typedef void (*ptr_state)(char);
ptr_state current_state;

void s1(char c);
void s2(char c);
void s3(char c);
void s4(char c);
void s5(char c);

void s1(char c){
    printf("stato 1\n");
    if(c == 'a')
        current_state = s2;
    else 
        current_state = s1;
}
void s2(char c){
    printf("stato 2\n");
    if(c == 'c')
        current_state = s3;
    else 
        current_state = s1; 
}
void s3(char c){    
    printf("stato 3\n");
    current_state = s4; 
}
void s4(char c){
    printf("stato 4\n");
    char cnt = c;
    while(cnt>0){
        getchar();
        cnt--;
        printf("stato 4\n");
    }
    current_state = s5;
}
void s5(char c){
    printf("stato 5\n");
    if(c == 'a')
        current_state = s2;
    else 
        current_state = s1; 
}

int main(){
    current_state = s1;
    while(1){
        char c = (char) getchar();
        (*current_state)(c);
    }
}

