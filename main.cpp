#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void naiveCheck(string pattern,string text, int startIndex){
int length=pattern.length();
int b=0;
for(int a=0;a<length;a++){
    if(pattern[a]==text[startIndex+a])   {   b++;    }
}
if(b==length){cout<<startIndex<<endl;}//writes index if charasters corresspond to pattern
}

int createHash(char s,int offset,int p,int power){
    return (((int)s - offset) * (int)pow(p,power));
}

int updateHash(int hash, char strPrev, char strNext, int offset, int p, int power)
{
   int  newHash=hash-((int) strPrev - offset) * (int)pow(p,power);
    newHash=newHash*p;
    newHash+=((int)strNext-offset);
    return newHash;
}

void karpRabinAlgorithm(string pattern,string text,int patternLen,int textLen,int p,int offset)
{
int hashW=0;
int hashT=0;
int a=0;
        while(a<patternLen){
            hashW=hashW+createHash(pattern[a],offset,p,patternLen-a-1);
            hashT=hashT+createHash(text[a],offset,p,patternLen-a-1);
            a=a+1;
        }
a=patternLen;
int b=0;
int indicator;
        while(a<=textLen){
            if(hashW==hashT){
                indicator=1;
                for(int k=0;k<pattern.length();k++){
                    if(pattern[k]!=text[k+b]){
                        indicator=0;
                        break;
                    }
                }
                if(indicator==1){
                    naiveCheck(pattern,text,b);
                }
            }
            if(a<textLen){
                hashT=updateHash(hashT,text[b],text[a],offset,p,patternLen-1);
            }
                a+=1;
                b+=1;
        }
}

void loadData(string &pattern,string &text)
{
    ifstream objectFile;
    objectFile.open("file.txt");
    objectFile>>pattern;
        while(!objectFile.eof())
        {
            objectFile>>text;
            int patternLen=pattern.length();
            int textLen=text.length();
            cout<<text<<endl;
            karpRabinAlgorithm(pattern,text,patternLen,textLen,5,65);
        }
        objectFile.close();
}

int main()
{
    string text;
    string pattern;
    loadData(pattern,text);
    return 0;
}
