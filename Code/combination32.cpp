
#include<bits/stdc++.h>
using namespace std;

int inputmsg[100][100];
int rowInMsg,colInMsg;
int cnt = 1,cnt1=0;
int rl,cl;



void combinationUtil(int arr[], int data[],
                     int start, int end,
                     int index, int r)
{
    if (index == r)
    {
        cout<<r<<endl;
        for(int i=0;i<r;i++){
            cout<<data[i]/colInMsg<<" "<<data[i]%colInMsg<<" ";
            if(inputmsg[])
        }
        cout<<endl;



        cout<<endl<<endl;

        return;
    }


    for (int i = start; i <= end &&
            end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1,
                        end, index+1, r);
    }

}

int main()
{
    colInMsg=4;
    rowInMsg = 8;
    freopen("combination32.txt","w",stdout);





    // combination-------------------------------


    int arr[32];
    for (int i=0; i<32; i++)
    {
        arr[i] = i;
    }
    for(int i=1; i<=32; i++)
    {

        int data[i];

        combinationUtil(arr,data,0,31,0,i);
    }



    //cout<<cnt<<endl;

    //cout<<cnt1<<endl;
}

