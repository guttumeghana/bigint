//CPL ASSIGNMENT-1
//Addition,Subtraction and Multiplication of BigInt

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct bigInt
{
    int num[310];
    int count;
    int sign;
} BigInt;

void Initialize(BigInt *b)
{
    b->count=0;
    b->sign=0;
	int i=0;
	for(i=0;i<310;i++)
	{
		b->num[i]=0;
	}
}

void Convert(BigInt *b,char *s)
{
    int i=0,j=0,k=0;
    if(s[i]=='-')
    {
        b->sign=1;
        i++;
    }
    if((s[i+1]=='\0')&&(s[i]=='0'))
    {
        b->count=1;
        b->num[i]=0;
    }
    else
    {
        while(s[i]=='0')
        {
            i++;
        }

        j=strlen(s)-1;

        while(j>=i)
        {
            b->num[k]=s[j]-'0';
            k++;j--;
            b->count++;
        }
    }
    
    if(b->count>309)
    {
        printf("LIMIT FOR BIGINT EXCEEDED\n");
    }
    
}

// 0 IF B1>B2  1 IF B2>=B1
int large(BigInt *b1,BigInt *b2)
{
	int retval=0;
	int i=b1->count-1;
	int flag=0;
	if(b1->count < b2->count)
	{
		retval=1;
	}
	else if(b1->count == b2->count)
	{
		while((i>=0)&&(flag==0))
		{
			if(b1->num[i] < b2->num[i])
			{
				flag=1;
			}
			i--;
		}
		if(flag==1)
		{
			retval=1;
		}
	}
	return retval;
	
}

void Add(BigInt *b1,BigInt *b2,BigInt *res)
{
    if((b1->count>310)||(b2->count>310))
    {
        printf("LIMIT FOR BIGINT ADDITION EXCEEDED\n");
    }
    else
    {
        
        int i=0,j=0,carry=0,max=0;
        if((b1->count)>(b2->count))
        {
            res->count=b1->count+1;
        }
        else
        {
            res->count=b2->count+1;
        }
        
        max=res->count-1;


        for(i=0;i<max;i++)
        {
        	res->num[i]=carry;
        	if(i<(b1->count))
        	{
        		res->num[i]+=b1->num[i];
        	}
        	if(i<(b2->count))
        	{
        		res->num[i]+=b2->num[i];
        	}
        	carry=res->num[i]/10;
        	res->num[i]%=10;
        }	

        res->num[i]=carry;
         if(carry==0)
         {
            res->count--;
         }
            
            for(i=res->count-1;i>=0;i--)
            {
                printf("%d",res->num[i]);
            }
            printf("\n");       
    }
    
}

void Subtract(BigInt *b1,BigInt *b2,BigInt *res)
{
	Initialize(res);
	int i=0,j=0,k=0,borrow=0,max=b1->count;
	
	res->count=max;

	for(i=0;i<max;i++)
	{
		res->num[i]=borrow+b1->num[i];

		if(i < b2->count)
		{
			if(res->num[i] < b2->num[i])
			{
				res->num[i]+=10;
				borrow=-1;
			}
			else
			{
				borrow=0;
			}

			res->num[i]-=b2->num[i];
		}
		else
		{
			if(res->num[i]==-1)
			{
				res->num[i]=9;
				borrow=-1;
			}
			else
			{
				borrow=0;
			}
			
		}
	}
	i=max;
	while((i>1)&&(res->num[i-1]==0))
	{
		i--;
		res->count--;
	}
	
	for(i=res->count-1;i>=0;i--)
	{
		printf("%d",res->num[i]);
	}
	printf("\n");
}

