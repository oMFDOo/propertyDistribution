#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

// �� ���� ������ ��
#define N_OF_GEN 128
// �ϳ��� ������ ���� : ��� n����
#define GEN_LENGTH 100
// �й��� �ڽ��� ��  : k���� �й��� ���̴�.
#define NUM_OF_CHILD 5
// �������� ����
#define MUTATE1 3
// ����Ʈ ����
#define ELITE 4

bool randomL[101] = { 0 };

// �ִ� ��ȭ ���� ��
#define ITER 10000
// �߰� �� ��� ����
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
            // �ʱ� ���� �밭 (�� ���� / �ڽ� ��)������ �������� ����
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