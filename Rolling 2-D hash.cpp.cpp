#include<bits/stdc++.h>
using namespace std;
#define mod 1000000009
#define modinv2 500000005


bool comp(pair<int,int>a,pair<int,int>b)
{
    if(a.first==b.first)
    return a.second<b.second;
    else
    return a.first<b.first;


}

void LCP(int lcp[], long long int pattern[],int n)
{

  int j=0;

  lcp[0]=0;

  for(int i=1;i<n;i++)
  {
      if(pattern[i]==pattern[j])
      {
           lcp[i] = lcp[j]+1;
           j++;
      }
      else
      {
          if(j==0)
          {
             lcp[i]=0;
          }
          else
          {
             j=lcp[j-1];
             i--;
          }

      }

  }



}


int main()
{

ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);

unordered_map<char,int> charmap;

int k=1;

for(char i='a';i<='z';i++)
{
    charmap[i]=k++;
}
for(char i='A';i<='Z';i++)
{
    charmap[i]=k++;

}
for(char i='0';i<='9';i++)
{
    charmap[i]=k++;
}

vector<long long int> powers2(1000000);

powers2[0] = 1;

for(int i=1;i<powers2.size();i++)
{

powers2[i] = (powers2[i-1]*2)%mod;

}



int t;
cin>>t;


for(int test=0;test<t;test++)
{


int m1;
int m2;

cin>>m1;
cin>>m2;

string text[m1];


for(int i=0;i<m1;i++)
cin>>text[i];


int n1;
int n2;

cin>>n1;
cin>>n2;

string pattern[n1];

for(int i=0;i<n1;i++)
cin>>pattern[i];


if(n1>m1||n2>m2)
{
    
cout<<"NO MATCH FOUND...\n";
exit(1);

}


long long int text_hash_val[m1][m2-n2+1];
long long int  txthelper=0;
long long int  pathelper=0;

for(int row=0;row<m1;row++)
{
    
txthelper=0;

for(int i=0;i<n2;i++)
{
     txthelper = (txthelper%mod+(powers2[n2-1-i]%mod*charmap[text[row][i]]%mod)%mod)%mod;
}


text_hash_val[row][0]=txthelper;


int i;
int flag;
for(i=1;i<m2-n2+1;i++)
{
   txthelper = (((mod + txthelper - (charmap[text[row][i-1]]%mod*powers2[n2-1]%mod)%mod )%mod * 2)%mod + charmap[text[row][i+n2-1]])%mod;

   text_hash_val[row][i]=txthelper;

}


}//rows of text

/*

for(int i=0;i<m1;i++)
{
  for(int j=0;j<m2-n2+1;j++)
  {
       cout<<text_hash_val[i][j]<<" ";
     
  }

  cout<<endl;
}
*/

//cout<<"\nsuccess--1\n";

long long int pat_hash_val[n1];

pathelper=0;

for(int row=0;row<n1;row++)
{
    
pathelper=0;

for(int i=0;i<n2;i++)
{
     pathelper = (pathelper%mod+(powers2[n2-1-i]%mod*charmap[pattern[row][i]]%mod)%mod)%mod;
}

pat_hash_val[row]=pathelper;

}//rows of pattern

/*cout<<endl;

for(int i=0;i<n1;i++)
{
    cout<<pat_hash_val[i]<<endl;
}

*/

//--------------kmp on hash values of text and pattern------------//

int lcp[n1];

LCP(lcp,pat_hash_val,n1);

//find transpose
/*
long long int T_text_hash_val[m2-n2+1][m1];

for(int i=0;i<m2-n2+1;i++)
{
   for(int j=0;j<m1;j++)
   {
         T_text_hash_val[i][j]=text_hash_val[j][i];
   }

}
*/
vector<pair<int,int>>result;

int k=0;

for(int col=0;col<m2-n2+1;col++)
{

       int j=0;
       for(int i=0;i<m1;i++)
       {
           if(text_hash_val[i][col]==pat_hash_val[j])
           { 
                 j++;
                 
                 if(j==n1)
                 {
                    //is the starting point of matched text i-n1+1;

                    //check all the corresponding values O(n1*n2) time
                  
                     int flag=0;

                     //cout<<"\n-----------------------\n";

                     for(int r=0;r<n1;r++)
                       {
 
                          //cout<<text[i-n1+r+1]<<endl;
                        
                           for(int c=0;c<n2;c++)
                           {
                                                         
                                 if(pattern[r][c]!=text[i-n1+r+1][col+c])
                                 {
                                     flag=1;
                                     break;
                                 }
                        
                           }

                      }

                     if(!flag)
                     {
                        result.push_back(make_pair(i-n1+1,col));
                            
                     }

                 }

           }
           else
           {
               if(j!=0)
               {
                   j = lcp[j-1];
                   i--;
               }
               else
               {
                   j=0;
               }

           }

       }



}//storing result;

if(result.size()==0)
{

cout<<"NO\n";

}
else
{
cout<<"YES\n";

sort(result.begin(),result.end(),comp);

for(int i=0;i<result.size();i++)
{
   cout<<"("<<result[i].first+1<<","<<result[i].second+1<<")\n"; 

}

result.clear();

}

cout<<"end\n";

}//testcases

cout<<"ending\n";
}//main
