/*
 * Name:  Noah Nininger
 * Date Submitted:  03/17/23
 * Lab Section: 001
 * Assignment Name: Finding the Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

struct point
{
    double x {0};
    double y {0};
};

// overrides '<' operator to allow usage with the point struct
bool operator<(const point& a, const point& b)
{
 	if(a.x < b.x)
    {
		if(a.y < b.y)
			{ return true; }
	}
	return false;
}

// checks if the two points have been compared to each other already
bool hasBeenCompared(point current, point points, 
					 set<vector<point>> checkedPoints)
{
	vector<point> head = {current, points};
	vector<point> tail = {points, current};

	auto a = checkedPoints.find(head);
	auto b = checkedPoints.find(tail);

	if(a != checkedPoints.end() || b != checkedPoints.end())
	    { return true; }
	else { return false; }
}

// checks group of points against the current point
double checkGroup(point current, vector<point> &grid, 
                   set<vector<point>> checkedPoints)
{
	double min {2};

	for(auto points : grid)		// loop through each point
    {
	 // compares point to itself
	    if(points.x == current.x && points.y == current.y)
			{ continue; }
		
	 // if distance between points is not already checked
	    if(hasBeenCompared(current, points, checkedPoints) == false)
    	{
		    vector<point> v(2, current);
		    v[1] = points;
		    checkedPoints.insert(v);

			double xDiff = current.x - points.x;
		    double yDiff = current.y - points.y;
		    double distance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
			
			if(distance < min)
		        { min = distance; }
		}
	}

	return min;		// returns minimum value from comparison of group
}

double closestPair(string filename)
{
	ifstream in (filename);
	int points {0};

	in >> points;

	int sqrtOfPoints = sqrt(points);

 // grid of each point
	vector<vector<vector<point>>> grid(sqrtOfPoints, 
    							  vector<vector<point>>(sqrtOfPoints));
	
	for(int i = 0; i < points; i++)   // loops until each point is in grid
    {
		point current;

		in >> current.x;
	    in >> current.y;

		int hashX = (int)(current.x * sqrtOfPoints);
	    int hashY = (int)(current.y * sqrtOfPoints);

		grid[hashX][hashY].push_back(current);
	}

	double min {1};

	set<vector<point>> checkedPoints;
	for(int x = 0; x < sqrtOfPoints; x++)	// looping through grid
    {
	    for(int y = 0; y < sqrtOfPoints; y++)
	    {
			for(auto i : grid[x][y])
        	{
				double temp = checkGroup(i, grid[x][y], checkedPoints);
				double compare = 2;
				
			 // finds shortest length from 'point' to the left of the grid
				if(y != 0)
                {
					compare = checkGroup(i, grid[x][y - 1], 
										 checkedPoints);
				 // ternary operator
			        temp = (compare < temp) ? compare : temp;
					
				 // finds shortest length from 'point' to top-left of the grid
					if(x != (sqrtOfPoints - 1))
                    {
						compare = checkGroup(i, grid[x + 1][y - 1], 
											 checkedPoints);
					 // ternary operator
					    temp = (compare < temp) ? compare : temp;
			        }
				}
				
			 // finds shortest length from 'point' to the right of the grid
				if(y != (sqrtOfPoints - 1))
                {
					compare = checkGroup(i, grid[x][y + 1], 
										 checkedPoints);
				 // ternary operator
			        temp = (compare < temp) ? compare : temp;
					
				 // finds shortest length from 'point' to top-right of the grid
					if(x != (sqrtOfPoints - 1))
                    {
					    compare = checkGroup(i, grid[x + 1][y + 1], 
											 checkedPoints);
					 // ternary operator
			            temp = (compare < temp) ? compare : temp;
					}
				}
				
			 // finds shortest length from 'point' to the bottom of the grid
		        if(x != 0)
                {
					compare = checkGroup(i, grid[x - 1][y], 
										 checkedPoints);
				 // ternary operator
			        temp = (compare < temp) ? compare : temp;
					
				 // finds shortest length from 'point' to bottom-left of grid
					if(y != 0)
                    {
						compare = checkGroup(i, grid[x - 1][y - 1], 
											 checkedPoints);
					 // ternary operator
			            temp = (compare < temp) ? compare : temp;
			        }
					
				 // finds shortest length from 'point' to bottom-right of grid
					if(y != (sqrtOfPoints - 1))
                    {
						compare = checkGroup(i, grid[x - 1][y + 1], 
											 checkedPoints);
					 // ternary operator
			            temp = (compare < temp) ? compare : temp;
				    }
			    }	
				
			 // finds shortest length from 'point' to the top of the grid
				if(x != (sqrtOfPoints - 1))
                {
					compare = checkGroup(i, grid[x + 1][y], 
										 checkedPoints);
				 // ternary operator
				    temp = (compare < temp) ? compare : temp;
				}
				
				if(temp < min)
					{ min = temp; }
			}
		}
	}

	return min;
}
