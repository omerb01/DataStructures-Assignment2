#include <iostream>
#include "../library2.h"
#include <cassert>
#include <ctime>
#include <thread>

void* testInit1() {
    int arr[]={5,2,1,4,3};
    int bad_arr[]={5,2,-1};
    assert(init(3,NULL)==NULL);
    assert(init(1,arr)==NULL);
    assert(init(0,arr)==NULL);
    assert(init(-1,arr)==NULL);
    assert(init(3,bad_arr)==NULL);
    bad_arr[1]=0; //just for csl..
    return init(5,arr);
}
void* testInit2(){ //this is the main init we will use
    int arr[20];
    for(int i=0; i<20; i++){
        arr[19-i]=i;
    }
    std::cout<<"Passed initial test..."<<std::endl;
    return init(20,arr);
}
void testAddClan1(void* oasis){
    assert(addClan(oasis,1)==FAILURE);
    assert(addClan(oasis,2)==FAILURE);
    assert(addClan(oasis,3)==FAILURE);
    assert(addClan(oasis,4)==FAILURE);
    assert(addClan(oasis,5)==FAILURE);
    assert(addClan(NULL,1)==INVALID_INPUT);
    assert(addClan(oasis,-1)==INVALID_INPUT);
}
void testAddClan2(void* oasis){
    for(int i=0;i<20;i++){
        assert(addClan(oasis,i)==FAILURE);
    }
    for(int i=100;i<110;i++){
        assert(addClan(oasis,i)==SUCCESS);
    }
    std::cout<<"Passed add clan test..."<<std::endl;
}
void testAddPlayer(void* oasis){
    assert(addPlayer(NULL, 1, 1, 1)==INVALID_INPUT);
    assert(addPlayer(oasis, -1, 1, 1)==INVALID_INPUT);
    assert(addPlayer(oasis, 1, -1, 1)==INVALID_INPUT);
    assert(addPlayer(oasis, 1, 1, -1)==INVALID_INPUT);
    assert(addPlayer(oasis, 1, 1, 20)==FAILURE);
    for (int i = 0; i < 10; ++i) {
        assert(addPlayer(oasis,60+i,55+i,0)==SUCCESS);
        //  player(i) with id 60+i score 55+i clan0
    }
    for (int i = 0; i < 10; ++i) {
        assert(addPlayer(oasis,100+i,100+i,1)==SUCCESS);
        //  player(i) with id 100+i score 100+i clan1
    }
    for (int i = 0; i < 5; ++i) {
        assert(addPlayer(oasis,20+i,20+i,2)==SUCCESS);
        //  player(i) with id 20+i score 20+i clan2
    }
    //check if the players are in the system
    for (int i = 0; i < 10; ++i) {
        assert(addPlayer(oasis,60+i,55+i,0)==FAILURE);
        assert(addPlayer(oasis,100+i,100+i,1)==FAILURE);
        if(i<5)
            assert(addPlayer(oasis,20+i,20+i,2)==FAILURE);
    }
    for (int i = 3; i < 19; ++i) {
        assert(addPlayer(oasis,i,i,i)==SUCCESS);
        //the clans 3-18 get one player each that have id as the clan and score as the clan
        assert(addPlayer(oasis,i,i,i)==FAILURE);
    }
    std::cout<<"Passed add player test..."<<std::endl;
}
void testFightAndMin(void* oasis){
    assert(clanFight(NULL, 0, 1, 1, 1)==INVALID_INPUT);
    assert(clanFight(oasis, -1, 1, 1, 1)==INVALID_INPUT);
    assert(clanFight(oasis, 0, -1, 1, 1)==INVALID_INPUT);
    assert(clanFight(oasis, 0, 1,0, 1)==INVALID_INPUT);
    assert(clanFight(oasis, 0, 1, 1, 0)==INVALID_INPUT);
    assert(clanFight(oasis, 0, 1, 11, 1)==FAILURE);
    assert(clanFight(oasis, 0, 1, 1, 11)==FAILURE);
    assert(clanFight(oasis,0,90,1,1)==FAILURE);
    assert(clanFight(oasis,90,0,1,1)==FAILURE);
    assert(getMinClan(oasis,NULL)==INVALID_INPUT);
    int min_alive;
    assert(getMinClan(NULL,&min_alive)==INVALID_INPUT);
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==0);
    assert(clanFight(oasis, 0, 1, 5, 5)==SUCCESS);    //first fight clan 1 won
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==1);
    assert(addClan(oasis,0)==FAILURE);
    assert(clanFight(oasis, 2, 1, 5, 1)==SUCCESS);    //clan2 won
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==2);
    assert(addClan(oasis,1)==FAILURE);
    assert(addPlayer(oasis,500,1000,19)==SUCCESS);
    assert(addPlayer(oasis,456,2,18)==SUCCESS);
    assert(clanFight(oasis,19,18,1,1)==SUCCESS);
    for (int i = 2; i < 17; ++i) {
        assert(clanFight(oasis, i, 19, 1, 1)==SUCCESS);    //clan19 won
        assert(clanFight(oasis,i-2,i-1,1,1)==FAILURE);      //they cant fight
        assert(getMinClan(oasis,&min_alive)==SUCCESS);
        assert(min_alive==i+1);
        assert(addClan(oasis,i)==FAILURE); //check clan exist
        assert(addPlayer(oasis,900+i,900+i,i)==SUCCESS); //check we can add players to clan
    }
    assert(clanFight(oasis, 17, 19, 1, 1)==SUCCESS); //19 win
    //clan 19 the only able to fight
    assert(addClan(oasis,50)==SUCCESS);
    assert(addClan(oasis,51)==SUCCESS);
    assert(addPlayer(oasis,777,9900,50)==SUCCESS);
    assert(clanFight(oasis,19,50,1,1)==SUCCESS);    //50 won
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==50);
    assert(addPlayer(oasis,776,9900,51)==SUCCESS);
    assert(clanFight(oasis,51,50,1,1)==SUCCESS);    //50 won - check who win if the have the same score
    assert(clanFight(oasis,51,50,1,1)==FAILURE);
    assert(getMinClan(oasis,&min_alive)==SUCCESS);
    assert(min_alive==50);
    std::cout<<"Passed fight and minimum clan alive test..."<<std::endl;
    min_alive=0; //just for csl..
}
void testQuit(void* oasis){
    void** tmp=NULL;
    void* temp=NULL;
    quit(tmp);
    quit(&temp);
    quit(&oasis);
    assert(oasis==NULL);
}

