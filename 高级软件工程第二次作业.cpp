#include<stdio.h>
#include<math.h>
#include<string.h>  
#include <stdlib.h>
#include <time.h> 
int count=0;//�����û���Ե���Ŀ���� 


//�����Լ�� 
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

//1.�������һ����ʽ���ʽ����
//2.ת���ɺ�׺���ʽ ���ο������沨��ʽ��
int create(int n,int a[])
 {
 	//�����������һ��������ʽ 
 	int m,i,j,t,top=0; 
 	m=2*(n-1);//���ʽ�ж��ٸ�����������Ҫ����Ӧ���ȵ����������� 	
 	
	//������ɱ��ʽ 
	for(i=0;i<=m;i++)
	{
		if(i%2==0)
		{
			a[i]=rand()%100+1;//1~100֮����������Ժ���Ҳ�����жϳ����Ƿ�Ϊ�㡣 
		}
		else 
		{
			j=rand()%4-4;//��Ϊ�����ͱ��棬����ʹ��-4��-3��-2��-1�ֱ��ʾ+��-��*��/ 
		    a[i]=j; 
		}
		if(a[i]==-4) printf("%c",'+');
		else if(a[i]==-3) printf("%c",'-');
		else if(a[i]==-2) printf("%c",'*');
		else if(a[i]==-1) printf("%c",'/');
		else printf("%d",a[i]);//������ʽ 
	}
	printf("="); 
}
	
	//��a[]ת���ɺ�׺���ʽ
int trans(int n,int *a)
	{
	  int i=0,j=0,top=0;
	  int t=a[i++]; //���浱ǰa[i]��ֵ 
	  int b[2*(n-1)];//�����׺���ʽ
	  int stack[2*(n-1)];//��Ϊջʹ�� 
	  while(i<=2*(n-1))
	 {
		switch(t)
		{
			case -4:/*�ж�Ϊ�Ӽ���*/
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
			default://Ĭ��Ϊ���� 
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
	
	//��ʱ�õ���׺���ʽb[j] 
	
	//�����׺���ʽ,�������ת��Ϊ�ַ��� 
void calculate(int n,int b[],char rs1[]) 
{
	int	i=0,t,top=0;
	int stack[2*(n-1)]={0};
	int r[3]={0,-1,1};//���������,��ʼ����£�����Ϊ0����ĸΪ,1 
	 
                            //rs1���������ȷ����ķ��� 
 	char rs2[2*(n-1)]={' '};//������ķ�ĸ���ַ�����ʾ 
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
	//�������ս��
	r[0]=r[0]/gcd(r[0],r[2]);
	r[2]=r[2]/gcd(r[0],r[2]); 
	//������ת�����ַ��� 
	itoa(r[0],rs1,10);
	itoa(r[2],rs2,10);
	strcat(rs1,"/");//�ַ���ƴ�� 
	strcat(rs1,rs2);
	
}



int main()
{
	int n,i,c;
	int a[20]={0};//�������ɵı��ʽ ����Ϊ��಻����10�������������20�����С������20 
	char s[20]={' '};//�����û�����Ĵ�,������������ 
	char r[20]={' '};//������ȷ��� 
	printf("��������Ҫ���ɵ���������ʽ�ĸ�����");
	scanf("%d",&c);
	for(i=0;i<c;i++)
	{
	  srand( (unsigned int)time( NULL ) ); //��ʼ�������
	  n=rand()%10+2;//������ɱ��ʽ���ȣ���2~10�������� 
	  create(n,a);	
	  trans(n,a);
	  calculate(n,a,r);
	  
	  printf("\n�������������");
	  scanf("%s",s);
      if (strcmp(s, r) == 0)
	 {
		printf("��ȷ\n");
		count++; 
	 }
	 else 
	 {
		printf("����,��ȷ���ǣ�%s\n",r); 
 	 }
	} 
	 printf("��ȷ��Ϊ%.2f%%\n",count*100/c);
}
 
 
