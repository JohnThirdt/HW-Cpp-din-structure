# include <iostream>
# include <string>

using namespace std;


class Key
{
	string field; // Значение ключа
	class Data_Node *ptr; // Указатель на информацию
public:
	Key(const string& f, Data_Node* pttr) : field(f), ptr(pttr) {} // Конструктор для инициализации
	Key() : ptr(nullptr) {} // Если без ничего
	friend class Data_node;
	friend class MDict;
};

class Data_Node
{
	string data; // Сама информация
public:
	Data_Node(const string& d) : data(d) {}
	friend class Key;
	friend class MDict;
};



class MDict
{
	int DS; // Ёмкость словаря
	int size; // Текущий рзамер
	Key* keys;
public:
	MDict(int initDS) : size(0), DS(initDS) { 
		keys = new Key[initDS]; 
	}
	void Clear() // Отчистить словарь
	{
		for (int i = 0; i < size; ++i) {
			delete keys[i].ptr;
		}
		delete[] keys;
		size = 0;
	}
	void Add(const string& field, const string& data) // Добавить запись
	{
		if (size < DS) {
			Data_Node* newData = new Data_Node(data);
			keys[size] = Key(field, newData);
			size++;
		}
		else {
			cout << "Словарь переполнен" << endl;
		}
	}
	Data_Node* Find(const string& field_find) // Найти указатель на узел
	{
		for (int i = 0; i < size; i++) {
			if (keys[i].field == field_find) {
				return keys[i].ptr;
			}
		}
		return nullptr;
	}
	string getValue(const string& field_find) // Получить значение по ключу
	{
		Data_Node* f_k = Find(field_find);
		if (f_k == nullptr) {
			return "Not found";
			}
		return f_k->data;
		}
	bool isEmpty() { return size == 0; } // Словарь пуст?
	void PrintD() // Полный вывод
	{
		if (isEmpty()) { cout << "Dict is empty" << endl; return; }
		for (int i = 0; i < size; i++) {
			cout << "'" << keys[i].field << "': " << getValue(keys[i].field) << "; ";
		}
		cout << endl;
	}
	void Edit(const string& field, const string& data_new) // Замена записи по ключу
	{
		Data_Node* node_ptr = Find(field);
		node_ptr->data = data_new;
	}
	void Delete(const string& field) // Удаление записи по ключу и удаление ключа.
	{
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
	MDict dictionary(10); // Эксперименты

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