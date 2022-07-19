#include<bits/stdc++.h>
using namespace std;
class wordF{
    int freq=0;
    public:
        string word;
        int getFreq(){return freq;}
        void incFreq(){freq++;}
        wordF(string word){
            this->word = word;
        }
};

int main()
{

    string word;
    ifstream file("D://data.txt");
    list<wordF> dataFreq;

    while (file>>word) {
        bool present = false;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        for(wordF &i : dataFreq){
            if(i.word==word){
                i.incFreq();
                present = true;
                break;
            }
        }

        if(!present){
            wordF w(word);
            w.incFreq();
            dataFreq.push_back(w);
        }
    }
    file.close();
    dataFreq.sort([](const wordF &a,const wordF &b){
        return a.word<b.word;
    });

    for(wordF i : dataFreq){
        cout<<i.word<<" ("<<i.getFreq()<<")\n";
    }
    return 0;
}
