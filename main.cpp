#include "MapAVL.h"
#include <bits/stdc++.h>

using namespace std;

int main(){
 
	string k;
	int n;
	
	string key = "KQfyMc";
	
	MapAVL *mapa = new MapAVL();
	
	while(cin>>k>>n){
	
//		cout<<"Insert: "<<k;
	
		mapa->insert(make_pair(k,n));
	
	
//		cout<<endl;

	}
	
	mapa->erase(key);
	
	return 0;
}