void Multiply(BigInt *b1, BigInt *b2, BigInt *res)
{
	int i=0,j=0,k=0;
	int l=0,m=0,n=0;
	int carry=0,pro=0;
	BigInt temp;
	Initialize(&temp);
	res->count=b1->count + b2->count;
	for(i=0;i<310;i++)
	{
		res->num[i]=0;
	}
	for(i=0;i < b1->count;i++)
	{
		carry=0;
		for(k=0;k<i;k++)
		{
			temp.num[k]=0;
		}
		k=i;
		for(j=0;j< b2->count;j++)
		{
			pro=(b1->num[i] * b2->num[j]) + carry;	
			carry=pro/10;							
			temp.num[k]=pro%10;						
			k++;
		}
		temp.num[k]=carry;
		n=b2->count;
		if(carry!=0)
		{
			n++;
		}
		carry=0;

		for(l=i;l<(i + n);l++)
		{
			m=res->num[l]+temp.num[l]+carry;
        	res->num[l] = m%10;	
        	carry= m/10;		
        	
		}
		res->num[l]=carry;
	}

	if(carry==0)
	{
		res->count--;
	}
	
	for(i=res->count-1;i>=0;i--)
	{
		printf("%d",res->num[i]);
	}
	printf("\n");
}

void main()
{
    BigInt b1,b2,sum,diff,pro;
    Initialize(&b1);
    Initialize(&b2);
    Initialize(&sum);
	Initialize(&diff);
	Initialize(&pro);

    int i=0,j=0;
    char s1[310],s2[310];
    printf("Enter first number:\n");
    scanf("%s",s1);
    printf("Enter second number:\n");
    scanf("%s",s2);
    Convert(&b1,s1);
    Convert(&b2,s2);
	
	//BOTH ARE POSITIVE
	if((b1.sign==0)&&(b2.sign==0))
	{
		printf("ADDITION OF TWO BIGINTS IS: ");
		Add(&b1,&b2,&sum);
		
		printf("SUBTRACTION OF TWO BIGINTS IS: ");
		if(large(&b1,&b2)==1)
		{
			printf("-");
			Subtract(&b2,&b1,&diff);
			diff.sign=1;
		}
		else
		{
			Subtract(&b1,&b2,&diff);
		}

		printf("MULTIPLICATION OF TWO BIGINTS IS: ");
		Multiply(&b1,&b2,&pro);
	}

	//1ST IS +VE 2ND IS -VE
	else if((b1.sign==0)&&(b2.sign==1))
	{
		printf("ADDITION OF TWO BIGINTS IS: ");
		if(large(&b1,&b2)==1)
		{
			printf("-");
			Subtract(&b2,&b1,&sum);
			sum.sign=1;
		}
		else
		{
			Subtract(&b1,&b2,&sum);
		}

		printf("SUBTRACTION OF TWO BIGINTS IS: ");
		Add(&b1,&b2,&diff);

		printf("MULTIPLICATION OF TWO BIGINTS IS: ");
		printf("-");
		Multiply(&b1,&b2,&pro);
		pro.sign=1;
	}

	//BOTH ARE -VE
	else if((b1.sign==1)&&(b2.sign==1))
	{
		printf("ADDITION OF TWO BIGINTS IS: ");
		printf("-");
		Add(&b1,&b2,&sum);
		sum.sign=1;

		printf("SUBTRACTION OF TWO BIGINTS IS: ");
		if(large(&b1,&b2)==1)
		{
			
			Subtract(&b2,&b1,&diff);
		}
		else
		{
			printf("-");
			Subtract(&b1,&b2,&diff);
			diff.sign=1;
		}

		printf("MULTIPLICATION OF TWO BIGINTS IS: ");
		Multiply(&b1,&b2,&pro);
	}

	//1ST IS -VE 2ND IS +VE
	else
	{
		printf("ADDITION OF TWO BIGINTS IS: ");
		if(large(&b1,&b2)==1)
		{
			
			Subtract(&b2,&b1,&sum);
		}
		else
		{
			printf("-");
			Subtract(&b1,&b2,&sum);
			diff.sign=1;
		}

		printf("SUBTRACTION OF TWO BIGINTS IS: ");
		printf("-");
		Add(&b1,&b2,&diff);
		diff.sign=1;

		printf("MULTIPLICATION OF TWO BIGINTS IS: ");
		printf("-");
		Multiply(&b1,&b2,&pro);
		pro.sign=1;
	}
	
}