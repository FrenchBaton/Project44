#include<iostream>
#include <vector>
#include<fstream>
using namespace std;


bool isFileEmpty(const string& filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		return false;
	}
	file.seekg(0, std::ios::end);
	std::streampos size = file.tellg();

	return size == 0;
}

class Card
{
	string firm;
	string owner;
	string number;
	string adress;
	string whatDo;
public:
	Card() {
		firm = "FIRM";
		owner = "OWNER";
		number = "+000.000.0000";
		adress = "st.ADRESS";
		whatDo = "DO";
	}
	Card(string f, string o, string n, string a, string d) {
		firm = f;
		owner = o;
		number = n;
		adress = a;
		whatDo = d;
	}

	Card& operator= (const Card& c) {
		if (&c != this) Init(c.firm, c.owner, c.number, c.adress, c.whatDo);
		return *this;
	}

	string GetFirm() { return firm; }
	string GetOwner() { return owner; }
	string GetNum() { return number; }
	string GetAdress() { return adress; }
	string GetDo() { return whatDo; }

	void Init(string f, string o, string n, string a, string d) {
		firm = f;
		owner = o;
		number = n;
		adress = a;
		whatDo = d;
	}
	void Input() {
		cout << "Write firm: ";
		cin >> firm;
		cout << "Write owner: ";
		cin >> owner;
		cout << "Write number: ";
		cin >> number;
		cout << "Write adress: ";
		cin >> adress;
		cout << "Write whatDo: ";
		cin >> whatDo;
	}
	void Print() {
		cout << "Firm: " << firm <<
			"\nOwner: " << owner <<
			"\nNumber: " << number <<
			"\nAdress: " << adress <<
			"\nDo: " << whatDo << endl;
	}
};


class Notes
{
	vector<Card> arr;
	int size;
public:
	Notes() {
		if (isFileEmpty("Notes.txt"))
		{
			size = 0;
			return;
		}
		Load();
	}
	Notes(const vector < Card> a, int s) {
		if (s == 0) {
			size = 0;
			return;
		}
			
		size = s;
		arr = a;
	}

	void Add(const Card& c) {
		size++;
		arr.push_back(c);
		Save();
	}

	void Print() {
		for (int i = 0; i < size; i++) {
			arr[i].Print();
			cout << endl;
		}
		cout << endl;
	}

	void Load() {
		ifstream in;
		in.open("Notes.txt", ios::in);

		if (in.is_open())
		{
			arr.clear();
			in >> size;

			for (int i = 0; i < size; i++)
			{
				string f, o, n, a, d;
				in >> f >> o >> n >> a >> d;
				Card c(f, o, n, a, d);
				arr.push_back(c);
			}

			in.close();
		}
		else
		{
			cout << "Could not open the file" << endl;
		}
	}

	void Save() {
		ofstream out;
		out.open("Notes.txt", ios::out | ios::trunc);

		if (out.is_open())
		{
			out << size << ' ';
			for (int i = 0; i < size; i++) {
				out << arr[i].GetFirm() << ' '
					<< arr[i].GetOwner() << ' '
					<< arr[i].GetNum() << ' '
					<< arr[i].GetAdress() << ' '
					<< arr[i].GetDo() << ' ';
			}

			out.close();
		}
		else
		{
			cout << "Could not open the file" << endl;
		}
	}
};






int main() {
	Notes n;
	int choice;
	bool isEnd = false;

	while (!isEnd) {
		cout << "0 - Exit \t 1 - Add \t 2 - Show" << endl;
		Card c;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			c.Input();
			n.Add(c);
			break;
		case 2:
			n.Print();
			break;
		default:
			isEnd = 1;
		}
	}
	

	return 0;
}