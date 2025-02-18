#include <string>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
using namespace std;

// PLEASE DO NOT MODIFY THE SOLUTION STRUCT
struct QmSolution {
	int numVar;
	vector<string> primes;
	vector<vector<string> > minimumSops;
};

//functions
string toBinary(int, int);
string countOne(string);
int NumOfDiff(string, string);
int PosOfDiff(string, string);
void print(vector<vector<pair<set<int>, string>>>);
void expand(vector<set<int>>&, int, set<int>, set<set<int>>&);
vector<string> ansForPI(vector<pair<set<int>, string>>);
vector<vector<string>> ansForSOP(const vector<pair<set<int>, string>>, vector<set<int>>, vector<pair<set<int>, string>>);
string binToString(string);
vector<pair<set<int>, string>> removeSamePI(vector<pair<set<int>, string>>, vector<int>);
bool minInPI(set<int> PI, int min);

//����i�Ϊ���set
set<int> nothing = { -1 };

//�[�c:[][0].first=minterm�s��  [][0].second=min��binary  [][1].first=��set  [][1].second=���L�ιL  [][2].first=��set  [][2].second=group
//'x':�S�ιL  'v':�ιL  'd':dontcare
vector<vector<pair<set<int>, string>>> table; //��l�o�쪺min�Mdont�s�J���Ŷ� 
vector<vector<pair<set<int>, string>>> oneCom;  //�C�@���X�֪����G�x�s���Ŷ�
vector<vector<pair<set<int>, string>>> twoCom;
vector<vector<pair<set<int>, string>>> threeCom;
vector<vector<pair<set<int>, string>>> fourCom;
vector<vector<pair<set<int>, string>>> fiveCom;
vector<vector<pair<set<int>, string>>> sixCom;
vector<vector<pair<set<int>, string>>> sevenCom;
vector<vector<pair<set<int>, string>>> eightCom;
vector<vector<pair<set<int>, string>>> nineCom;
vector<vector<pair<set<int>, string>>> tenCom;

vector<pair<set<int>, string>> PI; //�x�sprime implicant��minterm�s���Mbinary


