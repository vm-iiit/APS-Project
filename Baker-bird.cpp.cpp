#include<bits/stdc++.h>
using namespace std;

char text[1005][1005];
char pattern[1005][1005];
int match_found[1005][1005];

// char text[2005][2005];
// char pattern[305][305];
// int match_found[2005][2005];

struct Trie_node
{
    bool root_node;
    bool end_of_word;
    int end_index;
    unordered_map<char, Trie_node *> m;
    Trie_node *fail_link;
    Trie_node *back_link;
    char ch;
};

vector<pair<int,int>> answer_vector;

typedef Trie_node node;

node *build_trie(node *root, char pattern[1005][1005], int rows, int columns, vector<int>& pat_vec)
{
    int lvr, lvc;
    if(root == NULL)
    {
        root = new node();
        root->end_of_word = false;
        root->root_node = true;
        root->back_link = root;
        root->fail_link = root;
        root->ch = '.';
        // cout<<"root node asssigned\n";
    }


    node *ptr;
    for(lvr = 0; lvr < rows; lvr++)
    {
        // cout<<"building trie for pattern word "<<lvr+1<<endl;
        ptr = root;
        for(lvc = 0;lvc < columns; lvc++)
        {
            if(ptr->m[pattern[lvr][lvc]] == NULL)
            {
                ptr->m[pattern[lvr][lvc]] = new node();
                ptr->m[pattern[lvr][lvc]]->back_link = ptr;
                ptr->m[pattern[lvr][lvc]]->ch = pattern[lvr][lvc];
                ptr->m[pattern[lvr][lvc]]->root_node = false;
                ptr->m[pattern[lvr][lvc]]->end_index = INT_MAX;
            }
            
            ptr =  ptr->m[pattern[lvr][lvc]];

            if(lvc == columns-1)
            {
                ptr->end_of_word = true;
                ptr->end_index = min(ptr->end_index, lvr);
                pat_vec.push_back(ptr->end_index);
            }

        }
    }
    return root;
}

node *find_suffix(node *ptr, node *root, char c)
{
     // if(ptr->back_link == root)
     //     return root;

    ptr = ptr->back_link;
    ptr = ptr->fail_link;

    if(ptr->m[c] != NULL)
        return (ptr->m[c]);
    else
    {
        if(ptr == root)
            return root;
        else
            return find_suffix(ptr, root, c);
    }
}

void add_suffix_links(node *root)
{
    queue<node *> q;
    q.push(root);
    while(q.size())
    {
        auto ele = q.front();
        q.pop();
        // cout<<"adding suffix link for "<<ele->ch<<endl;
        if(ele == root || ele->back_link == root)
            ele->fail_link = root;
        else
            ele->fail_link = find_suffix(ele, root, ele->ch);
        // cout<<"suffix link made to "<<ele->fail_link->ch<<endl;
        for(auto mi = ele->m.begin(); mi != ele->m.end(); mi++)
            {
                q.push(mi->second);
                // cout<<"pushed in queue "<<mi->second->ch<<endl;
            }
    }
}

void kmp(vector<int>pattern, vector<int> text, int column)
{   
    //string text, pattern;
    //cin>>pattern>>text;
    int lt, lp, lv;
    lt = text.size();
    lp = pattern.size();

    // cout<<"in kmp, text \n";
    // for(auto ele: text)
    //  cout<<ele<<' ';

    // cout<<"\nin kmp, pattern \n";
    // for(auto ele: pattern)
    //  cout<<ele<<' ';
    // cout<<"\nstarting kmp\n";
    
    int lps[lp];
    //memset(lps, 0, sizeof(int)*lp);
    for(int lv =0; lv<lp;lv++)
        lps[lv] = 0;
    
    int p1=0, p2 = 1;
    while(p2 < lp)
    {
        // cout<<p1<<' '<<p2<<endl;
        if(pattern[p1] == pattern[p2])
        {
            lps[p2] = lps[p2-1] + 1;
            ++p1;
        }

        else
        {
            while(p1 >= 0 && pattern[p1] != pattern[p2])
            {
                --p1;
            }

            lps[p2] = p1+1;
            ++p1;
        }
        ++p2;
    }

    // for(lv=0;lv<lp; lv++)
    //     cout<<lps[lv]<<' ';
    // cout<<endl;
    // cout<<"lps printed\n\n";

    int matches = 0;
    int match_len = 0;

    p2=0;
    for(p1 = 0; p1<lt;)
    {
        
        if(text[p1] == pattern[p2])
        {
            // cout<<"match\n";
            ++p1;
            ++p2;

        }

        else
        {
            // cout<<"mismatch\n";
            if(p2 == 0)
                ++p1;
            else
            {
                p2 = lps[p2]-1;
                if(p2<0)
                    p2 = 0;
            }
        }

        if(p2 == lp)
        {
            // cout<<"word match\n";
            ++matches;
            // cout<<"Match at "<<p1-1<<' '<<column<<endl;
            answer_vector.push_back(make_pair(p1-1,  column));
            // cout<<"pushed "<<'('<<p1-pattern.size()+1<<','<<column-pattern.size()+2<<')'<<" into ans\n";
            p2 = lps[p2-1];
        }
    }

    //cout<<matches<<endl;
}

