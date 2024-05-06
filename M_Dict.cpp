# include <iostream>
# include <string>

using namespace std;


class Key
{
	string field;
	class Data_Node *ptr;
public:
	Key(const string& f, Data_Node* pttr) : field(f), ptr(pttr) {}
	Key() : ptr(nullptr) {}
	friend class Data_node;
	friend class MDict;
};

class Data_Node
{
	string data;
public:
	Data_Node(const string& d) : data(d) {}
	friend class Key;
	friend class MDict;
};



class MDict
{
	int DS;
	int size;
	Key* keys;
public:
	MDict(int initDS) : size(0), DS(initDS) { 
		keys = new Key[initDS]; 
	}
	void Clear() {
		for (int i = 0; i < size; ++i) {
			delete keys[i].ptr;
		}
		delete[] keys;
		size = 0;
	}
	void Add(const string& field, const string& data) {
		if (size < DS) {
			Data_Node* newData = new Data_Node(data);
			keys[size] = Key(field, newData);
			size++;
		}
		else {
			cout << "Словарь переполнен" << endl;
		}
	}
	Data_Node* Find(const string& field_find) {
		for (int i = 0; i < size; i++) {
			if (keys[i].field == field_find) {
				return keys[i].ptr;
			}
		}
		return nullptr;
	}
	string getValue(const string& field_find) {
		Data_Node* f_k = Find(field_find);
		if (f_k == nullptr) {
			return "Not found";
			}
		return f_k->data;
		}
	bool isEmpty() { return size == 0; }
	void PrintD() {
		if (isEmpty()) { cout << "Dict is empty" << endl; return; }
		for (int i = 0; i < size; i++) {
			cout << "'" << keys[i].field << "': " << getValue(keys[i].field) << "; ";
		}
		cout << endl;
	}
	void Edit(const string& field, const string& data_new) {
		Data_Node* node_ptr = Find(field);
		node_ptr->data = data_new;
	}
	void Delete(const string& field) {
		for (int i = 0; i < size; i++) {
			if (keys[i].field == field) {
				delete keys[i].ptr;
				for (int j = i; j < size - 1; j++) {
					keys[j] = keys[j + 1];
				}
				size--;
				return;
			}
		}
		cout << "There is nothing we can do" << endl;
	}
};


int main()
{
	MDict dictionary(10);
	cout << "Only init" << endl;
	dictionary.PrintD();
	dictionary.Add("key1", "value1");
	dictionary.Add("key2", "value2");
	dictionary.Add("key3", "value3");
	cout << "Made it full" << endl;
	dictionary.PrintD();
	dictionary.Edit("key2", "AAAA");
	cout << "Changed" << endl;
	cout << "Value for key1: " << dictionary.getValue("key1") << endl;
	dictionary.Delete("key1");
	dictionary.PrintD();

	return 0;
};