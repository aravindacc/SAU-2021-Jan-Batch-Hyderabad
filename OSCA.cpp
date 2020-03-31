

#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;

int minimum(int brr[],int count)
{
	
	int min = brr[0];
	
	for(int i=0;i<count&&brr[i]>0;i++)
	{
		if(min>brr[i])
		{
			min=brr[i];
		}
	}
	return min;
}

int index(int BT[],int count,int min)
{
	for(int i=0;i<count;i++)
	{
		if(BT[i]==min)
		{
			return i;	
		}
		
	}
	return 0;
}

float maximum(float Pd[],int count)
{
	float max = Pd[0];
	for(int i=0;i<count;i++)
	{
		if(max<Pd[i])
		{
			max=Pd[i];
		}
	}
	return max;	 
}

int index2(float Pd[],int count,float max)
{
	int ind[count]={-1};
	for(int i=0;i<count;i++)
	{
		if(Pd[i]==max)
		{
			return i;
		}
		
	}
	return 0;
}

int main()
{
	int count;
	cout<<"Enter the number of processes to be evaluated "<<endl;
	cin>>count;
	
	float Priority[count];
	int Process[count],AT[count],BT[count];
	int CT1[count],TAT1[count],WT1[count],RT1[count];
	int CT2[count],TAT2[count],WT2[count],RT2[count];
		
	for(int i=0;i<count;i++)
	{
		Process[i]=i+1;
		cout<<"Enter the Arrival Time of "<<"Process"<<i+1<<endl;	
		cin>>AT[i];
		cout<<"Enter the Burst Time of "<<"Process"<<i+1<<endl;	
		cin>>BT[i];	
	}
	
	cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t"<<"The Given Input Data is "<<endl;
	cout<<setw(42)<<"Process  |"<<setw(16)<<"Arrival Time  |"<<setw(15)<<"Burst Time  |"<<endl;
		
	for(int i=0;i<count;i++)
	{
		cout<<setw(38)<<"P"<<Process[i]<<setw(3)<<"|"<<setw(13)<<AT[i]<<setw(3)<<"|"<<setw(12)<<BT[i]<<setw(3)<<"|"<<endl;
	}
	
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<count;j++)
		{
			if(AT[i]<AT[j])
			{
				int temp;
				
				temp = Process[j];
				Process[j]= Process[i];
				Process[i]= temp;
				
				temp = AT[j];
				AT[j]= AT[i];
				AT[i]= temp;
				
				temp = BT[j];
				BT[j]= BT[i];
				BT[i]= temp;
			}
		}
	}
	
	cout<<"\t"<<"Estimated process taking place for Non-Preemptive SJN to calculate Waiting time for Priority calculation"<<endl;
	
	//Calculating Completion Time (CT)
	
	///Step1 Calculating the total burst time
	
	int BTsum=0;
	int BTd[count];//Burst Time Duplicate array which is used in later part(Step 2)
	
	for(int i=0;i<count;i++)
	{
		BTd[i]=BT[i];
		BTsum = BTsum+BT[i];	
	} 
	
	///Step 2
	static int CTvalue=0;//Completion time value
	
	for(int i=0;i<count;i++)
	{
		if(CTvalue<AT[i])
		{
			CTvalue=AT[i]+BT[i];
			CT1[i]=CTvalue;
		}
		else
		{
			int k=0;// variable for varied size array brr
		int brr[count]={0};//An array for finding minimum for specific processes in Step 2
		
		for(int i=0;i<count;i++)
		{
			if((BTd[i]>0) && (AT[i]<=CTvalue) )//conditionn that Burst time duplicacy has to be greater than zero
			{
			brr[k]=BTd[i];
			k=k+1;		
			} 
		}
		
		int min=minimum(brr,count);
		CTvalue=CTvalue+min;
		
		int g=index(BT,count,min);
		CT1[g]=CTvalue;
		BTd[g]=-1;
	
		}
		
	}
	//Gantt Chart 1 of generic SJF or SJN to calculate Waiting Time
	int ctd[count];
	int gcd[count];
	int x[count];
	int y[count];
	for(int i=0;i<count;i++)
	{
		ctd[i]=CT1[i];
		gcd[i]=Process[i];
		x[i]=AT[i];
		y[i]=BT[i];
	}
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<count;j++)
		{
			if(ctd[i]<ctd[j])
			{
				int temp;
				
				temp = ctd[j];
				ctd[j]= ctd[i];
				ctd[i]= temp;
				
				temp = gcd[j];
				gcd[j]= gcd[i];
				gcd[i]= temp;
				
				temp = x[j];
				x[j]= x[i];
				x[i]= temp;
				
				temp = y[j];
				y[j]= y[i];
				y[i]= temp;
							
			}
		}
	}
	cout<<"\t\t"<<"The Gantt Chart for SJF or SJN to calculate Waiting time "<<endl<<endl;
	cout<<"----------------------------------------------------------------------------------------"<<endl;
	cout<<setw(16)<<"";
	if(CTvalue!=BTsum)
	{

	for(int i=0;i<ctd[count-1];i++)
	{
		for(int j=0;j<count;j++)
		{
			if(i<x[j])
			{
				cout<<setw(4)<<"IT"<<setw(4)<<"|";
				i=x[j];	
			}	
			if(i==x[j])
			{
				cout<<setw(4)<<"P"<<gcd[j]<<setw(4)<<"|";
				i=x[j]+y[j];	
			}
			
		}		
		
	}
	
	cout<<endl<<setw(15)<<"";
	
	for(int i=0;i<ctd[count-1];i++)
	{
		for(int j=0;j<count;j++)
		{
			if(i<x[j])
			{
				cout<<setw(9)<<x[j];
				i=x[j];	
			}	
			if(i==x[j])
			{
				cout<<setw(9)<<ctd[j];
				i=x[j]+y[j];	
			}
			
		}		
		
	}
	
	
	}
	else
	{
	
	for(int i=0;i<count;i++)
	{
		cout<<setw(4)<<"P"<<gcd[i]<<setw(4)<<"|";
	}
	
	cout<<endl<<setw(16)<<"";
	
	for(int i=0;i<count;i++)
	{
		cout<<setw(9)<<ctd[i];
	}
	}
	cout<<endl<<"----------------------------------------------------------------------------------------"<<endl;
	//Calculating Turn Around Time, Waiting time, Response time and Priority
	
	int BTd2[count];
	for(int i=0;i<count;i++)
	{
		TAT1[i]=CT1[i]-AT[i];
		WT1 [i]=TAT1[i]-BT[i];
		RT1 [i]=WT1[i];
		Priority[i]=1.000000+WT1[i]/float(BT[i]);
		BTd2[i]=BT[i];//Create another duplicate of Burst time
	}
	
	cout<<endl<<"The SJF or SJN updated table to derive waiting time and find out Priority ( Sorted as per Arrival Time ) "<<endl;
	cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<setw(42)<<"Process  |"<<setw(15)<<"Arrival Time  |"<<setw(15)<<"Burst Time  |"<<setw(20)<<"Completion Time  |"<<setw(21)<<"Turn Around Time  |"<<setw(17)<<"Waiting Time  |"<<setw(18)<<"Response Time  |"<<endl;
		
	for(int i=0;i<count;i++)
	{
		cout<<setw(37)<<"P"<<Process[i]<<setw(4)<<"|"<<setw(11)<<AT[i]<<setw(4)<<"|"<<setw(11)<<BT[i]<<setw(4)<<"|"<<setw(16)<<CT1[i]<<setw(4)<<"|"<<setw(16)<<TAT1[i]<<setw(5)<<"|"<<setw(13)<<WT1[i]<<setw(4)<<"|"<<setw(14)<<RT1[i]<<setw(4)<<"|"<<endl;
	}
	
	
	// Recalculation of Completion time as per Priority
	//here Unititled4bTsort
	float Pd[count];
	for(int i=0;i<count;i++)
	{
		Pd[i]=Priority[i];// Creating a duplicate of Priority
	}
	
	static int CTvalue2=0;
	
	for(int j=0;j<count;j++)
	{
		if(CTvalue2<AT[j])
		{
			CTvalue2=AT[j]+BT[j];
			CT2[j]=CTvalue2;
		}
		else
		{
		float crr[count];
		for(int i=0;i<count;i++)
		{
			crr[i]=Pd[i];
			if(AT[i]>CTvalue2)
			{	
				crr[i]=-1;	
			}
						
		}
		
		float max = maximum(crr,count);
		int ind = index2(crr,count,max);
		CTvalue2 = CTvalue2 + BT[ind];
		CT2[ind] = CTvalue2;
		Pd[ind] =-1;
		}
	}
	
	//ReCalculating Turn Around Time, Waiting time, Response time (Part2)
	
	
	for(int i=0;i<count;i++)
	{
		TAT2[i]=CT2[i]-AT[i];
		WT2 [i]=TAT2[i]-BT[i];
		RT2 [i]=WT2[i];
		
	}
	
	
	//sorting data as per Process
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<count;j++)
		{
			if(Process[i]<Process[j])
			{
				int temp;
				float pmet;
				
				pmet = Priority[j];
				Priority[j]= Priority[i];
				Priority[i]= pmet;
				
				temp = Process[j];
				Process[j]= Process[i];
				Process[i]= temp;
				
				temp = AT[j];
				AT[j]= AT[i];
				AT[i]= temp;
				
				temp = BT[j];
				BT[j]= BT[i];
				BT[i]= temp;
				
				temp = CT2[j];
				CT2[j]= CT2[i];
				CT2[i]= temp;
				
				temp = TAT2[j];
				TAT2[j]= TAT2[i];
				TAT2[i]= temp;
				
				temp = WT2[j];
				WT2[j]= WT2[i];
				WT2[i]= temp;
				
				temp = RT2[j];
				RT2[j]= RT2[i];
				RT2[i]= temp;
								
			}
		}
	}
	//all correct
	int ctd2[count];
	int gcd2[count];
	int x2[count];
	int y2[count];
	for(int i=0;i<count;i++)
	{
		ctd2[i]=CT2[i];
		gcd2[i]=Process[i];
		x2[i]=AT[i];
		y2[i]=BT[i];
	}
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<count;j++)
		{
			if(ctd2[i]<ctd2[j])
			{
				int temp;
				
				temp = ctd2[j];
				ctd2[j]= ctd2[i];
				ctd2[i]= temp;
				
				temp = gcd2[j];
				gcd2[j]= gcd2[i];
				gcd2[i]= temp;
				
				temp = x2[j];
				x2[j]= x2[i];
				x2[i]= temp;
				
				temp = y2[j];
				y2[j]= y2[i];
				y2[i]= temp;
							
			}
		}
	}
	cout<<endl<<endl<<endl<<"\t"<<"The Gantt Chart of Non Preemptive Priortized SJF or SFN like Scheduling (Final Answer1)"<<endl;
	cout<<"----------------------------------------------------------------------------------------"<<endl;
	cout<<setw(16)<<"";
	if(CTvalue2!=BTsum)
	{

	for(int i=0;i<ctd2[count-1];i++)
	{
		for(int j=0;j<count;j++)
		{
			if(i<x2[j])
			{
				cout<<setw(4)<<"IT"<<setw(4)<<"|";
				i=x2[j];	
			}	
			if(i==x2[j])
			{
				cout<<setw(4)<<"P"<<gcd2[j]<<setw(4)<<"|";
				i=x2[j]+y2[j];	
			}
			
		}		
		
	}
	
	cout<<endl<<setw(16)<<"";
	
	for(int i=0;i<ctd2[count-1];i++)
	{
		for(int j=0;j<count;j++)
		{
			if(i<x2[j])
			{
				cout<<setw(9)<<x2[j];
				i=x2[j];	
			}	
			if(i==x2[j])
			{
				cout<<setw(9)<<ctd2[j];
				i=x2[j]+y2[j];	
			}
			
		}		
		
	}
	
	
	}
	else
	{
	
	for(int i=0;i<count;i++)
	{
		cout<<setw(4)<<"P"<<gcd2[i]<<setw(4)<<"|";
	}
	
	cout<<endl<<setw(16)<<"";
	
	for(int i=0;i<count;i++)
	{
		cout<<setw(9)<<ctd2[i];
	}
	}
	cout<<endl<<"----------------------------------------------------------------------------------------"<<endl;
	
	//all correct
	cout<<endl<<endl<<"The Non Preemptive Priortized SJF or SFN like Scheduling (Final Answer2)"<<endl;
	cout<<"The calculation is done giving importance to Priority and then followed by lesser Burst Time keeping Arrival Time in mind "<<endl;
	cout<<endl<<"========================================================================================================================================================="<<endl;
	cout<<setw(20)<<"Priority  |"<<setw(11)<<"Process  |"<<setw(16)<<"Arrival Time  |"<<setw(15)<<"Burst Time  |"<<setw(20)<<"Completion Time  |"<<setw(21)<<"Turn Around Time  |"<<setw(17)<<"Waiting Time  |"<<setw(18)<<"Response Time  |"<<endl;
		
	for(int i=0;i<count;i++)
	{
		cout<<setw(13)<<Priority[i]<<setw(7)<<"|"<<setw(6)<<"P"<<Process[i]<<setw(4)<<"|"<<setw(12)<<AT[i]<<setw(4)<<"|"<<setw(11)<<BT[i]<<setw(4)<<"|"<<setw(16)<<CT2[i]<<setw(4)<<"|"<<setw(16)<<TAT2[i]<<setw(5)<<"|"<<setw(13)<<WT2[i]<<setw(4)<<"|"<<setw(14)<<RT2[i]<<setw(4)<<"|"<<endl;
	}
	cout<<endl<<"========================================================================================================================================================="<<endl;
	
	int TATsum=0,WTsum=0,RTsum=0;
	float TATavg,WTavg,RTavg;
	for(int i=0;i<count;i++)
	{
		TATsum=TATsum+TAT2[i];
		WTsum=WTsum+WT2[i];
		RTsum=RTsum+RT2[i];
	}
	TATavg=TATsum/(float) count;
	WTavg=WTsum/(float) count;
	RTavg=RTsum/(float) count;
	cout<<"\t\t""The Average Turn Around Time is: "<<TATavg<<endl;
	cout<<"\t\t""The Average Wait Time is: "<<WTavg<<endl;
	cout<<"\t\t""The Average Response Time is: "<<RTavg<<endl;
	
}

