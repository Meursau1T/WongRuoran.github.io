# include <stdio.h>
# include <cstring>

int n;
int count=0,a[7],jump=0,jump2=0;
int plot[15][15]={0};

void ChangeState(int x,int y,char z){  // 让纵横斜行的格子表示的数+1或者-1,只有为0的格子可以放下棋子
  if(z == '+'){
    for(int i = 1 ; i <= n ; i++){
      plot[i][y] += 1;                 // 横行
      plot[x][i] += 1;                 // 纵行
      if(x+i <= n && y+i <= n){
        plot[x+i][y+i] += 1;           // 右下
      }
      if(x+i <= n && y-i >= 1){
        plot[x+i][y-i] += 1;           // 右上
      }
      if(x-i >= 1 && y-i >= 1){
        plot[x-i][y-i] += 1;           // 左上
      }
      if(x-i >= 1 && y+i <= n){
        plot[x-i][y+i] += 1;           // 左下
      }
    }
    plot[x][y] -= 1;                   // 防止棋子处被重复处理
  }
  else{                                // 同上，用于撤销操作
    for(int i = 1 ; i <= n ; i++){
      if(plot[i][y] != 0)
        plot[i][y] -= 1;
      if(plot[x][i] != 0)
        plot[x][i] -= 1;
      if(x+i <= n && y+i <= n && plot[x+i][y+i] != 0){
        plot[x+i][y+i] -= 1;
      }
      if(x+i <= n && y-i >= 1 && plot[x+i][y-i] != 0){
        plot[x+i][y-i] -= 1;
      }
      if(x-i >= 1 && y-i >= 1 && plot[x-i][y-i] != 0){
        plot[x-i][y-i] -= 1;
      }
      if(x-i >= 1 && y+i <= n && plot[x-i][y+i] != 0){
        plot[x-i][y+i] -= 1;
      }
    }
  }
}

void search(int mx,int got){
  if(got == n){
    count = count + 1;               // 计数，保证只输出前三个答案
    for(int i = 1 ; i <= n && count <= 3; i++){
      if(i != n)
        printf("%d ",a[i]);
      else
        printf("%d\n",a[i]);
    }
    return;
  }
  int i,y=1,x;
  for(i = mx ; i <= n*n; i++){      // mx用于防止重复计算
    if(i % n != 0)
      y = (i / n) + 1;
    else
      y = i / n;
    x = i - (y-1)*n;
    if(plot[x][y] == 0){
      a[y]=x;
      ChangeState(x,y,'+');
      search(i+(1+n-x),got+1);       //一旦放下棋子，跳过本行剩余的所有格子
      ChangeState(x,y,'-');
    }
  }
}

int main(){
  scanf("%d",&n);
  search(1,0);
  printf("%d\n",count);
  return 0;
}
