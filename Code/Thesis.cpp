#include<bits/stdc++.h>

using namespace std;

#define pp pair<int,int>
#define ppp pair<pp,int>
int cnt = 1;


vector<vector<int> > address;



void addGen(vector<int> v, int p)
{
    if(p==v.size())
    {

        address.push_back(v);
        return;
    }
    else
    {
        if(v[p] == -1)
        {
            v[p]=0;
            p++;
            addGen(v,p);
            p--;
            v[p]=1;
            p++;
            addGen(v,p);
        }
        else
        {
            p++;
            addGen(v,p);
        }
    }
}


int main()
{
    //freopen("input.txt","r",stdin);
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    cout<<"--------------------------Starting of the Sender part-----------------------------------"<<endl;
    int n, numberOfRules, rowBlock, colBlock, block, b,bitsInRule, bitsInRuleBlock;

    cout<<"Number of bits in the message : ";
    cin>>n;

    cout<<"Length of each block in the message : ";
    cin>> rowBlock;

    cout<<"Number of block in the message : ";
    cin>> block;



    numberOfRules = colBlock = n/block;

    bitsInRuleBlock = ceil(log2(rowBlock));
    bitsInRule = block*bitsInRuleBlock;
    //cout<<n<<" "<<rowBlock<<" "<<block<<" "<<numberOfRules<<endl;

    int msg[block][rowBlock][colBlock];

    int rules[block][numberOfRules][bitsInRuleBlock];

    int numberOfOnes[block][numberOfRules];
    int inputmsg[rowBlock][n];

    for(int i=0; i<rowBlock; i++)
    {
        for(int j=0; j<n; j++)
        {
            int b,c;
            b = j/numberOfRules;
            c = j%numberOfRules;
            cin>>msg[b][i][c];
        }
    }

    for( int b = 0; b<block; b++)
    {
        for(int i=0; i< numberOfRules; i++)
        {
            numberOfOnes[b][i]=0;
            for(int j=0; j< bitsInRuleBlock ; j++)
            {
                rules[b][i][j] = 0;
            }
        }
    }



    vector<vector<vector<int>>> onesPosInMsg(block,vector<vector<int>>(numberOfRules));
    vector<vector<vector<string>>> onesPosInMsgInBinary(block,vector<vector<string>>(numberOfRules));

    for(int b=0; b<block; b++)
    {
        for(int r=0; r<rowBlock; r++)
        {
            for(int c=0; c<colBlock; c++)
            {
                //cin>>msg[b][r][c];
                if(msg[b][r][c]==1) numberOfOnes[b][c]++;

                if(msg[b][r][c] == 1)
                {
                    onesPosInMsg[b][c].push_back(r);

                    int pos = r, lim;
                    string g="",s;
                    s = bitset<8>(pos).to_string();
                    lim = s.size() - bitsInRuleBlock;
                    for(int i=s.size()-1; i>=lim; i--)
                    {
                        g = g + s[i];

                    }
                    reverse(g.begin(),g.end());
                    onesPosInMsgInBinary[b][c].push_back(g);
                }
            }
        }
    }

    cout<<endl <<"Message : "<<endl;

    for(int r=0; r<rowBlock; r++)
    {
        for(int b=0; b<block; b++)
        {
            for(int c=0; c<colBlock; c++)
            {
                cout<<msg[b][r][c]<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl<<endl;


    //generating rules....................................................
    for(int b=0; b<block; b++)
    {
        for(int c=0; c<colBlock; c++)
        {
            for(int k =0; k<bitsInRuleBlock; k++)
            {
                int z = 0, o = 0;
                for(int i=0; i<onesPosInMsg[b][c].size(); i++)
                {
                    if(onesPosInMsgInBinary[b][c][i][k] == '0')
                    {
                        z=1;
                    }
                    else
                    {
                        o=1;
                    }
                }

                if(z==1 && o==1)
                {
                    rules[b][c][k] = -1;
                }
                else if (z==1 && o==0 )
                {
                    rules[b][c][k] = 0;
                }
                else if(z==0 && o==1)
                {
                    rules[b][c][k] = 1;
                }
                else if(numberOfOnes[b][c]==0)
                {
                    rules[b][c][k]=-2;
                }

            }
        }
    }

    for(int i=0; i<numberOfRules; i++)
    {
        cout<< "r"<<i+1<<" : ";
        for(int b=0; b<block; b++)
        {
            for(int j=0; j<bitsInRuleBlock; j++)
            {
                cout<<rules[b][i][j];
            }
            cout<<" ";
        }

        cout<<endl;
    }


    /*for(int i=0;i<block;i++){
        for(int j=0;j<numberOfRules;j++){
            cout<<numberOfOnes[i][j]<<endl;
        }
        cout<<endl;
    }*/


    cout<<"------------------------------Ending of the sender part------------------------------------"<<endl<<endl<<endl;






    /*cout<<"------------------------------starting of the error injection part------------------------------------"<<endl<<endl;
    int row, col, blk;
    cout<< " Give the row (0 to "<< rowBlock-1 <<"), col (0 to "<< colBlock-1<<") number of each block (0 to "<<block-1<< ") to inject error : " <<endl;
    while(cin>>blk>>row>>col)
    {
        if(0<=row<rowBlock && 0<=col<colBlock && 0<=blk<block)
        {
            msg[blk][row][col] = 1 - msg[blk][row][col];
        }
        else if(row==-1 && col==-1 && block==-1)
        {
            cout<<"Error enjection ended"<<endl;
        }
        else
        {
            cout<<"invalid output"<<endl;
        }
    }

    cout<<"------------------------------ending of the error injection part------------------------------------"<<endl<<endl<<endl;*/




    cout<<"------------------------------starting of the receiever part------------------------------------"<<endl<<endl;

    //vector<vector<vector<vector<int>>>> addressInBin(block,vector<vector<vector<int>>>(numberOfRules));
    //vector<vector<vector<int>>> addressInDec(block,vector<vector<int>>(numberOfRules));

    map<ppp,int> mapping;
    pp pa;
    ppp paa;

    for(int b=0; b<block; b++)
    {
        for(int i=0; i<numberOfRules; i++)
        {
            vector<int> v;
            for(int j=0; j<bitsInRuleBlock; j++)
            {
                v.push_back(rules[b][i][j]);
            }
            address.clear();
            addGen(v,0);
            //vector<int> bin;
            int val, c;
            for(int j=0; j<address.size() ; j++)
            {

                if(address[j][0]!=-2)
                {
                    val = 0;
                    c=0;
                    //addressInBin[b][i].push_back(address[j]);
                    for(int k=address[j].size()-1; k>=0; k--)
                    {
                        if(address[j][k]==1)
                        {
                            val = val + pow(2,c);
                        }
                        c++;
                    }

                    pa.first = b;
                    pa.second = i;
                    paa.first = pa;
                    paa.second = val;
                    mapping[paa] = 1;


                    //addressInDec[b][i].push_back(val);
                    val = 0;
                }

            }
        }
    }


    /*for(int b=0;b<block;b++){
        for(int i=0;i<numberOfRules;i++){
            for(int j=0;j<addressInBin[b][i].size();j++){
                for(int k=0;k<addressInBin[b][i][j].size();k++){
                    cout<<addressInBin[b][i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }*/

    /*for(int b=0; b<block; b++)
    {
        for(int i=0; i<numberOfRules; i++)
        {
            for(int j=0; j<addressInDec[b][i].size(); j++)
            {
                cout<<addressInDec[b][i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }*/

    for(int z=1; z<=1; z++)  //16777215
    {
        for(int i=0; i<rowBlock; i++)
        {
            for(int j=0; j<n; j++)
            {
                int b,c;
                b = j/numberOfRules;
                c = j%numberOfRules;
                cin>>msg[b][i][c];
            }
        }

        cout<<"Count : "<<z<<endl;
        cout<<"Message with error : "<<endl;

        for(int r=0; r<rowBlock; r++)
        {
            for(int b=0; b<block; b++)
            {
                for(int c=0; c<colBlock; c++)
                {
                    cout<<msg[b][r][c]<<" ";

                    pa.first = b;
                    pa.second =c;
                    paa.first = pa;
                    paa.second =r;

                    if(mapping[paa] ==1 && msg[b][r][c]==0)
                    {
                        msg[b][r][c] = 1;
                    }
                    else if(mapping[paa]==0 && msg[b][r][c]==1)
                    {
                        msg[b][r][c] = 0;
                    }

                }
            }
            cout<<endl;
        }
        cout<<endl<<endl;

        // message correction....................................................................
        /*for(int b=0; b<block; b++)
        {
            for(int i=0; i<numberOfRules; i++)
            {
                if(numberOfOnes[b][i]!=0)
                {
                    int first, last,sz;
                    sz = addressInDec[b][i].size();
                    first = addressInDec[b][i][0];
                    last = addressInDec[b][i][sz-1];

                    for(int j=0; j<first; j++)
                    {
                        msg[b][j][i] = 0;
                    }
                    //for(int j=first; j<=last; j++)
                    //{
                     //   msg[b][j][i] = 1;
                    //}

                    for(int z=0;z<sz;z++){
                        int l = addressInDec[b][i][z];
                        msg[b][l][i] = 1;
                    }

                    for(int j=last+1; j<rowBlock; j++)
                    {
                        msg[b][j][i] = 0;
                    }
                }
                else
                {
                    for(int j=0; j<rowBlock; j++)
                    {
                        msg[b][j][i]=0;
                    }
                }

            }
        }*/


        cout<<"Correct message : "<<endl;
        for(int r=0; r<rowBlock; r++)
        {
            for(int b=0; b<block; b++)
            {
                for(int c=0; c<colBlock; c++)
                {
                    cout<<msg[b][r][c]<<" ";
                }
            }
            cout<<endl;
        }
        cout<<endl<<endl;

    }


}



