//C:\Users\benh4\PycharmProjects\Circles

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include<vector>

using namespace std;

int main() {
	ifstream fin("C:\\Users\\benh4\\PycharmProjects\\Circles\\tracks.txt");
	ofstream fout("tracksfinal.txt");
	unordered_map<string, double> tracks;
	if (!fin)
	{
		cout << "Error ID107: File not found!" << endl;
		cout << endl;
		system("pause");
		return -1;
	}
	string tempKey = "";
	int rank = 1; //rank from 1-30 for "on repeat" playlist
				  //fin.ignore(100, 'k');
	getline(fin, tempKey, ',');
	while (!fin.eof()) {
		tracks[tempKey] += (rank / 30.0);
		if (rank == 30) {
			rank = 0;
		}
		rank++;
		//fin.ignore(100, 'k');
		getline(fin, tempKey, ',');
	}

	//Sort the songs
	vector<string> ids;
	vector<double> scores(2, 0.0);
	for (auto const& x : tracks)
	{
		for (int i = 0; i < 31; i++) {
			if (x.second > scores[i]) {
				ids.insert(ids.begin() + i, x.first);
				scores.insert(scores.begin() + i, x.second);
				break;
			}
			if (i == 30) {
				ids[30] = x.first;
				scores[30] = x.second;
			}
		}
	}
	for (int i = 0; i < 30; i++) {
		fout << ids[i] << ",";
	}

	//[number] is the key
	//value = appearances * (1 / ranking [1 - 30])
	//new playlist is populated with highest mapped values

	fin.close();
	fout.close();
	system("pause");
	return 0;
}
