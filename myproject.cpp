#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<iomanip>
#include<graphics.h>
using namespace std;

class ReadCSV{
	
	string file,delim;
	public:
	ReadCSV(string file,string delim)
	{
		this->file=file;
		this->delim=delim;
	}
	
	vector<string> split(string a)
    {  
		int i=0,start=0,end=0; //university,of,petrolium,energy,studies
		vector<string> s;
        while(a[i]!='\0')
	    {   
            if(a[i]==',')
            {
            	end=i;
            	//cout<<"start "<<start<<"\n";
            	//cout<<"i or end"<<i;
            	s.push_back(a.substr(start,end-start));
				start=i+1; //11
				i=i+1;
			}    
			else if(i==a.size()-1)
			{
				s.push_back(a.substr(end+1,a.size()-1));
			}
			//cout<<"out i "<<i<<" ";
            i++;
	    }	
		return s;
    }
	
	vector<vector<string> > readData()
	{
		ifstream rf;
		vector<vector<string> > mydata;
		rf.open(file);
		if(!rf.is_open())
		{
			cout<<"Error can not open file";
		}
		else
		{
			string line="";
			while(getline(rf,line))
			{
				vector<string> data;
				//cout<<line<<endl;
				//cout<<split(line)<<"\n";
				for(string i: split(line))
				{
					data.push_back(i);	
				}
				mydata.push_back(data);
			}
			rf.close();
		}
		return mydata;
	}
	
	void writeData(int *rank,double *score,string *state)
	{
		ofstream wf,outputFile;
		vector<vector<string> > mydata;
		wf.open(file);
		if(!wf.is_open())
		{
			cout<<"Error can not open file";
		}
		else
		{
			wf<<"Rank"<<","<<"State"<<","<<"Score"<<endl;
			for(int i=0;i<36;i++)
			{
				wf<<rank[i]<<","<<state[i]<<","<<score[i]<<endl;	
			}
			wf.close();
		}
	}
	
	/*void display()
	{
		//cout<<file<<" "<<delim;
	}*/
};

class Weight{
	double **AHPmatrix, ***fuzzymatrix, **meanmatrix, **fuzzyweightmatrix, *defuzzyweight, *weights;
	int n;
	public:
	Weight(double **AHPmatrix,int n)
	{
		this->AHPmatrix=AHPmatrix;
		this->n=n;
		
		//allocate the mamory to fuzzy matrix
		fuzzymatrix = new double**[n];
    	for(int i=0; i<n; i++)
    	{
        	fuzzymatrix[i] = new double*[n];
        	for(int j=0;j<n;j++) 
			{
            	fuzzymatrix[i][j]=new double[3];
        	}
    	}
    	
    	//allocate mamory to meanmatrix
    	meanmatrix=new double*[n];
		for(int i=0;i<n;i++)
		{
			meanmatrix[i]=new double[3];
		}
		
		//allocate mamory to fuzzyweightmatrix
		fuzzyweightmatrix=new double*[n];
		for(int i=0;i<n;i++)
		{
			fuzzyweightmatrix[i]=new double[3];
		}
		
		//allocate mamory to defuzzyweight
		defuzzyweight=new double[n];
    	
    	//allocate mamory to weights
		weights=new double[n];
	}
	
