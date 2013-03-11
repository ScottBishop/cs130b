//Scott Bishop 3954237
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

class Pair{
public:
	Point* one;
	Point* two;
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


double slope(Point* one, Point* two){
	return ((two->yCord - one->yCord)/(two->xCord - one->xCord));
}

double yIntercept(Point* one, double slope){
	return (one->yCord - (slope * one->xCord));
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
		mid = (size/2)-1;
		long one = median[mid];
		long two = median[mid+1];
		long hold1 = one + two;
		arrMedian = hold1/2.0;
	}
	else{
		mid = (median.size()/2);
		arrMedian = median[mid];
	}
	return ((double) arrMedian);
}

vector<Pair*> populatePairs(vector<Point*> allPoints){
	vector<Pair*> pairs;
	for (unsigned int b = 0; b < allPoints.size(); b++){
		for (unsigned int c = 0; c < allPoints.size(); c++){
			if (b == c){
				continue;
			}
			Pair* pair = new Pair();
			pair->one = allPoints[b];
			pair->two = allPoints[c];
			pairs.push_back(pair);
		}
	}
	return pairs;
}

double round(double d)
{
	return floor(d + 0.5);
}

int main(int argc, char* argv[]){
	vector<Point*> allPoints;
	vector<double> median;
	vector<Pair*> pairs;
	double finalSlope;
	double finalYInt;
	int numElements;
	double compMedian = 9999;
	allPoints = ReadFile(argv[1]);

	if (allPoints.size() < 10){
		cout << "Not enough sample points, please enter more than 10 points" << endl;
		exit(1);
	}
	//cout << "x: " << allPoints[0]->xCord << " y: " << allPoints[0]->yCord << endl;

	pairs = populatePairs(allPoints);

	// for (unsigned int d =0; d < pairs.size(); d++){
	// 	cout << pairs[d]->one->xCord << " " << pairs[d]->one->yCord << endl;
	// 	cout << pairs[d]->two->xCord << " " << pairs[d]->two->yCord << endl;
	// 	cout << endl;
	// }

	numElements = allPoints.size();

	for (unsigned int cur = 0; cur < pairs.size(); cur++){
		
		//find slope of those two points
		double ptSlope = slope(pairs[cur]->one, pairs[cur]->two);
		//find corresponding yintercept
		double yInt = yIntercept(pairs[cur]->one, ptSlope);
		// cout << "slope: " << ptSlope << endl;
		// cout << "yIntercept: " << yInt << endl;
		//erase those two points so they are not used again
		pairs[cur]->one->isChecked = true;
		pairs[cur]->two->isChecked = true;

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
			//cout << "new compMedian: " << compMedian << endl;
		}

		for (unsigned int i = 0; i < allPoints.size(); i++){
			allPoints[i]->isChecked = false;
		}
	}
	

	// for (vector<double>::iterator it=median.begin(); it!=median.end(); ++it){
	// 	cout << *it;
	// 	cout << '\n';
	// }

	double round1 = round(finalSlope);
	double round2 = round(finalYInt);
	cout << setprecision(5) << fixed << round1 << " ";
	cout << setprecision(5) << fixed << round2 << endl;
	return 0;
}















