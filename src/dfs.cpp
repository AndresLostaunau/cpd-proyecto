#include "tsmp.cpp"

using namespace std;

class graph{
    public:
        vector<path> cities;
        vector<int> order;
        graph();
        void DFS(int index);
        int closest_city(path city);
        void print_route();

};

graph::graph(){
    for(int i = 0; i < N; i++){
        path temp_obj(i);
        cities.push_back(temp_obj);
    }
}


void graph::DFS(int index){
    if(!cities[index].visited){
        cities[index].visited = true;
        order.push_back(index);
        int adjacent_city = closest_city(cities[index]);
        DFS(adjacent_city);
    }
    else{
        for(int i = 0; i < N; i++){
            if(!this->cities[i].visited)
                DFS(i);
        }
    }
}

int graph::closest_city(path city){
    int index_closest_city = 0;
    for(int i = 0; i < N; i++){
        if(city.route[index_closest_city] >= city.route[i])
            index_closest_city = i;
    }
    return index_closest_city;
}

void graph::print_route(){
    vector<int>::iterator it;
    for(it = order.begin(); it != order.end(); it++)
        cout << *it << " ";
}

int main(){
    graph g;
    g.DFS(0);
    g.print_route();
    double sum = 0;
    std::cout<<'\n';
    for(int i = 0; i < N; i++){
        std::cout<<g.order[i]<<"->"<<g.order[i+1]<<": "<<route_graph[g.order[i]][g.order[i+1]]<<'\n';
        sum+=route_graph[g.order[i]][g.order[i+1]];
    }
    std::cout<<'\n'<<sum<<'\n';
    return 0;
}