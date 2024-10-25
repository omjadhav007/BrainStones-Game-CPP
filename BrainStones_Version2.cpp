#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
int scoreA=0,scoreB=0;
bool takingInput;
void clearAfter(int second){
    this_thread::sleep_for(chrono::seconds(second));
    system("CLS");
}

void printBox(int a[]){
    clearAfter(1);
    int i;
    cout<<"\n-------------------------------------------";
    cout<<"\n|                Player A                 |";
    cout<<"\n-------------------------------------------";
    cout<<'\n';
    cout<<'|';
    cout<<"   ";
    for(i=0;i<5;i++)cout<<"------ ";
    cout<<"   ";
    cout<<'|';
    cout<<'\n';
    cout<<'|';
    cout<<"   ";
    for(i=0;i<5;i++)cout<<"| "<<setw(2)<<a[i]<<" | ";
    cout<<"   ";
    cout<<'|';
    cout<<'\n';
    cout<<'|';
    cout<<"   ";
    for(i=0;i<5;i++)cout<<"------ ";
    cout<<"   ";
    cout<<'|';

    if(takingInput){
        cout<<'\n';
        cout<<'|';
        cout<<"   ";
        for(i=1;i<=5;i++)cout<<"   "<<i<<"   ";
        cout<<"   ";
        cout<<'|';
        cout<<" <---- Box Numbers";
    }

    cout<<"\n-------------------------------------------";

    if(takingInput){
        cout<<'\n';
        cout<<'|';
        cout<<"   ";
        for(i=10;i>5;i--)cout<<"  "<<setw(2)<<i<<"   ";
        cout<<"   ";
        cout<<'|';
        cout<<" <---- Box Numbers";
    }

    cout<<'\n';
    cout<<'|';
    cout<<"   ";
    for(i=9;i>4;i--)cout<<"------ ";
    cout<<"   ";
    cout<<'|';
    cout<<'\n';
    cout<<'|';
    cout<<"   ";
    for(i=9;i>4;i--)cout<<"| "<<setw(2)<<a[i]<<" | ";
    cout<<"   ";
    cout<<'|';
    cout<<'\n';
    cout<<'|';
    cout<<"   ";
    for(i=9;i>4;i--)cout<<"------ ";
    cout<<"   ";
    cout<<'|';
    cout<<"\n-------------------------------------------";
    cout<<"\n|                Player B                 |";
    cout<<"\n-------------------------------------------";
    cout<<"\n\tScoreA : "<<scoreA<<"\tScoreB : "<<scoreB<<'\n';
}

void toss(int &r){ 
    srand(time(0));
    r=rand();
}

void input(char &direction,int &boxNo,char &ch,int a[]){
    takingInput=1;
    string s=ch=='A'?"(1 to 5)":"(6 to 10)";
    while(1){
        printBox(a);
        cout<<'\n'<<ch<<"'s Turn\n";
        cout<<"\nEnter Box Number "<<s<<" : ";
        cin>>boxNo;
        string o;
        if(ch=='A'){
            if(boxNo<1||boxNo>5){
                cout<<"\nWrong choice.\nDo you want to try again (y/n) : ";
                cin>>o;
                if(o[0]!='y'&&o[0]!='Y')exit(0);
                else continue;
            }
        }
        else{
            if(boxNo<6||boxNo>10){
                cout<<"\nWrong choice.\nDo you want to try again (y/n) : ";
                cin>>o;
                if(o[0]!='y'&&o[0]!='Y')exit(0);
                else continue;
            }
        }
        cout<<"\nEnter direction (L/R) : ";
        cin>>direction;
        if(direction>='a')direction-=32;
        if(direction!='L'&&direction!='R'){
            cout<<"\nWrong choice.\nDo you want to try again (y/n) : ";
            cin>>o;
            if(o[0]!='y'&&o[0]!='Y')exit(0);
        }
        else{
            if(ch=='B')direction=(direction=='L')?'R':'L';
            takingInput=0;
            break;
        }

    }
}

void pick(char &ch,char &direction,int &boxNo,int &i,int &inHand,int a[]){
    if(boxNo>0)i=boxNo-1,boxNo=-1;
    inHand=a[i];
    a[i]=0;
    printBox(a);
}
void check4(int &i,char &ch,int a[]){
    if(a[i]==4){
        if(i>=0&&i<5)scoreA+=a[i];
        else scoreB+=a[i];
        a[i]=0;
        printBox(a);
    }
}
void printa(int a[]){
    cout<<'\n';
    for(int j=0;j<10;j++)cout<<a[j]<<' ';
}
bool putInDirection(char &direction,int &i,int &inHand,char &ch,int a[]){
    if(direction=='R'){
        // direction is Right
        if(!inHand){
            i++;
            i+=10;
            i%=10;
            if(ch=='A')scoreA+=a[i],a[i]=0;
            else scoreB+=a[i],a[i]=0;
            printBox(a);
            // printa(a);
            return 1;
        }
        while(inHand){
            i++;
            i+=10;
            i%=10;
            a[i]++;
            printBox(a);
            check4(i,ch,a);
            inHand--;
        }
        i++;
        i+=10;
        i%=10;
    }
    else{
        // direction is Left
        if(!inHand){
            i--;
            i+=10;
            i%=10;
            if(ch=='A')scoreA+=a[i],a[i]=0;
            else scoreB+=a[i],a[i]=0;
            printBox(a);
            // printa(a);
            return 1;
        }
        while(inHand){
            i--;
            i+=10;
            i%=10;
            a[i]++;
            printBox(a);
            check4(i,ch,a);
            inHand--;
        }
        i--;
        i+=10;
        i%=10;
    }
    // printa(a);
    return 0;
}

int main(){
    int a[]={6,6,6,6,6,6,6,6,6,6};
    char ch;
    int boxNo,i=0,inHand,r;
    toss(r);
    // r=0;
    char direction;
    while((scoreA+scoreB)!=60){
        r++;
        r&=1;
        ch=r+'A';
        input(direction,boxNo,ch,a);
        while(1){
            // cout<<"\n\tScoreA : "<<scoreA<<"\tScoreB : "<<scoreB<<'\n';
            pick(ch,direction,boxNo,i,inHand,a);
            if(putInDirection(direction,i,inHand,ch,a)) break;
        }
    }
    if(scoreA>scoreB)cout<<"\nA is Winner....";
    else if(scoreA<scoreB)cout<<"\nB is Winner....";
    else cout<<"\nDraw....";
    return 0;
}