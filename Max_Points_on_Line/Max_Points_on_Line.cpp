// Max_Points_on_Line.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <string>
#include <vector>

using namespace std;



class Point {
public:
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int maxPoints(vector<Point> &points) {
        int n = points.size();

        if (n < 2)
        {
            return n;
        }

        map<string, int> hashS;

        int maxPoints = 0;
        int curMax = 0;
        string key;
        char tmp[20];
        Point curP;
        Point cmpP;
        int k, m, g;
        int samePoints, sameVpoints, sameHPoints;

        for (int i = 0; i < n; i++) //start checking lines crossing point i.
        {
            curMax = 0;
            curP = points.at(i);
            hashS.clear();
            samePoints = 0;
			sameVpoints = sameHPoints = 0;

            for (int j = i+1; j < n; j++)
            {
                cmpP = points.at(j);

                if(cmpP.y == curP.y && cmpP.x == curP.x)
                {
                    samePoints++;
                    continue;
                }

                if (cmpP.x == curP.x)
                {
                    sameVpoints++;
					if(sameVpoints > curMax)
						curMax = sameVpoints;
					continue;
                }
				else if(cmpP.y == curP.y)
				{
                    sameHPoints++;
					if(sameHPoints > curMax)
						curMax = sameHPoints;
					continue;
				}
                else
                {
					int diffy = (cmpP.y - curP.y);
					int diffx = (cmpP.x - curP.x);
					bool diff = false;
					if(diffy > 0 && diffx < 0)
					{
						diffx = 0-diffx;
						diff = true;
					}
					else if(diffy < 0 && diffx > 0)
					{
						diffy = 0-diffy;
						diff = true;
					}
					else if(diffy < 0 && diffx < 0)
					{
						diffx = 0-diffx;
						diffy = 0-diffy;					
					}
                    g = gcd(diffy,diffx);
                    diffy = diffy/g;
                    diffx = diffx/g;


                    k = diffy/diffx;
                    m = diffy - k*diffx;
                    

					if(diff)
					{
						k = 0-k;
						m = 0-m;
					}

                    itostr(k,tmp);
                    key = tmp;
                    key += " ";
                    itostr(m, tmp);
                    key += tmp;
                }

                if (hashS.find(key) == hashS.end())
                {
                    hashS[key] = 1;
                }
                else
                {
                    hashS[key]++;
                }

                if (hashS[key] > curMax)
                {
                    curMax = hashS[key];
                }
            }

            if ((curMax + samePoints) > maxPoints)
            {
                maxPoints = curMax + samePoints;
            }
        }

        return (maxPoints + 1);        
    }

private:
	void itostr(int a, char* str)
	{
		if(str == NULL)
			return;

		if(a == 0){
			*str = '0';
			str++;
			*str = '\0';
			return;
		}

		if(a < 0)
		{
			*(str++) = '-';
			a = 0 - a;
		}

		char* startStr = str;
		int r = 0;
		while(a)
		{
			r = a%10;
			a = a/10;
			*(str++) = '0' + r;
		}

		*str = '\0';
		str--;
		char tmp;
		while(startStr < str)
		{
			tmp = *startStr;
			*(startStr) = *(str);
			*str = tmp;
			startStr++;
			str--;
		}
	}

    int gcd(int a, int b)
    {
        if (a > b)
        {
            if(a%b == 0)
                return b;

            return gcd((a-b), b);
        }

        if (a == b)
        {
            return a;
        }

        if (a < b)
        {
            if(b%a == 0)
                return a;

            return gcd((b - a), a);
        }
    }
};

//class Solution {
//public:
//    int maxPoints(vector<Point> &points) {
//        int n = points.size();
//
//        if (n < 2)
//        {
//            return n;
//        }
//
//        map<double, int> hashS;
//
//        int maxPoints = 0;
//        int curMax = 0;
//        string key;
//        char tmp[20];
//        Point curP;
//        Point cmpP;
//        int k, m;
//        int samePoints, sameLine;
//
//        for (int i = 0; i < n; i++) //start checking lines crossing point i.
//        {
//            curMax = 0;
//            curP = points.at(i);
//            hashS.clear();
//            samePoints = 0;
//			sameLine = 0;
//
//            for (int j = i+1; j < n; j++)
//            {
//                cmpP = points.at(j);
//
//                if(cmpP.y == curP.y && cmpP.x == curP.x)
//                {
//                    samePoints++;
//                    continue;
//                }
//
//                if (cmpP.x == curP.x)
//                {
//                    sameLine++;
//					if(sameLine > curMax)
//						curMax = sameLine;
//					continue;
//                }
//
//				double diffy = (cmpP.y - curP.y);
//				int diffx = (cmpP.x - curP.x);
//				diffy = diffy/diffx;
//
//                if (hashS.find(diffy) == hashS.end())
//                {
//                    hashS[diffy] = 1;
//                }
//                else
//                {
//                    hashS[diffy]++;
//                }
//
//                if (hashS[diffy] > curMax)
//                {
//                    curMax = hashS[diffy];
//                }
//            }
//
//            if ((curMax + samePoints) > maxPoints)
//            {
//                maxPoints = curMax + samePoints;
//            }
//        }
//
//        return (maxPoints + 1);        
//    }
//
//private:
//	void itostr(int a, char* str)
//	{
//		if(str == NULL)
//			return;
//
//		if(a == 0){
//			*str = '0';
//			str++;
//			*str = '\0';
//			return;
//		}
//
//		if(a < 0)
//		{
//			*(str++) = '-';
//			a = 0 - a;
//		}
//
//		char* startStr = str;
//		int r = 0;
//		while(a)
//		{
//			r = a%10;
//			a = a/10;
//			*(str++) = '0' + r;
//		}
//
//		*str = '\0';
//		str--;
//		while(startStr < str)
//			*(startStr++) = *(str--);
//	}
//};


int _tmain(int argc, _TCHAR* argv[])
{
	vector<Point> v;
	Point p;
	p.x = 3;
	p.y = 1;
	v.push_back(p);

	p.x = 12;
	p.y = 3;
	v.push_back(p);

	p.x = 3;
	p.y = 1;
	v.push_back(p);

	p.x = -6;
	p.y = -1;
	v.push_back(p);

	Solution s;
	s.maxPoints(v);


	system("PAUSE");
	return 0;
}