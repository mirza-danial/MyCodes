class Matrix{
private:
	int **m; // integer array
	int col;
	int row;
public:
	//*************** Constructors *********************************
	Matrix(); //empty 0x0 matrix
	Matrix(char*);//reads from file
	Matrix(int, int);//creates a matrix with randm values
	Matrix(const Matrix&);
	//*************** OPERATOR OVERLOAD ****************************
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	const Matrix& operator=(const Matrix &);
	bool operator==(const Matrix&);
	bool operator!=(const Matrix&);
	void operator+=(int);
	void operator*=(int);
	int*operator[](int);
	//******************FRIEND FUNCTIONS / OPERATORS*********************
	friend Matrix operator-(const Matrix &);
	//******************FUNCTIONS****************************
	int getNumRows();
	int getNumCols();
	void transpose();
	//*******************DESTRUCTOR*****************************
	~Matrix();
};