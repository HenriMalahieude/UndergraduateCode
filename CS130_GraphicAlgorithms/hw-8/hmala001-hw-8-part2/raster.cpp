#include <vector>
#include <string>
#include <iostream>
#include <string>
#include "common.h"

static const double weight_tol = 1e-4;

const int check_x = 350;
const int check_y = 200;

template<class... Args>
static void debug_print(int x, int y, Args&&... args)
{
    //return;
    if(x != check_x || y != check_y) return;

    //for(int i=0;i<Debug_Scope::level;i++) std::cout<<"  ";
    (std::cout<<...<<std::forward<Args>(args))<<std::endl;
}

template<class... Args>
static void just_print(Args&&... args)
{
    //return;
    //for(int i=0;i<Debug_Scope::level;i++) std::cout<<"  ";
    (std::cout<<...<<std::forward<Args>(args))<<std::endl;
}

void bary(vec3 a, vec3 b, vec3 c, vec3 p, double &alpha, double &beta, double &gamma){
    vec3 d1 = b - a;
    vec3 d2 = c - a;
    vec3 norm = cross(d1, d2);

    double aABC = 0.5 * (dot(cross(d1, d2), norm));
    double aPBC = 0.5 * (dot(cross((b - p), (c - p)), norm));
    double aAPC = 0.5 * (dot(cross((p - a), d2), norm));
    double aABP = 0.5 * (dot(cross(d1, (p - a)), norm));

    alpha = aPBC / aABC;
    beta = aAPC / aABC;
    gamma = aABP / aABC;
}

void Rasterize(Pixel* pixels, int width, int height, const std::vector<Triangle>& tris)
{
    //Create Z-Buffer, Fill with negative infinity
    double zBuffer[width][height];
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            zBuffer[i][j] = 1;
        }
    }

    //For Each Pixel
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            double alpha, beta, gamma;
            vec3 screenSpaceCoords = {(i / ((double)width - 1)) * 2 - 1, (j / ((double)height - 1)) * 2 - 1, 0};

            //For each triangle
            for (size_t tt = 0; tt < tris.size(); tt++){
                Triangle cTri = tris[tt];
                
                //Convert vec4 homogenous to vec3 euclidean
                vec3 pA = {cTri.A[0], cTri.A[1], cTri.A[2]}; pA /= cTri.A[3];
                vec3 pB = {cTri.B[0], cTri.B[1], cTri.B[2]}; pB /= cTri.B[3];
                vec3 pC = {cTri.C[0], cTri.C[1], cTri.C[2]}; pC /= cTri.C[3];

                //debug_print(i, j, "Triangle ", tt, ": A ", pA, ", B ", pB, ", C ", pC);

                //Screen Space points
                vec3 sA = {pA[0], pA[1], 0};
                vec3 sB = {pB[0], pB[1], 0};
                vec3 sC = {pC[0], pC[1], 0};

                bary(sA, sB, sC, screenSpaceCoords, alpha, beta, gamma);

                if (alpha >= -weight_tol && beta >= -weight_tol && gamma >= -weight_tol){
                    //Perspective correction of alpha beta gamma
                    double perspectivePP = 1.0 / ((alpha / cTri.A[3]) + (beta / cTri.B[3]) + (gamma / cTri.C[3]));
                    double rAlpha = (perspectivePP * alpha) / cTri.A[3];
                    double rBeta = (perspectivePP * beta) / cTri.B[3];
                    double rGamma = (perspectivePP * gamma) / cTri.C[3];
                    

                    if (rAlpha >= -weight_tol && beta >= -weight_tol && gamma >= -weight_tol){
                        vec3 tA = pA; tA[3] *= 100000;
                        vec3 tB = pB; tB[3] *= 100000;
                        vec3 tC = pC; tC[3] *= 100000;

                        vec4 tr2 = rAlpha * cTri.A + rBeta * cTri.B + rGamma * cTri.C;
                        vec3 conv = {tr2[0], tr2[1], tr2[2]}; conv /= tr2[3];

                        vec3 objectSpaceCoord = rAlpha * pA + rBeta * pB + rGamma * pC;
                        vec3 screenSpace = alpha * pA + beta * pB  + gamma * pC;

                        vec3 somethingElse = rAlpha * tA + rBeta * tB + rGamma * tC;
                        //debug_print(i, j, "  ", conv[2], " vs ", objectSpaceCoord[2], " vs ", screenSpace[2], " vs ", somethingElse[2]);

                        double currentZ = zBuffer[i][j];
                        if (screenSpace[2] < currentZ){
                            pixels[j * (width) + i] = Pixel_Color(rAlpha * cTri.Ca + rBeta * cTri.Cb + rGamma * cTri.Cc);
                            zBuffer[i][j] = screenSpace[2];
                        }
                    }
                }
            }
        }
    }

    //For Debug Print
    //pixels[check_y* width + check_x] = Pixel_Color({1, 0, 0});
}