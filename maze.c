#include <stdio.h>
#include <stdlib.h>
#define ANSI_COLOR_RED     "\e[41m"
#define ANSI_COLOR_YELLOW  "\e[43m"
#define ANSI_COLOR_WHITE "\e[47m"
#define ANSI_COLOR_GREEN "\e[42m"
#define ANSI_COLOR_RESET "\e[0m"
#define ANSI_COLOR_BLACK "\e[40m"

#define LOG_RED(X) printf("%s%s%s",ANSI_COLOR_RED,X,ANSI_COLOR_RESET)
#define LOG_BLACK(X) printf("%s%s%s",ANSI_COLOR_BLACK,X,ANSI_COLOR_RESET)
#define LOG_WHITE(X) printf("%s%s%s",ANSI_COLOR_WHITE,X,ANSI_COLOR_RESET)
#define LOG_GREEN(X) printf("%s%s%s",ANSI_COLOR_GREEN,X,ANSI_COLOR_RESET)
#define LOG_YELLOW(X) printf("%s%s%s",ANSI_COLOR_YELLOW,X,ANSI_COLOR_RESET)


#include <windows.h>
void print_map(int map[24][80]){
    system("cls");
    for (int i=0;i<24;i++){
        for (int j=0;j<80;j++){
            if(map[i][j]==1)
                LOG_BLACK(" ");
            else if(map[i][j]==0 || map[i][j]==3)
                LOG_WHITE(" ");
            else if(map[i][j]==2)
                LOG_RED(" ");
            else if (map[i][j]==4)
                LOG_YELLOW(" ");

        }
        printf("\n");
    }

}
int slove_maze(int map[24][80],int current[2],int end[2]){
    const int x=current[0];
    const int y=current[1];
    if(x<24){
        if(map[x+1][y]==0){
            current[0]=x+1;
            map[x+1][y]=2;
            print_map(map);
            if(slove_maze(map,current, end)==0){
                map[x+1][y]=3;
                current[0]=x;
                print_map(map);
            }
            else{
                map[x+1][y]=4;
                return 1;
            }
        }
    }
    if(x>0){
        if(map[x-1][y]==0){
            current[0]=x-1;
            map[x-1][y]=2;
            print_map(map);
            if(slove_maze(map,current, end)==0){
                 map[x-1][y]=3;
                current[0]=x;
                print_map(map);
            }
            else{
                map[x-1][y]=4;
                return 1;
            }
        }
    }
    if(y<79){
        if(map[x][y+1]==0){
            current[1]=y+1;
            map[x][y+1]=2;
            print_map(map);
            if(slove_maze(map,current, end)==0){
                map[x][y+1]=3;
                current[1]=y;
                print_map(map);
            }
            else{
                map[x][y+1]=4;
                return 1;
            }
        }
    }
    if(y>0){
        if(map[x][y-1]==0){
            current[1]=y-1;
            map[x][y-1]=2;
            print_map(map);
            if(slove_maze(map,current, end)==0){
                map[x][y-1]=3;
                current[1]=y;
                print_map(map);
            }
            else{
                map[x][y-1]=4;
                return 1;
            }
        }
    }
    if(x!=end[0] || y!=end[1])
       return 0;
    else
        return 1;
}

int main(void) {
    int map[24][80];
    FILE *fp=fopen("map.txt", "r");
    int col=0,row=0;
    int s_p[2],e_p[2];
    while(1){
        char c = fgetc(fp);
        if(feof(fp)){
            break ;
        }
        if(c=='\n'){
            row++;
            col=0;
        }
        else if(c=='0'){
            if(col==0){
                s_p[0]=row;
                s_p[1]=col;
            }
            if(col==79){
                e_p[0]=row;
                e_p[1]=col;
            }
            map[row][col]=0;
            col++;
        }
        else{
            map[row][col]=1;
            col++;
        }
    }
    int s_x=s_p[0],s_y=s_p[1];
    map[s_x][s_y]=2;
    slove_maze(map,s_p,e_p);
    map[s_x][s_y]=4;
    print_map(map);


}
