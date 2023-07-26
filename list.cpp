#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <stdexcept>
// с++ standart: 14 , compiler: msvc


struct ListNode
{
	ListNode* prev = nullptr;
	ListNode* next = nullptr;
	ListNode* rand = nullptr;
	std::string data;
};

class List
{
public:
	List(unsigned size = 0) : size(size) {};// size нужна чтобы rand мог указывать на элемент добавленный после него


	void Serialize(FILE* file)
	{
		if (file == nullptr)
		{
			throw std::runtime_error("Error: Invalid file pointer");
		}
		fwrite(&size, sizeof(int), 1, file);
		ListNode* current = head;
		for (int i = 0; i < size; i++)
		{
			int dataLength = current->data.length();
			fwrite(&dataLength, sizeof(int), 1, file);
			fwrite(current->data.c_str(), sizeof(char), dataLength, file);
			fwrite(&(nodes[i].second), sizeof(int), 1, file);
			current = current->next;
		}
		return;
	}

	void Deserialize(FILE* file)
	{
		if (file == nullptr)
		{
			throw std::runtime_error("Error: Invalid file pointer");
		}
		std::string data;
		int rId = 0;
		fread(&size, sizeof(int), 1, file);
		for (int i = 0; i < size; i++)
		{
			int dataLength;
			fread(&dataLength, sizeof(int), 1, file);
			char* dataBuffer = new char[dataLength + 1];
			fread(dataBuffer, sizeof(char), dataLength, file);
			dataBuffer[dataLength] = '\0';
			std::string data(dataBuffer);
			delete[] dataBuffer;
			fread(&rId, sizeof(int), 1, file);
			AddNode(data, rId);

		}
		PrintList();
		return;
	}

	void AddNode(std::string data, int id = -1)
	{
		if (id > (size - 1))
		{
			throw std::runtime_error("Rand is outside the list");
		}
		ListNode* node = new ListNode;
		nodes[count] = { node, id };
		node->data = data;
		if (head == nullptr)
		{
			head = tail = node;
		}
		else
		{
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
		++count;
		if (count == size)
		{
			SetRand();
		}
	}
	void SetRand()// вызывается когда все узлы добавлены в список 
	{
		ListNode* current = head;
		for (int i = 0; i < size; i++)
		{
			if (current != nullptr)
			{
				if (nodes[i].second != -1 && nodes.count(nodes[i].second) != 0)
					current->rand = nodes[nodes[i].second].first;
				else
					current->rand = nullptr;
				current = current->next;
			}
		}

	}
	void PrintList()
	{
		ListNode* current = head;
		while (current != nullptr)
		{
			std::cout << "Data = " << current->data << " Adress = " << current << " Next = " << current->next << " Prev = " << current->prev << " rand = " << current->rand << std::endl;
			current = current->next;
		}
		std::cout << std::endl;
	}

	~List()
	{
		ListNode* current = head;
		for (int i = 0; i < size; i++)
		{
			ListNode* next = current->next;
			delete current;
			current = next;
		}
	}

private:
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
	int count = 0;
	int size;
	std::unordered_map<int, std::pair<ListNode*, int>> nodes; // хранит идентификатор, адрес узла, идентификатор случайного узла

};

int main()
{

	// вложенный блок кода для вызова деструктора List после выполнения
	{
		List list(4);
		list.AddNode("Node 0", 3);
		list.AddNode("Node 1");
		list.AddNode("Node 2");
		list.AddNode("Node 3", 1);
		list.PrintList();

		FILE* file = fopen("list.bin", "wb");
		list.Serialize(file);
		fclose(file);
	}


	FILE* file = fopen("list.bin", "rb");
	List newList;
	newList.Deserialize(file);
	fclose(file);
}

