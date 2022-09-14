vector<int> kmp(string s, string pat,int start_pos=0){
    int j=-1,i;
    int pat_length=pat.length();
    vector<int> table(pat_length,-1);
    for(i=1;i<pat_length;i++){
        if(table[i-1]==-1){
            if(pat[0]==pat[i]){
                table[i]=0;
            }
            
        }
        else{
            if(pat[i]==pat[table[i-1]+1]){
                table[i]=table[i-1]+1;

            }
            else{
                if(pat[i]==pat[0]){
                    table[i]=0;
                }
            }
        }
    }
    debug(table);
    i=start_pos;
    j=-1;
    vector<int> ans;
    for(i;i<(int)s.length();){
        
        if(s[i]==pat[j+1]){
            if(j==pat_length-2){
                ans.push_back(i-pat_length+1);
                j=pat[j]-1;
            }
            i++;j++;
        }
        else{
            if(j==-1){
                i++;
            }
            else{

            j=table[j];
            }
        }
    }

debug(ans);
return ans;


}