

#include <iostream>
#include <iomanip>
#include <istream>
#include <sstream>
#include <vector>

using namespace std;

class CSV {
public:
	static vector<string> splitBy(string line, char separator) {
		vector<string> result;

		int startIndex = 0;
		while (true) {
			int idx = line.find(separator, startIndex);
			
			// no more columns
			if (idx < 0) {
				string part = line.substr(startIndex, line.size() - startIndex);
				result.push_back(part);
				break;
			}

			int charsToCopy = idx - startIndex;
			string part = line.substr(startIndex, charsToCopy);
			result.push_back(part);

			startIndex += charsToCopy + 1;
		}

		return result;
	}

	static CSV from(istream& input, char separator = ',') {
		CSV csv;
		
		string line;
		while(getline(input, line)) {
			vector<string> currentLine = splitBy(line, separator);
			csv.addRow(currentLine);
		}
		return csv;
	}

	void print() const {
		if (data.size() != 0) {
			int columns = maxNumberOfColumns();
			for (int i = 0; i < data.size(); i++) {
				const vector<string>& currentLine = data.at(i);

				cout << "| ";
				for (int j = 0; j < columns; j++) { 
					if (j < currentLine.size()) {
						cout << setw(maxColumnWidth(j)) << currentLine[j] <<  " | ";
					} else {
						cout << setw(maxColumnWidth(j)) << " " <<  " | ";
					}
				}
				cout << endl;
			}
		} else {
			cout << "No data" << endl;	
		}
	}

	int maxColumnWidth(int column) const {
		int columnWidth = 1;
		for (int i = 0; i < data.size(); i++) {
			if (data[i].size() > column && data[i][column].size() > columnWidth) {
				columnWidth = data[i][column].size();
			}
		}
		return columnWidth;
	}

	int maxNumberOfColumns() const {
		int columns = 0;
		for (int i = 0; i < data.size(); i++) {
			if (data[i].size() > columns) {
				columns = data[i].size();
			}
		}
		return columns;
	}

private:
	vector<vector<string> > data;

	CSV() {
	}

	void addRow(vector<string> row) {
		data.push_back(row);
	}
};

int main() {
	stringstream ss;
	ss.str("user_id,age,name,address\n3,20,Mimi");
	CSV csv = CSV::from(ss);
	csv.print();
	return 0;
}

