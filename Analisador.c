/*
 * Ricardo Veiga Coelho
 * 
 */
#include<stdio.h>
#include<stdlib.h>
char lookahead;   /* Excepcionalmente variavel global */

int I(char palavra[], int *pos);
int S(char palavra[], int *pos);
int K(char palavra[], int *pos);
int T(char palavra[], int *pos);
int Z(char palavra[], int *pos);
int F(char palavra[], int *pos);
int N(char palavra[], int *pos);
int M(char palavra[], int *pos);

int  match(char t, char palavra[], int *pos){
	if (lookahead == t){
		lookahead= palavra[++(*pos)];
		return(1);
	}
	return(0);  
}

// I -> S$
// S -> T K
// K -> + T K
// K -> - T K
// K -> vazio
// T -> F Z
// Z -> * F Z
// Z -> / F Z
// Z -> vazio
// F -> (S)
// F -> N
// F -> -N
// N -> 0M|1M|2M|3M|4M|5M|6M|7M|8M|9M
// M -> 0M|1M|2M|3M|4M|5M|6M|7M|8M|9M
// M -> vazio

int I(char palavra[], int *pos){
    if (S(palavra, pos)){
        if (lookahead == '$')
            return(1);
        else return(0);
    } else return(0);
}

int S(char palavra[], int *pos){
    if (T(palavra, pos) &&
        K(palavra, pos)  )
        return(1);
    else return(0);
}

int K(char palavra[], int *pos){
    if (lookahead == '+'){
        if (match('+', palavra, pos) &&
            T(palavra, pos)          &&
            K(palavra, pos)          )
            return(1);
        else return(0);
    } else if (lookahead == '-'){
        if (match('-', palavra, pos) &&
            T(palavra, pos)          &&
            K(palavra, pos)          )
            return(1);
        else return(0);
    } else return(1);
}

int T(char palavra[], int *pos){
    if (F(palavra, pos) &&
        Z(palavra, pos)  )
        return(1);
    else return(0);
}

int Z(char palavra[], int *pos){
    if (lookahead == '*'){
        if (match('*', palavra, pos) &&
            F(palavra, pos)          &&
            Z(palavra, pos)          )
            return(1);
        else return(0);
    } else if (lookahead == '/'){
        if (match('/', palavra, pos) &&
            F(palavra, pos)          &&
            Z(palavra, pos)          )
            return(1);
        else return(0);
    } else return(1);
}

int F(char palavra[], int *pos){
    if (lookahead == '('){
        if (match('(', palavra, pos) &&
            S(palavra, pos)          &&
            match(')', palavra, pos)  )
            return(1);
        else return(0);
    } else if (N(palavra, pos)){
        return(1);
    } else if (lookahead == '-'){
        if (match('-', palavra, pos) &&
            N(palavra, pos)          )
            return(1);
        else return(0);
    } else return(0);
}

int N(char palavra[], int *pos){
    if (lookahead >= '0' && lookahead <= '9'){
        if (match(lookahead, palavra, pos) &&
            M(palavra, pos)                )
            return(1);
        else return(0);
    } else return(0);
}

int M(char palavra[], int *pos){
    if (lookahead == '0' || lookahead == '1' || lookahead == '2' || lookahead == '3' || lookahead == '4' || lookahead == '5' || lookahead == '6' || lookahead == '7' || lookahead == '8' || lookahead == '9' || lookahead == '$'){
        if (match(lookahead, palavra, pos) &&
            M(palavra, pos))
            return(1);
        else return(0);
    } else if(lookahead >= 'A' && lookahead <= 'z') return(0);
    else return(1);
}


void trataErro(){
	/* IMPORTANTE:  Faca um tratamento melhor !!! */

}

int main(){
	char palavra[]= "3+7(*8$";
	int  pos=0;
	
	lookahead= palavra[pos];
	if (S(palavra, &pos))
	    printf("\nPalavra %s reconhecida\n\n", palavra);
	else 
	    trataErro();
	system("PAUSE");
	return(0);
}
