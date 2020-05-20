#ifndef A_H
#define A_H
#include<algorithm>
#include<set>
#include <random>
#include <iterator>
#include <iostream>
#include<vector>
#include<cmath>
#include<cstring>
#include<time.h>
#include <QDir>
#include <QDebug>
#include <string>
using namespace std;
typedef long long ll;
const int m=10,n=100,GEN=2000;
int Inittime,Matchesperday,Whatday,Interval;
int Group;
int Contestant;
const double CROSS_RATE = 0.8;
const double MUTATE_RATE = 0.2;
const double PI = acos(-1);
const double eta = 20;//η
mt19937 mrand(random_device{}());
double alpha=0.3;
///                                  0     1    2   3   4   5   6   7   8    9  10  11  12  13  14  15  16  17  18  19  20  21  22  23
double WatchingRateWeekday[24]={0.0928,0.0166,0.0166,0.0166,0.0166,0.0166,0.0166,0.0166,0.0265,0.0265,0.0265,0.0265,0.0530,0.0530,0.0530,0.0530,0.0563,0.0563,0.2502,0.2502,0.2502,0.2502,0.2502,0.0928};
double WatchingRateWeekend[24]={0.1471,0.0436,0.0436,0.0436,0.0436,0.0436,0.0436,0.0436,0.0545,0.0545,0.0545,0.0545,0.1635,0.1635,0.1635,0.1635,0.1935,0.1935,0.3788,0.3788,0.3788,0.3788,0.3788,0.1471};
struct Team{
    char s[100];
    int TimeDiff;//与主办地的时差
    ll FanNum;//粉丝数
}team[888];
int las[888];
int mp[888][888];
double Exp[120001];
const int maxsz=1999523;
vector<pair<double,double>>dai;
#define rep(ii,a,b) for(int ii=a;ii<=b;++ii)
template<typename key,typename val>
class hash_map{public:
  struct node{
      key u;val v;int next;
      node(key U,val V,int Next) { u=U,v=V,next=Next;}
      node(void){}
  };
  vector<node> e;
  int head[maxsz],nume,numk,id[maxsz];
  bool count(key u){
    int hs=u%maxsz;
    for(int i=head[hs];i;i=e[i].next)
          if(e[i].u==u) return 1;
        return 0;
    }
    val& operator[](key u){
        int hs=u%maxsz;
        for(int i=head[hs];i;i=e[i].next)
        if(e[i].u==u) return e[i].v;
        if(!head[hs])id[++numk]=hs;
        if(++nume>=e.size())e.resize(nume<<1);
        return e[nume]=node(u,0,head[hs]),head[hs]=nume,e[nume].v;
    }
    void clear(){
        rep(i,0,numk)head[id[i]]=0;
        numk=nume=0;
    }
};
hash_map<int,bool>vis;
double solve(int Day,int Time,int id) {
    Time+=team[id].TimeDiff;
    if(Time<0) {
        Time+=24;
        Day--;
        if(Day==0) Day=7;
    }
    if(Time>=24) {
        Time-=24;
        Day++;
        if(Day>7) Day-=7;
    }
    if(Day>=6) return (WatchingRateWeekend[Time]+0.1)*team[id].FanNum;
    else return (0.05+WatchingRateWeekday[Time])*team[id].FanNum;
}
double cal(double dis,double avg) {
    dis=min(dis,avg);
    return Exp[(int)((avg-dis)/avg*100000)]-Exp[0];
}
int fgmx=0;
double gtmx=0;
double getmx() {
    if(fgmx) return gtmx;
    double sum=0,avg=Contestant/2;
    vector<pair<int,int>>arrange;
    for(int i=0;i<Group;i++) {
        int st=i*(Contestant/Group)+1;
        int ed=(i+1)*(Contestant/Group);
        for(int j=st;j<=ed;j++) {
            for(int k=j+1;k<=ed;k++) {
                arrange.push_back({j,k});
                arrange.push_back({k,j});
            }
        }
    }
    memset(las,-1,sizeof las);
    for(int i=0;i<arrange.size();i++) {
        if(las[arrange[i].first]!=-1)  sum+=cal((i-las[arrange[i].first]),avg);
        if(las[arrange[i].second]!=-1) sum+=cal((i-las[arrange[i].second]),avg);
        las[arrange[i].first]=i;
        las[arrange[i].second]=i;
        mp[arrange[i].first][arrange[i].second]=i;
    }
    for(int k=0;k<Group;k++) {
        int st=k*(Contestant/Group)+1;
        int ed=(k+1)*(Contestant/Group);
        for(int i=st;i<=ed;i++) {
            for(int j=i+1;j<=ed;j++) {
                sum+=cal(fabs(mp[i][j]-mp[j][i]),(Contestant*(Contestant/Group-1)/2))*2;
            }
        }
    }
    fgmx=1;
    gtmx=sum;
    return sum;
}
double get(vector<pair<int,int>>&arrange,double alpha) {
    double x1=1,avg=Contestant/2,x2=0;
    double sum=getmx();
    //cout<<sum<<endl;
    memset(las,-1,sizeof las);
    for(int i=0;i<arrange.size();i++) {
        if(las[arrange[i].first]!=-1) x1+=cal((i-las[arrange[i].first]),avg);
        if(las[arrange[i].second]!=-1) x1+=cal((i-las[arrange[i].second]),avg);
        las[arrange[i].first]=i;
        las[arrange[i].second]=i;
        mp[arrange[i].first][arrange[i].second]=i;
    }
    for(int k=0;k<Group;k++) {
        int st=k*(Contestant/Group)+1;
        int ed=(k+1)*(Contestant/Group);
        for(int i=st;i<=ed;i++) {
            for(int j=i+1;j<=ed;j++) {
                x1+=cal(fabs(mp[i][j]-mp[j][i]),(Contestant*(Contestant/Group-1)/2))*2;
            }
        }
    }
    double FanSum=0;
    for(int i=1;i<=Contestant;i++) FanSum+=team[i].FanNum*(Contestant/Group-1)*2;
    int Day=Whatday,Time=Inittime,Already=0;
    double Watching=0;
    for(int i=0;i<arrange.size();i++) {
        Already++;
        Watching+=solve(Day,Time/2,arrange[i].first);
        Watching+=solve(Day,Time/2,arrange[i].second);
        Time+=Interval;
        if(Already==Matchesperday) {
            Already=0;
            Time=Inittime;
            Day++;
            if(Day>7) Day-=7;
        }
    }
    //printf("%Lf\n",Watching);
    double f1=x1/sum;//混乱程度,越小越好
    double f2=1-Watching/FanSum/0.4;
    return alpha*f1+(1-alpha)*f2;
}
struct Arrangement {
    vector<pair<int,int>>arrange;
    double g,f[4];
    int rak,fck;
    double L,HAHAH;
    void build(int fg) {
        arrange.clear();
        for(int i=0;i<Group;i++) {
            int st=i*(Contestant/Group)+1;
            int ed=(i+1)*(Contestant/Group);
            for(int j=st;j<=ed;j++) {
                for(int k=j+1;k<=ed;k++) {
                    arrange.push_back({j,k});
                    arrange.push_back({k,j});
                }
            }
        }
        random_shuffle(arrange.begin(),arrange.end());
        //if(fg) {
            for(int i=0;i<arrange.size();i++) {
                for(int j=i+1;j<arrange.size();j++) {
                    int Dayi=Whatday+i/Matchesperday;
                    while(Dayi>7) Dayi-=7;
                    int Timei=Inittime+i%Matchesperday*Interval;
                    int Dayj=Whatday+j/Matchesperday;
                    while(Dayj>7) Dayj-=7;
                    int Timej=Inittime+j%Matchesperday*Interval;
                    double before=
                    solve(Dayi,Timei/2,arrange[i].first)+
                    solve(Dayi,Timei/2,arrange[i].second)+
                    solve(Dayj,Timej/2,arrange[j].first)+
                    solve(Dayj,Timej/2,arrange[j].second);
                    double after=
                    solve(Dayi,Timei/2,arrange[j].first)+
                    solve(Dayi,Timei/2,arrange[j].second)+
                    solve(Dayj,Timej/2,arrange[i].first)+
                    solve(Dayj,Timej/2,arrange[i].second);
                    set<int>s;
                    s.insert(arrange[j].first);
                    s.insert(arrange[j].second);
                    s.insert(arrange[i].first);
                    s.insert(arrange[i].second);
                    if(after>before&&s.size()==4) {
                        //swap(arrange[i],arrange[j]);
                        goto loop;
                    }
                }
            }
        loop:;
        //}
        init();
    }
    void init() {
        double tmp=0;
        rak=0;
        fck=0;
        L=0;
        get();
    }
    void get() {
        double x1=1,avg=Contestant/2,x2=0;
        double sum=getmx();
        //cout<<sum<<endl;
        memset(las,-1,sizeof las);
        for(int i=0;i<arrange.size();i++) {
            if(las[arrange[i].first]!=-1) x1+=cal((i-las[arrange[i].first]),avg);
            if(las[arrange[i].second]!=-1) x1+=cal((i-las[arrange[i].second]),avg);
            las[arrange[i].first]=i;
            las[arrange[i].second]=i;
            mp[arrange[i].first][arrange[i].second]=i;
        }
        for(int k=0;k<Group;k++) {
            int st=k*(Contestant/Group)+1;
            int ed=(k+1)*(Contestant/Group);
            for(int i=st;i<=ed;i++) {
                for(int j=i+1;j<=ed;j++) {
                    if(mp[i][j]!=-1) x1+=cal(fabs(mp[i][j]-mp[j][i]),(Contestant*(Contestant/Group-1)/2))*2;
                }
            }
        }
        double FanSum=0;
        for(int i=1;i<=Contestant;i++) FanSum+=team[i].FanNum*(Contestant/Group-1)*2;
        int Day=Whatday,Time=Inittime,Already=0;
        double Watching=0;
        for(int i=0;i<arrange.size();i++) {
            Already++;
            Watching+=solve(Day,Time/2,arrange[i].first);
            Watching+=solve(Day,Time/2,arrange[i].second);
            Time+=Interval;
            if(Already==Matchesperday) {
                Already=0;
                Time=Inittime;
                Day++;
                if(Day>7) Day-=7;
            }
        }
        //printf("%Lf\n",Watching);
        f[1]=x1/sum;//混乱程度,越小越好
        f[2]=1-Watching/FanSum/0.4;
        //fit=alpha*1/(1-x2)+(1-alpha)*(1/x1);
        HAHAH=Watching;
    }
    Arrangement& operator=(const Arrangement& d) {
        arrange=d.arrange;
        memcpy(f,d.f,sizeof f);
        L=d.L;
        rak=d.rak;
        fck=d.fck;
        g=d.g;
        return *this;
    }
}a[6*n+2],mom,dad;
vector<int>v[6*n+2];
int sz;
vector<int>s[6*n+2];
set<int> all;
vector<Arrangement>fa,son;
double rnd() {return mrand()%1000000*1.0/1000000;}
bool cmp(Arrangement& a,Arrangement& b) {
    int fg=0;
    if(a.f[1]<b.f[1]||a.f[2]<b.f[2]) fg=1;
    if(a.f[1]<=b.f[1]&&a.f[2]<=b.f[2]&&fg) return 1;
    return 0;
}
void quickget2() {
    for(int i=0;i<=son.size();i++) s[i].clear(),v[i].clear();
    for(int i=0;i<son.size();i++) son[i].fck=0;
    all.clear();
    for(int i=0;i<son.size();i++) {
        for(int j=0;j<son.size();j++)
            if(i!=j)
                if(cmp(son[i],son[j])) {
                    s[i].emplace_back(j);
                }else if(cmp(son[j],son[i])) son[i].fck++;
        if(son[i].fck==0) {
            all.insert(i);
        }
    }
    sz=0;
    set<int>tmp;
    while(all.size()) {
        sz++;
        tmp.clear();
        for(auto i=all.begin();i!=all.end();i++) {
            int id=*i;
            v[sz].push_back(id);
            son[id].rak=sz;
            for(auto j:s[id]) {
                son[j].fck--;
                if(son[j].fck==0)
                    tmp.insert(j);
            }
        }
        all=tmp;
    }
}

