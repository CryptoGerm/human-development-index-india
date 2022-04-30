#include<iostream>
#include<graphics.h>
#include <string.h>
#include<fstream>  
#include<math.h>
#include <cstdlib>
#include<iomanip>
using namespace std;

class Graph{
	string file;
	string delim;
	string *rank;
	double *score;
	string *state;
	
	public:
	
	Graph(string file,string delim,string *rank,double *score,string *state)
	{
		this->file=file;
		this->delim=delim;
		this->rank=rank;
		this->score=score;
		this->state=state;
	}
	
	void readData()
	{
		FILE *rf;
		rf=fopen("output.csv","r");
		
		int m=0;
		int n=0,i=0,k=0;
		char line[100];
		
		while(fgets(line,sizeof(line),rf))
    	{  
			m=0;
			char *token;
			token=strtok(line,",");
			while(token!=NULL)
			{
				if(m==0)
				{
					rank[i]=token;
				  	i++;
				}
				else if(m==1)
				{
				 	state[n]=token;
				 	n++;
				}
				else if(m==2)
				{ 
					score[k]=atof(token);
					k++;
				}
				token=strtok(NULL,",");
				m++;
			}
    	}
		
	}
	
	void plotgraph()
	{
		initwindow(1450,850);
		int x,y;
int rk[36]=     {110,140,170,200,230,260,290,320,350,380,410,440,470,500,530,560,590,620,650,680,710,740,770,800,830,860,890,920,950,980,1010,1040,1070,1100,1130,1160};
//int score[36]={440.23,424.56,408,406,403,402,400,398,391,390,389,377,372,371,357,356,355,348,345,339,333,326,324,322,318,316,314,302,294,291,290,288,273,252,202,184};
		int width =20;
//char str[36][36]={"UP","BR","RJ","WB","AS","MP","JH","LK","OR","MH","NL","AR","HR","TS","JK","AP","CG","PB","KA","MN","UK","TN","AN","ML","GJ","HP","DL","TR","GA","PY","KL","DN","SK","CH","MZ","DD"
//};
		char sc[10][10]={"7","14","21","28","35","42","49","56","63","70"};
		settextstyle(DEFAULT_FONT,0,0);
		//outtextxy(350,40,"BAR GRAPH");
   		//setbkcolor(WHITE);

   		setlinestyle(SOLID_LINE,0,2);
   		/* Draw X and Y Axis */
 		x= getmaxx();
		y=getmaxy();
		//printf("max x is =%d , max y is %d",x,y);
   		line(100,10,100,550);
   		line(x-20,550,100,550);
   		line(90,20,100,10);
   		line(110,20,100,10);
   		line(x-40,540,x-20,550);
   		line(x-40,560,x-20,550);

   		outtextxy(70,10,(char*)"Y");
   		outtextxy(x-20,570,(char*)"X");
   		outtextxy(90,570,(char*)"O");
		int k =1;int y_origin= 550;
		for(int i=0;i<10;i++)
		{
			//settextstyle(DEFAULT_FONT,0,0);
			y_origin = y_origin-50;
			outtextxy(70,y_origin,sc[i]);
		}
		int j=0,p=36;
		settextstyle(DEFAULT_FONT,1,0);
		for(int i=1;i<37;i++)
		{
			if(k>14)
			{
				k=1;
			}
			settextstyle(DEFAULT_FONT,1,0);
			outtextxy(rk[j],760,strdup(state[p].c_str()));
			setfillstyle(SOLID_FILL, k);
			bar(rk[j],score[i],rk[j]+20,550);
			settextstyle(DEFAULT_FONT,0,2);
			outtextxy(rk[j],score[i]-40,strdup(rank[p].c_str()));
			j++;
			k++;
			p--;
		}
		settextstyle(DEFAULT_FONT,1,0);
		outtextxy(40,400,(char*)"SCORE");
   		getch();
   		closegraph();
	}
};

int main()
{
	string *rank = new string[37];
	double *score = new double[37];
	string *state = new string[37];
	Graph graph("output.csv",",",rank,score,state);
	graph.readData();
	for(int m=0;m<37;m++)
	{
		cout<<setw(2)<<rank[m]<<"\t"<<setw(25)<<state[m]<<"\t\t\t"<<score[m]<<endl;
	}
	graph.plotgraph();
}
