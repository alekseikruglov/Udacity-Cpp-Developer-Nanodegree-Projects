#include "route_planner.h"
#include <algorithm>
#include <iostream>


RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    RoutePlanner::start_node = &m_Model.FindClosestNode(start_x, start_y);  
    RoutePlanner::end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    //h = |x2-x1|+|y2-y1|
    //Pointer -> first dereference!
    return RoutePlanner::end_node->distance(*node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    
    //-> used to access fields of object with its pointer
    current_node->visited = true;
    current_node->FindNeighbors();

    //go through all neighbors 
    for (auto & theNode : current_node->neighbors) 
    {
        //if theNode is not already visited - add to open_list
       // if(theNode->visited == false)
        //{
            //set the parrent node of each neighbour-node to current_node
            theNode->parent = current_node;
            //set h_value
            theNode->h_value = CalculateHValue(theNode);
            //set g_value
            theNode->g_value = RoutePlanner::distance + current_node->distance(*theNode);
                    
            //set the node's visited attribute to true
            theNode->visited = true;

            //add the neighbor to open_list
            RoutePlanner::open_list.push_back(theNode);
       // }
        
        
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.


 // Compare the F values of two cells.
bool Compare(const RouteModel::Node* a, const RouteModel::Node* b) {
  return (a->g_value+a->h_value) > (b->g_value+b->h_value);
}

RouteModel::Node *RoutePlanner::NextNode() {

    std::sort(RoutePlanner::open_list.begin(), RoutePlanner::open_list.end(), Compare);

    RouteModel::Node *lowestFNode = RoutePlanner::open_list.back();
    distance = lowestFNode->g_value;    //save the distance here (not direct distance between two points, but sum of all steps-length)

    RoutePlanner::open_list.pop_back(); 

    return lowestFNode;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.
    //RouteModel::Node *theNode;
    while(true)
    {
        path_found.push_back(*current_node);
        if(current_node == start_node)
        {
            break;
        }

        distance = distance + current_node->distance(*current_node->parent);
        
        current_node = current_node->parent;

        
    }

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.

    std::reverse(path_found.begin(),path_found.end()); 
    return path_found;
 
}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.
    RoutePlanner::m_Model.path = {};

    current_node = RoutePlanner::start_node;
    open_list.push_back(current_node);

    while(open_list.size() > 0)
    {
        

        if((current_node->x == end_node->x) && (current_node->y == end_node->y))
        {
            //now current_node is end_node!
            break;
        }

        
        AddNeighbors(current_node);
        
        current_node = NextNode();
              
    }

    RoutePlanner::m_Model.path = ConstructFinalPath(current_node);
}
