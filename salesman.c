#include <stdio.h>

// 4 Cities: 0=Mumbai, 1=Delhi, 2=Bengaluru, 3=Chennai
int matrix[4][4] = {
    {0, 1400, 980, 1330},
    {1400, 0, 2150, 2200},
    {980, 2150, 0, 350},
    {1330, 2200, 350, 0}
};

int visited[4] = {0, 0, 0, 0};
int final_ans = 999999; // Start with a very high cost

void tsp(int current_city, int count, int current_cost) {

    // 1. BASE CASE: If we have visited all 4 cities AND can return to start
    if (count == 4 && matrix[current_city][0] > 0) {
        int total_cost = current_cost + matrix[current_city][0];
        
        // Print the path cost found
        printf("Path found! Total Cost: %d km\n", total_cost);

        // Update minimum if this path is cheaper
        if (total_cost < final_ans) {
            final_ans = total_cost;
        }
        return;
    }

    // 2. RECURSIVE STEP: Try to go to every other city
    for (int i = 0; i < 4; i++) {
        // If city 'i' is not visited and a road exists
        if (visited[i] == 0 && matrix[current_city][i] > 0) {
            
            visited[i] = 1; // Mark as visited
            
            // Go to the next city (Recursion)
            tsp(i, count + 1, current_cost + matrix[current_city][i]);
            
            visited[i] = 0; // BACKTRACK: Unmark to allow other paths
        }
    }
}

int main() {
    // Start at Mumbai (0)
    visited[0] = 1; 
    
    printf("--- Calculating Paths ---\n");
    tsp(0, 1, 0); 
    
    printf("-------------------------\n");
    printf("Minimum Cost: %d km\n", final_ans);
    
    return 0;
}