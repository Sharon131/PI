#include <iostream>

using namespace std;

struct Event {
    int start, end;
};

void PrintSchedule(Event *events, int N){
	cout << "Pritowanie rozk³adu" << endl;
	for(int i=0;i<N;i++){
		cout << events[i].start << '\t';
	}
	cout << endl;
	for(int j=0;j<N;j++){
		cout << events[j].end << '\t';
	}
	cout << endl << "Koniec" << endl;
}

int Partition(Event *events,int l, int r){
	Event pivot=events[r];
	
	int i=l-1;
	
	for(int j=l;j<r;j++){
		if(events[j].end < pivot.end){
			i++;
			Event temp=events[j];
			events[j]=events[i];
			events[i]=temp;
		}
	}
	
	events[r]=events[i+1];
	events[i+1]=pivot;
	
	return i+1;
}

void QuickSortRek(Event *events, int l, int r){
	if(l>r)		return;
	
	int index=Partition(events,l,r);
	
	QuickSortRek(events,l,index-1);
	QuickSortRek(events,index+1,r);
}

void QuickSort(Event *events, int N){
	QuickSortRek(events,0,N-1);
}


int how_many_rooms (Event* events, int N) {
    
    QuickSort(events,N);
	
	bool* selected=new bool[N];
    for(int i=0;i<N;i++){
    	selected[i]=false;
	}
    
    bool move=true;
    int count=0;
    int i=0;
    
    while(i<N){
    	i=0;
    	while(selected[i] && i<N)		i++;
    	selected[i]=true;
    	
		for(int j=i+1;j<N;j++){
	    	if(!selected[j] && events[j].start>=events[i].end){
	    		selected[j]=true;
				i=j;
			}
		}
		if(i<N)		count++;
	}
    
    return count;
}

int main() {
    int N;
    cin >> N;
    Event e[N];
    for (int i=0; i<N; i++) cin >> e[i].start >> e[i].end;

    cout << how_many_rooms(e, N) << endl;
}
