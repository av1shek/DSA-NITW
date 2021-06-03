#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ofstream fout;
    int num;
    /*fout.open("output.txt");
    while (fout)
    {
        cin>>num;
        if (num == -1)
            break;
        cout<<"writing "<<num<<endl;
        fout << num << " ";
    }
    fout.close();*/

    ifstream fin;
    fin.open("input.txt");
    while (true)
    {

        fin>>num;
        if(fin.eof())
        {
            cout<<"end of file"<<endl;
            break;
        }
        cout << num << " ";
    }
    fin.close();

    return 0;
}
