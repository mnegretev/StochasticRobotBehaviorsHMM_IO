#include "PathCalculator.h"

bool PathCalculator::AStar(nav_msgs::OccupancyGrid& map, nav_msgs::OccupancyGrid& cost_map,
                           geometry_msgs::Pose& start_pose, geometry_msgs::Pose& goal_pose, bool diagonal_paths, nav_msgs::Path& result_path)
{
    std::cout << "PathCalculator.-> Calculating by A* from " << start_pose.position.x << "  ";
    std::cout << start_pose.position.y << "  to " << goal_pose.position.x << "  " << goal_pose.position.y << std::endl;

    int idx_start_x;
    int idx_start_y;
    int idx_goal_x;
    int idx_goal_y;
    idx_start_y = (int)((start_pose.position.y - map.info.origin.position.y)/map.info.resolution);
    idx_start_x = (int)((start_pose.position.x - map.info.origin.position.x)/map.info.resolution);
    idx_goal_y  = (int)((goal_pose.position.y  - map.info.origin.position.y)/map.info.resolution);
    idx_goal_x  = (int)((goal_pose.position.x  - map.info.origin.position.x)/map.info.resolution);
    int idx_start = idx_start_y*map.info.width + idx_start_x;
    int idx_goal  = idx_goal_y *map.info.width + idx_goal_x;

    std::vector<Node> nodes;
    Node* current_node; 
    int runtime_steps = 0;
    std::vector<int> node_neighbors;
    nodes.resize(map.data.size());
    if(diagonal_paths)
        node_neighbors.resize(8);
    else
        node_neighbors.resize(4);

    std::priority_queue<Node*, std::vector<Node*>, CompareByFValue>   open_list;

    for(size_t i=0;  i < map.data.size(); i++)
    {
	nodes[i].index          = i;
	nodes[i].distance       = INT_MAX;
	nodes[i].f_value        = INT_MAX;
        nodes[i].in_open_list   = false;
        nodes[i].in_closed_list = false;
        nodes[i].parent         = NULL;
    }
    current_node = &nodes[idx_start];
    current_node->distance     = 0;
    current_node->in_open_list = true;    
    open_list.push(current_node);
    
    while(!open_list.empty() && current_node->index != idx_goal)
    {
	current_node = open_list.top();  
	open_list.pop();                   
	current_node->in_closed_list = true;
	
	node_neighbors[0] = current_node->index + map.info.width;
	node_neighbors[1] = current_node->index + 1;
	node_neighbors[2] = current_node->index - map.info.width;
	node_neighbors[3] = current_node->index - 1;
        if(diagonal_paths)
        {
            node_neighbors[0] = current_node->index + map.info.width + 1;
            node_neighbors[1] = current_node->index + map.info.width - 1;
            node_neighbors[2] = current_node->index - map.info.width + 1;
            node_neighbors[3] = current_node->index - map.info.width - 1;
        }
	
	for(size_t i=0; i < node_neighbors.size(); i++)
	{
	    if(map.data[node_neighbors[i]] > 40 || map.data[node_neighbors[i]] < 0 || nodes[node_neighbors[i]].in_closed_list)
		continue;
	    
	    Node* neighbor = &nodes[node_neighbors[i]];
	    int g_value = current_node->distance + 1 + cost_map.data[node_neighbors[i]];
            int h_value;
            int h_value_x = node_neighbors[i]%map.info.width - idx_goal_x;
            int h_value_y = node_neighbors[i]/map.info.width - idx_goal_y;
            if(diagonal_paths)
                h_value = (int)(sqrt(h_value_x*h_value_x + h_value_y*h_value_y));
            else
                h_value = fabs(h_value_x) + fabs(h_value_y);
            
	    if(g_value < neighbor->distance)
	    {
		neighbor->distance = g_value;
		neighbor->f_value  = g_value + h_value;
		neighbor->parent   = current_node;
	    }

	    if(!neighbor->in_open_list)
	    {
		neighbor->in_open_list = true;
		open_list.push(neighbor);
	    }
	    
	    runtime_steps++; 
	}
    }

    //Check if the path was found
    if(current_node->index != idx_goal)
	return false;

    std::cout << "Path found using A STAR after " << runtime_steps << " steps." << std::endl;
    result_path.header.frame_id = "map";
    result_path.poses.clear();
    geometry_msgs::PoseStamped p;
    p.header.frame_id = "map";
    while(current_node->parent != NULL)
    {
	p.pose.position.x = current_node->index % map.info.width * map.info.resolution + map.info.origin.position.x;	
	p.pose.position.y = current_node->index / map.info.width * map.info.resolution + map.info.origin.position.y;
	result_path.poses.insert(result_path.poses.begin(), p);
	current_node = current_node->parent;
    }
    
    std::cout << "PathCalculator.->Resulting path by A* has " << result_path.poses.size() << " points." << std::endl;
    return true;
}

/*
 * FUNCION PARA SUAVIZAR LA RUTA
 * Parámetros:
 * nav_msgs::Path path    Ruta original sin suavizar calculada con A*. 
 * float weight_data      Peso que se le da al parecido con la ruta original. 
                          Un valor de cero provocará que el resultado sea una línea recta
 * float weight_path      Peso que se le da a qué tan suave será la ruta 
                          Un valor de cero provocará que el resultado sea la ruta original
 * float tolerance        Tolerancia para considerar que el descenso del gradiente ya convergió.
 * Valor de retorno:
 * nav_msgs::Path         Ruta ya suavizada.
 */
nav_msgs::Path PathCalculator::SmoothPath(nav_msgs::Path& path, float weight_data, float weight_smooth, float tolerance)
{
    nav_msgs::Path newPath;
    for(int i=0; i< path.poses.size(); i++) newPath.poses.push_back(path.poses[i]);
    newPath.header.frame_id = "map";   
    if(path.poses.size() < 3)  return newPath;
    int attempts = 0;
    tolerance *= path.poses.size();
    float change = tolerance + 1;
    while(change >= tolerance && ++attempts < 1000)
    {
        change = 0;
        for(int i=1; i< path.poses.size() - 1; i++)
        {
            geometry_msgs::Point old_p = path.poses[i].pose.position;
            geometry_msgs::Point new_p = newPath.poses[i].pose.position;
            geometry_msgs::Point new_p_next = newPath.poses[i+1].pose.position;
            geometry_msgs::Point new_p_prev = newPath.poses[i-1].pose.position;
            float last_x = newPath.poses[i].pose.position.x;
            float last_y = newPath.poses[i].pose.position.y;
            new_p.x += weight_data*(old_p.x - new_p.x) + weight_smooth*(new_p_next.x + new_p_prev.x - 2.0*new_p.x);
            new_p.y += weight_data*(old_p.y - new_p.y) + weight_smooth*(new_p_next.y + new_p_prev.y - 2.0*new_p.y);
            change += fabs(new_p.x - last_x) + fabs(new_p.y - last_y);
            newPath.poses[i].pose.position = new_p;
        }
    }
    std::cout << "PathCalculator.->Smoothing finished after " << attempts << " attempts" <<  std::endl;
    return newPath;
}

Node::Node()
{
    this->index            = -1;
    this->distance         = INT_MAX;
    this->f_value          = INT_MAX;
    this->in_open_list     = false;
    this->in_closed_list   = false;
    this->parent           = NULL;  
}

Node::~Node()
{
}