void crowded2() {
    for(int i=0;i<son.size();i++) son[i].L=0;
    for(int level=1;level<=sz;level++) {
        for(int k=1;k<=2;k++) {
            sort(v[level].begin(),v[level].end(), [k] (int i, int j) {
                return son[i].f[k]<son[j].f[k];
            });
            son[v[level][0]].L=son[v[level][v[level].size()-1]].L=0xffffff;
            double mn=0xffffff,mx=-0xffffff;
            for(auto i:v[level]) {
                mn=min(son[i].f[k],mn);
                mx=max(son[i].f[k],mx);
            }
            for(int i=1;i<v[level].size()-1;i++) {
                int pre=v[level][i-1];
                int now=v[level][i];
                int nex=v[level][i+1];
                son[now].L+=(son[nex].f[k]-son[pre].f[k])/(mx-mn);
                //printf("pre:%f nex:%f\n",son[pre].f[k],son[nex].f[k]);
            }
        }
    }
}
bool cmp2(Arrangement &a,Arrangement &b) {
    if(a.rak<b.rak||(a.rak==b.rak&&a.L>b.L)) return 1;
    //if(a.L>b.L) return 1;
    return 0;
}
double down=0.9999;
vector<pair<int,int>> mutate(vector<pair<int,int>>my) {
    auto a=clock();
    vector<pair<int,int>> tmp;
    double AP=0.3;
    double teampture=10000;
    double presum=get(my,AP);
    //printf("Before:%f\n",get(my,AP));
    while(teampture>1e-14) {
        tmp=my;
        int idx1=mrand()%tmp.size();
        int idx2=mrand()%tmp.size();
        while(idx2==idx1) idx2=mrand()%tmp.size();
        swap(tmp[idx1],tmp[idx2]);
        double pre=presum;
        double now=get(tmp,AP);//越小越好
        double e=exp(fabs(pre-now)/teampture);
        if(now<pre||1.0/(1+e)>mrand()%100000*1.0/100000) {
            my=tmp;
            presum=now;
        }
        teampture*=down;
    }
    //printf("After:%f time:%d\n",get(my,AP),clock()-a);
    return my;
}
int h=1,fg=0;bool VIS[660];
void makeson() {
    fa.clear();
    son.clear();
    memset(VIS,0,sizeof VIS);
    int cnt=0;
    while(cnt<n/2) {
        cnt++;
        int id1=mrand()%n+1;
        int id2=id1;
        while(VIS[id1]) id1=id2=mrand()%n+1;
        while(id1==id2||VIS[id2]) {
            id2=mrand()%n+1;
        }
        if(!cmp2(a[id1],a[id2])) id1=id2;
        VIS[id1]=1;
        fa.push_back(a[id1]);
        //printf("%d\n",a[id1].arrange.size());
    }
    cnt=0;int tot=0;
    for(;cnt<n;) {
        tot++;
        double kk=rnd();
        if(kk<CROSS_RATE) {
            Arrangement son1;
            int id1=mrand()%(fa.size());
            int id2=mrand()%(fa.size());
            dad=fa[id1];
            mom=fa[id2];
            vis.clear();
            son1.arrange.clear();
            son1.arrange.resize(Contestant*(Contestant/Group-1));
            int tim=Contestant*(Contestant/Group-1)/2;
            while(tim--) {
                int ch=mrand()%(Contestant*(Contestant/Group-1));
                while(vis[dad.arrange[ch].first*10000+dad.arrange[ch].second]) {
                    ch=mrand()%(Contestant*(Contestant/Group-1));
                }
                son1.arrange[ch]=dad.arrange[ch];
                vis[son1.arrange[ch].first*10000+son1.arrange[ch].second]=1;
            }
            int pos=0;
            for(auto k:mom.arrange) {
                if(vis[k.first*10000+k.second]) continue;
                while(vis[son1.arrange[pos].first*10000+son1.arrange[pos].second]) pos++;
                son1.arrange[pos]=k;
                vis[son1.arrange[pos].first*10000+son1.arrange[pos].second]=1;
            }
            son1.init();
            cnt++;
            son.push_back(son1);
        }else if(kk-CROSS_RATE<=MUTATE_RATE) {
            dad=fa[mrand()%fa.size()];
            cnt++;
            int idx1=mrand()%(dad.arrange.size());
            int idx2=mrand()%(dad.arrange.size());
            swap(dad.arrange[idx1],dad.arrange[idx2]);
            //puts("SSSS");
            dad.get();

            son.push_back(dad);
        }
        //puts("A");
    }//puts("B");
    for(int i=1;i<=n;i++) son.push_back(a[i]);
}
void compete_selection() {
    quickget2();
    crowded2();
    int tot=0;
    for(int level=1;level<=sz;level++) {
        sort(v[level].begin(),v[level].end(), [] (int i, int j) {
            return son[i].L>son[j].L;
        });
        for(auto i:v[level]) {
            tot++;
            a[tot]=son[i];
            if(tot==n) goto loop;
        }
    }
    loop:;
    makeson();
    double mn1=1e9,mn2=1e9;
    for(int i=1;i<=n;i++) {
        mn1=min(mn1,a[i].f[1]);
        mn2=min(mn2,a[i].f[2]);
    }
    dai.push_back({mn1,mn2});
}