	void converttoFuzzy()
	{
//		double ***fuzzymatrix;
//		fuzzymatrix = new double**[n];
// 
//    	for(int i=0; i<n; i++)
//    	{
//        	fuzzymatrix[i] = new double*[n];
//        	for(int j=0;j<n;j++) 
//			{
//            	fuzzymatrix[i][j]=new double[3];
//        	}
//    	}
    	
		for(int i=0;i<n;i++)
		{
			int k=0;
			for(int j=0;j<n;j++)
			{
				if(AHPmatrix[i][j]==1)
				{
					fuzzymatrix[i][j][k]=1;
					fuzzymatrix[i][j][k+1]=1;
					fuzzymatrix[i][j][k+2]=1;
				}
				else if(AHPmatrix[i][j]==9)
				{
					fuzzymatrix[i][j][k]=9;
					fuzzymatrix[i][j][k+1]=9;
					fuzzymatrix[i][j][k+2]=9;
				}
				else if(AHPmatrix[i][j]==0.111111)
				{
					fuzzymatrix[i][j][k]=0.111111;
					fuzzymatrix[i][j][k+1]=0.111111;
					fuzzymatrix[i][j][k+2]=0.111111;
				}
				else if(AHPmatrix[i][j]>0 && AHPmatrix[i][j]<1)
				{
					int temp=1/AHPmatrix[i][j];
					fuzzymatrix[i][j][k]=(1.0/(temp+1));
					fuzzymatrix[i][j][k+1]=AHPmatrix[i][j];
					fuzzymatrix[i][j][k+2]=(1.0/(temp-1));
				}
				else
				{
					fuzzymatrix[i][j][k]=AHPmatrix[i][j]-1;
					fuzzymatrix[i][j][k+1]=AHPmatrix[i][j];
					fuzzymatrix[i][j][k+2]=AHPmatrix[i][j]+1;
				}
			}
		}
		
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				for(int k=0;k<3;k++)
				{
					cout<<fuzzymatrix[i][j][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl<<endl;
		}
	}
	
	void fuzzyGMean()
	{
//		double **meanmatrix;
//		meanmatrix=new double*[n];
//		for(int i=0;i<n;i++)
//		{
//			meanmatrix[i]=new double[3];
//		}
		double mult=1.0;
		for(int i=0;i<n;i++)
		{
			for(int k=0;k<3;k++)
			{
				mult=1.0;
				for(int j=0;j<n;j++)
				{
					mult=mult*fuzzymatrix[i][j][k];
				}
				meanmatrix[i][k]=pow(mult,(1.0/n));
			}
		}
		
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<3;j++)
			{
				cout<<meanmatrix[i][j]<<" ";
			}
			cout<<endl;
		}
//		return meanmatrix;
	}
	
	void fuzzyWeights()
	{
		double fuzzysumofinverse[3];
		double sum=0.0;
		
		for(int j=0;j<3;j++)
		{
			sum=0.0;
			for(int i=0;i<n;i++)
			{
				sum=sum+meanmatrix[i][j];
			}
			fuzzysumofinverse[j]=sum;	
		}
		fuzzysumofinverse[1]=1.0/fuzzysumofinverse[1];
		double temp = 1.0/fuzzysumofinverse[0];
		fuzzysumofinverse[0] = 1.0/fuzzysumofinverse[2];
		fuzzysumofinverse[2]=temp;
		
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<3;j++)
			{
				fuzzyweightmatrix[i][j]=meanmatrix[i][j]*fuzzysumofinverse[j];
			}
		}
		
		
		cout<<"Fuzzy sum of inverse = "<<endl;
		for(int i=0;i<3;i++)
		{	
			cout<<fuzzysumofinverse[i]<<" ";
		}
		
		cout<<"Fuzzy weights = "<<endl;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<3;j++)
			{
				cout<<fuzzyweightmatrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	
	void defuzzied()
	{
		double sum=0.0,COA;
		for(int i=0;i<n;i++)
		{
			sum=0.0;
			for(int j=0;j<3;j++)
			{
				sum=sum+fuzzyweightmatrix[i][j];
			}
			COA=sum/3;
			defuzzyweight[i]=COA;
		}
		
		cout<<"Defuzzy Weights = "<<endl;
		for(int i=0;i<n;i++)
		{
			cout<<defuzzyweight[i]<<" ";
		}
	}
	
	double* normalizeWeight()
	{
		double sum=0.0;
		for(int i=0;i<n;i++)
		{
			sum=sum+defuzzyweight[i];
		}
		for(int i=0;i<n;i++)
		{
			weights[i]=defuzzyweight[i]/sum;
		}
		
		cout<<"Weights = "<<endl;
		for(int i=0;i<n;i++)
		{
			cout<<weights[i]<<" ";
		}
		
		return weights;
	}
	
	void display()
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<AHPmatrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};

class Analysis{
	double *weights;
	vector<vector<string> > mydata;
	string filename, delim;
	double score[36];
	double criteria_score[36], overall_score[36];
	string state[36];
	
	public:
	Analysis(string filename,string delim, double *weights)
	{
		this->filename=filename;
		this->delim=delim;	
		this->weights=weights;
	}
	
	string* getState()
	{
		return state;	
	}
	
	void calculateScore()
	{
		ReadCSV obj(filename,delim);
		int t=0,k=0;
		double sum=0.0;
		int l=0;
		
		// Read the data from file
		for(vector<string> i: obj.readData())
		{
			t=0;
			k=0;
			sum=0.0;
			for(string j: i)
			{
				if(t>0)
				{
					sum=sum+(stod(j)*weights[k]);	
					k++;	
				}
				if(t==0)
				{
					state[l]=j;	
				}
				t++;
			}
			score[l]=sum;
			l++;
		}
		cout<<"scores = "<<endl;
		for(int i=0;i<36;i++)
		{
			cout<<state[i]<<"->"<<score[i]<<endl;
		}			
	}
	
