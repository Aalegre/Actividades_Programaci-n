#include <vector>
#include <fstream>
#include <iostream>

#pragma region Ejercicio1

void SaveVector(std::vector<int> o_, std::string fileName_) {
	std::ofstream file;
	file.open(fileName_, std::ios::out | std::ios::binary);
	size_t size = o_.size() * sizeof(int);
	file.write(reinterpret_cast<char*>(&size), sizeof(size_t));
	file.write(reinterpret_cast<char*>(o_.data()), size);
	file.close();
}
void RecoverVector(std::vector<int>& o_, std::string fileName_) {
	o_.clear();
	std::ifstream file;
	file.open(fileName_, std::ios::in | std::ios::binary);
	size_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	size_t vectorSize = size / sizeof(int);
	o_.resize(vectorSize);
	file.read(reinterpret_cast<char*>(o_.data()), size);

	file.close();
}

void Ejercicio1()
{
	std::vector<int> a({ 5,2,3,4,5,6,7,8,9,10 });
	SaveVector(a, "TestSaveVector.bin");
	for (int i = 0; i < 10; i++) {
		a[i] = a[i] + 10;
	};
	RecoverVector(a, "TestSaveVector.bin");
	for (int i = 0; i < 10; i++) {
		std::cout << a[i] << std::endl;
	};
}

#pragma endregion

#pragma region Ejercicio2

struct Object {
	char type;
	int x;
	int y;
};

void Save(std::vector<Object> o_, std::string fileName_) {
	std::ofstream file;
	file.open(fileName_, std::ios::out | std::ios::binary);
	size_t size = o_.size() * sizeof(Object);
	file.write(reinterpret_cast<char*>(&size), sizeof(size_t));
	file.write(reinterpret_cast<char*>(o_.data()), size);
	file.close();
}
void Recover(std::vector<Object>& o_, std::string fileName_) {
	o_.clear();
	std::ifstream file;
	file.open(fileName_, std::ios::in | std::ios::binary);
	size_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	size_t vectorSize = size / sizeof(Object);
	o_.resize(vectorSize);
	file.read(reinterpret_cast<char*>(o_.data()), size);

	file.close();
}
void Ejercicio2()
{
	std::vector<Object> objects;
	objects.push_back({ 'A', 3, 0 });
	objects.push_back({ 'B', 2, 1 });
	objects.push_back({ 'C', 1, 2 });
	objects.push_back({ 'D', 0, 3 });
	Save(objects, "TestSaveVectorObjects.bin");
	objects.push_back({ 'X', 24,346 });
	Recover(objects, "TestSaveVectorObjects.bin");

	//uwu
}

#pragma endregion

int main()
{
	//Ejercicio1();
	Ejercicio2();
	return 0;
}
