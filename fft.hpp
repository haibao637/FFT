
/**
 * @author      : Yan Jianfeng
 * @date        : 2020-04-10
 * @description : dct implementation 
 * @version     : 1.0
 */
#include <vector>
#include <complex>
using std::complex;
using std::vector;

namespace bbf
{
const static double PI =std::acos(-1);;
using cf = complex<float>;

class FFT
{
private:

    void fft(cf* a,int n, bool invert);
    void fft2(vector<cf>& a , int height,int width,bool invert);
public:

    void dft(vector<cf>& a);
    void dft2(vector<cf>& a,int height,int width);
    void idft2(vector<cf>& a,int height,int width);

    void idft(vector<cf>& a);
};
}  // namespace bbf
