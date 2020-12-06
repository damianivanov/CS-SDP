#include <iostream>
#include <queue>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;
void generate_next_prime(vector<int> &primes)
{
	if (primes.empty())
	{
		primes.push_back(2);
		return;
	}
	int last_prime = primes[primes.size()-1] + 1;
	bool isPrime = false;
	while (!isPrime)
	{
		isPrime = true;
		for (int x : primes)
		{
			if(last_prime% x == 0)
			{
				last_prime++;
				isPrime = false;
			}
		}

	}
	primes.push_back(last_prime);
}

void generate_password(queue<int> &numbers,vector<int> &primes) {
	if (numbers.empty())
	{
		cout << endl;
		return;
	}
	queue<int> buffer;
	int p = primes[primes.size() - 1];
	while (!numbers.empty())
	{
		int x = numbers.front();
		numbers.pop();

		if (x % p == 0) cout << x << " ";
		else buffer.push(x);
	}
	generate_next_prime(primes);
	generate_password(buffer,primes);
}
int main()
{
	srand(time(NULL));
	vector<int> primes;
	int n = 0;
	cin >> n;
	queue<int> numbers;
	for (size_t i = 0; i < n; i++)
		numbers.push(rand() % 10000 + 1);

	generate_next_prime(primes);
	generate_password(numbers,primes);
	return 0;
}