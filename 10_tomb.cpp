#include <iostream>

using namespace std;

int how_many_rek(string map, int N, int start){
	
	if(start>=N)	return 1;
	
	int count=0;
	int steps=0;
	for(int i=start;steps<6 && i<N;i++){
		if(map[i]=='1'){
			count+=how_many_rek(map,N,i+1);
		}
		steps++;
	}
	return count;
}

int how_many_ways(string map, int N) {
	
	return how_many_rek(map,N,1);
}

int main() {
    int N;
    cin >> N;
    string map;
    cin >> map;
    if (map.size() != N) {
        cout << "Incorrect map size" << endl;
        return -1;
    }
    cout << how_many_ways(map, N) << endl;
}
