#include <stdio.h>
#include <time.h>

int wartosc_obecna(int tab[], int szukana, int max){
    int x;
    for(x = 0;x < max; x++){
        if(tab[x] == szukana){
            return 1;
        }
    }
    
    return 0;
}

int main(void){
    
   
    int tab[] = {3,5,6,7,8,4,3,6,7,4,5,7,6,7,3,6,7,5,6,8,4,8,3,4,5,5,7,3,5,6,0,9,7,9,4,5,2,7,5,0,9,7,8,4,5,0,9,7,4,5,9,0};
    int n = sizeof(tab)/sizeof(tab[0]);
    printf("rozmiar tablicy = %d\n", n);
    //sprawdzam ile unikatowych wartości w tab
    
    int ile_roznych = 0;
    int i = 0;
    int x = 0;
    int bylo = 0;
    for(i = 0; i < n; i++){
    bylo = wartosc_obecna(tab, tab[i], i);
/*
        for(x = 0; x <i; x++){
            
            if(tab[x] == tab[i]){
                //printf("index: %d\n", i);
                //printf("%d : %d\n", tab[x], tab[i]);
                bylo = 1;
            }
        }
*/        
        //printf ("bylo: %d\n", bylo);
        if(bylo == 0){
            ile_roznych += 1;
        } else {
            bylo = 0;
        }
    }
    

    
    printf("Unikatowe wpisy w tab = %d\n",ile_roznych);
    
    if(ile_roznych == 1){
        puts("Brak dominanty.");
    } else {
        int tab_domi[ile_roznych][2];
        int y = 0;
        bylo = 0;

        for(i = 0; i < ile_roznych; i++){
            //przy okazji zeruje wartosci tab_domi[i][1]
            tab_domi[i][1]=0;
            
            for(x = 0; x < n; x++){
                //wypełniam tablicę unikatowymi wartościami
/*
                for(y = 0; y < i; y++){
                //sprawdzam czy wartosc była już w tab_domi
                    if(tab_domi[y][0] == tab[x]){
                        bylo = 1;
                    }
                }
*/
                bylo = wartosc_obecna(tab, tab[i], i);
                if(bylo == 0) {
                    tab_domi[i][0] = tab[x];
                } else {
                    bylo = 0;
                }
            }
        }
        puts("wartosci w tab_domi");
        for(i=0; i < ile_roznych; i++){
            printf("i:%d w:%d\n",i, tab_domi[i][0]);

        }
        
        //zliczam ilosc wystapien
        for(i=0; i<ile_roznych; i++){
            for(x = 0; x<=n; x++){
                if(tab_domi[i][0] == tab[x]){
                    tab_domi[i][1] +=1;
                }
            }
        }
        
        puts("tab_domi: i : w : s");
        for(i=0; i < ile_roznych; i++){
            printf("i:%d w:%d s:%d\n",i, tab_domi[i][0], tab_domi[i][1]);
        }
                
        //szukam wartosci, która występuje najwiecej razy:
        
        int max = 0;
        int ile_max = 0;
        for(i = 0; i < ile_roznych; i++){
            if(tab_domi[i][1] > max){
                max = tab_domi[i][1];
                ile_max = 1;
            } else if(tab_domi[i][1] == max){
                ile_max +=1;
            }
        }
        
        //drukuję wyniki
        if(ile_max == ile_roznych) {
            puts("Brak dominanty, wszystkie wyniki takie same.");
        } else {
            if(ile_max > 1) {
                puts("-----Dominanty:");
            } else {
                puts("-----Dominanta:");
            }
            for(i=0; i < ile_roznych; i++){
                if(tab_domi[i][1] == max){
                    printf("i:%d w:%d s:%d\n",i, tab_domi[i][0], tab_domi[i][1]);
                }
            }
        }
        
    }
    

        
    return 0;
}