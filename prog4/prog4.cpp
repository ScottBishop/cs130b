#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <algorithm>


using namespace std;

class Point{
public:
	double xCord;
	double yCord;
};

class Line{
public:
	double slope;
	double yInt;
	double median;
};

vector<Point*> ReadFile(char* filename){
	ifstream myfile(filename);
	string line;
	vector<Point*> samplePoints;
	if (myfile.is_open()){
		while ( getline (myfile,line))
		{
			stringstream parse(line);
			Point* point = new Point();
			parse >> point->xCord;
			parse >> point->yCord;
			samplePoints.push_back(point);
			
		}
	}
	return samplePoints;
}

void Choose (const int size, int &first, int &second)
{
  // pick a random element
	first = rand () % size;
  // pick a random element from what's left (there is one fewer to choose from)...
	second = rand () % (size - 1);
  // ...and adjust second choice to take into account the first choice
	if (second >= first)
	{
		++second;
	}
}

double slope(Point* one, Point* two){
	return ((two->yCord - one->yCord)/(two->xCord - one->xCord));
}

double yIntercept(Point* one, double slope){
	return ((slope * one->xCord) + one->yCord);
}

double linePointDistance(Point* one, double slope, double yInt){
	double top = (one->yCord - (slope * one->xCord) - yInt);
	double totalTop = ((double) fabs(top));
	double bottom = sqrt((slope*slope) + 1);
	return totalTop/bottom;
}

double findMedian(int size, vector<double> median){
	double arrMedian;
	int mid = 0;

	if(size % 2 == 0){
		mid = (size/2)-1;
		arrMedian = ((median[mid]+median[mid + 1])/2.0);
	}
	else{
		mid = (median.size()/2);
		arrMedian = median[mid];
	}
	return arrMedian;
}

int main(int argc, char* argv[]){
	vector<Point*> allPoints;
	vector<double> median;
	double compMedian;
	allPoints = ReadFile(argv[1]);
	//cout << "x: " << allPoints[0]->xCord << " y: " << allPoints[0]->yCord << endl;

	while (allPoints.size() > 1){
		int first,second;
		
		//select 2 random points
		Choose(allPoints.size(), first, second);
		//find slope of those two points
		double ptSlope = slope(allPoints[first], allPoints[second]);

		//find corresponding yintercept
		double yInt = yIntercept(allPoints[first], ptSlope);

		//erase those two points so they are not used again
		allPoints.erase(allPoints.begin() + first);
		allPoints.erase(allPoints.begin() + second);

		//pick another random point from those remaining
		int nextPoint = rand() % allPoints.size();

		//calculate closest distance between that point and the line
		double sampleDistance = linePointDistance(allPoints[nextPoint], ptSlope, yInt);

		//erase that point as well
		allPoints.erase(allPoints.begin() + nextPoint);

		//store the distance for median calculation
		median.push_back(sampleDistance);
	}
	
	sort(median.begin(), median.end());
	double actualMedian = findMedian(median.size(), median);

	for (vector<double>::iterator it=median.begin(); it!=median.end(); ++it){
		cout << ' ' << *it;
		cout << '\n';
	}


	// cout << "distance: " << sampleDistance << endl;
	// cout << "slope: " << ptSlope << endl;
	// cout << "yIntercept: " << yInt << endl;
	// cout << "first1: " << first << " second1: " << second << endl;

	// cout << "x: " << allPoints[first]->xCord << " y: " << allPoints[first]->yCord << endl;
	// cout << "x: " << allPoints[second]->xCord << " y: " << allPoints[second]->yCord << endl;
	return 0;
}















