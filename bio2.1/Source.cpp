#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int amount_str(string abc) {
	int res = 0;
	string s;
	ifstream fin(abc, ios_base::in);
	if (fin.is_open()) while (getline(fin, s)) res++;
	else return 0;
	fin.close();
	return res;
}

void get_info(string abc, int* a){
	int k = 0;
	string chislo = "";
	int f = 0;
	int len = abc.length();
	int ind = 0;
	
	for (int i = 0; i < len; i++){

		if (abc[i] >= '0'&&abc[i] <= '9')
		{
			chislo += abc[i];
		}
		else
		{
			if ((f < 2) && (chislo != ""))
			{
				a[ind] = std::stoi(chislo);
				chislo = "";
				ind++;
				f++;
			}
			else
			{
				break;
			}
		}
	}
}

int fill_prof(char** alfmatr, int** curmatr, int t, int l){

	int score = 0;
	for (int j = 0; j < l; j++){
		for (int m = 0; m < t; m++){
			if (((alfmatr[m][j]) == 'a') || ((alfmatr[j][m]) == 'A'))
				curmatr[0][j]++;
			if (((alfmatr[m][j]) == 'c') || ((alfmatr[j][m]) == 'C'))
				curmatr[1][j]++;
			if (((alfmatr[m][j]) == 'g') || ((alfmatr[j][m]) == 'G'))
				curmatr[2][j]++;
			if (((alfmatr[m][j]) == 't') || ((alfmatr[j][m]) == 'T'))
				curmatr[3][j]++;
		}
	}

	for (int j = 0; j < l; j++)
	{
		int max_col = 0;
		for (int i = 0; i < 4; i++)
		{
			if (curmatr[i][j] > max_col){ max_col = curmatr[i][j]; }
		}
		score += max_col;
	}

	return score;

}

string* search_motifs(string* dna,int l,int t,int n){

	string* answer = new string[t];
	int loc_score = 0;
	int gl_score = 0;
	int dif_pos = pow(n - l + 1, t);
	int** curmatr = new int*[4];
	for (int i = 0; i < 4; i++){
		curmatr[i] = new int[l];
	}
	
	char** alfmatr = new char*[t];
	for (int i = 0; i < t; i++)
	{
		alfmatr[i] = new char[l];
	}

	string* strmat = new string[t];

	int *ind = new int[t];//iterator
	for (int i = 0; i < t; i++)//first combination
		ind[i] = 0;

	
	for (int i = 0; i < dif_pos; i++)
	{
		
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < l; j++){
				curmatr[i][j] = 0;
			}
		}

		for (int j = 0; j < t; j++)
		{
			strmat[j] = dna[j].substr(ind[j], l);
		}

		//fill in profile matrix
		for (int i = 0; i < t; i++)
		{
			strcpy(alfmatr[i], strmat[i].c_str());
		}

	
		loc_score = fill_prof(alfmatr, curmatr, t, l);

		
			if (loc_score >= gl_score)
			{
				gl_score = loc_score;
				for (int i = 0; i < t; i++)
				{
					answer[i] = "";
				}

				for (int i = 0; i < t; i++)
				{
					answer[i] = alfmatr[i];
				}
			}

		//next iteration
		for (int j = 0; j < t; j++)
		{
			ind[j]++;
			if (ind[j] < (n - l + 1))
				break;
			ind[j] = 0;
		}


	}

	for (int i = 0; i < 4;i++){
		delete[] curmatr[i];
	}
	delete[] strmat;
	return answer;
}



int main(){

	FILE* input_file;
	input_file = fopen("input.txt", "rb");
	if (getc(input_file) == EOF){
		cout << "empty file";
		fclose(input_file);
	}
	else
	{

		fclose(input_file);
		string info;
		string *dna;
		int *a = new int[2];
		ifstream input("input.txt", ios_base::in);
		getline(input, info);
		info += "   ";
		get_info(info, a);
	//	cout << a[0] << a[1];// a[0] - pattern size, a[1] - amount of strings
		dna = new string[a[1]];
		string* answer1 = new string[a[1]];
		int i = 0;
		input.seekg(0, ios::cur);

		while (getline(input, dna[i])){
			i++;
			if (i == a[1]){ break; }
		}
	
		int n = dna[1].size();

		answer1 = search_motifs(dna, a[0],a[1],n);
		
		ofstream new_file("output.txt");
		for (int i = 0; i < a[1]; i++)
		new_file << answer1[i]<<endl;
		new_file.close();
		delete[] a;
		delete[] answer1;		
		}

	
	return 0;
}
