#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define MAX_STRING_LENGTH 50

void parse_string(char *string){
    int i,j=0, k = strlen(string);
    char temp=' ';

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

void push(char *p, char element, int *top){

    p[*top] = element;
    ++*top;
}

char pop(char *p, int *top){
    
    if( *top <= 0 ){
        return '!';
    }
    else{
        --*top;
        return p[*top];
    }
}

char check_top(char *p, int *top){
    if( *top == 0 )
        return '!';
    else
        return p[*top-1];    
}

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
        return p[*top];
    }
}

float check_top_num(float *p, int *top){
    if( *top <= 0 )
        return -100;
    else
        return p[*top-1];    
}



float calculation(float *array2, int *top2, char operator){
   
    float value = 0;
    float operand1, operand2;


    if( *top2 > 0)
        operand1 = remove_num(array2,top2);
    else
        operand1=0;
    if(*top2 > 0)
        operand2 = remove_num(array2,top2);
    else
        operand2=0;


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
    
    int i=0, flag=0;
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
        if( isOperator(string[i]) )
        {
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
            else if(string[i] == '('){
                push(array,string[i],top);
            }       
            else if(string[i] == ')'){
                while( (operator=pop(array,top)) != '(' ){
                    value = calculation(array2,top2,operator);
                    insert_num(array2,value,top2);
                    if( *top == 0 ){
                        flag = 1;
                        break;
                    }
                }
            }
			else{
                while(precedenceOf(string[i]) <=  precedenceOf(check_top(array,top))){
                    operator = pop(array,top);
                    value = calculation(array2,top2,operator);
                    insert_num(array2,value,top2);   //put value in place of operand1;
                }
                push(array,string[i],top); 
            }
        }   

        else{
            num = num*10 + ((int)string[i] - 48);           
        }
        i++;
    }
    
    if(string[str_len-2] != ')' ){
        insert_num(array2,num,top2);  //inserting last number
    }
    
    
    while( *top >  0 )
    {
        operator = pop(array,top);
        if( operator == '(' || operator == ')' ){
            flag = 1;
            break;
        }
        value = calculation(array2,top2,operator);
        insert_num(array2,value,top2);

    }
    
    if (flag == 0)
        printf("\nfinal value=%.2f\n",array2[0]);
    else
        printf("\ninvalid expression\n");
}
                    
            
      
void calculate(char *string){

    infix_to_postfix(string);
        
}



int main(){

    char *input,*string;
    int value1,value2; 
    string = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));

    printf("\n welcome to simple calculator project \n");
    printf(".......................................\n");
    printf("enter the value : ");


    fgets(string,MAX_STRING_LENGTH,stdin);
    calculate(string);
    free(string);
    return 0;
}


