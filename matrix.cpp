#include "matrix.h"
#include "omp.h"

// CONSTRUCTORS & DESTRUCTOR
Matrix::Matrix(int n, int m, int thread)
{
	this->n = n;
	this->m = m;
	this->thread = thread;
	omp_set_num_threads(this->thread);
	
	this->values = new int*[n];
	#pragma omp parallel for num_threads(this->thread) num_threads(this->thread)
	for(int i = 0; i<n ;i++)
	{
		this->values[i] = new int[m];
	}
	#pragma omp barrier
	this->init();
}

Matrix::Matrix(const Matrix& matrix)
{
	this->n = matrix.n;
	this->m = matrix.m;
	this->values = new int*[this->n];
	#pragma omp parallel for num_threads(this->thread)
	for(int i = 0; i<this->n ;i++)
	{
		this->values[i] = new int[this->m];
	}
	#pragma omp barrier
	
	#pragma omp parallel for num_threads(this->thread)
	for(int i = 0; i<this->n ;i++)
    {
		for(int j = 0;j < this->m; j++)
		{
			this->values[i][j] = matrix.values[i][j];
		}
	}
	#pragma omp barrier
}

Matrix::~Matrix()
{
	#pragma omp parallel for num_threads(this->thread)
	for(int i = 0; i<n; i++)
	{
		delete[] this->values[i];
	}
	#pragma omp barrier
	delete[] this->values;
}


// USEFUL METHODS
void Matrix::init(int val)
{
	#pragma omp parallel for num_threads(this->thread)
	for(int i = 0; i<this->n; i++)
    {
		for(int j = 0; j<this->m; j++)
		{
			this->values[i][j] = val;
		}
	}
	#pragma omp barrier
}

unsigned long long int Matrix::sum()
{
	unsigned long long int sum = 0;
	#pragma omp parallel for num_threads(this->thread)
	for(int i = 0; i<this->n ;i++)
    {
		for(int j = 0;j<this->m; j++)
		{
			sum += this->values[i][j];
		}
	}
	#pragma omp barrier
	return sum;
}


// OPERATORS OVERLOAD
ostream& operator<< (ostream &out, const Matrix &matrix)
{
    for(int i = 0; i<matrix.n; i++)
    {
		for(int j = 0; j<matrix.m; j++)
		{
			out << matrix.values[i][j] << ' ';
		}
		out << endl;
	}
	out << endl;
    return out;
}

Matrix Matrix::operator+(const Matrix& matrix)
{
    Matrix m3 = *this;
    
    #pragma omp parallel for num_threads(this->thread)
    for(int i = 0; i<this->n ;i++)
    {
		for(int j = 0;j<this->m; j++)
		{
			m3.values[i][j] = this->values[i][j] + matrix.values[i][j];
		}
	}
	#pragma omp barrier
    return m3;
}

Matrix Matrix::operator*(const Matrix& matrix)
{
    Matrix m3 = *this;
    m3.init(0);
    
    #pragma omp parallel for num_threads(this->thread)
    for (int i=0;i<this->n;i++)
	{
		for (int j=0;j<matrix.m;j++)
		{
			for (int k=0;k<this->m;k++)
			{
				m3.values[i][j]=this->values[i][k]*matrix.values[k][j]+m3.values[i][j];
			}
		}
	}    
	#pragma omp barrier
    
    return m3;
}

Matrix operator*(const Matrix& matrix, int product)
{
    Matrix m3 = matrix;
    
    #pragma omp parallel for num_threads(this->thread)
    for(int i = 0; i<m3.n ;i++)
    {
		for(int j = 0;j<m3.m; j++)
		{
			m3.values[i][j] *= product;
		}
	}
	#pragma omp barrier
    return m3;
}


