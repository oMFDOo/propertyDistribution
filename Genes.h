#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

// 각 세대 유전자 수
#define N_OF_GEN 128
// 하나의 유전자 길이 : 재산 n개를
#define GEN_LENGTH 100
// 분배할 자식의 수  : k명에게 분배할 것이다.
#define NUM_OF_CHILD 5
// 돌연변이 비율
#define MUTATE1 3
// 엘리트 비율
#define ELITE 4

bool randomL[101] = { 0 };

// 최대 진화 세대 수
#define ITER 10000
// 중간 값 출력 세대
#define SKIP 1000

bool getRandom() {
    for (int i = 0; i < MUTATE1; i++) {
        randomL[i] = 1;
    }
    return randomL[rand() % 100];
}

class Genes {
private:
    vector<int> genes;
    int fitness;

public:
    Genes() {
        for (int i = 0; i < GEN_LENGTH; i++) {
            // 초기 값을 대강 (총 재산수 / 자식 수)범위의 랜덤으로 설정
            this->genes.push_back(rand() % (NUM_OF_CHILD));
        }
        fitness = 0;
    }

    int calFitness(const vector<int> properties, const vector<int> target) {
        vector<int> temp(target.size(), 0);
        this->fitness = 0;

        for (int i = 0; i < GEN_LENGTH; i++) {
            temp[genes[i]] += properties[i];
        }
        for (int i = 0; i < NUM_OF_CHILD; i++) {
            this->fitness += abs(temp[i] - target[i]);
        }
        return this->fitness;
    }

    void printGenes() const {
        cout << "[ ";
        for (int i = 0; i < GEN_LENGTH; i++) {
            cout << genes[i] << " ";
        }
        cout << "]\n";
    }
    int getFit() const {
        return this->fitness;
    }
    void setGenes(vector<int> c) {
        for (int i = 0; i < GEN_LENGTH; i++) {
            genes[i] = c[i];
        }
    }
    vector<int> getGenes() {
        return genes;
    }

    void setHalfIn(vector<int> v, int idx1, int idx2) {
        for (int i = idx1; i <= idx2; i++) {
            genes[i] = v[i];
        }
        return;
    }

    void setHalfOut(vector<int> v, int idx1, int idx2) {
        for (int i = 0; i < GEN_LENGTH; i++) {
            if (i <= idx1 && i >= idx2)
                genes[i] = v[i];
        }
        return;
    }

    void mutate() {
        for (int i = 0; i < GEN_LENGTH; i++) {
            if (getRandom()) {
                genes[i] = rand() % NUM_OF_CHILD;
            }
        }
    }
};