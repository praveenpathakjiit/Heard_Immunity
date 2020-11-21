#include<iostream>
#include<stdio.h>
#include<deque>
#include<vector>
#include<map>
#include<math.h>
#include<algorithm>
#include<queue>
#include<bits/stdc++.h>

using namespace std;
#define lli long long int
#define ull unsigned long long int
#define ff first
#define MOD 1000000007
#define ss second
#define print(containeer) \
for(auto iterator:containeer)cout<<iterator<<" ";cout<<endl;
#define PI 3.14159265
#define N 2008
struct person{

lli x,y;
lli is_positive;
lli is_dead=false;
lli infection_time;
lli is_immune=false;


};
double dist(struct person p1, struct person p2)
{

    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)* (p1.y-p2.y));
}
void movement(vector<struct person> & population,lli x_limit,lli y_limit,lli movement_number)
{

    map<lli,lli>m;
    lli k=movement_number;
    while(k)
    {

       lli l=rand()%population.size();
       if(m.count(l)==false)
       {

           m[l]++;
           population[l].x=rand()%x_limit;
           population[l].y=rand()%y_limit;
           k--;
       }
    }
}
void infection_spread(vector<struct person> & population,lli mortality_rate, lli response_time,lli cur_time,lli infection_rate, lli infection_radius)
{
    vector<lli>ind;
    for(lli i=0;i<population.size();i++)
    {

        if(population[i].is_positive && cur_time-population[i].infection_time==response_time)
        {
            ind.push_back(i);
        }
    }
    lli dead=(mortality_rate*ind.size())/100;

    cout<<dead<<"  people dead on "<<cur_time<<"th day  "<<endl;
    map<lli,lli>m;
    while(dead)
    {
       lli k=rand()%ind.size();

       if(m.count(k)==false)
       {

           m[k]=true;
           population[ind[k]].is_dead=true;
           population[ind[k]].is_positive=false;
           dead--;

       }

    }
    for(auto i:ind)
    {

        if(population[i].is_dead==false)
           {

           population[i].is_immune=true;
           population[i].is_positive=false;
           }
    }

    // the infection will start to spread
    //already immune/ dead person will not get infected again
    // only a living person can spread infection if it comes under infection radius of un immune person
lli i,j;
    for(i=0;i<population.size();i++)
    {
        if(population[i].is_positive==false && population[i].is_immune==false && population[i].is_dead==false)
        {

            for(j=0;j<population.size();j++)
            {
                if(i!=j && population[j].is_positive==true && dist(population[j],population[i])<=infection_radius)
                {
                        lli prob=100/infection_rate;
                        lli odds=rand()%prob;
                        if(odds==0)
                        {
                            population[i].is_positive=true;
                            population[i].infection_time=cur_time;
                            break;
                        }
                }
            }
        }

    }

}
double percent_infected_persons(vector<struct person> & population)
{
    lli totl=0;
    lli infected=0;
    for(lli i=0;i<population.size();i++)
    {

        if(population[i].is_dead==false)
        {

            if(population[i].is_positive)
                infected++;
            totl++;
        }
    }
    cout<<"totl no of infected persons are    "<<infected<<endl;
    double per=(double)infected/totl;
    return per;
}
void solve()
{
    lli a,b,c,d,i,j,k,l;
    cout<<"enter the amount of person in the society"<<endl;
    lli pop_size;
    cin>>pop_size;
    cout<<"Enter the radius of infection"<<endl;
    lli infection_radius;
    cin>>infection_radius;
    cout<<"Enter the infection rate "<<endl;
  lli  infection_rate;
  cin>>infection_rate;
  cout<<"Enter the currently infected people"<<endl;
  lli cur_infected;
  cin>>cur_infected;

  cout<<"Enter the dimension of the society"<<endl;

  lli x_limit,y_limit;
  cin>>x_limit>>y_limit;
  cout<<"Enter the number person moving"<<endl;
  lli movement_number;
  cin>>movement_number;
  cout<<"Enter the response time"<<endl;
  lli response_time;
  cin>>response_time;
  cout<<"Enter the infection mortality rate"<<endl;
  lli mortality_rate;
  cin>>mortality_rate;





  vector<struct person> population(pop_size);
  struct person cur;
  for(i=0;i<pop_size;i++)
  {

      population[i].x=rand()%x_limit;
      population[i].y=rand()%y_limit;
  }
  k=cur_infected;
  while(k)
  {
      j=rand()%pop_size;
      if(population[j].is_positive==false)
      {

          k--;
          population[j].is_positive=true;
          population[j].infection_time=0;
      }
  }

  cout<<"Initialization successfully completed "<<endl;

  for(i=0;i<100;i++)
  {
      movement(population,x_limit,y_limit,movement_number);

      infection_spread(population,mortality_rate, response_time,i,infection_rate,infection_radius);


      cout<<"infection percent at "<<i<<"th day  "<<percent_infected_persons(population)<<endl;

      cout<<"=============================================="<<endl<<endl;
  }

lli totl_dead=0, totl_immune=0, totl_non_immune=0;

for(i=0;i<population.size();i++)
{

    if(population[i].is_dead==true)
        totl_dead++;
    else if(population[i].is_immune==true)
        totl_immune++;
    else if(population[i].is_immune==false)
        totl_non_immune++;
}

cout<<"Total no of dead persons"<<"-->>"<<totl_dead<<endl;
cout<<"Total no of immune persons"<<"-->>"<<totl_immune<<endl;
cout<<"Total no of non_immune persons"<<"-->>"<<totl_non_immune<<endl;


}
int main()
{

    lli a=1;

//cin>>a;
    while(a--)
        solve();

}
