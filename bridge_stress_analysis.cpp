#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

float length, height, startPosi, startMag, cover, RLx, RLy, RRx, RRy, incre;
int noSpan, a, b, noSec;

vector<int>typeLoad;
vector<float>loadPosi;
vector<float>loadMag;
vector<float>coverDis;
vector<float>X;
vector<float>Theta;
vector<float>Axial;
vector<float>Shear;
vector<float>Y;
vector<float>Moment;

int main()
{
    cout << "*************THREE HINGED ARCH BRIDGE CALCULATOR******************************" << endl << endl;
    cout << "#IF THE BRIDGE HAS MULTIPLE SPANS, PLEASE SPLIT THE LOAD ON EACH SPAN!!" << endl;
    
    cout << "Enter the length of each span of the bridge in m: ";
    cin >> length;

    cout << "Enter the number of span: ";
    cin >> noSpan;

    cout << "Enter the height of the arch in m: ";
    cin >> height;

    cout << "Enter the number of section to be analysed per span: ";
    cin >> noSec;

    incre = length/noSec;

    for(int k = 0; k <= noSec; k++)
    {
        float x = 0.0 + (k*incre);
        X.push_back(x);

        float y = (4 * height / (length * length)) * X[k] * (length - X[k]);
        Y.push_back(y);

        float slope = ((4 * height)/(length * length)) * (length - 2 * X[k]);

        float theta = atan(slope);
        Theta.push_back(theta);
    }

    float c = length / 2.0;

    for(int i = 0; i < noSpan; i++)
    {
        double Ax = 0;
        double Ay = 0;
        double Bx = 0;
        double By = 0;

        cout << "\n******************************************************************************" << endl;
        cout << "Span No." << i + 1 << endl;
        cout << "Enter the number of load on the span: ";
        cin >> a;

        if(a > 0)
        {
            for(int j = 0; j < a; j++)
            {
                cout << " Load number " << j + 1 << endl;
                cout << " Type of load: " << endl;
                cout << "    1. Point Load                 " << endl;
                cout << "    2. Uniform Distributed Load   " << endl;
                cout << " Enter the type of load: ";
                cin >> b;

                while(b > 2 || b < 1)
                {
                    cout << " INVALID LOAD TYPE!!! Enter again \nEnter the type of load: ";
                    cin >> b;
                }
                typeLoad.push_back(b);

                cout << " Enter the position of Load from the left support in m: ";
                cin >> startPosi;
                loadPosi.push_back(startPosi);

                switch(b)
                {
                    case 1:
                        cout << " Enter the magnitude of Load in kN: ";
                        cin >> startMag;
                        cover = 0;
                        cout << endl;
                        break;
                    case 2:
                        cout << " Enter the magnitude of Load in kN/m: ";
                        cin >> startMag;

                        cout << " Enter the cover distance of the load in m: ";
                        cin >> cover;
                        cout << endl;
                        break;  
                }
                loadMag.push_back(startMag);
                coverDis.push_back(cover);

                if(typeLoad[j] == 1)
                {
                    RRy = (loadPosi[j] * loadMag[j]) / length;
                    RLy = loadMag[j] - RRy;

                    if(loadPosi[j] <= c)
                    {
                        RRx = RRy * c / height;
                        RLx = RRx;
                    }
                    if (loadPosi[j] > c)
                    {
                        RLx = RLy * c / height;
                        RRx = RLx;
                    }
                    Ax += RLx;
                    Ay += RLy;
                    Bx += RRx;
                    By += RRy;
                }

                if(typeLoad[j] == 2)
                {
                    RRy = ((loadMag[j] * coverDis[j]) * (loadPosi[j] + (coverDis[j] / 2.0))) / length;
                    RLy = (loadMag[j] * coverDis[j]) - RRy;

                    if(loadPosi[j] + coverDis[j] <= c)
                    {
                        RRx = RRy * c / height;
                        RLx = RRx;
                    }
                    if(loadPosi[j] >= c)
                    {
                        RLx = RLy * c / height;
                        RRx = RLx;
                    }
                    if((loadPosi[j] < c) && (loadPosi[j] + coverDis[j] > c))
                    {
                        RLx = ((RLy * c ) - (loadMag[j] * (c - loadPosi[j])) * ((c - loadPosi[j]) / 2.0 )) / height;
                        RRx = RLx;
                    }
                    Ax += RLx;
                    Ay += RLy;
                    Bx += RRx;
                    By += RRy;
                }
            }
            float H = Ax;

            cout << "Left support vertical reaction, Ay = " << Ay << endl;
            cout << "Right support vertical reaction, By = " << By << endl;
            cout << "Horizontal reaction, H = " << H << endl;

            for(int i = 0; i <= noSec; i++)
            {
                float N = (H * cos(Theta[i])) + (Ay * sin(Theta[i]));
                
                for(int j = 0; j < a; j++)
                {
                    if(loadPosi[j] <= X[i])
                    {
                        if(typeLoad[j] == 1)
                        {
                            N -= loadMag[j] * sin(Theta[i]);
                        }
                        if(typeLoad[j] == 2)
                        {
                            N -= loadMag[j] * (X[i] - loadPosi[j] * sin(Theta[i]));
                        }
                    }
                }
                Axial.push_back(N);
            }
            for(int j = 0; j <= noSec; j++)
            {
                float V = (Ay * cos(Theta[j])) - (H * sin(Theta[i]));

                for(int j = 0; j < a; j++)
                {
                    if(loadPosi[j] <= X[i])
                    {
                        if(typeLoad[j] == 1)
                        {
                            V -= loadMag[j] * cos(Theta[i]);
                        }
                        if(typeLoad[j] == 2)
                        {
                            V -= (loadMag[j] * (X[i] - loadPosi[j])) * cos(Theta[i]);
                        }
                    }
                }
                Shear.push_back(V);
            }
            for(int i = 0; i <= noSec; i++)
            {
                float M;
                M = (Ay * X[i]) - (H * Y[i]);

                for(int j = 0; j < a; j++)
                {
                    if(loadPosi[j] <= X[i])
                    {
                        if(typeLoad[j] == 1)
                        {
                            M -= loadMag[j] * (X[i] - loadPosi[j]);
                        }
                        if(typeLoad[j] == 2)
                        {
                            M -= loadMag[j] * (X[i] - loadPosi[j]) * ((X[i] - loadPosi[j]) / 2 );
                        }
                    }
                }
                Moment.push_back(M);
            }
            cout << "\n****************************RESULT********************************************" << endl << endl;
            cout << setw(10) << "X" << setw(20) << "Axial" << setw(20) << "Shear" << setw(20) << "B.Moment" << endl;

            for(int i = 0; i <= noSec; i++)
            {
                cout << setw(10) << X[i] << setw(20) << Axial[i] << setw(20) << Shear[i] << setw(20) << Moment[i] << endl;
            }
        }

        if (a == 0)
        {
            cout << "\n !!! NO LOAD ON SPAN !!!" << endl;
            cout << " !!! ALL VALUE IS ZERO !!!" << endl;
        }
        typeLoad.clear();
        loadPosi.clear();
        loadMag.clear();
        coverDis.clear();
        Axial.clear();
        Shear.clear();
        Moment.clear();
    }
    cout << "\n\n End of calculation";
}