// PLEASE DO NOT MODIFY THE FUNCTION DEFINITION
QmSolution *solveQm(int numVar, vector<int> minterms, vector<int> dontcares, bool verbose)
{
	QmSolution *sol = new QmSolution;
	sol->numVar = numVar;

	//�إ�column 1
	for (int i = 0; i < minterms.size(); i++) {
		vector<pair<set<int>, string>> t_v;
		set<int> t_s = { minterms[i] }; //mintern���s����J
		pair<set<int>, string> t_p1(t_s, toBinary(numVar, minterms[i]));
		pair<set<int>, string> t_p2(nothing, "x");
		pair<set<int>, string> t_p3(nothing, countOne(t_p1.second));
		t_v.push_back(t_p1);
		t_v.push_back(t_p2);
		t_v.push_back(t_p3);
		table.push_back(t_v);
	}
	for (int i = 0; i < dontcares.size(); i++) {
		vector<pair<set<int>, string>> t_v;
		set<int> t_s = { dontcares[i] }; //dontcare���s����J
		pair<set<int>, string> t_p1(t_s, toBinary(numVar, dontcares[i]));
		pair<set<int>, string> t_p2(nothing, "d");
		pair<set<int>, string> t_p3(nothing, countOne(t_p1.second));
		t_v.push_back(t_p1);
		t_v.push_back(t_p2);
		t_v.push_back(t_p3);
		table.push_back(t_v);
	}

	//�إ�column 2 �X��1��
	for (int i = 0; i < table.size(); i++) {
		for (int j = i + 1; j < table.size(); j++) {
			if (abs(stoi(table[i][2].second) - stoi(table[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(table[i][0].second, table[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(table[i][0].second, table[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = table[i][0].first;
					for (auto & k : table[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = table[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					oneCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (table[i][1].second == "x") {
						table[i][1].second = "v";
					}
					if (table[j][1].second == "x") {
						table[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < table.size(); i++) {
		if (table[i][1].second == "x") {
			PI.push_back(table[i][0]);
		}
	}


	//�إ�column 3 �X��2��
	for (int i = 0; i < oneCom.size(); i++) {
		for (int j = i + 1; j < oneCom.size(); j++) {
			if (abs(stoi(oneCom[i][2].second) - stoi(oneCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(oneCom[i][0].second, oneCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(oneCom[i][0].second, oneCom[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = oneCom[i][0].first;
					for (auto & k : oneCom[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = oneCom[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					twoCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (oneCom[i][1].second == "x") {
						oneCom[i][1].second = "v";
					}
					if (oneCom[j][1].second == "x") {
						oneCom[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < oneCom.size(); i++) {
		if (oneCom[i][1].second == "x") {
			PI.push_back(oneCom[i][0]);
		}
	}


	//�إ�column 4 �X��3��
	for (int i = 0; i < twoCom.size(); i++) {
		for (int j = i + 1; j < twoCom.size(); j++) {
			if (abs(stoi(twoCom[i][2].second) - stoi(twoCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(twoCom[i][0].second, twoCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(twoCom[i][0].second, twoCom[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = twoCom[i][0].first;
					for (auto & k : twoCom[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = twoCom[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					threeCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (twoCom[i][1].second == "x") {
						twoCom[i][1].second = "v";
					}
					if (twoCom[j][1].second == "x") {
						twoCom[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < twoCom.size(); i++) {
		if (twoCom[i][1].second == "x") {
			PI.push_back(twoCom[i][0]);
		}
	}


	//�إ�column 5 �X��4��
	for (int i = 0; i < threeCom.size(); i++) {
		for (int j = i + 1; j < threeCom.size(); j++) {
			if (abs(stoi(threeCom[i][2].second) - stoi(threeCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(threeCom[i][0].second, threeCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(threeCom[i][0].second, threeCom[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = threeCom[i][0].first;
					for (auto & k : threeCom[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = threeCom[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					fourCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (threeCom[i][1].second == "x") {
						threeCom[i][1].second = "v";
					}
					if (threeCom[j][1].second == "x") {
						threeCom[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < threeCom.size(); i++) {
		if (threeCom[i][1].second == "x") {
			PI.push_back(threeCom[i][0]);
		}
	}


	//�إ�column 6 �X��5��
	for (int i = 0; i < fourCom.size(); i++) {
		for (int j = i + 1; j < fourCom.size(); j++) {
			if (abs(stoi(fourCom[i][2].second) - stoi(fourCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(fourCom[i][0].second, fourCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(fourCom[i][0].second, fourCom[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = fourCom[i][0].first;
					for (auto & k : fourCom[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = fourCom[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					fiveCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (fourCom[i][1].second == "x") {
						fourCom[i][1].second = "v";
					}
					if (fourCom[j][1].second == "x") {
						fourCom[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < fourCom.size(); i++) {
		if (fourCom[i][1].second == "x") {
			PI.push_back(fourCom[i][0]);
		}
	}

	//�إ�column 7 �X��6��
	for (int i = 0; i < fiveCom.size(); i++) {
		for (int j = i + 1; j < fiveCom.size(); j++) {
			if (abs(stoi(fiveCom[i][2].second) - stoi(fiveCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(fiveCom[i][0].second, fiveCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(fiveCom[i][0].second, fiveCom[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = fiveCom[i][0].first;
					for (auto & k : fiveCom[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = fiveCom[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					sixCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (fiveCom[i][1].second == "x") {
						fiveCom[i][1].second = "v";
					}
					if (fiveCom[j][1].second == "x") {
						fiveCom[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < fiveCom.size(); i++) {
		if (fiveCom[i][1].second == "x") {
			PI.push_back(fiveCom[i][0]);
		}
	}


	//�إ�column 8 �X��7��
	for (int i = 0; i < sixCom.size(); i++) {
		for (int j = i + 1; j < sixCom.size(); j++) {
			if (abs(stoi(sixCom[i][2].second) - stoi(sixCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(sixCom[i][0].second, sixCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(sixCom[i][0].second, sixCom[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = sixCom[i][0].first;
					for (auto & k : sixCom[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = sixCom[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					sevenCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (sixCom[i][1].second == "x") {
						sixCom[i][1].second = "v";
					}
					if (sixCom[j][1].second == "x") {
						sixCom[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < sixCom.size(); i++) {
		if (sixCom[i][1].second == "x") {
			PI.push_back(sixCom[i][0]);
		}
	}


	//�إ�column 9 �X��8��
	for (int i = 0; i < sevenCom.size(); i++) {
		for (int j = i + 1; j < sevenCom.size(); j++) {
			if (abs(stoi(sevenCom[i][2].second) - stoi(sevenCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
				if (NumOfDiff(sevenCom[i][0].second, sevenCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
					int pos = PosOfDiff(sevenCom[i][0].second, sevenCom[j][0].second); //����binary���P����m
					//�X�֫�sminterm�s��
					set<int> t_s = sevenCom[i][0].first;
					for (auto & k : sevenCom[j][0].first) {
						t_s.insert(k);
					}
					//�X�֫�s�sbinary �X�֪���m�s'-'
					string s = sevenCom[i][0].second;
					s[pos] = '-';
					//�إ�col 2 ���C��row
					vector<pair<set<int>, string>> t_v;
					pair<set<int>, string> t_p1(t_s, s);
					pair<set<int>, string> t_p2(nothing, "x");
					pair<set<int>, string> t_p3(nothing, countOne(s));
					t_v.push_back(t_p1);
					t_v.push_back(t_p2);
					t_v.push_back(t_p3);
					eightCom.push_back(t_v);
					//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
					if (sevenCom[i][1].second == "x") {
						sevenCom[i][1].second = "v";
					}
					if (sevenCom[j][1].second == "x") {
						sevenCom[j][1].second = "v";
					}
				}
			}
		}
	}
	///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
	for (int i = 0; i < sevenCom.size(); i++) {
		if (sevenCom[i][1].second == "x") {
			PI.push_back(sevenCom[i][0]);
		}
	}


	if (numVar > 8) { //9�M10�ܼƤ~�ݭn����o��
		//�إ�column 10 �X��9��
		for (int i = 0; i < eightCom.size(); i++) {
			for (int j = i + 1; j < eightCom.size(); j++) {
				if (abs(stoi(eightCom[i][2].second) - stoi(eightCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
					if (NumOfDiff(eightCom[i][0].second, eightCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
						int pos = PosOfDiff(eightCom[i][0].second, eightCom[j][0].second); //����binary���P����m
						//�X�֫�sminterm�s��
						set<int> t_s = eightCom[i][0].first;
						for (auto & k : eightCom[j][0].first) {
							t_s.insert(k);
						}
						//�X�֫�s�sbinary �X�֪���m�s'-'
						string s = eightCom[i][0].second;
						s[pos] = '-';
						//�إ�col 2 ���C��row
						vector<pair<set<int>, string>> t_v;
						pair<set<int>, string> t_p1(t_s, s);
						pair<set<int>, string> t_p2(nothing, "x");
						pair<set<int>, string> t_p3(nothing, countOne(s));
						t_v.push_back(t_p1);
						t_v.push_back(t_p2);
						t_v.push_back(t_p3);
						nineCom.push_back(t_v);
						//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
						if (eightCom[i][1].second == "x") {
							eightCom[i][1].second = "v";
						}
						if (eightCom[j][1].second == "x") {
							eightCom[j][1].second = "v";
						}
					}
				}
			}
		}
		///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
		for (int i = 0; i < eightCom.size(); i++) {
			if (eightCom[i][1].second == "x") {
				PI.push_back(eightCom[i][0]);
			}
		}


		if (numVar > 9) { //10�ܼƤ~�ݭn����o��
			//�إ�column 11 �X��10��
			for (int i = 0; i < nineCom.size(); i++) {
				for (int j = i + 1; j < nineCom.size(); j++) {
					if (abs(stoi(nineCom[i][2].second) - stoi(nineCom[j][2].second)) == 1) { //�p�G1���ӼƬۮt��1
						if (NumOfDiff(nineCom[i][0].second, nineCom[j][0].second) == 1) { //�p�G��Ӫ�binary���t������Ƭ�1
							int pos = PosOfDiff(nineCom[i][0].second, nineCom[j][0].second); //����binary���P����m
							//�X�֫�sminterm�s��
							set<int> t_s = nineCom[i][0].first;
							for (auto & k : nineCom[j][0].first) {
								t_s.insert(k);
							}
							//�X�֫�s�sbinary �X�֪���m�s'-'
							string s = nineCom[i][0].second;
							s[pos] = '-';
							//�إ�col 2 ���C��row
							vector<pair<set<int>, string>> t_v;
							pair<set<int>, string> t_p1(t_s, s);
							pair<set<int>, string> t_p2(nothing, "x");
							pair<set<int>, string> t_p3(nothing, countOne(s));
							t_v.push_back(t_p1);
							t_v.push_back(t_p2);
							t_v.push_back(t_p3);
							tenCom.push_back(t_v);
							//��scol 1 �ϥΪ��A �p�G�Odontcare���Χ�s
							if (nineCom[i][1].second == "x") {
								nineCom[i][1].second = "v";
							}
							if (nineCom[j][1].second == "x") {
								nineCom[j][1].second = "v";
							}
						}
					}
				}
			}
			///�X�ֹL��p�G���S���Ψ쪺minterm�N�OPI
			for (int i = 0; i < nineCom.size(); i++) {
				if (nineCom[i][1].second == "x") {
					PI.push_back(nineCom[i][0]);
				}
			}
		}
	}

	vector<pair<set<int>, string>> newPI = removeSamePI(PI, dontcares);
	vector<pair<set<int>, string>> newPI_copy = newPI;

	//��essential PI
	vector<int> only_one_min;
	int num = 0;
	for (int i = 0; i < minterms.size(); i++) {
		for (int j = 0; j < newPI.size(); j++) {
			if (newPI[j].first.count(minterms[i]) == 1) { //�b�Ҧ�PI���u���X�{�@����minterm
				num++;
			}
		}
		if (num == 1) {
			only_one_min.push_back(minterms[i]);
		}
	}

	vector<pair<set<int>, string>> esPI;
	for (int i = 0; i < newPI.size(); i++) {
		for (int j = 0; j < only_one_min.size(); j++) {
			if (newPI[i].first.count(only_one_min[j]) != 0) { //�o��PI�̦��u���X�{�L�@����minterm
				esPI.push_back(newPI[i]); //esPI�s�_�ӡA���@�U�MminSOP�X��
				newPI.erase(newPI.begin() + i); //�h��esPI�ѤU��PI
			}
		}
	}

	//��{Patrick Method
	//Step 1:��C��minterm�Q���X��PI���t�A�쪺PI�O���_��
	vector<int> min_r = minterms;
	for (auto & i : esPI) {
		for (int j = 0; j < min_r.size(); j++) {
			for (auto & k : i.first) {
				if (min_r[j] == k) {
					min_r.erase(min_r.begin() + j);
				}
			}
		}
	}

	vector<set<int>> pat;
	for (int i = 0; i < min_r.size(); i++) {
		set<int> temp;
		for (int j = 0; j < newPI.size(); j++) {
			if (newPI[j].first.count(min_r[i]) != 0) { //��즳�o��minterm��PI
				temp.insert(j); //��o��PI�bvector��index�s�_��
			}
		}
		if (temp.size() != 0) {
			pat.push_back(temp);
		}
	}

	//Step 2:���X�Ҧ��զX
	set<set<int>> allSOP; //��esPI
	set<int> product;
	expand(pat, 0, product, allSOP);

	for (auto & i : allSOP) {
		for (auto & j : i) {
			cout << j << " ";
		}
		cout << endl;
	}

	int min = 99999;
	for (auto & i : allSOP) {
		if (i.size() < min) {
			min = i.size(); //���i�H�[�A�Ҧ�minterm��PI�̤֬O�X��
		}
	}

	vector<set<int>> minSOP; //��esPI
	for (auto & i : allSOP) {
		if (i.size() == min) {
			minSOP.push_back(i); //�ŦXPI�̤p��SOP�N�OminSOP
		}
	}

	//��Ѵ����ŦX�n�D���Φ�
	//prime impliciant
	sol->primes = ansForPI(newPI_copy);

	//minSOP
	sol->minimumSops = ansForSOP(newPI, minSOP, esPI);

	if (verbose) {
		// print the process of QM method (every column)
		cout << "=====================" << endl;
		cout << "Column 1" << endl;
		cout << "=====================" << endl;
		int group = 0;
		bool print = false;
		while (group <= numVar) {
			for (int i = 0; i < table.size(); i++) {
				if (table[i][2].second == to_string(group)) {
					print = true;
					if (table[i][1].second == "x") cout << "  ";
					else cout << setw(2) << table[i][1].second;
					cout << setw(11) << table[i][0].second << ": ";
					for (auto & j : table[i][0].first) {
						cout << j;
					}
					cout << endl;
				}
			}
			if (print) cout << "---------------------" << endl;
			group++;
			print = false;
		}

		if (!oneCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 2" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < oneCom.size(); i++) {
					if (oneCom[i][2].second == to_string(group)) {
						print = true;
						if (oneCom[i][1].second == "x" && twoCom.empty() == false) cout << "  ";
						else if (oneCom[i][1].second == "x" && twoCom.empty() == true) {
							if (i - 1 >= 0) {
								if (oneCom[i][0].second == oneCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << oneCom[i][1].second;
						cout << setw(11) << oneCom[i][0].second << ": ";
						for (auto & j : oneCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!twoCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 3" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < twoCom.size(); i++) {
					if (twoCom[i][2].second == to_string(group)) {
						print = true;
						if (twoCom[i][1].second == "x" && threeCom.empty() == false) cout << "  ";
						else if (twoCom[i][1].second == "x" && threeCom.empty() == true) {
							if (i - 1 >= 0) {
								if (twoCom[i][0].second == twoCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << twoCom[i][1].second;
						cout << setw(11) << twoCom[i][0].second << ": ";
						for (auto & j : twoCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!threeCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 4" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < threeCom.size(); i++) {
					if (threeCom[i][2].second == to_string(group)) {
						print = true;
						if (threeCom[i][1].second == "x" && fourCom.empty() == false) cout << "  ";
						else if (threeCom[i][1].second == "x" && fourCom.empty() == true) {
							if (i - 1 >= 0) {
								if (threeCom[i][0].second == threeCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << threeCom[i][1].second;
						cout << setw(11) << threeCom[i][0].second << ": ";
						for (auto & j : threeCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!fourCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 5" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < fourCom.size(); i++) {
					if (fourCom[i][2].second == to_string(group)) {
						print = true;
						if (fourCom[i][1].second == "x" && fiveCom.empty() == false) cout << "  ";
						else if (fourCom[i][1].second == "x" && fiveCom.empty() == true) {
							if (i - 1 >= 0) {
								if (fourCom[i][0].second == fourCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << fourCom[i][1].second;
						cout << setw(11) << fourCom[i][0].second << ": ";
						for (auto & j : fourCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!fiveCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 6" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < fiveCom.size(); i++) {
					if (fiveCom[i][2].second == to_string(group)) {
						print = true;
						if (fiveCom[i][1].second == "x" && sixCom.empty() == false) cout << "  ";
						else if (fiveCom[i][1].second == "x" && sixCom.empty() == true) {
							if (i - 1 >= 0) {
								if (fiveCom[i][0].second == fiveCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << fiveCom[i][1].second;
						cout << setw(11) << fiveCom[i][0].second << ": ";
						for (auto & j : fiveCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!sixCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 7" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < sixCom.size(); i++) {
					if (sixCom[i][2].second == to_string(group)) {
						print = true;
						if (sixCom[i][1].second == "x" && sevenCom.empty() == false) cout << "  ";
						else if (sixCom[i][1].second == "x" && sevenCom.empty() == true) {
							if (i - 1 >= 0) {
								if (sixCom[i][0].second == sixCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << sixCom[i][1].second;
						cout << setw(11) << sixCom[i][0].second << ": ";
						for (auto & j : sixCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!sevenCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 8" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < sevenCom.size(); i++) {
					if (sevenCom[i][2].second == to_string(group)) {
						print = true;
						if (sevenCom[i][1].second == "x" && eightCom.empty() == false) cout << "  ";
						else if (sevenCom[i][1].second == "x" && eightCom.empty() == true) {
							if (i - 1 >= 0) {
								if (sevenCom[i][0].second == sevenCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << sevenCom[i][1].second;
						cout << setw(11) << sevenCom[i][0].second << ": ";
						for (auto & j : sevenCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!eightCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 9" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < eightCom.size(); i++) {
					if (eightCom[i][2].second == to_string(group)) {
						print = true;
						if (eightCom[i][1].second == "x" && nineCom.empty() == false) cout << "  ";
						else if (eightCom[i][1].second == "x" && nineCom.empty() == true) {
							if (i - 1 >= 0) {
								if (eightCom[i][0].second == eightCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << eightCom[i][1].second;
						cout << setw(11) << eightCom[i][0].second << ": ";
						for (auto & j : eightCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!nineCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 10" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < nineCom.size(); i++) {
					if (nineCom[i][2].second == to_string(group)) {
						print = true;
						if (nineCom[i][1].second == "x" && tenCom.empty() == false) cout << "  ";
						else if (nineCom[i][1].second == "x" && tenCom.empty() == true) {
							if (i - 1 >= 0) {
								if (nineCom[i][0].second == nineCom[i - 1][0].second) {
									cout << "x";
								}
								else cout << " ";
							}
							else cout << " ";
						}
						else cout << setw(2) << nineCom[i][1].second;
						cout << setw(11) << nineCom[i][0].second << ": ";
						for (auto & j : nineCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

		if (!tenCom.empty()) {
			cout << endl << endl;
			cout << "=====================" << endl;
			cout << "Column 11" << endl;
			cout << "=====================" << endl;
			group = 0;
			print = false;
			while (group <= numVar) {
				for (int i = 0; i < tenCom.size(); i++) {
					if (tenCom[i][2].second == to_string(group)) {
						print = true;
						if (i - 1 >= 0) {
							if (tenCom[i][0].second == tenCom[i - 1][0].second) {
								cout << "x";
							}
							else cout << " ";
						}
						cout << setw(2) << tenCom[i][1].second;
						cout << setw(11) << tenCom[i][0].second << ": ";
						for (auto & j : tenCom[i][0].first) {
							cout << j << " ";
						}
						cout << endl;
					}
				}
				if (print) cout << "---------------------" << endl;
				group++;
				print = false;
			}
		}

	}
	if (verbose) {
		// print the prime implicant chart of final result
		cout << endl << endl;
		cout << "=====================" << endl;
		cout << "Prime Implicant Chart" << endl;
		cout << "=====================" << endl << endl;

		cout << setw(16) << " ";
		for (int i = 0; i < minterms.size(); i++) {
			cout << setw(5) << minterms[i];
		}
		cout << endl;

		for (int i = 0; i < newPI_copy.size(); i++) {
			cout << setw(16) << left << binToString(newPI_copy[i].second);
			for (int j = 0; j < minterms.size(); j++) {
				if (minInPI(newPI_copy[i].first, minterms[j])) {
					cout << setw(5) << right << "x";
				}
				else cout << setw(5) << right << " ";
			}
			cout << endl;
		}

	}
	return sol;
};

string toBinary(int numVar, int n)
{
	string r;
	string s;
	r.clear();
	s.clear();

	if (n == 0) {  //min�O0���ɭ�binary���O0
		for (int i = 0; i < numVar; i++) {
			r += "0";
		}
		return r;
	}

	while (n != 0) {
		r += (n % 2 == 0 ? "0" : "1");
		n /= 2;
	}
	reverse(r.begin(), r.end());
	s = string(numVar - r.length(), '0') + r;
	return s;
}


string countOne(string s)
{
	int count = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '1') {
			count++;
		}
	}

	return to_string(count);
}

int NumOfDiff(string a, string b)
{
	int diff = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			diff++;
		}
	}
	return diff;
}

int PosOfDiff(string a, string b) {
	int pos = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			pos = i;
		}
	}
	return pos;
}

void print(vector<vector<pair<set<int>, string>>> v)
{
	for (const auto& row : v) {
		for (const auto& element : row) {
			const std::set<int>& setValues = element.first;
			const std::string& strValue = element.second;
			// ���Lset������
			for (const auto& value : setValues) {
				cout << value << " ";
			}
			// ���L�r�Ŧ��
			cout << strValue << " ";
		}
		cout << endl;
	}
}

void expand(vector<set<int>>& pat, int n, set<int> product, set<set<int>>& allSOP)
{
	if (n == pat.size()) {
		set<int> temp = product;
		allSOP.insert(temp);
		return;
	}
	else {
		set<int>::iterator i;
		for (i = pat[n].begin(); i != pat[n].end(); ++i) {
			int x = *i;
			bool inserted = product.insert(x).second;
			expand(pat, n + 1, product, allSOP);
			if (inserted) {
				product.erase(x);
			}
		}
	}
}

vector<string> ansForPI(vector<pair<set<int>, string>> PI)
{
	vector<string> ansForPI;
	for (int i = 0; i < PI.size(); i++) {
		string s;
		for (int j = 0; j < PI[i].second.size(); j++) {
			if (PI[i].second[j] == '1') {
				char c = 97 + j;
				s += c;
			}
			else if (PI[i].second[j] == '0') {
				char c = 97 + j;
				s += c;
				s += "'";
			}
		}
		ansForPI.push_back(s);
	}
	return ansForPI;
}

vector<vector<string>> ansForSOP(const vector<pair<set<int>, string>> PI, vector<set<int>> minSOP, vector<pair<set<int>, string>> esPI)
{
	vector<vector<string>> ansForSOP;
	if (minSOP.size() != 0) { //���FesPI���O��PI
		for (auto & i : minSOP) {
			vector<string> temp;
			for (auto & j : i) {
				temp.push_back(binToString(PI[j].second));
			}
			for (int k = 0; k < esPI.size(); k++) {
				temp.push_back(binToString(esPI[k].second));
			}
			ansForSOP.push_back(temp);
		}
	}
	else { //�u��esPI
		vector<string> temp;
		for (int k = 0; k < esPI.size(); k++) {
			temp.push_back(binToString(esPI[k].second));
		}
		ansForSOP.push_back(temp);
	}

	return ansForSOP;
}

string binToString(string s)
{
	string ans;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '1') {
			char c = 97 + i;
			ans += c;
		}
		else if (s[i] == '0') {
			char c = 97 + i;
			ans += c;
			ans += "'";
		}
	}
	return ans;
}

vector<pair<set<int>, string>> removeSamePI(vector<pair<set<int>, string>> PI, vector<int> dontcares)
{
	//�h�����Odoncare��PI
	vector<int> remove;
	for (int i = 0; i < PI.size(); i++) {
		int count = 0;
		for (auto & j : PI[i].first) {
			for (int k = 0; k < dontcares.size(); k++) {
				if (j == dontcares[k]) {
					count++;
				}
				if (count == PI[i].first.size()) {
					remove.push_back(i);
					break;
				}
			}
		}
	}

	sort(remove.begin(), remove.end());

	for (int i = remove.size() - 1; i > -1; i--) {
		PI.erase(PI.begin() + remove[i]);
	}

	//�h�����ƪ�PI
	set <pair<set<int>, string>> s;
	for (auto & i : PI) {
		s.insert(i);
	}
	vector<pair<set<int>, string>> newPI(s.begin(), s.end());
	return newPI;
}

bool minInPI(set<int> PI, int min)
{
	for (auto & i : PI) {
		if (i == min) {
			return true;
		}
	}
	return false;
}


int main()
{
	int numVar = 0;
	int a;
	vector<int> minterms;
	vector<int> dontcares;
	cout << "Please input numVar :";
	cin >> numVar;

	cout << "\nPlease input minterms :";
	while (cin >> a) {
		if (a == -1) break;
		minterms.push_back(a);
	}

	cout << "\nPlease input dontcares :";
	while (cin >> a) {
		if (a == -1) break;
		dontcares.push_back(a);
	}

	*solveQm(numVar, minterms, dontcares, true);
}

/*
//�L�Xinitial table
	for (const auto& row : table) {
		for (const auto& element : row) {
			const std::set<int>& setValues = element.first;
			const std::string& strValue = element.second;
			// ���Lset������
			for (const auto& value : setValues) {
				cout << value << " ";
			}
			// ���L�r�Ŧ��
			cout << strValue << " ";
		}
		cout << endl;
	}

		for (const auto& p : PI) {
		cout << "Set: ";
		for (int num : p.first) {
			cout << num << " ";
		}
	}

		cout << "\nnewPI:" << endl;
	for (int i = 0; i < newPI.size(); i++) {
		cout << i << "��" << endl;
		cout << "prime implicant �t�A��minterm:";
		for (auto & j : newPI[i].first) {
			cout << j << " ";
		}
		cout << endl;
		cout << "prime implicant��binary:";
		cout << newPI[i].second << " ";
		cout << endl;
	}

		/*cout << endl << "prime implicants:" << endl;
	for (auto & i : sol->primes) {
		cout << i << " ";
	}
	cout << endl;

	cout << "minimun SOPs:" << endl;
	for (auto & i : sol->minimumSops) {
		for (auto & j : i) {
			cout << j << " ";
		}
		cout << endl;
	}*/