//this is an extra - not the test, erase if you want to run on csl
const int DONE =-1;
void printSomeChar(char c, int amount){
    for(int i=0; i<amount*2; i++)
        std::cout<<c;
}
void printLine(int *square_num, char first, char second){
    bool first_char=true;
    for(int i=0; square_num[i]!= DONE; i++){
        if(first_char){
            printSomeChar(first,square_num[i]);
            first_char= false;
        }else{
            printSomeChar(second,square_num[i]);
            first_char= true;
        }
    }
    std::cout << std::endl;
}
void pDown(char c, char space, int side){
    int move=6+side;
    int l1[] = {move+8,7,8+move,DONE};printLine(l1,space,c);
    int l2[] = {move+6,11,6+move,DONE};printLine(l2,space,c);
    int l3[] = {move+5,13,5+move,DONE};printLine(l3,space,c);
    int l4[] = {move+4,15,4+move,DONE};printLine(l4,space,c);
    int l5[] = {move+4,3,4,1,4,3,4+move,DONE};printLine(l5,space,c);
    int l6[] = {move+3,3,11,3,3+move,DONE};printLine(l6,space,c);
    int l7[] = {move+3,3,12,2,3+move,DONE};printLine(l7,space,c);
    int l8[] = {move+3,2,13,2,3+move,DONE};printLine(l8,space,c);
    int l9[] = {move+3,2,3,2,3,2,3,3,2+move,DONE};printLine(l9,space,c);
    int l10[] = {move+2,3,3,2,3,2,3,3,2+move,DONE};printLine(l10,space,c);
    int l11[] = {move+2,3,13,3,2+move,DONE};printLine(l11,space,c);
    int l12[] = {move+2,3,5,3,5,3,2+move,DONE};printLine(l12,space,c);
    int l13[] = {move+2,3,6,1,6,3,2+move,DONE};printLine(l13,space,c);
    int l14[] = {move+2,3,13,3,2+move,DONE};printLine(l14,space,c);
    int l15[] = {move+1,4,13,4,1+move,DONE};printLine(l15,space,c);
    int l16[] = {move+1,4,13,4,1+move,DONE};printLine(l16,space,c);
    int l17[] = {move,5,13,5,move,DONE};printLine(l17,space,c);
    int l18[] = {move,5,13,5,move,DONE};printLine(l18,space,c);
    int l19[] = {move,5,13,5,move,DONE};printLine(l19,space,c);
    int l20[] = {move,6,11,6,move,DONE};printLine(l20,space,c);
    int l21[] = {move,2,1,4,9,4,1,2,move,DONE};printLine(l21,space,c);
    int l22[] = {move,1,3,5,5,5,3,1,move,DONE};printLine(l22,space,c);
    int l23[] = {move+6,11,6+move,DONE};printLine(l23,space,c);
    int l24[] = {move+3,17,3+move,DONE};printLine(l24,space,c);
    int l25[] = {move+3,7,3,7,3+move,DONE};printLine(l25,space,c);
}
void pSide(char c, char space,int side){
    int move=6+side;
    int l1[] = {move+8,7,8+move,DONE};printLine(l1,space,c);
    int l2[] = {move+6,11,6+move,DONE};printLine(l2,space,c);
    int l3[] = {move+5,13,5+move,DONE};printLine(l3,space,c);
    int l4[] = {move+4,15,4+move,DONE};printLine(l4,space,c);
    int l5[] = {move+4,3,4,1,4,3,4+move,DONE};printLine(l5,space,c);
    int l6[] = {move+3,3,11,3,3+move,DONE};printLine(l6,space,c);
    int l7[] = {move+3,3,12,2,3+move,DONE};printLine(l7,space,c);
    int l8[] = {move+3,2,13,2,3+move,DONE};printLine(l8,space,c);
    int l9[] = {move+3,2,3,2,3,2,3,3,2+move,DONE};printLine(l9,space,c);
    int l10[] = {move+2,3,3,2,3,2,3,3,2+move,DONE};printLine(l10,space,c);
    int l11[] = {move+2,3,13,3,2+move,DONE};printLine(l11,space,c);
    move=side;
    int l12[] = {move+5,6,5,3,5,6,5+move,DONE};printLine(l12,space,c);
    int l13[] = {move+2,9,6,1,6,9,2+move,DONE};printLine(l13,space,c);
    int l14[] = {move,11,13,11,move,DONE};printLine(l14,space,c);
    int l15[] = {move+1,5,2,3,13,3,2,5,1+move,DONE};printLine(l15,space,c);
    int l16[] = {move+8,3,13,3,8+move,DONE};printLine(l16,space,c);
    int l17[] = {move+8,3,13,3,8+move,DONE};printLine(l17,space,c);
    int l18[] = {move+8,3,13,3,8+move,DONE};printLine(l18,space,c);
    int l19[] = {move+8,3,13,3,8+move,DONE};printLine(l19,space,c);
    int l20[] = {move+9,3,11,3,9+move,DONE};printLine(l20,space,c);
    int l21[] = {move+9,4,9,4,9+move,DONE};printLine(l21,space,c);
    int l22[] = {move+10,5,5,5,10+move,DONE};printLine(l22,space,c);
    move=6+side;
    int l23[] = {move+6,11,6+move,DONE};printLine(l23,space,c);
    int l24[] = {move+3,17,3+move,DONE};printLine(l24,space,c);
    int l25[] = {move+3,7,3,7,3+move,DONE};printLine(l25,space,c);
}
void pUp(char c, char space,int side){
    int move=6+side;
    int l1[] = {move+8,7,8+move,DONE};printLine(l1,space,c);
    int l2[] = {move+6,11,6+move,DONE};printLine(l2,space,c);
    int l3[] = {move+5,13,5+move,DONE};printLine(l3,space,c);
    int l4[] = {move+4,15,4+move,DONE};printLine(l4,space,c);
    int l5[] = {move+4,3,4,1,4,3,4+move,DONE};printLine(l5,space,c);
    int l6[] = {move+3,3,11,3,3+move,DONE};printLine(l6,space,c);
    move=4+side;
    int l7[] = {move,1,4,3,12,2,4,1,move,DONE};printLine(l7,space,c);
    int l8[] = {move,2,3,2,13,2,3,2,move,DONE};printLine(l8,space,c);
    int l9[] = {move,3,2,2,3,2,3,2,3,2,2,3,move,DONE};printLine(l9,space,c);
    int l10[] = {move,7,3,2,3,2,3,7,move,DONE};printLine(l10,space,c);
    int l11[] = {move+1,6,13,6,1+move,DONE};printLine(l11,space,c);
    int l12[] = {move+1,6,5,3,5,6,1+move,DONE};printLine(l12,space,c);
    int l13[] = {move+2,5,6,1,6,5,2+move,DONE};printLine(l13,space,c);
    int l14[] = {move+2,5,13,5,2+move,DONE};printLine(l14,space,c);
    int l15[] = {move+3,4,13,4,3+move,DONE};printLine(l15,space,c);
    move=4+side;
    int l16[] = {move+4,3,13,3,4+move,DONE};printLine(l16,space,c);
    int l17[] = {move+4,3,13,3,4+move,DONE};printLine(l17,space,c);
    int l18[] = {move+4,3,13,3,4+move,DONE};printLine(l18,space,c);
    int l19[] = {move+4,3,13,3,4+move,DONE};printLine(l19,space,c);
    int l20[] = {move+5,3,11,3,5+move,DONE};printLine(l20,space,c);
    int l21[] = {move+5,4,9,4,5+move,DONE};printLine(l21,space,c);
    int l22[] = {move+6,5,5,5,6+move,DONE};printLine(l22,space,c);
    move=6+side;
    int l23[] = {move+6,11,6+move,DONE};printLine(l23,space,c);
    int l24[] = {move+3,17,3+move,DONE};printLine(l24,space,c);
    int l25[] = {move+3,7,3,7,3+move,DONE};printLine(l25,space,c);
}
void printMovingP(char c, char space){
    system("cls");
    std::cout << "Get ready...";
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    system("cls");
    int k=7, side=0;
    while(k--){
        pDown(c,space,side);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
        pSide(c,space,side);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
        pUp(c,space,side);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        system("cls");
        side+=2;
    }
    k=7; side-=2;
    while(k--){
        pDown(c,space,side);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
        pSide(c,space,side);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
        pUp(c,space,side);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        system("cls");
        side+=-2;

    }
}
void coverP(){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    printMovingP(178,' ');
    while(true){
        std::cout<<"Once again?"<<std::endl<<"Press y/n"<<std::endl;
        char c;
        std::cin>>c;
        if(c=='n'){
            return;
        }else if(c=='y'){
            printMovingP(178,' ');
        }else{
            std::cout<<"Bad input :/"<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            return;
        }
    }
}
//till here

int main(){
    void* oasis=testInit1();
    assert(oasis);
    testAddClan1(oasis);
    quit(&oasis);
    oasis=testInit2(); //on oasis we got 0-19 clans till now
    assert(oasis);
    testAddClan2(oasis); //add some more clans that we wont use and check if all 0-19 are in
    testAddPlayer(oasis);
    testFightAndMin(oasis);
    testQuit(oasis);

    coverP();   //penguin fun :0
    return 0;
}