#include "p301_2.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// 클래스 생성자
MyDic::MyDic() {
    nWords = 0;
}

// 단어 추가
void MyDic::add(string eng, string kor) {
    if (nWords >= MAXWORDS) {
        cout << "단어장이 가득 찼습니다." << endl;
        return;
    }
    words[nWords].eng = eng;
    words[nWords].kor = kor;
    nWords++;
}

// 단어 파일에서 읽기
void MyDic::load(string filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "파일 열기 실패: " << filename << endl;
        return;
    }
    nWords = 0;
    while (fin >> words[nWords].eng >> words[nWords].kor) {
        nWords++;
        if (nWords >= MAXWORDS) break;
    }
    fin.close();
}

// 단어 파일에 저장
void MyDic::store(string filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "파일 저장 실패: " << filename << endl;
        return;
    }
    for (int i = 0; i < nWords; i++) {
        fout << words[i].eng << " " << words[i].kor << endl;
    }
    fout.close();
}

// 단어 목록 출력
void MyDic::print() {
    cout << left;
    cout << "------------------------------" << endl;
    cout << setw(5) << "No." << setw(20) << "English" << "Korean" << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < nWords; i++) {
        cout << setw(5) << i + 1
             << setw(20) << words[i].eng
             << words[i].kor << endl;
    }
    cout << "------------------------------" << endl;
}

// 영어 단어 반환
string MyDic::getEng(int id) {
    if (id < 0 || id >= nWords) return "";
    return words[id].eng;
}

// 한글 뜻 반환
string MyDic::getKor(int id) {
    if (id < 0 || id >= nWords) return "";
    return words[id].kor;
}

// 메인 함수
int main() {
    MyDic dic;
    string eng, kor;

    cout << "단어를 입력하세요. (끝내려면 'end' 입력)\n";
    while (true) {
        cout << "\n영어 단어: ";
        cin >> eng;
        if (eng == "end") break;

        cout << "한글 뜻: ";
        cin >> kor;

        dic.add(eng, kor);
    }

    dic.store("p301_2.txt");
    cout << "\n단어장을 'p301_2.txt'에 저장했습니다.\n";

    MyDic dic2;
    dic2.load("p301_2.txt");

    cout << "\n[불러온 단어장 출력]\n";
    dic2.print();

    return 0;
}
