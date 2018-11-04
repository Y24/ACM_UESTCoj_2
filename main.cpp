//
// Created by root on 11/3/18.
//
/* 1
   6 7 0 1 1 2 2 3 3 4 4 5 2 5 0 5
   3 0 0 2 1 5 1
*/
#include<iostream>
#include<map>
#define DEFAULT_INIT_LENGTH 4
using namespace std;
void result_output(int test_sum, const string *result);
enum color {
    WHITE, RED, BLACK
};
    template<typename T>
    class Array {
    private:
        T *element;
        unsigned length;
        unsigned allocated_size;

        void allocate_double() {
            if(allocated_size!=0)allocated_size *= 2;
            else allocated_size=length+1;
            T *new_location = new T[allocated_size];
            for (int i = 0; i < length - 1; i++)
                new_location[i] = element[i];
            delete[] element;
            element = new_location;
        }

    public:
        Array() {
            length = 0;
            allocated_size = DEFAULT_INIT_LENGTH;
            element = new T[allocated_size];
        }

        ~Array(){
            if(!element)delete[] element;
        };
        T& operator[](unsigned position){
            if(position<length)
            return  element[position];
                while (allocated_size<=position){
                allocate_double();
            }
            length=position+1;
            return element[position];
        }

        void push_back(T t) {
            if (++length > allocated_size) {
                allocate_double();
                element[length - 1] = t;
            } else
                element[length - 1] = t;
        }

        bool remove(unsigned position) {
            if (position > length - 1)
                return false;
            length--;
            for (unsigned i = position; i < length; i++)
                element[i] = element[i + 1];
            return  true;
        }

        bool empty() {
            return length == 0;
        }

        void clear() {
            length = 0;
        }
        int find(T& test){
            for(auto i=0;i<length;i++)
                if(element[i]==test)
                    return i;
            return -1;
        }

        unsigned size() const {
            return length;
        }
        void resize(unsigned size){
            length =size;
            if(allocated_size<=length)
                allocate_double();
        }

    };

struct city {
    color flag;//the flag of belong
    int id;
    Array<int> boundary{}; //the directly connected cities(id refrences)
    city() {
        flag = WHITE;
        id = 0;
        boundary.clear();
    }
};

class cities {
private:
    Array<city> inter;
    unsigned size{};
    int **roads{};
    int roads_sum{};
    int **belongs{};
    int belongs_sum{};

    void init_cities() {
        inter.resize(size);
        for (int i = 0; i < size; i++) {
            inter[i].id = i;
            inter[i].flag=WHITE;
        }
        for (int i = 0; i < belongs_sum; i++) {
            if (belongs[i][1] == 1) inter[belongs[i][0]].flag = BLACK;
            else inter[belongs[i][0]].flag = RED;
        }
        for (int i = 0; i < roads_sum; i++) {
            inter[roads[i][1]].boundary.push_back(roads[i][0]);
            inter[roads[i][0]].boundary.push_back(roads[i][1]);
        }
    }

public:
    cities() = default;

    cities(unsigned size, int **roads, int roads_sum, int **belongs, int belongs_sum) {
        this->size = size;
        this->roads = roads;
        this->belongs = belongs;
        this->roads_sum = roads_sum;
        this->belongs_sum = belongs_sum;
        init_cities();
    }

    ~cities() = default;;

    city &find_city_by_id(int id) {
        for (auto i = 0; i < inter.size(); i++)
            if (inter[i].id == id)
                return inter[i];
        return inter[0];
    }

    void change_color(int id, color c) {
        for (auto i = 0; i < inter.size(); i++)
            if (inter[i].id == id)
                inter[i].flag = c;
    }

    int getSize() const {
        return size;
    }
    Array<city>& getInter(){
        return inter;
    }
};

class kingdom {
private:
    bool belong{};
    Array<int> inter;
    Array<int> boundary;
    Array<int> add_flag;
public:
    kingdom() {
        this->inter.clear();
        this->boundary.clear();
        add_flag.clear();
    }

    kingdom(city &c, cities &grobal) {
        this->inter.clear();
        this->inter.push_back(c.id);
        this->belong = c.flag == BLACK;
        for (int i = 0; i < c.boundary.size(); i++)
            this->boundary.push_back(c.boundary[i]);
    }

    bool boundary_analyze(cities &grobal) {
        add_flag.clear();
        for (int i = 0; i < boundary.size(); i++)
            if (grobal.find_city_by_id(boundary[i]).flag == (belong ? BLACK : RED))
                if (add_flag.find(boundary[i]) == -1)
                    add_flag.push_back(boundary[i]);

        return !add_flag.empty();
    }

//    bool can_increase(cities &grobal) {
//        for (auto i = 0; i < boundary.size(); i++)
//            if (grobal.find_city_by_id(boundary[i]).flag == (belong ? BLACK : RED)) {
//                added_flag = i;
//                return true;
//            }
//        return false;
//    }

