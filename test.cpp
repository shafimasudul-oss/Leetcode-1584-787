class Solution(object):
    def minCostConnectPoints(self, points):
        
        n = len(points)  # number of points
        parent = list(range(n))  # each node starts as its own parent i.e. its own component

        def find(x):
            if parent[x] != x:  # if x is not its own root
                parent[x] = find(parent[x])  # path compression, flatten the tree
            return parent[x]  # return the root

        def union(x, y):
            px, py = find(x), find(y)  # find the root of each node's component
            if px == py:        # same root = already in the same component
                return False    # adding this edge would create a cycle, skip it
            parent[px] = py     # different roots = safe to merge, point px's root to py
            return True         # edge was successfully added

        # generate all pairs of points, compute manhattan distance, sort cheapest first
        edges = sorted(
            (abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]), i, j)
            for i in range(n)           # loop over every point
            for j in range(i + 1, n)   # only look at pairs ahead to avoid duplicates
        )

        total, count = 0, 0  # total cost and number of edges added so far

        for dist, u, v in edges:  # go through edges cheapest first
            if union(u, v):       # if safe to add (no cycle)
                total += dist     # add cost to total
                count += 1        # increment edge count
                if count == n - 1:  # n-1 edges = complete spanning tree
                    break           # done, stop early

        return total  # minimum cost to connect all points


class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int big = 100000; //constraint

        vector<int> price(n, big); //price ranging vector
        price[src] = 0; // starting price

        for (int i = 0; i <= k; i++) { //loop for each stop k
            vector<int> temp = price; //updates the vector of temp for each price for each stop

            for (int j = 0; j < flights.size(); j++) { //loop for each flight
                int from = flights[j][0]; //starting node
                int to = flights[j][1]; //ending node
                int cost = flights[j][2]; //cost from start to end

                if (price[from] != big) { //uses this flight if the starting node is a path to ending node 
                    int newPrice = price[from] + cost; //updating newprice if reachable

                    if (newPrice < temp[to]) { //finds the new apth and compares to the updated newprice
                        temp[to] = newPrice;
                    }
                }
            }

            price = temp; //saves price for that given stop
        }

        if (price[dst] == big) {
            return -1; //unreachable
        }

        return price[dst]; //gives total cost
    }
};
