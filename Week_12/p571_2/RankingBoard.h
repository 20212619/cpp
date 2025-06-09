#pragma once
#include <iostream>
#include <fstream>
#include "FileException.h"
using namespace std;
#define NUM_MVP 5 // 최대 랭킹 5개

// PlayInfo: 플레이어의 랭킹 정보 저장
struct PlayInfo {
    string name;        // 플레이어 이름
    int nItem;          // 먹은 아이템 수
    double itemPerMove; // 이동 거리당 아이템 수
    PlayInfo(string na = "신인류", int ni = 0, double ipm = 0.0)
        : name(na), nItem(ni), itemPerMove(ipm) {}
};

// RankingBoard: 랭킹 관리 및 파일 입출력
class RankingBoard {
    PlayInfo MVP[NUM_MVP]; // 상위 5명 정보
    int nMVP = NUM_MVP;

public:
    void load(string filename) {
        ifstream is(filename);
        if (!is)
            throw FileException(filename, true);
        for (int i = 0; i < nMVP; i++)
            is >> MVP[i].nItem >> MVP[i].name >> MVP[i].itemPerMove;
        is.close();
    }
    void store(string filename) {
        ofstream os(filename);
        if (!os)
            throw FileException(filename, false);
        for (int i = 0; i < nMVP; i++)
            os << MVP[i].nItem << " " << MVP[i].name << " "
               << MVP[i].itemPerMove << "\n";
        os.close();
    }
    void print(string title = "게임 랭킹") {
        cout << endl << title << endl;
        for (int i = 0; i < nMVP; i++)
            cout << "[" << i + 1 << "위] " << MVP[i].name << "\t"
                 << MVP[i].nItem << " " << MVP[i].itemPerMove << "\n";
        cout << "엔터를 입력하세요.";
        getchar();
        cout << endl;
    }
    int add(int nItem, double ipm, bool isRightPlayer) {
        if (nItem <= MVP[nMVP - 1].nItem) return 0;
        int pos = nMVP - 1;
        for (; pos > 0; pos--) {
            if (nItem <= MVP[pos - 1].nItem) break;
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nItem = nItem;
        MVP[pos].itemPerMove = ipm;
        cout << "\n[" << pos + 1 << "위] " << (isRightPlayer ? "☞" : "☜") << " 이름을 입력하세요: ";
        getline(cin, MVP[pos].name);
        return pos + 1;
    }
};