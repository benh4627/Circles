#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>

using namespace std;

int main() {
    ifstream fin("C:\\Users\\ben\\PycharmProjects\\pythonProject1\\tracks.txt");
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

    //[number] is the key
    //value = appearances * (1 / ranking [1 - 30])
    //new playlist is populated with highest mapped values

    fin.close();
    system("pause");
    return 0;
}