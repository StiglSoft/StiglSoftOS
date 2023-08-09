#include "../io/console.c"
#include "../io/vga.c"
char Sreg[128];
char Areg[128];
int GetVal(int val0, int val1, int operator){
    switch (operator){
        case 0:
            return val0 + val1;
            break;
        case 1:
            return val0 - val1;
            break;
        case 2:
            return val0 * val1;
            break;
        case 3:
            return val0 / val1;
            break;
    }
}
void st(int src, int us, int operator){
    int cr;
    if(us < 128)
        cr = (Sreg)[us];
    else cr = (Areg)[us-128];
    if(src < 128)
        (Sreg)[src] = GetVal((Sreg)[src],cr,operator);
    else (Areg)[src] = GetVal((Areg)[src], cr, operator);
}
void cpy(int dest, int src){
    if(dest < 128)
        (Sreg)[dest] = src;
    else (Areg)[dest-128] = src;
}
void mov(int src, int dest){
    int cr;
    if(src < 128)
        cr = (Sreg)[src];
    else cr = (Areg)[src-128];
    if(dest < 128)
        (Sreg)[dest] = cr;
    else (Areg)[dest-128] = cr;
}
void cmp(int src){
    if(Sreg[1] == Sreg[src])
        Sreg[0] = 0;
    else if(Sreg[1] < Sreg[src])
        Sreg[0] = -1;
    else if(Sreg[1] > Sreg[src])
        Sreg[0] = 1;
    else if(Sreg[1] == 0)
        Sreg[0] = 2;
}
int je(){
    if(Sreg[0] == 0){
        return 1;
    }return 0;
}
int jne(){
    if(Sreg[0] == 0){
        return 0;
    }return 1;
}
int jnz(){
    if(Sreg[0] == 2){
        return 1;
    }return 0;
}
void print(){
    if(Sreg[0] == 0){
        Clear();
        Row = -1;
        Column = 0;
    }
    for(int i = 1; i < Sreg[0];i++){
        printCh(Sreg[i]);
    }
}
void Execute(int source[], int srcLenght){
    for(int i =0; i < srcLenght;i++){
        switch (source[i]){
            case 1:
                mov(source[++i],source[++i]);
                break;
            case 2:
                cpy(source[++i],source[++i]);
                break;
            case 3:
                break;
            case 4:
                print();
                break;
            case 5:
                break;
            case 6:
                st(source[++i],source[++i],0);
                break;
            case 7:
                st(source[++i],source[++i],1);
                break;
            case 8:
                st(source[++i],source[++i],2);
                break;
            case 9:
                st(source[++i],source[++i],3);
                break;
            case 10:
                i = source[++i] -1;
                break;
            case 11:
                cmp(source[++i]);
                break;
            case 12:
                if(je())
                    i = source[++i] -1;
                break;
            case 13:
                if(jne())
                    i = source[++i] -1;
                break;
            case 14:
                if(jnz())
                    i = source[++i] -1;
                break;
            case 15:
                if(Sreg[0] == 0){
                    Clear();
                }else if(Sreg[0] == 1){
                    drawPixel(Sreg[1],Sreg[2],Sreg[3]);
                }
                break;
        }
    }
}