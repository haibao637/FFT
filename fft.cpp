
/**
 * @author      : Yan Jianfeng
 * @date        : 2020-04-10
 * @description : dct implementation ,cited from https://cp-algorithms.com/algebra/fft.html
 * @version     : 1.0
 */
#include <memory.h>
#include <complex>
#include <cmath>
#include <vector>
#include<iostream>
#include<cassert>
#include<iterator>
#include "fft.hpp"
#include<algorithm>
using std::complex;
using std::vector;
namespace bbf
{

    void FFT::fft(cf* a,int n , bool invert) {
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? 1 : -1);
            cf wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cf w(1);

                for (int j = 0; j < len / 2 && (i+j+len/2 < n) && i+j < n; j++) {
                    assert(i+j<n);
                    assert(i+j+len/2<n);
                    cf u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (int i = 0;i<n;++i)
                a[i]/=n;
        }
    }

void FFT::dft(vector<cf>& a)
{
    fft(a.data(),a.size(),false);

}

void FFT::idft(vector<cf>& a)
{
    fft(a.data(),a.size(),true);


}

template <class T>
static void rotateMatrix(const vector<T>& matrix,vector<T>& dist,int height,int width)
{
    for(int i = 0;i<height;++i){
        for(int j = 0;j<width;++j){
            dist[j*height+i]=matrix[i*width+j];
        }
    }
}
void  FFT::fft2(vector<cf>& a , int height,int width,bool invert)
{
    auto temp = a;


    rotateMatrix(a,temp,height,width);
//
    for(int i =0;i<width;++i){

        fft(temp.data()+i*height,height,invert);
    }
    rotateMatrix(temp,a,width,height);
    for(int i =0;i<height;++i){

        fft(a.data()+i*width,width,invert);
    }
//    rotateMatrix(a,temp,height,width);

}
void FFT::dft2(vector<cf>& a,int height,int width)
{

    fft2(a,height,width,false);
}
void FFT::idft2(vector<cf>& a,int height,int width)
{
    std::cout<<height<<" "<<width<<std::endl;
    fft2(a,height,width,true);



}
}  // namespace bbf