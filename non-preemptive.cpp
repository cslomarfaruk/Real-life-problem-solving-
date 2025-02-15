//non-premptive:

#include<bits/stdc++.h>
using namespace std;
const int M=1e9+7;
struct process{
	int id=0, at=0, bt=0, ct=0, tat=0, wt=0, rt=-1;
};
int main()
{
	//input:
	int n, i;
	cin>>n;
	vector<process>pr(n);
	for(i=0; i<n; i++){
		pr[i].id=i;
		cin>>pr[i].at>>pr[i].bt;
	}

	//calculation
	int time=0, cnt=0;
	vector<pair<int, int>>gc;
	vector<bool>com(n, false);

	while(cnt<n){
		int j=-1, ma=M, mm=M, mb=M;
		for(i=0; i<n; i++){
			if(!com[i] and pr[i].at<=time and pr[i].bt<mb){
				j=i;
				mb=pr[i].bt;
			}
			if(pr[i].at>time)
				mm=min(mm, pr[i].at);
		}
		if(j==-1){
			time=mm;
			gc.push_back({time, -1});
			continue;
		}
		if(pr[j].rt==-1)
			pr[j].rt= time-pr[j].at;

		time+=pr[j].bt;
		gc.push_back({time, pr[j].id});
		
		pr[j].ct=time;
		com[j]=true;
		cnt++;
	}

	int r=0, w=0;
	for(i=0; i<n; i++){
		pr[i].tat=pr[i].ct-pr[i].at;
		pr[i].wt=pr[i].tat-pr[i].bt;

		w+=pr[i].wt;
		r+=pr[i].rt;
	}

	//output
	cout<<"Completion time : ";
	for(i=0; i<n; i++)
		cout<<pr[i].ct<<' ';
	cout<<endl;
	cout<<"Turn around time: ";
	for(i=0; i<n; i++)
		cout<<pr[i].tat<<' ';
	cout<<endl;
	cout<<"Waiting time    : ";
	for(i=0; i<n; i++)
		cout<<pr[i].wt<<' ';
	cout<<endl;
	cout<<"Response time   : ";
	for(i=0; i<n; i++)
		cout<<pr[i].rt<<' ';
	cout<<endl<<endl;

	for(i=0; i<n; i+=2)

	cout<<"Grand Chart:"<<endl<<'|';
	for(auto [x, y]:gc)
		if(y==-1)
			cout<<"----|";
		else
			cout<<" P"<<y+1<<(y==pr[x].ct?' ':'*')<<'|';
		cout<<endl<<0;
	for(auto [x, y]:gc)cout<<"   "<<(x>9?"":" ")<<x;
		cout<<endl;

	cout<<"Average Waiting time: "<<((w*1.0)/n)<<endl;
	cout<<"Average response time: "<<((r*1.0)/n);
	
	return 0;
}