////Implementation of the IDFT
//
//#include <complex>
//
//#define PI 3.1415926535897932384
//
//#define N 8
//
//#define HIGH_BOUND 10
//#define LOW_BOUND -10
//
//int main()
//{
//	std::complex<float> x[N];
//	std::complex<float> temp;
//	float real, imag;
//	printf("Input vector:\n");
//	x[0] = 0;
//	x[1] = std::complex<float>(0, -4);
//	x[2] = 0;
//	x[3] = 0;
//	x[4] = 0;
//	x[5] = 0;
//	x[6] = 0;
//	x[7] = std::complex<float>(0, 4);
//
//	for (int i = 0; i < N; i++)
//	{
//		printf("%f + i%f\n", x[i].real(), x[i].imag());
//	}
//
//	std::complex<float> root = std::complex<float>(std::cos(2 * (float)PI / (float)(N)), std::sin(2 * (float)PI / (float)(N)));
//
//	std::complex<float> X[N];
//	for (int i = 0; i < N; i++)
//	{
//		temp = std::complex<float>(0, 0);
//		for (int j = 0; j < N; j++)
//		{
//			temp += (std::complex<float>)pow(root, i * j) * x[j];
//		}
//		X[i] = temp * (1 / (float)N);
//	}
//
//	printf("Output vector:\n");
//	for (int i = 0; i < N; i++)
//	{
//		printf("%f + i%f\n", X[i].real(), X[i].imag());
//	}
//
//	return 0;
//}