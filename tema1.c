// Gherasie Stefania Elena
// 313 CB

#include <stdio.h>
#include <math.h>
 
//functie care testeaza daca un anumit 
//bit este setat
int is_set(unsigned long long n, int i) {
    unsigned long long  mask = ((unsigned long long)1 << i);
    return (n & mask) != 0;
}
 
 //functie care afiseaza harta
void print_map(unsigned long long n) {
    int i = 0, j = 0;
    for (i = 63; i >=0; i--) {
            if (is_set(n, i))
                printf("#");
            else
                printf(".");
            j++;
            if(j%8 == 0)
                printf("\n");
        }
        printf("\n");
}

//functie care seteaza bitii de pe 
//marginea din dreapta
unsigned long long build_right() {
    unsigned long long  col = 1;
    int i;
    for (i = 1; i <= 7; i++)
        col = col | ((unsigned long long)1 << 8 * i);
    return col;
}
 
//functie care seteaza bitii de pe 
//marginea din stanga
unsigned long long build_left() {
    unsigned long long m = 1, col = 1;
    int i;
    col <<= 7;
    m <<= 7;
    for (i = 1; i <= 7; i++)
        col = col | (m << 8 * i);
    return col;
}
 
//functie care testeaza daca exista linii 
//completate in harta si le retine
int check_line(unsigned long long n) {
    int i, j, k;
    for (i = 0; i <= 7; i++) {
        k = 0;
        for (j = 0; j <= 7; j++)
            if(is_set(n, 8*i+j) == 1)
                k++;
        if(k == 8)
            return i;
        }
    return -1;
}
 
 //functie care returneaza harta fara linia completata
unsigned long long remove_line(unsigned long long n, int i) {
    unsigned long long p = n, m = n;
 
    m >>= 8*(i+1);
    m <<= 8*i;
    p <<= 8*(7-i);
    p <<= 8;
    p >>= 8*(7-i);
    p >>= 8;
    n = (m | p);

    return n;
}
 
 //functie care afla numarul de 0 din scriere
int zeros_number(unsigned long long n) {
   int k = 0, i;
   for (i = 0; i <= 63; i++) {
    if((n & 1 ) == 0)
        k++;
    n >>= 1;
    }
    return k;
}
 
 //functie care afiseaza "GAME OVER!" si scorul
void print_score(unsigned long long n, int completed_lines){
    float score;
    score = pow(zeros_number(n), 0.5) + pow(1.25, completed_lines);
    printf("GAME OVER!\n");
    printf("Score:%.2f\n",score);
}

 
int main()
{   
    unsigned long long P, H, copy_P, copy2_P, margin_right, margin_left;
    int M, t, j, k, i, completed_lines = 0, ok, line;
 
    scanf("%llu", &H);
    scanf("%d", &M);
 
    print_map(H);

    margin_left = build_left();
    margin_right = build_right();

    for (i = 1; i <= M; i++) {  
        scanf("%llu", &P);
        copy2_P = P;
        P <<= 48;
        copy_P = P;
        copy_P <<= 8;
        for (j = 1; j <= 8; j++) {
            scanf("%d", &t);
            if (j == 1) {
                if (copy_P & H) {
                    print_map(H);
                    print_score(H, completed_lines);
                    return 0;
                } else {
                    if (t > 0) {
                        for (k = 1; k <= t; k++) {
                            if(copy_P & margin_right)
                                break;
                            copy_P >>= 1;
                            P >>= 1;
                            if (copy_P & H) {
                                copy_P <<= 1;
                                P <<= 1;
                                break;
                            }
                        }
                    } else {
                        for (k = 1; k <= -t; k++) {
                            if(copy_P & margin_left)
                                break;
                            copy_P <<= 1;
                            P <<= 1;
                            if (copy_P & H) {
                                copy_P >>= 1;
                                P >>= 1;
                                break;
                            }
                        }
                    }
                    print_map(H | copy_P);
                }
            } else {
                    if (P & H) {
                        if (j == 2) {
                            if (copy2_P > 255) {
                                H = H | P << 8;
                                print_map(H);
                                print_score(H, completed_lines);
                               return 0;
                            } else {
                                P <<= 8;
                                for (j = j + 1; j <= 8; j++)
                                    scanf("%d", &t);
                            }
                        } else {
                            P <<= 8;
                            for (j = j + 1; j <= 8; j++)
                                scanf("%d", &t);
                        }
                    } else {
                        if (t > 0) {
                            for (k = 1; k <= t; k++) {
                                if(P & margin_right)
                                    break;
                                P >>= 1;
                                if (P & H) {
                                    P <<= 1;
                                    break;
                                }
                            }
                        } else {
                            for (k = 1; k <= -t; k++) {
                                if(P & margin_left)
                                    break;
                                P <<= 1;
                                if (P & H) {
                                    P >>= 1;
                                    break;
                                }
                            }
                        }
                    }
                if(j < 9)
                print_map(H | P);
                if(j < 8)
                    P >>= 8;
                }
            }  
            H = H | P;
            ok = 0;
            for (j = 1; j <= 8; j++) {
                line = check_line(H);
                if (line != -1) {
                    ok = 1;
                    completed_lines++;
                    H = remove_line(H, line);
                }
            }
            if (ok == 1)
                print_map(H);
        }
 
    print_score(H, completed_lines);
 

    return 0;
}