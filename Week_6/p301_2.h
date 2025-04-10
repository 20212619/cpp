#ifndef P301_2_H
#define P301_2_H

#include <string>
using namespace std;

const int MAXWORDS = 1000;

struct WordPair {
    string eng;
    string kor;
};

class MyDic {
    WordPair words[MAXWORDS];  // 저장된 단어 배열
    int nWords;                // 현재 등록된 단어의 수

public:
    MyDic();                                   // 생성자
    void add(string eng, string kor);          // 하나의 단어 추가
    void load(string filename);                // 파일에서 단어 읽기
    void store(string filename);               // 파일에 모든 단어 저장
    void print();                              // 모든 단어를 화면에 출력
    string getEng(int id);                     // id번째 영어단어 반환
    string getKor(int id);                     // id번째 한글 설명 반환
};

#endif