	double* calculateCriteriaTotalScore(double myoverall_weight)
	{
		for(int i=0;i<36;i++)
		{
			criteria_score[i]=score[i]*myoverall_weight;
		}
		cout<<"criteria scores = "<<endl;
		for(int i=0;i<36;i++)
		{
			cout<<state[i]<<"->"<<criteria_score[i]<<endl;
		}
		return criteria_score;
	}

	double* calculateoverallscore(double *scores_crime,double *scores_health,double *scores_education,double *scores_unemploy,string *state)
	{
		for(int i=0;i<36;i++)
		{
			overall_score[i]=(scores_health[i]+scores_education[i])-(scores_crime[i]+scores_unemploy[i]);
		}
		for(int i=0;i<36;i++)
		{
			cout<<endl<<endl<<state[i]<<" "<<overall_score[i]<<endl;
		}
		return overall_score;
	}
};

class Rank{
	double *overall_score;
	string *state;
	int rank[36];
	
	public:
	Rank(double *overall_score,string *state)
	{
		this->overall_score=overall_score;
		this->state=state;
	}
	
	void merge_sort(double *score,string *state, int l, int h)
	{
		int mid,i;
		if(l<h)
		{
			mid=(l+h)/2;
			merge_sort(score,state,l,mid);
			merge_sort(score,state,mid+1,h);
			merging(score,state,l,mid,h);
		}
	}
	
	void merging(double *arr,string *s, int l, int m, int r) 
	{ 
    	int i, j, k; 
    	int n1 = m - l + 1; 
    	int n2 = r - m; 
  
  		double L1[n1], R1[n2];
		string L2[n1], R2[n2]; 
  
	    for (i = 0; i < n1; i++) 
	    {
	    	L1[i] = arr[l + i]; 
			L2[i] = s[l + i]; 	
		}
	    for (j = 0; j < n2; j++)
		{
			R1[j] = arr[m + 1 + j];
			R2[j] = s[m + 1 + j];  	
		} 
  
	    i = 0; 
	    j = 0; 
	    k = l; 
	    while (i < n1 && j < n2)
		{ 
	        if (L1[i] >= R1[j]) 
			{ 
	            arr[k] = L1[i]; 
	            s[k]= L2[i];
	            i++; 
	        } 
	        else 
			{ 
	            arr[k] = R1[j];
				s[k] = R2[j]; 
	            j++; 
	        } 
	        k++; 
	    } 
	  
	    while (i < n1)
		{ 
	        arr[k] = L1[i];
			s[k] = L2[i]; 
	        i++; 
	        k++; 
	    } 
	  
	    while (j < n2) 
		{ 
	        arr[k] = R1[j];
			s[k] = R2[j]; 
	        j++; 
	        k++; 
	    } 
	}
	
	int* assignRank()
	{
		merge_sort(overall_score,state,0,35);
		for(int i=0;i<36;i++)
		{
			rank[i]=i+1;
		}
		return rank;
	}
	
	double* getRankedScore()
	{
		return overall_score;
	}
	
	string* getRankedState()
	{
		return state;
	}
	
};

class Common{
	double crimematrix[4][4]= {
				{1,3,9,5},
				{0.333333,1,7,3},
				{0.111111,0.142857,1,0.142857},
				{0.200000,0.333333,7,1}
			};
	double healthmatrix[2][2]= {
				{1,0.142857},
				{7,1}
			};
	double educationmatrix[2][2]= {
				{1,0.166666},
				{6,1}
			};
	double unemploymatrix[1][1]= {
				{1}
			};
	double overallmatrix[4][4]= {
			{1,5,0.142857,0.333333},
			{0.200000,1,3,0.200000},
			{7,0.333333,1,9},
			{3,5,0.111111,1}
			};
	public:
	double** initializeMatrix(int n,string s)
	{
		double **AHPmatrix;
		AHPmatrix=new double*[n];
		for(int i=0;i<n;i++)
		{
			AHPmatrix[i]=new double[n];
		} 
		if(s=="crime")
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					  AHPmatrix[i][j]=crimematrix[i][j];
		    	}
			}	
		}
		else if(s=="health")
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					  AHPmatrix[i][j]=healthmatrix[i][j];
		    	}
			}	
		}
		else if(s=="education")
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					  AHPmatrix[i][j]=educationmatrix[i][j];
		    	}
			}	
		}		
		else if(s=="unemploy")
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					  AHPmatrix[i][j]=unemploymatrix[i][j];
		    	}
			}	
		}		
		else if(s=="overall")
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					  AHPmatrix[i][j]=overallmatrix[i][j];
		    	}
			}	
		}	
		return AHPmatrix;
	}
};


