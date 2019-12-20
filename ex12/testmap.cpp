#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Product {
public:
	Product(string name, string category) {
		setName(name);
		setCategory(category);
	}

	string getName() {
		return this->name;
	}

	string getCategory() {
		return this->category;
	}

	void setName(string name) {
		this->name = name;
	}
	
	void setCategory(string category) {
		this->category = category;
	}

	ostream& operator<<(ostream& out) {
		out << "Product: " << getName() 
			<< " in category: " << getCategory() 
			<< endl;
		return out;
	}

private:
	string name;
	string category;
};

class ProductPrinter {
public:
		
	virtual void printHeader(string category) = 0;

	virtual void printProduct(Product product) = 0;
	
	virtual void printFooter() = 0 ;
};


class ConsoleProductPrinter : public ProductPrinter {
public:
		
	void printHeader(string category) {
		cout << endl << endl << endl;
		cout << "***" << category << "***" << endl;
	}

	void printProduct(Product product) {
		cout << " " << product.getName() << endl;
	}
	
	void printFooter() {
		cout << "*****************************" << endl;
		cout << endl << endl << endl;
	}
};

class XMLProductPrinter : public ProductPrinter {
public:
	void printHeader(string category) {
		cout << "<category name=\"" << category <<  "\">" << endl;
	}

	void printProduct(Product product) {
		cout << "  " << "<product>" << product.getName() << "</product>" << endl;
	}
	
	void printFooter() {
		cout << "</category>" << endl;
	}
};

template <typename VAL>
bool containsKey(map<string, VAL> searchIn, string key) {
	return searchIn.find(key) != searchIn.end();
}

map<string, int> numberOfProductsPerCategory(vector<Product> products) {
	map<string, int> productsPerCategory;

	for (auto product: products) {
		if (containsKey(productsPerCategory, product.getCategory())) {
			productsPerCategory[product.getCategory()]++;
		} else {
			productsPerCategory[product.getCategory()] = 1;
		}
	}

	return productsPerCategory;
}

map<string, vector<Product> > groupProductsByCategory(vector<Product> products) {
	map<string, vector<Product> > productsPerCategory;

	for (auto product: products) {
		string category = product.getCategory();

		if (!containsKey(productsPerCategory, category)) {
			productsPerCategory[category] = vector<Product>();
		}

		productsPerCategory[category].push_back(product);

	}

	return productsPerCategory;
}

void print(map<string, int> data) {
	for (auto elem : data) {
		cout << elem.first << ": " << elem.second << endl;
	}
}

void print(map<string, vector<Product> > data, ProductPrinter* productPrinter) {
	for (auto elem : data) {		
		productPrinter->printHeader(elem.first);

		for (auto product : elem.second) {
			productPrinter->printProduct(product);
		}
		productPrinter->printFooter();
	}
}

void print(multimap<string, Product> data) {
	for (auto elem : data) {
		cout << elem.first << ": " << elem.second.getName() << endl;
	}
}


void numberOfOccurences(string text) {
	int charCount[256] = {0};

	for (char c : text) {
		charCount[(short) c]++;
	}
}

int main() {
	map<string, ProductPrinter*> productPrinters;
	productPrinters["console"] = new ConsoleProductPrinter();
	productPrinters["xml"] = new XMLProductPrinter();

	vector<Product> products;
	products.push_back(Product("Pink XMas Hat XL", "XMas Hats"));
	products.push_back(Product("Pink XMas Hat XXXXL (Programmer edition)", "XMas Hats"));
	products.push_back(Product("Blue XMas Hat S", "XMas Hats"));
	products.push_back(Product("Blue XMas Hat M", "XMas Hats"));
	products.push_back(Product("Santa size (or developer)", "Xmas boots"));
	products.push_back(Product("Elf size", "Xmas boots"));
	products.push_back(Product("Snowwhite size", "Xmas boots"));
	products.push_back(Product("The one and only", "Xmas Tree"));
	// map<string, int> productsPerCategory = numberOfProductsPerCategory(products);
	// print(productsPerCategory);
	// cout << "============================" << endl;

	string printerOption = "error";
	while (!containsKey(productPrinters, printerOption)) {
		cout << "Type what printer you want to use. Choose one of: (";
		for (auto printer : productPrinters) {
			cout << printer.first << ", ";
		}
		cout << ") ";
		cin >> printerOption;
	}
	print(groupProductsByCategory(products), productPrinters[printerOption]);


	delete productPrinters["console"];
	delete productPrinters["xml"];
	return 0;
}
















