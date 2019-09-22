#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <fstream>
using namespace std;

struct sample{
	vector<int> data;
	int label;
}sgrp[10];

vector<int> w;
int label[10000];
int ds[10000][2];
int n1=0;
int a = 1;

void preload(){
	for(int i=0;i<n1;i++){
		sgrp[i].data.push_back(1);
		sgrp[i].data.push_back(ds[i][0]);
		sgrp[i].data.push_back(ds[i][1]);
		sgrp[i].label = label[i];
	}
	for(int i=0;i<3;i++){
		w.push_back(0);
	}
}

int mul(sample s){
	int mr = 0;
	for(int i=0;i<3;++i){
		mr += s.data[i] * w[i];
	}
	mr *= s.label;
	return mr;
}

int mulj(sample s){
	int mr = 0;
	for(int i=0;i<3;++i){
		mr += s.data[i];
	}
	mr *= s.label;
	return mr;
}

void train(){
	vector<sample> smis;
	int n = 0;
	for(int i=0;i<n1;++i){
		int r = mul(sgrp[i]);
		if(r>0) continue;
		else{
			smis.push_back(sgrp[i]);
			n++;
		}
	}
	if(n==0)return;
	for(int i=0;i<n;++i){
		sample m = smis[i];
		for(int j=0;j<3;++j){
			w[j] = w[j] + a*m.label*m.data[j];
		}
	}
	train();
}

int test(int x1,int x2){
	int m = w[0] + w[1]*x1 + w[2]*x2;
	if(m>0)return 1;
	if(m<0)return -1;
}

int main(){
	string nmb;
	cout<<"�������ģ����������չ������";
	cin>>nmb;
	string fn = "perceptron_"+nmb+".model";
	ofstream ofl(fn);
	cout<<"����ѵ�����ݶ��٣�";
	cin>>n1;
	for(int i=0;i<n1;++i){
		cout<<"�����"<<(i+1)<<"�����ݣ�";
		cin>>ds[i][0]>>ds[i][1];
		cout<<"\t������ʵ���ࣺ";
		cin>>label[i];
	}
	preload();
	train();
	string s1,s2;
	s1=" +";s2=" +";
	int c1,c2,c0;
	c1=w[1];c2=w[2];c0=w[0];
	if(w[2]<0){
		s1=" -";
		c2 = -c2;
	}
	if(w[0]<0){
		s2=" -";
		c0 = -c0;
	} 
	cout<<"ѵ�������"<<endl<<"\t���ֳ�ƽ��Ϊ��"<<c1<<"X1"<<s1<<" "<<c2<<"X2"<<s2<<" "<<c0<<" = 0"<<endl;
	ofl<<to_string(w[0])<<"\n";
	ofl<<to_string(w[1])<<"\n";
	ofl<<to_string(w[2])<<"\n";
	ofl.close();
	int t;
	cout<<"������Դ�����";
	cin>>t;
	int i=0;
	while(i<t){
		int x1,x2;
		cin>>x1>>x2;
		cout<<"���Խ����";
		int r = test(x1,x2);
		if(r==1)cout<<"����"<<endl;
		else cout<<"����"<<endl;
		++i;
	}
}
