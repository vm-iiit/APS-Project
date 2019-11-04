#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    
   
        int m,n;
        cin>>m>>n;
        char x[m][n];
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>x[i][j];
            }
        }
        
        int r,c;
        cin>>r>>c;
        char y[r][c];
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                cin>>y[i][j];
            }
        }
             int flag1=0;

                for(int i=0;i<m;i++)
                {
                    for(int j=0;j<n;j++)
                    {
                        int flag=0;
                        for(int k=0;k<r;k++)
                            {
                              for(int l=0;l<c;l++)
                               {   
                                   if(i+k<m&&j+l<n)
                                   {
                                      if(x[i+k][j+l]==y[k][l])
                                      {
                                        continue;
                                       }
                                       else
                                       { 
                                          flag=1;
                                          break; 
                                       }
                                    }
                                    else { flag=1;}
                               }
                            
                               if(flag)break;
                           }
                        
                        if(!flag)
                        {
                             cout<<"\nPattern starting at ("<<i<<","<<j<<")"<<endl;
                             flag1=1;
                        }
                    
                     }
                   
                       
                }
        
            if(!flag1)
            cout<<"No Pattern found\n";
   
    
    return 0;
}
