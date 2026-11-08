/*
 * Homework 9 — main.cpp
 * 이 파일은 수정하지 마세요.
 * problem1.cpp ~ problem3.cpp 에 있는 TODO 클래스와 함수만 구현하세요.
 *
 * 실행: ./hw9_main Test/case1.txt
 */
#include <iostream>
#include <fstream>
using namespace std;

void runProblem1(istream& in);
void runProblem2(istream& in);
void runProblem3(istream& in);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <test_data_file>" << "\n";
        return 1;
    }
    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Cannot open: " << argv[1] << "\n";
        return 1;
    }

    runProblem1(fin);
    runProblem2(fin);
    runProblem3(fin);

    return 0;
}
