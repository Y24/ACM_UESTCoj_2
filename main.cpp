#include<iostream>
#include<vector>
using namespace std;
struct city{
    int flag;//the flag of belong : red:0;black:1;white:-1;
    int id; 
    vector<int> boundary;//the directly connected cities(id refrences)
    city(int flag,int id){
        this->flag=flag;
        this->id=id;
    }
};
struct cities{
    vector<city> inter;
    city find_city_by_id(int id){
    for(auto i:inter)
        if(i.id==id)
        return i;
}
};

class kingdom{
    private: 
    bool belong;
    int size;
    vector<city> inter;
    vector<city> boundary;
    public:
    kingdom(vector<city>& array,vector<city>& boundary){
      for(int i=0;i<array.size;i++)
          if(belong)this->inter.push_back(array[i]);
        for(int i=0;i<boundary.size;i++)
          this->boundary.push_back(boundary[i]);
    }
    bool getBelong() const{
        return belong;
    }
    void setBelong(bool belong){
        this->belong=belong;
    }
    int getSize() const{
        return size;
    }
    void setSize(int size){
        this->size=size;
    }
    vector<city>& getBoundary(){
        return boundary;
    }
    void addBoundary(city a){
        this->boundary.push_back(a);
    }
};
class kingdoms{
    private:
    vector<kingdom> inter;
};
int main(){
    return 0;
}