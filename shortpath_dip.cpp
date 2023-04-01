#include <iostream>

#define MW 10
#define MH 12
#define PL 30

#define For(I,MAX) for(int I=0; I<MAX; I++)
//#define FMap(I,K) for(int I=0; I<MH; I++)for(int K=0; K<MW; K++)

using namespace std;

int Px[PL];
int Py[PL];
int Plen=0;
int EndX, EndY;

int map[MH][MW] = {
// 0  1  2  3  4  5  6  7  8  9
 {99,99,99,99,99,99,99,99,99, 0}, // 0
 {99, 0, 0, 0,99, 0, 0, 0, 0, 0}, // 1
 {99, 0,99, 0,99, 0,99, 0, 0,99}, // 2
 {99, 0, 0, 0, 0, 0,99,99, 0,99}, // 3
 {99, 0,99, 0, 0, 0, 0,99,99,99}, // 4
 {99, 0,99, 0,99, 0, 0, 0, 0,99}, // 5
 {99, 0,99, 0,99, 0, 0, 0, 0,99}, // 6
 {99, 0,99, 0,99, 0,99, 0, 0,99}, // 7
 {99, 0,99, 0, 0, 0,99, 0, 0,99}, // 8
 {99, 0,99, 0, 0, 0, 0, 0, 0,99}, // 9
 {99, 0,99, 0, 0, 0,99, 0, 0,99}, //10
 {99,99,99,99,99,99,99,99,99,99}  //11
};


int getMap(int x, int y){return map[y][x];}
void setMap(int x, int y, int v){map[y][x]=v;}

void dumpMap(){
    For(i,MH){For(k,MW)printf("%3d",getMap(k,i)); cout<<"\n";}
}


bool OutMap(int x, int y){return(x<0||y<0||x>=MW||y>=MH);}
bool fillVal(int x, int y, int v){
    if(OutMap(x,y)||getMap(x,y)==99)return false;
    if(getMap(x,y)==0){setMap(x,y,v); return true;}
    return false;
}


// fill plus levelfor each level v
bool fv(int v){
    bool found=false;
    For(i,MH)For(k,MW){
        if(getMap(i,k)==v){
            int x=i, y=k;
            fillVal(x-1,y,v+1);
            fillVal(x+1,y,v+1);
            fillVal(x,y-1,v+1);
            fillVal(x,y+1,v+1);
            found=true;
        }
    }
    return found;
}

// fill each level with depth
void Fv(){ 
    for(int i=1;i<PL;i++){
        if(!fv(i)) break; // not found level
        if(getMap(EndX,EndY)!=0)break; // found location
    }
}

bool fillBack(int x, int y, int v){
    if(OutMap(x,y))return false;
    if(getMap(x,y)==1){Px[0]=x; Py[0]=y; return true;}
    if(getMap(x,y)==v){ 
        Px[v-1]=x; Py[v-1]=y;
        fillBack(x-1,y,v-1);
        fillBack(x+1,y,v-1);
        fillBack(x,y-1,v-1);
        fillBack(x,y+1,v-1);
        return true;
    }
    return false;
}

bool getPath(int ox, int oy, int X, int Y){
    EndX=X; EndY=Y;
    setMap(ox,oy,1);
    Fv(); 
    if(getMap(X,Y)==0)return false;
    Plen=getMap(X,Y);
    fillBack(X,Y,Plen);
    return true;
}

void dumpPath(int L){for(int i=0;i<L; i++)printf("(%d,%d) ", Px[i],Py[i]); cout<<"\n";}


int main()
{
    if(getPath(1,7, 7,9)){
        dumpMap();
        dumpPath(Plen);
        printf("Path length %d\n", Plen);
    }else{
        dumpMap();
        printf("Path not found!");
    }
}
