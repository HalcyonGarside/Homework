//Implementation of the DFT

#include <complex>

#define PI 3.1415926535897932384

#define N 1024

#define HIGH_BOUND 10
#define LOW_BOUND -10

bool ifft(int n, std::complex<float>* in_vec, std::complex<float>*& out_vec)
{
	out_vec = (std::complex<float>*)malloc(n * sizeof(std::complex<float>));
	if (n == 1)
	{
		out_vec[0] = in_vec[0];
		return true;
	}
	if (n % 2 != 0)
	{
		printf("Error: Not a power of 2\n");
		return false;
	}

	int n_dev_2 = n / 2;

	std::complex<float>* y0 = (std::complex<float>*)malloc((n_dev_2) * sizeof(std::complex<float>));
	std::complex<float>* y1 = (std::complex<float>*)malloc((n_dev_2) * sizeof(std::complex<float>));
	std::complex<float>* xe = (std::complex<float>*)malloc((n_dev_2) * sizeof(std::complex<float>));
	std::complex<float>* xo = (std::complex<float>*)malloc((n_dev_2) * sizeof(std::complex<float>));

	for (int i = 0; i < n_dev_2; i++)
	{
		xe[i] = in_vec[i * 2];
		xo[i] = in_vec[i * 2 + 1];
	}

	if (!ifft(n_dev_2, xe, y0) || !ifft(n_dev_2, xo, y1))
	{
		delete[] xe;
		delete[] xo;
		return false;
	}

	delete[] xe;
	delete[] xo;

	std::complex<float> root = std::complex<float>(std::cos(2 * (float)PI / (float)(n)), std::sin(2 * (float)PI / (float)(n)));
	std::complex<float>* omeg_rem = (std::complex<float>*)malloc((n_dev_2) * (n_dev_2) * sizeof(std::complex<float>));
	
	for (int i = 0; i < n_dev_2; i++)
	{
		for (int j = 0; j < n_dev_2; j++)
		{
			if (i == j)
			{
				omeg_rem[i * (n_dev_2) + j] = std::pow(root, j);
			}
			else
			{
				omeg_rem[i * (n_dev_2) + j] = std::complex<float>(0, 0);
			}
		}
	}

	std::complex<float>* omega_y1 = (std::complex<float>*)malloc((n_dev_2) * sizeof(std::complex<float>));

	for (int i = 0; i < n_dev_2; i++)
	{
		omega_y1[i] = y1[i] * (std::complex<float>)pow(root, i);
	}

	delete[] y1;

	for (int i = 0; i < n_dev_2; i++)
	{
		out_vec[i] = (y0[i] + omega_y1[i]) / std::complex<float>(2);
		out_vec[i + n_dev_2] = (y0[i] - omega_y1[i]) / std::complex<float>(2);
	}

	delete[] y0;
	delete[] omega_y1;
}

int main()
{
	std::complex<float>* x = (std::complex<float>*)malloc(8 * sizeof(std::complex<float>));

	x[0] = 0;
	x[1] = std::complex<float>(0, -4);
	x[2] = 0;
	x[3] = 0;
	x[4] = 0;
	x[5] = 0;
	x[6] = 0;
	x[7] = std::complex<float>(0, 4);

	std::complex<float> temp;
	float real, imag;
	printf("Input vector:\n");

	for (int i = 0; i < 8; i++)
	{
		printf("%f + %fi\n", x[i].real(), x[i].imag());
	}

	std::complex<float>* X = (std::complex<float>*)malloc(8 * sizeof(std::complex<float>));

	ifft(8, x, X);

	printf("\n");
	printf("Output vector:\n");
	for (int i = 0; i < 8; i++)
	{
		printf("%f + %fi\n", X[i].real(), X[i].imag());
	}

	return 0;
}