bool compare(pair<int,int> a, pair<int,int> b)
{
    if(a.first == b.first)
        return a.second <= b.second;
    else
        return a.first < b.first;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tc;
    cin>>tc;
    while(tc--)
    {
        int t1, t2, p1, p2, lv, lvr, lvc;
        // ios_base::sync_with_stdio(false);
        // cin.tie(0);
        // cout.tie(0);
        // cout<<"\nEnter dimensions of pattern grid:";

        cin>>t1>>t2;
        
        // cout<<"\nEnter text array\n";
        for(lvr=0;lvr<t1;lvr++)
            for(lvc=0;lvc<t2;lvc++)
                cin>>text[lvr][lvc];

        cin>>p1>>p2;
        
        // cout<<"\nEnter pattern array\n";
        for(lvr=0;lvr<p1;lvr++)
            for(lvc=0;lvc<p2;lvc++)
                cin>>pattern[lvr][lvc]; 

        
        // cout<<"Enter dimensions of text grid :";
        

        // cout<<endl;
        // for(lvr =0; lvr < t1; lvr++)
        // {
        //  for(lvc = 0; lvc < t2;lvc++)
        //      cout<<text[lvr][lvc]<<' ';
        //  cout<<endl;
        // }
        // cout<<endl;


        node *root = NULL;
        vector<int> pat_vec;
        root = build_trie(root, pattern, p1, p2, pat_vec);
        add_suffix_links(root);

        node *ptr;
        
        //memset(match_found, -1, sizeof(int)*t1*t2);
        //cout<<endl;
        for(lvr =0; lvr < t1; lvr++)
        {
            for(lvc = 0; lvc < t2;lvc++)
                match_found[lvr][lvc]=-1;
            
        }
        //cout<<endl;

        for(lvr =0; lvr < t1; lvr++)
        {
            ptr = root;
            for(lvc = 0; lvc < t2;lvc++)
            {
                // cout<<"matching indices "<<lvr<<' '<<lvc<<" from text pattern\n";
                if(ptr->m[text[lvr][lvc]] != NULL)
                    {
                        ptr = ptr->m[text[lvr][lvc]];
                        // cout<<"pointer advanced to next node\n";
                    }
                else
                {
                    // cout<<"character mismatch\n";
                    if(ptr != root)
                    {
                        // cout<<"pointer following suffix link\n";
                        ptr = ptr->fail_link;
                        --lvc;
                    }
                    
                    
                }

                if(ptr->end_of_word == true)
                {
                    // cout<<"match !!!\n";
                    match_found[lvr][lvc] = ptr->end_index;
                }
            }
        }

        cout<<endl;
        for(lvr =0; lvr < t1; lvr++)
        {
         for(lvc = 0; lvc < t2;lvc++)
             cout<<match_found[lvr][lvc]<<' ';
         cout<<endl;
        }
        cout<<endl;

        answer_vector.clear();
        vector<int> col;
        for(lvc = p2-1 ;lvc < t2 ; lvc++)
        {
            col.clear();
            for(lvr=0;lvr<t1;lvr++)
                col.push_back(match_found[lvr][lvc]);
            // cout<<"sending col ";
            // for(auto ele:col)
            //  cout<<ele<<' ';
            // cout<<" to kmp\n";
            kmp(pat_vec, col, lvc);

            if(answer_vector.size())
                break;
        }

        // if(answer_vector.size())
        //     sort(answer_vector.begin(), answer_vector.end(), compare);

        // if(answer_vector.size() == 0)
        //     cout<<"NO MATCH FOUND...\n";
        // else
        //     for(auto pair: answer_vector)
        //     {
        //         cout<<'('<<pair.first - pat_vec.size()+2<<','<<pair.second-p2+2<<')'<<endl;
        //     }

        if(answer_vector.size())
            cout<<"YES\n";
        else
            cout<<"NO\n";
        
    }
}