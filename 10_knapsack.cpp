#include <iostream>

using namespace std;

struct Item {
    double value, weight,rho;
};

struct Knapsack {
    Item* items;
    int n_elems;
    double capacity;
};

int Partition(Knapsack *knapsack,int l, int r){
	Item pivot=knapsack->items[r];
	
	int i=l-1;
	
	for(int j=l;j<r;j++){
		if(knapsack->items[j].rho<pivot.rho){
			i++;
			Item temp=knapsack->items[j];
			knapsack->items[j]=knapsack->items[i];
			knapsack->items[i]=temp;
		}
	}
	
	knapsack->items[r]=knapsack->items[i+1];
	knapsack->items[i+1]=pivot;
	
	return i+1;
}

void QuickSortRek(Knapsack *knapsack, int l, int r){
	if(l>r)		return;
	
	int index=Partition(knapsack,l,r);
	
	QuickSortRek(knapsack,l,index-1);
	QuickSortRek(knapsack,index+1,r);
}

void QuickSort(Knapsack *knapsack){
	QuickSortRek(knapsack,0,knapsack->n_elems-1);
}


double max_profit(Knapsack knapsack) {
	
	for(int i=0;i<knapsack.n_elems;i++){
		knapsack.items[i].rho=knapsack.items[i].value/knapsack.items[i].weight;
	}
	
	QuickSort(&knapsack);
	
	int indx=knapsack.n_elems-1;
	double carried=0;
	double money=0;
	while(indx<knapsack.n_elems && carried<knapsack.capacity){
		if(carried+knapsack.items[indx].weight<knapsack.capacity){
			money+=knapsack.items[indx].value;
			carried+=knapsack.items[indx].weight;
			indx--;
		}
		else{
			double take=knapsack.capacity-carried;
			carried+=take;
			money+=knapsack.items[indx].rho*take;
		}
	}
	
	return money;
}

int main() {
    int N, cap;
    cin >> N >> cap;
    Knapsack k;
    k.n_elems = N;
    k.capacity = cap;
    k.items = new Item[N];
    for (int i=0; i<N; i++) {
        cin >> k.items[i].value >> k.items[i].weight;
    }

    cout << max_profit(k);
    delete[] k.items;
}
