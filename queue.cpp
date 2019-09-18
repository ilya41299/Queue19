#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

class Queue
{
	std::string* mas;
	long long int size, head, tail;
	bool is_active;

public:
	Queue()
	{
		mas = nullptr;
		size = 0;
		head = 0;
		tail = 0;
		is_active = false;
	}
	~Queue()
	{
		if (is_active)
			delete[] mas;
	}

	Queue(long long int new_size)
	{
		size = new_size;
		mas = new std::string[size];
		head = 0;
		tail = 0;
		is_active = true;
		for (size_t i = 0; i < new_size; i++)
		{
			mas[i].clear();
		}
	}
	void set(long long int new_size)
	{
		size = new_size;
		mas = new std::string[size];
		head = 0;
		tail = 0;
		is_active = true;
		for (size_t i = 0; i < new_size; i++)
		{
			mas[i].clear();
		}
	}
	void pop(std::ofstream& file_out);
	void push(std::string X, std::ofstream& file_out);
	void print(std::ofstream& file_out);
	bool Is_active();
};

void Queue::pop(std::ofstream &file_out)
{
	if (head == tail && mas[head] == "") 
	{
		file_out << "underflow\n";
		return;
	}
	else if (head == size - 1) 
	{
		file_out << mas[head] << "\n";
		mas[head].clear();
		head = 0;
	}
	else 
	{
		file_out << mas[head] << "\n";
		mas[head++].clear();
	} 	
}
bool Queue::Is_active()
{
	return is_active;
}

void Queue::push(std::string X, std::ofstream& file_out)
{
	if ((head == 0 && tail == size) || ((tail == head) && mas[head] != ""))  file_out << "overflow\n";
	else if (tail == size - 1) 
	{
		mas[tail] = X;
		tail = 0;
	}
	else mas[tail++] = X;
}

void Queue::print(std::ofstream& file_out)
{
	if (head == tail && mas[head] == "")
	{
		file_out << "empty\n";
	}
	else if (head < tail)
	{
		for (size_t i = head; i < tail; i++)
		{
			file_out << mas[i];
			if (i < tail - 1) file_out << " ";
		}
		file_out << "\n";
	}
	else if (head >= tail && head != 0 && tail != 0) 
	{
		for (size_t i = head; i < size; i++)
		{
			file_out << mas[i];
			if (i < size)file_out << " ";
		}
		for (size_t i = 0; i < tail; i++)
		{
			file_out << mas[i];
			if (i < tail - 1)file_out << " ";
		}
		file_out << "\n";
	}
	else if (head > tail && head != 0 && tail == 0) 
	{
		for (size_t i = head; i < size; i++)
		{
			file_out << mas[i];
			if (i < size - 1)file_out << " ";
		}
		file_out << "\n";
	}
	else 
	{
		for (size_t i = 0; i < size; i++)
		{
			file_out << mas[i];
			if (i < size - 1)file_out << " ";
		}
		file_out << "\n";
	}
		
}

int main(int argc, char* argv[])
{
	std::string path_1 = argv[1];
	std::string path_2 = argv[2];
	std::ifstream file_in(path_1);
	std::ofstream file_out(path_2);
	std::string temp, number = "", line = "";
	Queue A;
	while (std::getline(file_in, line))
	{
		number.clear();
		temp.clear();
		if (!A.Is_active())
		{
			std::istringstream str_stream(line);
			str_stream >> temp;
			if (temp == "set_size")
			{
				temp.clear();
				str_stream >> temp;
				if (temp == "")
				{
					file_out << "error\n";
					continue;
				}
				bool set_size = true;
				for (size_t i = 0; i < temp.length() && set_size; i++)
				{
					if (!isdigit(temp[i]))
					{
						set_size = false;
						number.clear();
						temp.clear();
						break;
					}
					else
						number.push_back(temp[i]);
				}
				if (set_size && std::stod(number) != 0 && (!(str_stream >> std::noskipws >> temp) && temp != ""))
				{
					A.set(std::stoi(number));
					continue;
				}
				else if (set_size && std::stod(number) == 0)
				{

					file_out << "error\n";
					continue;
				}
				else
				{
					file_out << "error\n";
					temp.clear();
					continue;
				}
			}
			else if (temp == "") continue;
			else
			{
				file_out << "error\n";
				temp.clear();
				continue;
			}
		}
		std::istringstream str_stream(line);
		str_stream >> temp;
		if (temp == "push")
		{
			str_stream >> temp;
			for (size_t i = 0; i < temp.length(); i++)
			{
				number.push_back(temp[i]);
			}
			if (!(str_stream >> std::noskipws >> temp) && temp != "")
				A.push(number, file_out);
			else file_out << "error\n";
		}
		else if (temp == "pop")
		{
			if (!(str_stream >> std::noskipws >> temp) && temp != "")
				A.pop(file_out);
			else
			{
				file_out << "error\n";
				continue;
			}
		}
		else if (temp == "print")
		{
			if (!(str_stream >> std::noskipws >> temp) && temp != "")
				A.print(file_out);
			else
			{
				file_out << "error\n";
				continue;
			}
		}
		else if (A.Is_active() && temp != "") file_out << "error\n";
	}
	file_in.close();
	file_out.close();
	return 0;
}
