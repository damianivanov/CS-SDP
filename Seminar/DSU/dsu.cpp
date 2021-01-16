#include <map>
#include <iostream>
using namespace std;


class DSU
{
private:
    map<int,pair<int,int>> tree;
public:
    DSU(){}
    ~DSU(){}
    void make_set(const int x){
        tree[x]=make_pair(x,1);
    }
    int find_set(const int x){
        if (tree.find(x)==tree.end())
        {   
            make_set(x);
            return x;
        }
        if (tree[x].first == x)
            return x;
        return find_set(tree[x].first);
    }
    void union_sets(int x,int y){
        x = find_set(x);
        y = find_set(y);
        if(x==y) return; 
        tree[x].second >= tree[y].second ?
            tree[y].first = x :
            tree[x].first = y;
        }
    void print_set(const int x){
            if(tree[x].first == x){
                cout << x <<endl;
                return;
            }
            cout <<x <<"->";
            print_set(tree[x].first);
    }  
};

int main()
{
    DSU dsu;
    dsu.union_sets(3,4);
    dsu.print_set(4);
    dsu.union_sets(1,5);
    dsu.union_sets(2,4);
    dsu.print_set(2);
    dsu.union_sets(1,4);
    dsu.print_set(5);
    dsu.print_set(4);



    return 0;
}


