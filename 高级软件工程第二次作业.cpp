#include<stdio.h>
#include<math.h>
#include<string.h>  
#include <stdlib.h>
#include <time.h> 
int count=0;//保存用户答对的题目数量 


//求最大公约数 
int gcd(int x,int y)
{
while(x!=y)
{
if(x>y)
x=x-y;
else
y=y-x;
}
return x;
}

//1.随机生成一个算式表达式函数
//2.转换成后缀表达式 （参考网上逆波兰式）
int create(int n,int a[])
 {
 	//首先随机生成一个运算表达式 
 	int m,i,j,t,top=0; 
 	m=2*(n-1);//表达式有多少个操作数，就要用相应长度的数组来保存 	
 	
	//随机生成表达式 
	for(i=0;i<=m;i++)
	{
		if(i%2==0)
		{
			a[i]=rand()%100+1;//1~100之间的数，所以后面也无需判断除数是否为零。 
		}
		else 
		{
			j=rand()%4-4;//因为用整型保存，所以使用-4，-3，-2，-1分别表示+，-，*，/ 
		    a[i]=j; 
		}
		if(a[i]==-4) printf("%c",'+');
		else if(a[i]==-3) printf("%c",'-');
		else if(a[i]==-2) printf("%c",'*');
		else if(a[i]==-1) printf("%c",'/');
		else printf("%d",a[i]);//输出表达式 
	}
	printf("="); 
}
	
	//将a[]转化成后缀表达式
int trans(int n,int *a)
	{
	  int i=0,j=0,top=0;
	  int t=a[i++]; //保存当前a[i]的值 
	  int b[2*(n-1)];//保存后缀表达式
	  int stack[2*(n-1)];//作为栈使用 
	  while(i<=2*(n-1))
	 {
		switch(t)
		{
			case -4:/*判定为加减号*/
            case -3:
                while(top!=0)
                {
            	    b[j]=stack[top];
            	    top--;j++;
                }
                top++;
                stack[top]=t;
                break;
            case -2:
			case -1:
				while(stack[top]==-2||stack[top]==-1)
				{
					b[j]=stack[top];
					top--;j++;
				}
				stack[++top]=t;
				break;
			default://默认为数字 
                while(t>=0&&t<=100)
                {
                	b[j]=t;j++;
                	t=a[i];i++;
                }
		}
	}
	while(top!=0)
	{
		b[j]=stack[top];
		j++;top--;
	} 
}
	
	//此时得到后缀表达式b[j] 
	
	//计算后缀表达式,并将结果转化为字符串 
void calculate(int n,int b[],char rs1[]) 
{
	int	i=0,t,top=0;
	int stack[2*(n-1)]={0};
	int r[3]={0,-1,1};//保存最后结果,初始情况下，分子为0，分母为,1 
	 
                            //rs1保存最后正确结果的分子 
 	char rs2[2*(n-1)]={' '};//最后结果的分母用字符串表示 
   	t=b[i];i++;
	while(i<=2*(n-1))
	{
		switch(t)
		{
		  case -4:r[0]=r[0]+stack[top]*r[2];top--;break;//+
		  case -3:r[0]=stack[top]*r[2]-r[0];top--;break;//-
		  case -2:r[0]=r[0]*stack[top];top--;break;//*
		  case -1:r[2]=r[2]*stack[top];top--;break;
		  default: top++;stack[top]=t;	
		}
	 	t=b[i++]; 	
	}
	//化简最终结果
	r[0]=r[0]/gcd(r[0],r[2]);
	r[2]=r[2]/gcd(r[0],r[2]); 
	//将整形转化成字符串 
	itoa(r[0],rs1,10);
	itoa(r[2],rs2,10);
	strcat(rs1,"/");//字符串拼接 
	strcat(rs1,rs2);
	
}



int main()
{
	int n,i,c;
	int a[20]={0};//保存生成的表达式 ，因为最多不超过10个运算符，所以20数组大小不超过20 
	char s[20]={' '};//保存用户输入的答案,分数或者整数 
	char r[20]={' '};//保存正确结果 
	printf("请输入需要生成的四则运算式的个数：");
	scanf("%d",&c);
	for(i=0;i<c;i++)
	{
	  srand( (unsigned int)time( NULL ) ); //初始化随机数
	  n=rand()%10+2;//随机生成表达式长度，有2~10个操作数 
	  create(n,a);	
	  trans(n,a);
	  calculate(n,a,r);
	  
	  printf("\n请输入计算结果：");
	  scanf("%s",s);
      if (strcmp(s, r) == 0)
	 {
		printf("正确\n");
		count++; 
	 }
	 else 
	 {
		printf("错误,正确答案是：%s\n",r); 
 	 }
	} 
	 printf("正确率为%.2f%%\n",count*100/c);
}
 
 