class method {
public:
    static string init(int group,int contestant,int inittime,int matchesperday,int interval,int whatday,string s) {
        string ans="";
        Inittime=inittime;Matchesperday=matchesperday;
        Group=group;Contestant=contestant;
        Interval=interval;Whatday=whatday;
        for(int i=0;i<=110005;i++) {
            Exp[i]=exp(i/100000.0+4);
        }
        string sss = QDir::currentPath().toStdString()+"/1.in";
        freopen(sss.c_str(),"w",stdout);
        cout<<s<<endl;
        freopen(sss.c_str(),"r",stdin);
        for(int i=1;i<=Contestant;i++) scanf("%s %d %lld",team[i].s,&team[i].TimeDiff,&team[i].FanNum);
        for(int i=1;i<=n;i++) {
            a[i].build(0);
        }a[1].arrange=mutate(a[1].arrange);
        a[1].get();
        makeson();
        for(h=1;h<=GEN;h++)
            compete_selection();
        double mn=1e9;
        int ch;
        for(int i=1;i<=n;i++) {
            if(mn>alpha*a[i].f[1]+(1-alpha)*(a[i].f[2])) {
                mn=alpha*a[i].f[1]+(1-alpha)*(a[i].f[2]);
                ch=i;
            }
            //printf("%f %f\n",a[i].f[1],a[i].f[2]);
        }
        int Day=Whatday,Time=Inittime,Already=0;
        double Watching=0;
        vector<int>vv;
        for(int i=0;i<a[ch].arrange.size();i++) {
            Already++;
            double tmp=0;
            tmp+=solve(Day,Time/2,a[ch].arrange[i].first);
            tmp+=solve(Day,Time/2,a[ch].arrange[i].second);
            vv.push_back(tmp);
            Watching+=tmp;
            Time+=Interval;
            if(Already==Matchesperday) {
                Already=0;
                Time=Inittime;
                Day++;
                if(Day>7) Day-=7;
            }
        }
        //printf("%.0f %f\n",Watching,mn);
        ans=to_string((long long)a[ch].HAHAH)+","+to_string((long long)Watching);
        int tttt=0;
        for(auto i:a[ch].arrange) ans+="("+(string)team[i.first].s+","+(string)team[i.second].s+","+to_string(vv[tttt++])+")";
        //cout<<ans<<endl;
        return ans;
    }
};


#endif // A_H
