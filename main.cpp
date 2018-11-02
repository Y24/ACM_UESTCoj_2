#include<iostream>
#include<vector>
using namespace std;
enum color{WHITE,RED,BLACK};
struct city{
    color flag;//the flag of belong 
    int id; 
    vector<int> boundary;//the directly connected cities(id refrences)
    city(){
        flag=WHITE;
        id = 0;
        boundary.clear();
    }
    city(color flag,int id){
        this->flag=flag;
        this->id=id;
        boundary.clear();
    }
};
class cities{
    private:
    vector<city> inter;
    city* allcities;
    int size;
    int** roads;
    int roads_sum;
    int**  belongs;
    int belongs_sum;
    void init_cities(){
         inter.resize(size);
        for(int i=0;i<size;i++){
            allcities[i].id=i;
        }
          for(int i=0;i<belongs_sum;i++){
              if(belongs[i][1]==1) allcities[belongs[i][0]].flag=BLACK;
              else allcities[belongs[i][0]].flag=RED;
          }
          for(int i=0;i<roads_sum;i++){
              allcities[roads[i][0]].boundary.push_back(roads[i][1]);
              allcities[roads[i][1]].boundary.push_back(roads[i][0]);
          }
          for(int i=0;i<size;i++)
            inter.push_back(allcities[i]);

            
    }
    public:
    cities(){}
    cities(int size,int** roads,int roads_sum,int** belongs,int belongs_sum){
        this->size=size;
        this->roads=roads;
        this->belongs=belongs;
        this->roads_sum=roads_sum;
        this->belongs_sum=belongs_sum;
        allcities = new city[size];
        init_cities();
    }
    ~cities(){
        for(int j=0;j<roads_sum;j++)
         delete[] roads[j];
        for(int j=0;j<belongs_sum;j++)
        delete[] belongs[j];
        delete[] roads;
        delete[] belongs;
        delete[] allcities;
    }
    city find_city_by_id(int id) const{
    for(auto i:inter)
        if(i.id==id)
        return i;
}
    int getSize() const{
        return size;
    }
};

class kingdom{
    private: 
    bool belong;
    int size;
    vector<city> inter;
    vector<city> boundary;
    public:
    kingdom(){
        this->size=0;
        this->inter.clear();
        this->boundary.clear();
    }
    kingdom(city c,const cities grobal){
        this->size=1;
        this->inter.push_back(c);
        this->belong= c.flag==BLACK;
        for(int i=0;i<c.boundary.size();i++)
        this->boundary.push_back(grobal.find_city_by_id(c.boundary[i]));
    }
     bool can_increase(){
        for(auto i:boundary)
          if(i.flag==belong?BLACK:RED)
           return true;
        return false;
    }
   
     void increase(const cities grobal){
        for(int i=0;i<boundary.size();i++)
        invade_one(boundary[i],i,grobal,this->belong?BLACK:RED);
         
    }
    void invade_one(city c,int position,const cities grobal,color flag){
         if(c.flag==flag){
              this->inter.push_back(c);
              this->size++;
              this->boundary.erase(boundary.begin()-1+position);
              for(auto i:c.boundary)
                if(grobal.find_city_by_id(i).id!=boundary[i].id)
                 this->boundary.push_back(grobal.find_city_by_id(i));
          }
    }
    bool getBelong() const{
        return belong;
    }
    void changeBelong(){
        this->belong = !this->belong;
    }
    int getSize() const{
        return size;
    }
    const vector<city>& getInter(){
        return inter;
    }
    const vector<city>& getBoundary(){
        return boundary;
    }
};
class kingdoms{
    private:
    vector<kingdom> inter;
    public:
    kingdoms(){
        inter.clear();
    }
    void addnew(kingdom k){
        inter.push_back(k);
    }
    void delete_one(int position){
        inter.erase(inter.begin()-1+position);
    }
    bool isEmpty(){
        return inter.size()==0;
    }
    int getSize() const{
        return inter.size();
    }
};
class Game{
    private:
    cities grobal;
    vector<city> white_cities;
    kingdoms bK;
    kingdoms rK;
    color winner;
    int final[2];
    string result;
    void add_white(city c){
       white_cities.push_back(c);

    }
    void form_kindom(){
        bool* processed =new bool[grobal.getSize()];
        for(int i=0;i<grobal.getSize();i++)
         processed[i]= grobal.find_city_by_id(i).flag==WHITE;
        for(int i=0;i<grobal.getSize();i++){
            city c=grobal.find_city_by_id[i];
            if(!processed[i]){
                kingdom k(c,this->grobal);
                while(k.can_increase())
                 k.increase(this->grobal);
                for(auto j: k.getInter()){
                    processed[j.id]==true;
                }
                if(k.getBelong())
                  this->bK.addnew(k);
                else this->rK.addnew(k);
            }
        }
    }
    bool has_white_cities() const{
        return white_cities.size()!=0;
    }
    void invade_per_second(){

    }
    bool game_over() const{

    }
    void attack_per_second(){

    }
    const string& result_record() const{
            
        }
    public:
    Game(cities& grobal){
        this->grobal=grobal;
        this->white_cities.clear();
        this->winner=WHITE;
        for(int i=0;i<grobal.getSize();i++){
            if(grobal.find_city_by_id(i).flag==WHITE)
              (this->white_cities).push_back(grobal.find_city_by_id(i));
        }
    }
    void first_stage(){
        form_kindom();
        while(has_white_cities())
        invade_per_second();
    }
    void second_stage(){
        while(!game_over())
        attack_per_second();
    }
    
};
int main(){
    int test_sum;
    cin>>test_sum;
    string* result=new string[test_sum];
    for(int i=0;i<test_sum;i++){
        int size,roads_sum, belongs_sum;
        int** roads;
        int** belongs;
        init(&size,&roads_sum,&belongs_sum,roads,belongs);      
      cities global=cities(size,roads,roads_sum,belongs,belongs_sum);
      result_output(test_sum,result);
      delete[] result;
    }
   
    return 0;
}
void init(int* size,int* roads_sum,int* belongs_sum,int** roads,int** belongs){
    cin>>*size>>*roads_sum;
    roads=new int*[*roads_sum];
    for(int j=0;j<*roads_sum;j++)
     roads[j] = new int[2];
    for(int j=0;j<*roads_sum;j++)
     cin>>roads[j][0]>>roads[j][1];
     cin>>*belongs_sum;
     belongs=new int*[*belongs_sum];
     for(int j=0;j<*belongs_sum;j++)
      belongs[j]=new int [2];
     for(int j=0;j<*belongs_sum;j++)
      cin>>belongs[j][0]>>belongs[j][1];
}
void result_output(int test_sum,const string* result){
     for(int i=0;i<test_sum;i++)
      cout<<result[i]<<endl;
}