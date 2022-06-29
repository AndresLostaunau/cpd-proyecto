#include "tsmp.cpp"


double min_graph[N][N];
double max_value = inf;
std::vector<pile_elem> ordered_pile;

void ordered_insert(pile_elem ins){
    for(auto it = ordered_pile.begin(); it != ordered_pile.end(); it++){
        if(ins.reduced_value < it->reduced_value){
            ordered_pile.insert(it, ins);
            return;
        }
    }
    ordered_pile.push_back(ins);
}

void reduce_graph(pile_elem &ins, double graph[N][N]){
    int i, j;
    double min;
    for(i = 0; i < N; i++){
        min = inf;
        for(j = 0; j < N; j++){
            if(graph[i][j] < min){
                min = graph[i][j];
            }
        }
        if(min == inf) continue;
        for(j = 0; j < N; j++) {
            if(graph[i][j] != inf) 
                ins.graph[i][j] = graph[i][j] - min;
            else
                ins.graph[i][j] = inf;  
        }
        ins.reduced_value += min;
    }
    for(j = 0; j < N; j++){
        min = inf;
        for(i = 0; i < N; i++){
            if(graph[i][j] < min){
                min = graph[i][j];
            }
        }
        if(min == inf) continue;
        for(i = 0; i < N; i++) {
            if(graph[i][j] != inf) 
                ins.graph[i][j] = graph[i][j] - min;
            else
                ins.graph[i][j] = inf;  
        }
        ins.reduced_value += min;
    }
}

void print_graph(double graph[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(graph[i][j] == inf) std::cout<<"  inf ";
            else std::cout<<std::setw(5)<<graph[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}

void branch_entry(){
    
}

int main(int argc, char **argv){
    // std::cout<<init_min_graph()<<'\n';
    // print_min_graph();
    // ordered_insert(pile_elem(10));
    // ordered_insert(pile_elem(50));
    // ordered_insert(pile_elem(30));
    // ordered_insert(pile_elem(45));
    // ordered_insert(pile_elem(80));
    // ordered_insert(pile_elem(20));
    // for(auto it:ordered_pile){
    //     std::cout<<it.reduced_value<<'\n';
    // }
    print_graph(route_graph);
}