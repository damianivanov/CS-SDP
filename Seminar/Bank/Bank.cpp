// Bank.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
using namespace std;

int bank(queue<int> q){

    int balance = 0;
    int max_counter = 0;
    q.push(INT_MIN);
    bool next_it = true;
    bool served_clients = true;
    while (next_it&&served_clients) //
    {
            next_it = false;
            served_clients = false;

        while (q.front()!=INT_MIN )
        {
            if (q.front() > 0)
            {
                if (q.front() + balance <=500 )
                {
                    balance += q.front();
                    served_clients = true;
                }
                else
                {
                    q.push(q.front());       
                    next_it = true;
                }
            }
            else 
            {
                if (abs(q.front()) <= balance)
                {
                    balance += q.front();
                    served_clients = true;
                }
                else {
                    q.push(q.front());
                    next_it = true;
                }
            }
            q.pop();

        }
        max_counter++;        
        q.pop();
        q.push(INT_MIN);
    }
    if (q.size()!=1)
    {
        return -1;
    }
    return max_counter;
}

int main()
{
    queue<int> q;
    q.push(1);
    q.push(-2);
    q.push(3);
    q.push(-4);
    q.push(100);
    q.push(400);
    q.push(-500);
    q.push(2);
    cout << bank(q) << endl;
    return 0;
}

