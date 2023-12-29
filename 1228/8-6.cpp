#include <iostream>

using namespace std;

class BaseArray
{
private:
	int capacity;
	int* mem;
protected:
	BaseArray(int capacity = 100) { this->capacity = capacity; mem = new int[capacity]; }
	~BaseArray() { delete[] mem; }
	void put(int index, int val) { mem[index] = val; }
	int get(int index) { return mem[index]; }
	int getCapacity() { return capacity; }
};

class MyStack: public BaseArray
{
	int tos;
public:
	MyStack(int capacity) : BaseArray(capacity) { tos = 0; }
	void enqueue(int n) {
		if (tos == capacity()) return;
		put(tos, n);
		tos++;
	}
	int dequeue() {
		if (tos == 0) return -1;
		tos--;
		return get(tos);
	}
	int capacity() { return getCapacity(); }
	int length() { return tos; }
};

int main() {
	MyStack mStack(100);
	int n;
	cout << "���ÿ� ������ 5���� ������ �Է��϶�>> ";
	for (int i = 0; i < 5; i++) {
		cin >> n;
		mStack.enqueue(n);
	}
	cout << "���ÿ뷮 : " << mStack.capacity() << ", ����ũ�� : " << mStack.length() << endl;
	cout << "������ ���Ҹ� ������� �����Ͽ� ����Ѵ�>> ";
	while (mStack.length() != 0) {
		cout << mStack.dequeue() << ' ';
	}
	cout << endl << "������ ���� ũ�� : " << mStack.length() << endl;
}