#pragma once
#include <string>
#include <iostream>
using namespace std;

// FileException: 파일 읽기/쓰기 오류 정보를 저장
struct FileException {
    string filename; // 오류가 발생한 파일 이름
    bool bRead;      // true: 읽기 오류, false: 쓰기 오류
    FileException(string name, bool b) : filename(name), bRead(b) {}
};