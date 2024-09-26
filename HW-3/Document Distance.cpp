#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 100;

int N, M, vocabSize;
string title;

vector <int> freq[MAXN];
set <string> dict;
map <string, int> count[MAXN];
map <string, int> titleList;

double docDis(int m, int n)
{
    int sum = 0;
    for (int i = 1; i <= vocabSize; i++)
        sum += freq[m][i] * freq[n][i];

    int length_m = 0;
    for (int i = 1; i <= vocabSize; i++)
        length_m += freq[m][i] * freq[m][i];
    int length_n = 0;
    for (int i = 1; i <= vocabSize; i++)
        length_n += freq[n][i] * freq[n][i];
    
    return acos(sum * 1.0 / (sqrt(length_m) * sqrt(length_n) * 1.0));
}

string stemmer(string str){
    if(str.size() >= 2 && str.substr(str.size() - 2) == "ed"){
        return(str.substr(0, str.size() - 2));
    }
    if(str.size() >= 3 && str.substr(str.size() - 3) == "ies"){
        return(str.substr(0, str.size() - 3) + "y");
    }
    if(str.size() >= 3 && str.substr(str.size() - 3) == "ing"){
        return(str.substr(0, str.size() - 3));
    }
    if(str.size() >= 2 && str.substr(str.size() - 2) == "es"){
        return(str.substr(0, str.size() - 2));
    }
    if (str.size() > 7 && str.substr(str.size() - 7) == "ational") {
        return(str.substr(0, str.size() - 7) + "ate");
    }
    if (str.size() > 6 && str.substr(str.size() - 6) == "tional") {
        return(str.substr(0, str.size() - 6) + "tion");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "enci") {
        return(str.substr(0, str.size() - 4) + "ence");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "anci") {
        return(str.substr(0, str.size() - 4) + "ance");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "izer") {
        return(str.substr(0, str.size() - 4) + "ize");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "abli") {
        return(str.substr(0, str.size() - 4) + "able");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "alli") {
        return(str.substr(0, str.size() - 4) + "al");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "entli") {
        return(str.substr(0, str.size() - 5) + "ent");
    }
    if (str.size() > 3 && str.substr(str.size() - 3) == "eli") {
        return(str.substr(0, str.size() - 3) + "e");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "ousli") {
        return(str.substr(0, str.size() - 5) + "ous");
    }
    if (str.size() > 7 && str.substr(str.size() - 7) == "ization") {
        return(str.substr(0, str.size() - 7) + "ize");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "ation") {
        return(str.substr(0, str.size() - 5) + "ate");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "ator") {
        return(str.substr(0, str.size() - 4) + "ate");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "alism") {
        return(str.substr(0, str.size() - 5) + "al");
    }
    if (str.size() > 7 && str.substr(str.size() - 7) == "iveness") {
        return(str.substr(0, str.size() - 7) + "ive");
    }
    if (str.size() > 7 && str.substr(str.size() - 7) == "fulness") {
        return(str.substr(0, str.size() - 7) + "ful");
    }
    if (str.size() > 7 && str.substr(str.size() - 7) == "ousness") {
        return(str.substr(0, str.size() - 7) + "ous");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "aliti") {
        return(str.substr(0, str.size() - 5) + "al");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "iviti") {
        return(str.substr(0, str.size() - 5) + "ive");
    }
    if (str.size() > 6 && str.substr(str.size() - 6) == "biliti") {
        return(str.substr(0, str.size() - 6) + "ble");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "logi") {
        return(str.substr(0, str.size() - 4) + "log");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "icate") {
        return(str.substr(0, str.size() - 5) + "ic");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "ative") {
        return(str.substr(0, str.size() - 5) + "");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "alize") {
        return(str.substr(0, str.size() - 5) + "al");
    }
    if (str.size() > 5 && str.substr(str.size() - 5) == "iciti") {
        return(str.substr(0, str.size() - 5) + "ic");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "ical") {
        return(str.substr(0, str.size() - 4) + "ic");
    }
    if (str.size() > 3 && str.substr(str.size() - 3) == "ful") {
        return(str.substr(0, str.size() - 3) + "");
    }
    if (str.size() > 4 && str.substr(str.size() - 4) == "ness") {
        return(str.substr(0, str.size() - 4) + "");
    }
    if (str.size() > 2 && str.substr(str.size() - 2) == "al") {
        return(str.substr(0, str.size() - 2) + "");
    }

    return str;
}

void tokenizer(int ID){
    char ch;
    string token;
    do{
        scanf("%c", &ch);
        if (isalpha(ch))
            token += tolower(ch);
        else{
            token = stemmer(token);
            dict.insert(token);
            count[ID][token]++;
            token = "";
        }
    } while (ch != '#');
}

void setfreq(){
    for (int i = 1; i <= N; i++){
        freq[i].resize(vocabSize);
        int j = 0;
        for (auto word = dict.begin(); word != dict.end(); word++)
            freq[i][j++] = count[i][*word];
    }
}

int main()
{
    scanf("%d", &N);
    for (int ID = 1; ID <= N; ID++){
        cin >> title;
        titleList[title] = ID;
        tokenizer(ID);
    }
    vocabSize = dict.size();
    setfreq();

    string title1, title2;
    scanf("%d", &M);
    for (int i = 1; i <= M; i++){
        cin >> title1 >> title2;
        printf("Case %d: %.3f\n", i, docDis(titleList[title1], titleList[title2]));
    }
}