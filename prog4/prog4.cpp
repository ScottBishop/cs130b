#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iomanip>


using namespace std;

class Point{
public:
	double xCord;
	double yCord;
	bool isChecked;
	bool choseForLine;
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
			point->isChecked = false;
			point->choseForLine = false;
			samplePoints.push_back(point);
			
		}
	}
	return samplePoints;
}

void Choose (const int size, int &first, int &second, vector<Point*> allPoints)
{
  // pick a random element
	first = rand () % size;
	while(allPoints[first]->choseForLine != false){
		first = rand () % size;
	}
	allPoints[first]->choseForLine = true;
	

  // pick a random element from what's left (there is one fewer to choose from)...
	second = rand () % (size - 1);
	while(allPoints[second]->choseForLine != false){
		second = rand () % (size - 1);
	}
	allPoints[second]->choseForLine = true;

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
	long arrMedian;
	int mid = 0;

	if(size % 2 == 0){
		cout << "made it" << endl;
		mid = (size/2)-1;
		long one = median[mid];
		long two = median[mid+1];
		long hold1 = one + two;
		// cout << "hold1: " << hold1 << endl;
		// cout << "mid: " << mid << endl;
		// cout << "median[mid]: " << median[mid] << endl;
		// cout << "median[mid + 1]: " << median[mid+1] << endl;
		// double hold = (median[mid]) + (median[mid + 1]) ;
		// cout << "hold: " << hold << endl;
		arrMedian = hold1/2.0;
		cout << "arrMedian: " << arrMedian << endl;
	}
	else{
		mid = (median.size()/2);
		arrMedian = median[mid];
	}
	return ((double) arrMedian);
}

double round(double d)
{
  return floor(d + 0.5);
}

int main(int argc, char* argv[]){
	vector<Point*> allPoints;
	vector<double> median;
	double finalSlope;
	double finalYInt;
	int numElements;
	int numPossible;
	double compMedian = 9999;
	allPoints = ReadFile(argv[1]);
	//cout << "x: " << allPoints[0]->xCord << " y: " << allPoints[0]->yCord << endl;

	numElements = allPoints.size();
	numPossible = (numElements/2);


	while (numPossible > 0){
		int first,second;
	//select 2 random points
		Choose(allPoints.size(), first, second, allPoints);

	//find slope of those two points
		double ptSlope = slope(allPoints[first], allPoints[second]);
	//find corresponding yintercept
		double yInt = yIntercept(allPoints[first], ptSlope);
		cout << "slope: " << ptSlope << endl;
		cout << "yIntercept: " << yInt << endl;
	//erase those two points so they are not used again
		allPoints[first]->isChecked = true;
		allPoints[second]->isChecked = true;

		numElements -= 2;
	//allPoints.erase(allPoints.begin() + first);
	//allPoints.erase(allPoints.begin() + second-1);
		int nextPoint = rand() % allPoints.size();

		while (numElements > 0){
		//pick another random point from those remaining
			while(allPoints[nextPoint]->isChecked != false){
				nextPoint = rand() % allPoints.size();
			}

		//calculate closest distance between that point and the line
			double sampleDistance = linePointDistance(allPoints[nextPoint], ptSlope, yInt);

		//erase that point as well
			allPoints[nextPoint]->isChecked = true;
		//allPoints.erase(allPoints.begin() + nextPoint);

		//store the distance for median calculation
			median.push_back(sampleDistance);
			numElements--;
		}

		sort(median.begin(), median.end());
		double actualMedian = findMedian(median.size(), median);

		if (actualMedian < compMedian){
			compMedian = actualMedian;
			finalSlope = ptSlope;
			finalYInt = yInt;
			cout << "new compMedian: " << compMedian << endl;
		}
		numPossible--;
	}
	

	// for (vector<double>::iterator it=median.begin(); it!=median.end(); ++it){
	// 	cout << *it;
	// 	cout << '\n';
	// }

	// for (vector<double>::iterator it=median.begin(); it!=median.end(); ++it){
	// 	*it -= actualMedian;
	// }


	// for (vector<double>::iterator it=median.begin(); it!=median.end(); ++it){
	// 	cout << *it;
	// 	cout << '\n';
	// }

	// double theMedian = findMedian(median.size(), median);
	// cout << "actual median: " << theMedian << endl;


	// cout << "distance: " << sampleDistance << endl;
	// cout << "slope: " << ptSlope << endl;
	// cout << "yIntercept: " << yInt << endl;
	// cout << "first1: " << first << " second1: " << second << endl;

	// cout << "x: " << allPoints[first]->xCord << " y: " << allPoints[first]->yCord << endl;
	// cout << "x: " << allPoints[second]->xCord << " y: " << allPoints[second]->yCord << endl;
	double round1 = round(finalSlope);
	double round2 = round(finalYInt);
	cout << setprecision(5) << fixed << round1 << " ";
	cout << setprecision(5) << fixed << round2 << endl;
	return 0;
}















