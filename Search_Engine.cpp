#include <iterator>
#include <iostream>
#include <fstream>
#include <map>
#include <hash_map>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
using namespace std;
hash_multimap <string, string> hashmap;
typedef pair<string,string> spair, mpair;
map<string,int> words;
map<string,string> tree;
vector<pair<string,int>> items;
bool wayToSort(pair<string, int> i, pair<string, int> j) { return i.second > j.second; }
void load_In_Map();
int main()
{

	string str;
    fstream inFile("input1.txt", ios::in);
	getline(inFile, str);
    while(!inFile.eof())
	{
            ++words[str];
			getline(inFile, str);
	}
	inFile.close();
	for(auto it = words.begin(); it != words.end(); it++)
	{	
         if(it->second>=54)
		 items.push_back(make_pair(it->first, it->second));
	}
	sort(items.begin(), items.end(),wayToSort); // Sorting to get top searches
	load_In_Map();
	int i = 0;
	int j = 0;
	for(vector<pair<string,int>>::iterator iter = items.begin(); iter!=items.end()&& i<10000; ++iter,i++)
	{
		for(auto it = hashmap.begin(); it != hashmap.end(); it++,j++)
		{	
	         if(iter->first==it->first)
			 {
				  if(j<=1000)
					tree.insert(mpair(it->first, it->second));
				 else
				 {
					tree.insert(mpair(it->first,""));
				 }
			 }
		}
    }
	for(int i = 0; i<=3;i++)
	{
	string input;
	string url, mem;
	cout<<"\n Please enter a query: ";
	cin>>input;
	map<string,string>:: iterator it = tree.find(input);
	cout<<"\n Output: ";
	if(it==tree.end() || it->second=="None")
	{
		cout<<"\n URLS NOT FOUND\n";
	}
	else
	{
		 url = it->second;
		 mem = "memory";
		if(url=="")
		{
			auto iter = hashmap.find(input);
			url = iter->second;
			mem = "disk";
		}
	cout<<url<<endl;
	cout<<"URLs Read from: "<<mem<<endl;
	}
	}
	system("PAUSE");
	return 0;
}
void load_In_Map()
{
	fstream inFile;
	string line, name;
	inFile.open("urls.txt", ios::in);
	getline(inFile, name, ':');
	getline(inFile, line);
	while(!inFile.eof())
	{
	  hashmap.insert(spair(name,line));
	  getline(inFile, name, ':');
	  getline(inFile, line);
	}
	inFile.close();
}