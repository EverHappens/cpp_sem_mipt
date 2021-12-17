#include <iostream>
#define f first
#define s second

class BHeap{
    int curr;
    std::pair<long long, int> *heapArr;
    int size;
    int *indexes;
public:
    BHeap(int sz, int* queue_indexes);

    std::pair<long long, int> getMin(){ return heapArr[1]; };

    void siftUp(int v);
    void siftDown(int v);
    void insert(std::pair<int, int> x);
    void extractMin();
    void decreaseKey(int queue_index, long long delta);
};

void BHeap::siftUp(int v){
    while(v != 1){
        int u = v/2;
        if(heapArr[u].f > heapArr[v].f){
            indexes[heapArr[u].s] = v;
            indexes[heapArr[v].s] = u;
            std::swap(heapArr[u], heapArr[v]);
            v = u;
        }
        else break;
    }
}

void BHeap::siftDown(int v){
    while(2 * v <= curr){
        int u = 2 * v;
        if(heapArr[u].f > heapArr[u + 1].f and u + 1 <= curr) u++;
        if(heapArr[u].f < heapArr[v].f){
            indexes[heapArr[u].s] = v;
            indexes[heapArr[v].s] = u;
            std::swap(heapArr[u], heapArr[v]);
            v = u;
        }
        else break;
    }
}

BHeap::BHeap(int sz, int* queue_indexes){
    heapArr = new std::pair<long long, int>[1000001];
    curr = 0;
    size = sz + 1;
    indexes = queue_indexes;
}

void BHeap::insert(std::pair<int, int> x){
    heapArr[++curr] = x;
    indexes[x.s] = curr;
    siftUp(curr);
}

void BHeap::extractMin(){
    std::swap(heapArr[1], heapArr[curr--]);
    indexes[heapArr[1].s] = 1;
    siftDown(1);
}

void BHeap::decreaseKey(int queue_index, long long delta){
    heapArr[indexes[queue_index]].f -= delta;
    siftUp(indexes[queue_index]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int indexes[1000001];
    BHeap bheap(1000001, indexes);
    int n;
    std::cin >> n;
    int cnt = 1;
    for(int i = 1; i <= n; i++){
        std::string query;
        std::cin >> query;
        if(query == "insert"){
            long long num;
            std::cin >> num;
            bheap.insert({num, i});
        }
        else if(query == "getMin"){
            std::cout << bheap.getMin().f << '\n';
        }
        else if(query == "extractMin"){
            bheap.extractMin();
        }
        else if(query == "decreaseKey"){
            int ind;
            long long delta;
            std::cin >> ind >> delta;
            bheap.decreaseKey(ind, delta);
        }
    }
    return 0;
}