int main()
{
//	vector<vector<string> > mydata;
//	ReadCSV obj_crime("final_crime.csv",",");
//
//	// Read the data from file
//	for(vector<string> i: obj_crime.readData())
//	{
//		for(string j: i)
//		{
//			cout<<j<<"|";
//		}
//		cout<<"\n";
//	}
	
	

	double *weights_crime,*weights_health,*weights_education,*weights_unemploy,*weights_overall;
	double *scores_crime,*store_scores_crime,*scores_health,*store_scores_health,*scores_education,*store_scores_education,*scores_unemploy,*store_scores_unemploy,*scores_overall;
	string *state,store_state1[36],store_state2[36],store_state3[36],store_state4[36],*rankedstate;
	int *ranks,*temp_rank;
	double *rankedscore;
	
	cout<<endl<<endl<<"Crime Subcategories weights----------- "<<endl<<endl;
	Common obj_AHPmatrixcrime;
	Weight obj_weightcrime(obj_AHPmatrixcrime.initializeMatrix(4,"crime"),4);
	obj_weightcrime.display();
	obj_weightcrime.converttoFuzzy();
	obj_weightcrime.fuzzyGMean();
	obj_weightcrime.fuzzyWeights();
	obj_weightcrime.defuzzied();
	weights_crime=obj_weightcrime.normalizeWeight();
	
	cout<<endl<<endl<<"Health Subcategories weights----------- "<<endl<<endl;
	Common obj_AHPmatrixhealth;
	Weight obj_weighthealth(obj_AHPmatrixhealth.initializeMatrix(2,"health"),2);
	obj_weighthealth.display();
	obj_weighthealth.converttoFuzzy();
	obj_weighthealth.fuzzyGMean();
	obj_weighthealth.fuzzyWeights();
	obj_weighthealth.defuzzied();
	weights_health=obj_weighthealth.normalizeWeight();
	
	cout<<endl<<endl<<"Education Subcategories weights----------- "<<endl<<endl;
	Common obj_AHPmatrixeducation;
	Weight obj_weighteducation(obj_AHPmatrixeducation.initializeMatrix(2,"education"),2);
	obj_weighteducation.display();
	obj_weighteducation.converttoFuzzy();
	obj_weighteducation.fuzzyGMean();
	obj_weighteducation.fuzzyWeights();
	obj_weighteducation.defuzzied();
	weights_education=obj_weighteducation.normalizeWeight();
	
	cout<<endl<<endl<<"Unemployment Subcategories weights----------- "<<endl<<endl;
	Common obj_AHPmatrixunemploy;
	Weight obj_weightunemploy(obj_AHPmatrixunemploy.initializeMatrix(1,"unemploy"),1);
	obj_weightunemploy.display();
	obj_weightunemploy.converttoFuzzy();
	obj_weightunemploy.fuzzyGMean();
	obj_weightunemploy.fuzzyWeights();
	obj_weightunemploy.defuzzied();
	weights_unemploy=obj_weightunemploy.normalizeWeight();
	
	cout<<endl<<endl<<"Crime Subcategories Total Score----------- "<<endl<<endl;
	Analysis crime_score("final_crime.csv",",",weights_crime);
	crime_score.calculateScore();
	
	cout<<endl<<endl<<"Health Subcategories Total Score----------- "<<endl<<endl;
	Analysis health_score("final_health.csv",",",weights_health);
	health_score.calculateScore();
	
	cout<<endl<<endl<<"Education Subcategories Total Score----------- "<<endl<<endl;
	Analysis education_score("final_education.csv",",",weights_education);
	education_score.calculateScore();
	
	cout<<endl<<endl<<"Unemployment Subcategories Total Score----------- "<<endl<<endl;
	Analysis unemploy_score("final_unemployment.csv",",",weights_unemploy);
	unemploy_score.calculateScore();
	
	cout<<endl<<endl<<"Overall Weight----------- "<<endl<<endl;
	Common obj_AHPmatrixoverall;
	Weight obj_weightoverall(obj_AHPmatrixoverall.initializeMatrix(4,"overall"),4);
	obj_weightoverall.display();
	obj_weightoverall.converttoFuzzy();
	obj_weightoverall.fuzzyGMean();
	obj_weightoverall.fuzzyWeights();
	obj_weightoverall.defuzzied();
	weights_overall=obj_weightoverall.normalizeWeight();
	
	state=crime_score.getState();
	cout<<endl<<endl<<"Crime Criteria Total Score----------- "<<endl<<endl;
	scores_crime=crime_score.calculateCriteriaTotalScore(weights_overall[0]);
	store_scores_crime=(double*)malloc(36*sizeof(double));
	for(int i=0;i<36;i++)
	{
		store_scores_crime[i]=scores_crime[i];
		store_state1[i]=state[i];
	}
	Rank rank1(store_scores_crime,store_state1);
	ranks=rank1.assignRank();
	rankedstate=rank1.getRankedState();
	rankedscore=rank1.getRankedScore();
	for(int i=0;i<36;i++)
	{
		rankedscore[i]=rankedscore[i]*10;
	}
	ReadCSV myyobj1("output_crime.csv",",");
	myyobj1.writeData(ranks,rankedscore,rankedstate);


	cout<<endl<<endl<<"Health Criteria Total Score----------- "<<endl<<endl;
	scores_health=health_score.calculateCriteriaTotalScore(weights_overall[1]);
	store_scores_health=(double*)malloc(36*sizeof(double));
	for(int i=0;i<36;i++)
	{
		store_scores_health[i]=scores_health[i];
		store_state2[i]=state[i];
	}
	Rank rank2(store_scores_health,store_state2);
	ranks=rank2.assignRank();
	rankedstate=rank2.getRankedState();
	rankedscore=rank2.getRankedScore();
	for(int i=0;i<36;i++)
	{
		rankedscore[i]=rankedscore[i]*10;
	}
	ReadCSV myyobj2("output_health.csv",",");
	myyobj2.writeData(ranks,rankedscore,rankedstate);

	
	cout<<endl<<endl<<"Education Criteria Total Score----------- "<<endl<<endl;
	scores_education=education_score.calculateCriteriaTotalScore(weights_overall[2]);
	store_scores_education=(double*)malloc(36*sizeof(double));
	for(int i=0;i<36;i++)
	{
		store_scores_education[i]=scores_education[i];
		store_state3[i]=state[i];
	}
	Rank rank3(store_scores_education,store_state3);
	ranks=rank3.assignRank();
	rankedstate=rank3.getRankedState();
	rankedscore=rank3.getRankedScore();
	for(int i=0;i<36;i++)
	{
		rankedscore[i]=rankedscore[i]*10;
	}
	ReadCSV myyobj3("output_education.csv",",");
	myyobj3.writeData(ranks,rankedscore,rankedstate);

	
	cout<<endl<<endl<<"Unemployment Criteria Total Score----------- "<<endl<<endl;
	scores_unemploy=unemploy_score.calculateCriteriaTotalScore(weights_overall[3]);
	store_scores_unemploy=(double*)malloc(36*sizeof(double));
	for(int i=0;i<36;i++)
	{
		store_scores_unemploy[i]=scores_unemploy[i];
		store_state4[i]=state[i];
	}
	Rank rank4(store_scores_unemploy,store_state4);
	ranks=rank4.assignRank();
	rankedstate=rank4.getRankedState();
	rankedscore=rank4.getRankedScore();
	for(int i=0;i<36;i++)
	{
		rankedscore[i]=rankedscore[i]*10;
	}
	ReadCSV myyobj4("output_unemploy.csv",",");
	myyobj4.writeData(ranks,rankedscore,rankedstate);
	
	
	cout<<endl<<endl<<"Overall Scores----------- "<<endl<<endl;
	Analysis overall("","",scores_overall);
	scores_overall=overall.calculateoverallscore(scores_crime,scores_health,scores_education,scores_unemploy,state);
	
	cout<<endl<<endl<<"Ranks----------- "<<endl<<endl;
	Rank rank(scores_overall,state);
	ranks=rank.assignRank();
	rankedstate=rank.getRankedState();
	rankedscore=rank.getRankedScore();
	
	cout<<endl<<setw(2)<<"Rank"<<setw(25)<<"State"<<"\t\t\t\t"<<"Score"<<endl<<
	"---------------------------------------------------------------"<<endl;
	for(int i=0;i<36;i++)
	{
		cout<<setw(2)<<ranks[i]<<"\t"<<setw(25)<<rankedstate[i]<<"\t\t\t"<<rankedscore[i]<<endl;
	}
	for(int i=0;i<36;i++)
	{
		rankedscore[i]=rankedscore[i]*10;
	}
//	initwindow(1450,850);
//	getch();
//	closegraph();
	
	
	ReadCSV myyobj("output.csv",",");
	myyobj.writeData(ranks,rankedscore,rankedstate);

}
