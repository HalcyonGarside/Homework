////Implementation of the DFT
//
//#include <complex>
//
//#define PI 3.1415926535897932384
//
//#define N 1024
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
//	for (int i = 0; i < N; i++)
//	{
//		real = (rand() / (float)(RAND_MAX / HIGH_BOUND - LOW_BOUND));
//		imag = (rand() / (float)(RAND_MAX / HIGH_BOUND - LOW_BOUND));
//		x[i] = std::complex<float>(real, imag);
//	}
//
//	for (int i = 0; i < N; i++)
//	{
//		printf("%f + i%f\n", x[i].real(), x[i].imag());
//	}
//
//	std::complex<float> root = std::complex<float>(std::cos(-2 * (float)PI / (float)(N)), std::sin(-2 * (float)PI / (float)(N)));
//
//	std::complex<float> X[N];
//	for (int i = 0; i < N; i++)
//	{
//		temp = std::complex<float>(0, 0);
//		for (int j = 0; j < N; j++)
//		{
//			temp += (std::complex<float>)pow(root, i * j) * x[j];
//		}
//		X[i] = temp;
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