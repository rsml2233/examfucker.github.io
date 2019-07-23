#include <stdio.h>
#include <stdlib.h>


/*不分割单词的程序思路：
S1:循环获取一行字符存入数组a，如果获取成功，执行S2~S4.
     用while(gets(a)!=NULL)即可实现。
     如：输入“  You are a good boy  .  \n”时，内存为：



S2：统计单词个数word_count，把空格、\t等分割字符改成\0并查找英文句子最后的结束字符(. ? !)后把结束字符换成\0
     用char * 变量p访问数组a，即(p=a+1)开始,p++ 直到*p=='.' 或者 *p=='?' *p=='！';  p从a+1开始是因为第一个位置不可能是单词的结束
     遇到单词结束（当前位置不是字母，但是前一个位置是字母，也可以用当前位置是空格，前一个位置不是空格,因为前面的空格改成\0了，
     所以用\0替换）.但是，此时容易忘记统计结束字符前的单词。所以需要在结束后再判断一次。
     程序以下两种方法都可以实现
     (1)  if(isalpha(*p)==0) *p='\0';  //因为p从a+1开始，因此要处理当开头是空格时字符变为\0的问题。
          p=a+1; word_count=0;
          while(*p!='.' && *p!='?' && *p!='!')
          {
            if(isalpha(*p)==0 && isalpha(*(p-1))==1 ) word_count++;
            if(*p==' ' || *p=='\t' ) *p='\0';
            p++;
          }

          c=*p;
          *p='\0';
          if(*(p-1)!=' ' && *(p-1)!='\t') word_count++;
     (2)if(isalpha(*p)==0) *p='\0'; //因为p从a+1开始，因此要处理当开头是空格时字符变为\0的问题。
        p=a+1;
        while(*p!='\0')
         {
          if( (*p==' ' || *p=='\t') && ( *(p-1)!='\0' ) word_count++;
          if(*p==' ' || *p=='\t' ) *p='\0';
          if(*p=='.' || *p=='?' || *p=='!') break;
          p++;
         }
         c=*p;
         *p='\0';
         if(*(p-1)!=' ' && *(p-1)!='\t') word_count++;
         注意，处理后p指向原来句子的结束字符，只不过现在结束字符改成\0了，这样输出单词的时候就不会有问题了。处理后内存情况为：















S3：用p逆序访问数组a中的字符，查找单词开始，然后输出各单词。注意不要改动p的值。
     单词的开始的标志为：p指向的字符不是\0，同时p==a或者(p-1)指向的是\0。也就是说数组的开头是字母时是单词的开始，或者p-1指向的是\0时也是单词的开始













     输出一个单词后，根据word_count的值确定是否输出空格。然后让word_count--.
     用以下代码即可实现：
     while(p>=a)
     {
         if(*p!='\0' && (p==a || *(p-1)=='\0')
           {
              printf("%s",p);
              if(word_count!=1) printf(" ");
              word_count--;
           }

        p--;
     }




S4：输出结尾的字符和回车。
     printf("%c\n",c);
*/

int isalpha(char a)
{
    //判断字符a是否为单词中的字符，注意本题目中'也是单词的一部分，如it's是一个单词。因此，把它也作为字母处理了。正常情况下用下面语句来实现：
    //return a>='a' && a<='z' || a>='A' && a<='Z' || a=='\'' || a=='‘';

    //但是本题目中测试例子中存在一个中文状态下的单引号，这个单引号是用两个字符来表示的，因此直接用上面这样处理不可以。
    //可以转换为用如下方法： 不是分割字符，不是结束字符就是单词组成
    return (a!=' ' && a!='\t' && a!='\0' && a!='\r' && a!='.' && a!='?' && a!='!');
}
int main(int argc,char * argv[])
{
    char a[1000],*p,c;
    int j,row,is_word,word_count;
    printf("Enter a sentence: ");
    while(gets(a)!=NULL)
    {
        if(isalpha(*a)==0) *a='\0';
        p=a+1;
        word_count=0;
        while(*p!='\0')
        {
            if( (*p==' ' || *p=='\t') && ( *(p-1)!='\0' )) word_count++;
            if(*p==' ' || *p=='\t' ) *p='\0';
            if(*p=='.' || *p=='?' || *p=='!') break;
            p++;
        }
        c=*p;
        *p='\0';

        if(*(p-1)!='\0') word_count++;

        printf("Reversal of sentence: ");
        while(p>=a)  //逆序访问数组a 查找单词开始并输出该单词
        {
            if(*p!='\0' && (p==a || *(p-1)=='\0'))
              {
                printf("%s",p);
                if(word_count!=1) printf(" ",word_count);
                word_count--;
              }

            p--;
        }
        //输出结尾字符，并换行，这样一组数据的输出占一行。
        printf("%c\n",c);
    }
    return 0;
}
