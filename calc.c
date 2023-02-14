#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>






#define MAX_STRING_LENGTH 50

void parse_string(char *string){
    int i,j=0, k = strlen(string);
    char temp=' ';
//    printf("\nhere0..%d",k);

    for(i=0; i<k+1 ; i++){
        if(string[i] == ' '){
            for(j=i+1; j<k+1; j++ ){
                if( string[j] != ' ' ){
                    string[i] = string[j];
                    string[j] = temp;
                    break;
                }    
            }
        }
    }
}

///////////////////////////////////////for character stack ////////////////////////////////////////
void push(char *p, char element, int *top){

//    printf("\ninside push,,,top=%d",*top);
    p[*top] = element;
    ++*top;
//    printf("\ninside push...stacktop=%d",*top);
}

char pop(char *p, int *top){
    
//    printf("\ninside pop");
    if( *top <= 0 ){
//        printf("\n popping '!'");
        return '!';
    }
    else{
        --*top;
//        printf("\npopping = %c",p[*top]);
        return p[*top];
    }
}

char check_top(char *p, int *top){
//    printf("\ninside check_top");
    if( *top == 0 )
        return '!';
    else
        return p[*top-1];    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////for number stack////////////////////////////////////////////////////
void insert_num(float *p, float element, int *top){

    p[*top] = element;
    ++*top;
}

float remove_num(float *p, int *top){
    
    if( *top <= 0 ){
        return -100;
    }
    else{
        --*top;
//        printf("\npopping = %c",p[*top]);
        return p[*top];
    }
}

float check_top_num(float *p, int *top){
    if( *top <= 0 )
        return -100;
    else
        return p[*top-1];    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////



float calculation(float *array2, int *top2, char operator){
   
    float value = 0;
    float operand1, operand2;

    printf("\n top2 = %d",*top2);

    if( *top2 > 0)
        operand1 = remove_num(array2,top2);
    else
        operand1=0;
    if(*top2 > 0)
        operand2 = remove_num(array2,top2);
    else
        operand2=0;

    printf("\noperand1=%f",operand1);
    printf("\noperand2=%f",operand2);
    printf("\noperator=%c",operator);

    switch(operator){
        case '+':
            value=operand2+operand1;
            break;
        case '-':
            value=operand2-operand1;
            break;
        case '*':
            value=operand2*operand1;
            break;
        case '/':
            value=operand2/operand1;
            break;
        case '^':
            value=pow(operand2,operand1);
    }
    printf("\ntotal=%f",value);
    
    return value;

}

int precedenceOf(char operator){

    switch(operator){
        case '!':
            return 0;
        case '+' :
        case '-' :
            return 1;
        case '*' :
            return 2;
        case '/' :
            return 3;
        case '^':
            return 4;
        default :   
            return -1;
    }
    
}

int isNum(char a){

    return ( a >= '0' && a <= '9');
}

int isOperator(char op){
    return( op == '+' || op == '-' || op == '/' || op == '*' || op == '^' || op == '(' || op == ')' );
}

void infix_to_postfix(char *string){
    
    int i=0;
    char operator;
    float value,num=0;
    int str_len = strlen(string);
    
    char array[str_len];
    int val = 0;
    int *top = &val;
    float array2[str_len];
    int val2 = 0;
    int *top2 = &val2;


    while(i < (str_len-1) )
    {
//        printf("\nstring[i]= %c",string[i]);
        if( isOperator(string[i]) )
        {
//            printf("before pushing %c number pushing=%d",string[i],num);
            if( i != 0 && isNum(string[i-1]) ){
                insert_num(array2,num,top2);
                num=0;
            }

            if( precedenceOf(string[i]) > precedenceOf(check_top(array,top) )){
                
                push(array,string[i],top);
            }
            else if( string[i] == '^' && check_top(array,top) == '^'){
                                                    
                push(array,string[i],top);
            }
            
            
//        }    //runnable code till this position
//////////////////////////////////////////new code//////////////////////////
            else if(string[i] == '('){
                push(array,string[i],top);
            }       
            else if(string[i] == ')'){
                while( (operator=pop(array,top)) != '('){
                    value = calculation(array2,top2,operator);
                    printf("\n pushing value = %f",value);
                    insert_num(array2,value,top2);
                }
//                operator = pop(array,top);                
            }
//////////////////////////////////////////////////////////////////////////////
			else{
                while(precedenceOf(string[i]) <=  precedenceOf(check_top(array,top))){
                    operator = pop(array,top);
                    value = calculation(array2,top2,operator);
//                    printf("\niserting value=%f",value);
                    insert_num(array2,value,top2);   //put value in place of operand1;
                }
                push(array,string[i],top); 
            }
        }   
/////////////////////////////////////////////////////////////////////////////
        else{
            num = num*10 + ((int)string[i] - 48);           
        }
        i++;
    }
    
    if(string[str_len-2] != ')' ){
        printf("inserting last num=%f",num);
        insert_num(array2,num,top2);  //inserting last number
    }
    
    
//    printf("\nvalue of top=%d",*top);
    while( *top >  0 )
    {
        operator = pop(array,top);
        printf("\nops=%c",operator);
        value = calculation(array2,top2,operator);
//        printf("value=%f",value);
        insert_num(array2,value,top2);

    }
    
    printf("\nfinal value=%.2f\n",array2[0]);
}
                    
            
      
void calculate(char *string){

//    printf("\ninside-calculate----%s\n",string); 
    infix_to_postfix(string);
        
}



int main(){

    char *input,*string;
    int value1,value2; 
//    input = (char*)malloc(1*sizeof(char));
    string = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));

    printf("\n welcome to simple calculator project \n");
    printf(".......................................\n");
    printf("enter the value : ");


    fgets(string,MAX_STRING_LENGTH,stdin);
    calculate(string);
/*
    printf("\n%s\n",string);
    parse_string(string);
    printf("\n%s\n",string);    
    printf("%d\n",(int)strlen(string));
*/

//    free(input);
    free(string);
    return 0;
}


