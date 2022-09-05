#include "Genes.h"
#include <fstream>

void createGenes();

// 유전자 리스트
vector<Genes> GenesList;

// 물건의 가치보관
vector<int> Properties;
// 지식별 배분 비율
vector<double> Child;
// 비율로 계산한 목표 재산값
vector<int> Target;

bool compare(const Genes& p1, const Genes& p2) {
	return p1.getFit() < p2.getFit();
}


int main() {

	// 재산 데이터와 비율 데이터 입력
	int inputType = 0, propertiSum = 0;


	ifstream devideFile, propertyFile;
	string dFile = "./divide", pFile = "./res/properties"; // GEN_LENGTH
	dFile += to_string(NUM_OF_CHILD) + ".txt";
	pFile += to_string(GEN_LENGTH) + ".txt";

	devideFile.open(dFile);
	propertyFile.open(pFile);


	// 재산 데이터 입출력
	if (propertyFile.is_open()) {
		cout << pFile << "파일 read \n";
		int num;
		while (propertyFile >> num) {
			Properties.push_back(num);
			propertiSum += num;
		}
		propertyFile.close();
	}
	else {
		cout << pFile << "파일 read 실패 : 랜덤 데이터 생성\n";
		// 재산 데이터 설정
		for (int i = 0; i < GEN_LENGTH; i++) {
			int temp = rand() % 128;
			Properties.push_back(temp);
			propertiSum += temp;
		}
	}

	// 자식 데이터 입력
	if (devideFile.is_open()) {
		cout << dFile << "파일 read \n";
		double num;
		while (devideFile >> num) {
			Child.push_back(num);
			// 정답 데이터 설정
			Target.push_back(propertiSum * num);
		}
		devideFile.close();
	}
	else {
		cout << dFile << "파일 read 실패 : 랜덤 데이터 생성\n";
		int per = 100;
		// 비율 데이터 설정
		for (int i = 0; i < NUM_OF_CHILD; i++) {
			int temp = rand() % per;
			if (temp > 20) {
				temp = 10 + temp % 10;
			}
			if (i == NUM_OF_CHILD - 1) {
				temp = per;
			}
			per -= temp;
			Child.push_back(temp / 100.0);
			// 정답 데이터 설정
			Target.push_back(propertiSum * temp / 100);
		}
	}


	//cin >> inputType;
	//if (inputType == 1) {
	//    // 재산 데이터 설정
	//    srand(static_cast<unsigned int>(std::time(0)));
	//    for (int i = 0; i < GEN_LENGTH; i++) {
	//        int temp = rand() % 128;
	//        Properties.push_back(temp);
	//        propertiSum += temp;
	//    }
	//    int per = 100;
	//    // 비율 데이터 설정
	//    for (int i = 0; i < NUM_OF_CHILD; i++) {
	//        int temp = rand() % per;
	//        if (temp > 20) {
	//            temp = 10 + temp%10;
	//        }
	//        if (i == NUM_OF_CHILD - 1) {
	//            temp = per;
	//        }
	//        per -= temp;
	//        Child.push_back(temp / 100.0);
	//        // 정답 데이터 설정
	//        Target.push_back(propertiSum * temp / 100);
	//    }
	//}
	//else {
	//    int temp;
	//    cout << "재산 데이터 입력 : \n";
	//    for (int i = 0; i < GEN_LENGTH; i++) {
	//        cin >> temp;
	//        Properties.push_back(temp);
	//        propertiSum += temp;
	//    }
	//    cout << "비율 데이터 입력 : \n";
	//    for (int i = 0; i < NUM_OF_CHILD; i++) {
	//        cin >> temp;
	//        Child.push_back(temp);
	//        // 정답 데이터 설정
	//        Target.push_back(propertiSum * temp);
	//    }
	//}

	/*
	cout << "[ ";
	for (int i = 0; i < GEN_LENGTH; i++) {
		cout << Properties[i]  << " ";
	}
	cout << "]\n";
	cout << "[ ";
	for (int i = 0; i < NUM_OF_CHILD; i++) {
		cout << Child[i] << " ";
	}
	cout << "]\n";
	cout << "[ ";
	for (int i = 0; i < NUM_OF_CHILD; i++) {
		cout << Target[i] << " ";
	}
	cout << "]\n";*/



	// 초기 유전자 생성
	for (int i = 0; i < N_OF_GEN; i++) {
		Genes g;
		GenesList.push_back(g);
	}

	// 반복 지점 : 세대 반복 - ITER
	for (int g = 0; g <= ITER; g++) {
		// 선택 : 엘리트 탐색
		for (int i = 0; i < N_OF_GEN; i++) {
			int fit = GenesList[i].calFitness(Properties, Target);
		}
		sort(GenesList.begin(), GenesList.end(), compare);

		if (g % SKIP == 0) {
			cout << g << "-fit : " << GenesList[0].getFit() << endl;
			GenesList[0].printGenes();
		}

		// 한 4퍼센트는 엘리트로 둠
		int eliteIdx = N_OF_GEN * ELITE / 100;
		bool isin[GEN_LENGTH][GEN_LENGTH] = { 0, };
		// 교차
		for (int i = eliteIdx + 1; i < N_OF_GEN - 1; ) {
			vector<int> c1, c2;
			c1 = GenesList[i].getGenes();
			c2 = GenesList[rand() % 30].getGenes();

			int idx1 = rand() % GEN_LENGTH;
			int idx2 = rand() % GEN_LENGTH;
			if (idx2 >= GEN_LENGTH - 1) {
				idx2 = GEN_LENGTH - 1;
			}
			if (idx2 < idx1) {
				int temp = idx2; idx2 = idx1; idx1 = temp;
			}
			GenesList[i].setHalfIn(c2, idx1, idx2);
			GenesList[i + 1].setHalfIn(c1, idx1, idx2);
			i += 2;
		}

		// 돌연변이
		for (int i = eliteIdx + 1; i < N_OF_GEN; i++) {
			// 돌연변이 확률
			if (getRandom()) {
				GenesList[i].mutate();
			}
		}
	}
	cout << "휴우";
}


// 각 세대 유전자 수 만큼 생성
void createGenes() {
	for (int i = 0; i < N_OF_GEN; i++) {
		Genes temp;
		GenesList.push_back(temp);
	}
}