    bool isIn(int id, cities &grobal) {
        for (int i = 0; i < inter.size(); i++)
            if (grobal.find_city_by_id(inter[i]).id == id)
                return true;
        for (int i = 0; i < boundary.size(); i++)
            if (grobal.find_city_by_id(boundary[i]).id == id)
                return true;
        return false;
    }

    void boundary_union(city city, cities &cities) {
        for (int i = 0; i < city.boundary.size(); i++)
            if (!isIn(city.boundary[i], cities))
                boundary.push_back(city.boundary[i]);
    }

    void increase(cities &grobal) {
        for (int i = 0; i < add_flag.size(); i++) {
            inter.push_back(add_flag[i]);
            city c = grobal.find_city_by_id(add_flag[i]);
            int position=boundary.find(add_flag[i]);
            if(position!=-1)boundary.remove(static_cast<unsigned int>(position));
            boundary_union(c, grobal);
        }
    }

    bool getBelong() const {
        return belong;
    }

    unsigned size() const {
        return inter.size();
    }

    Array<int> &getInter() {
        return inter;
    }

    Array<int> &getBoundary() {
        return boundary;
    }
};

class kingdoms {
private:
    Array<kingdom> inter;
public:
    kingdoms() {
        inter.clear();
    }

    void addnew(const kingdom &k) {
        inter.push_back(k);
    }

    void clear() {
        inter.clear();
    }

    Array<kingdom> &getInter() {
        return inter;
    }

    unsigned size() {
        unsigned count = 0;
        for (unsigned i = 0; i < inter.size(); i++)
            count += inter[i].size();
        return count;
    }
};

struct competitor {
    Array<int> red_sizes;
    Array<int> black_sizes;
};

class Game {
private:
    cities grobal;
    Array<int> changed_cities;
    map<int, competitor> white_cities;
    kingdoms bK;
    kingdoms rK;
    color winner;
    int final[2]{};
    string result;

    void form_kingdom() {
        bool *processed = new bool[grobal.getSize()];
        this->bK.clear();
        this->rK.clear();
        for (int i = 0; i < grobal.getSize(); i++)
            processed[i] = grobal.find_city_by_id(grobal.getInter()[i].id).flag == WHITE;
        for (int i = 0; i < grobal.getSize(); i++) {
            city c = grobal.find_city_by_id(i);
            if (!processed[i]) {
                kingdom k(c, this->grobal);
                while (k.boundary_analyze(grobal))
                    k.increase(this->grobal);
                for (unsigned j = 0; j < k.getInter().size(); j++) {
                    processed[k.getInter()[j]] = true;
                }
                if (k.getBelong())
                    this->bK.addnew(k);
                else this->rK.addnew(k);
            }
        }
        delete[] processed;
    }

    bool white_analyze() {
        white_cities.clear();
        for (unsigned i = 0; i < bK.getInter().size(); i++) {
            auto boundary = bK.getInter()[i].getBoundary();
            for (unsigned int j = 0; j < boundary.size(); j++)
                if (grobal.find_city_by_id(boundary[j]).flag == WHITE)
                    white_cities[boundary[j]].black_sizes.push_back(bK.getInter()[i].size());

        }
        for (unsigned i = 0; i < rK.getInter().size(); i++) {
            auto boundary = rK.getInter()[i].getBoundary();
            for (unsigned int j = 0; j < boundary.size(); j++)
                if (grobal.find_city_by_id(boundary[j]).flag == WHITE)
                    white_cities[boundary[j]].red_sizes.push_back(rK.getInter()[i].size());

        }
        return !white_cities.empty();
    }

    int Max(Array<int> &com) {
        int max = 0;
        for (auto i = 0; i < com.size(); i++)
            if (com[i] > max)
                max = com[i];
        return max;
    }

    int Sum(Array<int> &com) const {
        int sum = 0;
        for (auto i = 0; i < com.size(); i++)
            sum += com[i];
        return sum;
    }

    color judge(competitor &com) {
        int bmax = Max(com.black_sizes);
        int rmax = Max(com.red_sizes);
        int bsum = Sum(com.black_sizes);
        int rsum = Sum(com.red_sizes);
        int btsum = bK.size();
        int rtsum = rK.size();
        if (bmax != rmax) {
            if (bmax > rmax) return BLACK;
            else return RED;
        } else if (bsum != rsum) {
            if (bsum > rsum) return BLACK;
            else return RED;
        } else if (btsum != rtsum) {
            if (btsum > rtsum) return BLACK;
            else return RED;
        } else return BLACK;
    }

    void invade_per_second() {
        for (auto &i:white_cities) {
            grobal.change_color(i.first, judge(i.second));
        }
    }

