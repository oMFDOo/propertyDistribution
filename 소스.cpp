#include "Genes.h"
#include <fstream>

void createGenes();

// ������ ����Ʈ
vector<Genes> GenesList;

// ������ ��ġ����
vector<int> Properties;
// ���ĺ� ��� ����
vector<double> Child;
// ������ ����� ��ǥ ��갪
vector<int> Target;

bool compare(const Genes& p1, const Genes& p2) {
	return p1.getFit() < p2.getFit();
}


int main() {

	// ��� �����Ϳ� ���� ������ �Է�
	int inputType = 0, propertiSum = 0;


	ifstream devideFile, propertyFile;
	string dFile = "./divide", pFile = "./properties"; // GEN_LENGTH
	dFile += to_string(NUM_OF_CHILD) + ".txt";
	pFile += to_string(GEN_LENGTH) + ".txt";

	devideFile.open(dFile);
	propertyFile.open(pFile);


	// ��� ������ �����
	if (propertyFile.is_open()) {
		cout << pFile << "���� read \n";
		int num;
		while (propertyFile >> num) {
			Properties.push_back(num);
			propertiSum += num;
		}
		propertyFile.close();
	}
	else {
		cout << pFile << "���� read ���� : ���� ������ ����\n";
		// ��� ������ ����
		for (int i = 0; i < GEN_LENGTH; i++) {
			int temp = rand() % 128;
			Properties.push_back(temp);
			propertiSum += temp;
		}
	}

	// �ڽ� ������ �Է�
	if (devideFile.is_open()) {
		cout << dFile << "���� read \n";
		double num;
		while (devideFile >> num) {
			Child.push_back(num);
			// ���� ������ ����
			Target.push_back(propertiSum * num);
		}
		devideFile.close();
	}
	else {
		cout << dFile << "���� read ���� : ���� ������ ����\n";
		int per = 100;
		// ���� ������ ����
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
			// ���� ������ ����
			Target.push_back(propertiSum * temp / 100);
		}
	}


	//cin >> inputType;
	//if (inputType == 1) {
	//    // ��� ������ ����
	//    srand(static_cast<unsigned int>(std::time(0)));
	//    for (int i = 0; i < GEN_LENGTH; i++) {
	//        int temp = rand() % 128;
	//        Properties.push_back(temp);
	//        propertiSum += temp;
	//    }
	//    int per = 100;
	//    // ���� ������ ����
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
	//        // ���� ������ ����
	//        Target.push_back(propertiSum * temp / 100);
	//    }
	//}
	//else {
	//    int temp;
	//    cout << "��� ������ �Է� : \n";
	//    for (int i = 0; i < GEN_LENGTH; i++) {
	//        cin >> temp;
	//        Properties.push_back(temp);
	//        propertiSum += temp;
	//    }
	//    cout << "���� ������ �Է� : \n";
	//    for (int i = 0; i < NUM_OF_CHILD; i++) {
	//        cin >> temp;
	//        Child.push_back(temp);
	//        // ���� ������ ����
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



	// �ʱ� ������ ����
	for (int i = 0; i < N_OF_GEN; i++) {
		Genes g;
		GenesList.push_back(g);
	}

	// �ݺ� ���� : ���� �ݺ� - ITER
	for (int g = 0; g <= ITER; g++) {
		// ���� : ����Ʈ Ž��
		for (int i = 0; i < N_OF_GEN; i++) {
			int fit = GenesList[i].calFitness(Properties, Target);
		}
		sort(GenesList.begin(), GenesList.end(), compare);

		if (g % 500 == 0) {
			cout << g << "-fit : " << GenesList[0].getFit() << endl;
			GenesList[0].printGenes();
		}

		// �� 4�ۼ�Ʈ�� ����Ʈ�� ��
		int eliteIdx = N_OF_GEN * ELITE / 100;
		bool isin[GEN_LENGTH][GEN_LENGTH] = { 0, };
		// ����
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

		// ��������
		for (int i = eliteIdx + 1; i < N_OF_GEN; i++) {
			// �������� Ȯ��
			if (getRandom()) {
				GenesList[i].mutate();
			}
		}
	}
	cout << "�޿�";
}


// �� ���� ������ �� ��ŭ ����
void createGenes() {
	for (int i = 0; i < N_OF_GEN; i++) {
		Genes temp;
		GenesList.push_back(temp);
	}
}
