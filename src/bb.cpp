#include "tsmp.cpp"


double min_graph[N][N];
double max_value = inf;
std::vector<pile_elem> ordered_pile;

void ordered_insert(pile_elem ins){
    for(auto it = ordered_pile.begin(); it != ordered_pile.end(); it++){
        if(ins.reduced_value > it->reduced_value){
            ordered_pile.insert(it, ins);
            return;
        }
    }
    ordered_pile.push_back(ins);
}

void reduce_graph(pile_elem &ins){
    int i, j;
    double min;
    for(i = 0; i < N; i++){
        min = inf;
        for(j = 0; j < N; j++){
            if(ins.graph[i][j] < min) min = ins.graph[i][j];
        }
        if(min == inf) continue;
        for(j = 0; j < N; j++) {
            if(ins.graph[i][j] != inf) ins.graph[i][j] = ins.graph[i][j] - min;
            else ins.graph[i][j] = inf;  
        }
        ins.reduced_value += min;
    }
    for(j = 0; j < N; j++){
        min = inf;
        for(i = 0; i < N; i++){
            if(ins.graph[i][j] < min) min = ins.graph[i][j];
        }
        if(min == inf) continue;
        for(i = 0; i < N; i++) {
            if(ins.graph[i][j] != inf) ins.graph[i][j] = ins.graph[i][j] - min;
            else ins.graph[i][j] = inf;  
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
    std::cout<<'\n';
}

void branch_entry(pile_elem node){
    pile_elem working;
    for(int i = 0; i < N; i++){
        if(node.unvisited[i] == -1) continue;
        working = pile_elem(node, i);
        reduce_graph(working);
        // print_graph(working.graph);
        // // std::cout<<working.reduced_value<<'\n';
        // // return;
        if(working.reduced_value >= max_value) return;
        if(working.is_empty()){
            max_value = working.reduced_value;
        }else{
            ordered_insert(working);
            return;
        }
    }
}

void start(int starting_point){
    int cities[N];
    for(int i = 0; i < N; i++) {
        if(i != starting_point) cities[i] = i;
        else cities[i] = -1;
    }
    pile_elem first(route_graph, cities, starting_point), work_elem;
    reduce_graph(first);
    ordered_pile.push_back(first);
    while(!ordered_pile.empty()){
        work_elem = ordered_pile.back();
        ordered_pile.pop_back();
        branch_entry(work_elem);
    }
}

int main(int argc, char **argv){
    start(0);
    std::cout<<max_value<<'\n';
    // ordered_insert(pile_elem(10));
    // ordered_insert(pile_elem(50));
    // ordered_insert(pile_elem(30));
    // ordered_insert(pile_elem(45));
    // ordered_insert(pile_elem(80));
    // ordered_insert(pile_elem(20));
    // for(auto it:ordered_pile){
    //     std::cout<<it.reduced_value<<'\n';
    // }
}