    kingdom &find_kingdom_by_id(int id) {
        for (auto i = 0; i < bK.getInter().size(); i++) {
            for (auto j = 0; j < bK.getInter()[i].getInter().size(); j++)
                if (bK.getInter()[i].getInter()[j] == id)
                    return bK.getInter()[i];
        }
        for (auto i = 0; i < rK.getInter().size(); i++) {
            for (auto j = 0; j < rK.getInter()[i].getInter().size(); j++)
                if (rK.getInter()[i].getInter()[j] == id)
                    return rK.getInter()[i];
        }
        return bK.getInter()[0];
    }

    bool game_analyze() {
        changed_cities.clear();
        for (auto i = 0; i < bK.getInter().size(); i++) {
            auto boundary = bK.getInter()[i].getBoundary();
            for (auto j = 0; j < boundary.size(); j++)
                if (grobal.find_city_by_id(boundary[j]).flag == RED) {
                    kingdom k = find_kingdom_by_id(boundary[j]);
                    if (k.size() < bK.getInter()[i].size())
                        for (auto c = 0; c < k.getInter().size(); c++)
                            changed_cities.push_back(k.getInter()[c]);
                }
        }

        for (auto i = 0; i < rK.getInter().size(); i++) {
            auto boundary = rK.getInter()[i].getBoundary();
            for (auto j = 0; j < boundary.size(); j++)
                if (grobal.find_city_by_id(boundary[j]).flag == BLACK) {
                    kingdom k = find_kingdom_by_id(boundary[j]);
                    if (k.size() < rK.getInter()[i].size())
                        for (auto c = 0; c < k.getInter().size(); c++)
                            changed_cities.push_back(k.getInter()[c]);
                }
        }
        return !changed_cities.empty();
    }

    void attack_per_second() {
        for (auto i = 0; i < changed_cities.size(); i++)
            grobal.change_color(changed_cities[i],
                                (grobal.find_city_by_id(changed_cities[i]).flag == BLACK) ? RED : BLACK);
    }

    const string &result_record() {
        switch (winner) {
            case BLACK:
                result = "Black";
                break;
            case RED:
                result = "Red";
                break;
            case WHITE:
                result = to_string(final[0]) + " " + to_string(final[1]);
        }
        return result;
    }

public:
    explicit Game(cities &grobal) {
        this->grobal = grobal;
        this->white_cities.clear();
        this->winner = WHITE;
        white_cities.clear();
        form_kingdom();
    }

    void first_stage() {
        while (white_analyze()) {
            invade_per_second();
            form_kingdom();
        }
    }

    const string &second_stage() {
        while (game_analyze()) {
            attack_per_second();
            form_kingdom();
        }
        if (bK.size() == 0)
            winner = RED;
        else if (rK.size() == 0)
            winner = BLACK;
        else {
            winner = WHITE;
            final[0] = rK.size();
            final[1] = bK.size();
        }
        return result_record();
    }

};

int main() {
    int test_sum;
    cin >> test_sum;
    auto *result = new string[test_sum];
//    auto * size=new unsigned[test_sum];
//    int* roads_sum=new int[test_sum];
//    int* belongs_sum=new int[test_sum];
//    int*** roads=new int**[test_sum];
//    for(int i=0;i<test_sum;i++) {
//        roads[i] = new int *[roads_sum[i]];
//        for (int j = 0; j < roads_sum[test_sum]; j++)
//            roads[i][j]=new int[2];
//    }
//    int*** belongs=new int**[test_sum];
//    for(int i=0;i<test_sum;i++) {
//        belongs[i] = new int *[roads_sum[i]];
//        for (int j = 0; j < belongs_sum[test_sum]; j++)
//            belongs[i][j]=new int[2];
//    }
//
    for (int i = 0; i < test_sum; i++) {
        unsigned size;
        int roads_sum, belongs_sum;
        int **roads = nullptr;
        int **belongs = nullptr;
        cin >> size >> roads_sum;
        roads = new int *[roads_sum];
        for (int j = 0; j < roads_sum; j++)
            roads[j] = new int[2];
        for (int j = 0; j < roads_sum; j++)
            cin >> roads[j][0] >> roads[j][1];
        cin >> belongs_sum;
        belongs = new int *[belongs_sum];
        for (int j = 0; j < belongs_sum; j++)
            belongs[j] = new int[2];
        for (int j = 0; j < belongs_sum; j++)
            cin >> belongs[j][0] >> belongs[j][1];
        cities global = cities(size, roads, roads_sum, belongs, belongs_sum);
        Game game = Game(global);
        game.first_stage();
        result[i] = game.second_stage();
        for (int j = 0; j < roads_sum; j++)
            delete[] roads[j];
        for (int j = 0; j < belongs_sum; j++)
            delete[] belongs[j];
        delete[] roads;
        delete[] belongs;
    }
    result_output(test_sum, result);
    delete[] result;
    return 0;
}

void result_output(int test_sum, const string *result) {
    for (int i = 0; i < test_sum; i++)
        cout << "Case #" << i + 1 << ": " << result[i] << endl;
}
