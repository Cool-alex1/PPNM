#include<cmath>
#include<string>
#include<iostream>
#include"matrix.h"
// #include"vector.h"
#define SELF (*this)

matrix& matrix::operator+=(double n){
	for (int i=0; i < nRow; i++){
		for (int j=0; j < nCol; j++){
			mat[i*nCol + j] += n;
		}
	}
	return *this;
}
matrix& matrix::operator-=(double n){
	*this += -n;
	return *this;
}
matrix& matrix::operator*=(double n){
	for (int i=0; i < nRow; i++){
		for (int j=0; j < nCol; j++){
			mat[i*nCol + j] *= n;
		}
	}
	return *this;
}
matrix& matrix::operator/=(double n){
	*this *= 1/n;
	return *this;
}
matrix& matrix::operator+=(const matrix& a){
	matrix m(a.nRow, a.nCol);
	if(SELF.nRow == a.nRow && SELF.nCol == a.nCol){
		for (int i=0; i < m.nRow; i++){
			for (int j=0; j < m.nCol; j++){
				mat[i*nCol + j] += a(i,j);
			}
		}
		return *this;
	} else {
		throw std::invalid_argument( "Shapes of the matrisies does not match: (" + std::to_string(SELF.nRow) + ", " + std::to_string(SELF.nCol) + ") != (" + std::to_string(a.nRow) + ", " + std::to_string(a.nCol) + ")");
	}
}
matrix& matrix::operator-=(const matrix& a){
	*this += -a;
	return *this;
}

matrix operator+(const matrix& mOri, double a){
	matrix m(mOri.nRow, mOri.nCol);
	for (int i=0; i < m.nRow; i++){
		for (int j=0; j < m.nCol; j++){
			m(i, j) = mOri(i,j) + a;
			// std::cout <<  << std::endl;
		}
	}
	return m;
}
matrix operator+(const matrix& a, const matrix& b){
	matrix m(a.nRow, a.nCol);
	if(a.nRow == b.nRow && a.nCol == b.nCol){
		for (int i=0; i < m.nRow; i++){
			for (int j=0; j < m.nCol; j++){
				m(i, j) = a(i,j) + b(i,j);
			}
		}
		return m;
	} else {
		throw std::invalid_argument( "Shapes of the matrisies does not match: (" + std::to_string(a.nRow) + ", " + std::to_string(a.nCol) + ") != (" + std::to_string(b.nRow) + ", " + std::to_string(b.nCol) + ")");
	}
}
matrix operator+(double a, const matrix& mOri){return mOri + a;}
matrix operator-(const matrix& mOri, double a){
	matrix m(mOri.nRow, mOri.nCol);
	for (int i=0; i < m.nRow; i++){
		for (int j=0; j < m.nCol; j++){
			m(i, j) = mOri(i,j) - a;
		}
	}
	return m;
}
matrix operator-(const matrix& a, const matrix& b){
	matrix m(a.nRow, a.nCol);
	if(a.nRow == b.nRow && a.nCol == b.nCol){
		for (int i=0; i < m.nRow; i++){
			for (int j=0; j < m.nCol; j++){
				m(i, j) = a(i,j) - b(i,j);
			}
		}
		return m;
	} else {
		throw std::invalid_argument( "Shapes of the matrisies does not match: (" + std::to_string(a.nRow) + ", " + std::to_string(a.nCol) + ") != (" + std::to_string(b.nRow) + ", " + std::to_string(b.nCol) + ")");
	}
}
matrix operator-(const matrix& mOri){
	matrix m(mOri.nRow, mOri.nCol);
	return m - mOri;
}
matrix operator*(const matrix& mOri, double a){
	matrix m(mOri.nRow, mOri.nCol);
	for (int i=0; i < m.nRow; i++){
		for (int j=0; j < m.nCol; j++){
			m(i, j) = mOri(i,j) * a;
		}
	}
	return m;
}
matrix operator*(double a, const matrix& mOri){return mOri * a;}
matrix operator*(const matrix& a, const matrix& b){
	if(a.nCol == b.nRow){
		matrix m(a.nRow, b.nCol);
		for (int i=0; i < m.nRow; i++){
			for (int j=0; j < m.nCol; j++){
				for (int k=0; k<a.nCol; k++){
					m(i, j) += a(i,k) * b(k,j);
				}
			}
		}
		return m;
	} else {
		throw std::invalid_argument( "Shapes of the matrisies does not match: (" + std::to_string(a.nRow) + ", " + std::to_string(a.nCol) + ") * (" + std::to_string(b.nRow) + ", " + std::to_string(b.nCol) + ")");
	}
}
matrix operator/(const matrix& mOri, double a){
	if(a != 0){
		matrix m(mOri.nRow, mOri.nCol);
		for (int i=0; i < m.nRow; i++){
			for (int j=0; j < m.nCol; j++){
				m(i, j) = mOri(i,j) / a;
			}
		}
		return m;
	} else {
		throw std::invalid_argument("Dividing with 0");
	}
}

matrix compPro(const matrix& a, const matrix& b){
	matrix m(a.nRow, a.nCol);
	if(a.nRow == b.nRow && a.nCol == b.nCol){
		for (int i=0; i < m.nRow; i++){
			for (int j=0; j < m.nCol; j++){
				m(i, j) = a(i,j) * b(i,j);
			}
		}
		return m;
	} else {
		throw std::invalid_argument( "Shapes of the matrisies does not match: (" + std::to_string(a.nRow) + ", " + std::to_string(a.nCol) + ") != (" + std::to_string(b.nRow) + ", " + std::to_string(b.nCol) + ")");
	}
}
matrix I(int n){
	matrix m(n, n);
	for (int i=0; i < n; i++){m(i, i) = 1;}
	return m;
}
matrix invers(const matrix& a){
	matrix aI = a.append(I(a.nRow));
	matrix normalSolve = solve(aI);
	matrix inv = normalSolve.getCol(a.nRow, a.nRow);
	inv.det = normalSolve.det;
	return inv;
}
matrix solve(const matrix& a){
	int x = 0;
	int y = 0;
	double det = 1;
	matrix m = a.copy();

	for(int i=0; i<a.nCol; i++){
		bool colOfZero = false;
		for(int k=0; k<a.nRow-y; k++){ //Finds and preparing the row og interesed
			if(m(y,x) != 0){
				double s = m(y,x);
				det *= s;
				for(int j=x; j<a.nCol; j++){
					m(y, j) = m(y, j)/s;
				}
				break;
			} else {
				m = m.swapRow(y, a.nRow-1);
				det *= pow(-1, a.nRow-y-1);
				if(k == a.nRow-y-1){colOfZero = true;}
			}
		}
		
		if(!colOfZero){
			for(int k=0; k<a.nRow; k++){ //Finds and preparing the row og interesed
				if(k != y){
					double s = m(k,x);
					for(int j=x; j<a.nCol; j++){
						m(k, j) = m(k, j) - m(y, j)*s;
					}
				}
			}
			y++;
		}

		if(y == a.nRow){break;}
		x++;
	}

	m.det = det;
	return m;
}
double length(const matrix& a){
	if(a.nRow == 1 && a.nCol == 1){return a(0,0);} 
	else if(a.nRow == 1){return length(a.T());} 
	else if (a.nCol == 1) {
		double l = 0;
		for (int i=0; i < a.nRow; i++){
			for (int j=0; j < a.nCol; j++){
				l += pow(a(i,j),2);
			}
		}
		return sqrt(l);
	} else {throw std::invalid_argument("No axis had dimention 1");}
}
matrix proj(const matrix& u, const matrix& a){
	return (u*a)/length(u)*u;
}
// vector toVector(const matrix& a){
// 	if(a.nRow == 1){
// 		vector v(a.nCol);
// 		for(int i=0; i<a.nCol; i++){v(i) = a(0,i);}
// 	} else {
// 		vector v(a.nRow);
// 		for(int i=0; i<a.nRow; i++){v(i) = a(i,0);}
// 	}
// 	return vector;
// }


matrix matrix::T() const {
	matrix m(nCol, nRow);
	for (int j=0; j < nCol; j++){
		for (int i=0; i < nRow; i++){
			m(j, i) = mat[i*nCol + j];
		}
	}
	return m;
}
matrix matrix::reshape(int newRow, int newCol) const {
	if(nCol*nRow == newCol*newRow){
		matrix m(newRow, newCol);
		for (int i=0; i < nRow; i++){
			for (int j=0; j < nCol; j++){
				int index = i*nCol + j;
				m(floor(index/newCol), index%newCol) = mat[index];
			}
		}
		return m;
	} else {
		throw std::invalid_argument( "Old shape can't be turned to new shape: (" + std::to_string(nRow) + ", " + std::to_string(nCol) + ") -/-> (" + std::to_string(newRow) + ", " + std::to_string(newCol) + ")");

	}
}
matrix matrix::append(const matrix& b, int axis) const {
	if(axis == 0){
		if(SELF.nRow == b.nRow){
			matrix m(SELF.nRow, SELF.nCol + b.nCol);
			for (int i=0; i < SELF.nRow; i++){
				for (int j=0; j < m.nCol; j++){
					if(j < SELF.nCol) {m(i, j) = mat[i*nCol + j];}
					else {m(i, j) = b(i, j-SELF.nCol);}
				}
			}
			return m;
		} else {
			throw std::invalid_argument("Shapes doesn't match: " + std::to_string(SELF.nRow) + " != " + std::to_string(b.nRow));
		}
	} else if(axis == 1){
		if(SELF.nCol == b.nCol){
			matrix m(SELF.nRow + b.nRow, SELF.nCol);
			for (int i=0; i < m.nRow; i++){
				for (int j=0; j < SELF.nCol; j++){
					if(i < SELF.nRow) {m(i, j) = mat[i*nCol + j];} 
					else 	   {m(i, j) = b(i-SELF.nRow, j);}
				}
			}
			return m;
		} else {
			throw std::invalid_argument("Shapes doesn't match");
		}
	}
	throw std::invalid_argument("Axis must be 0 or 1");
}
matrix matrix::copy() const {
	matrix m(nRow, nCol);
	for (int i=0; i < nRow; i++){
		for (int j=0; j < nCol; j++){
			m(i, j) = mat[i*nCol + j];
		}
	}
	return m;
}
matrix matrix::getCol(int start, int n) const {
	matrix m(nRow, n);
	for (int i=0; i < nRow; i++){
		for (int j=start, nrj=0; j < start+n; j++,nrj++){
			m(i,nrj) = mat[i*nCol + j];
		}
	}
	return m;
}
matrix matrix::getRow(int start, int n) const {
	matrix m(n, nCol);
	for (int i=start, nri=0; i < start+n; i++,nri++){
		for (int j=0; j < nCol; j++){
			m(nri,j) = mat[i*nCol + j];
		}
	}
	return m;
}
void matrix::setCol(int j, const matrix& a) {
	for (int i=0; i < nRow; i++){
		mat[i*nCol + j] = a(i, 0);}
}
void matrix::setRow(int i, const matrix& a) {
	for (int j=0; j < nCol; j++){
		mat[i*nCol + j] = a(0, j);}
}
matrix matrix::swapCol(int a, int b) const {
	matrix m = SELF.copy();
	matrix temp1 = m.getCol(a);
	matrix temp2 = m.getCol(b);
	for (int i=0; i < nRow; i++){
		m(i,b) = temp1(i,0);
		m(i,a) = temp2(i,0);
	}
	return m;
}
matrix matrix::swapRow(int a, int b) const {
	matrix m = SELF.copy();
	matrix temp1 = m.getRow(a);
	matrix temp2 = m.getRow(b);
	for (int j=0; j < nCol; j++){
		m(b,j) = temp1(0,j);
		m(a,j) = temp2(0,j);
	}
	return m;
}

void matrix::print(std::string s) const {
	std::cout << s << "";
	std::string front = std::string(s.length()+0, ' ');
	for (int i=0; i < nRow; i++){
		if(i == 0) std::cout << "[";
		else std::cout << front << "[";
		
		for (int j=0; j < nCol; j++){
			if(j == 0) std::cout << mat[i*nCol + j];
			else std::cout << ", " << mat[i*nCol + j];
		}
		if(i == nRow-1) std::cout << "]";
		else std::cout << "]" << std::endl;
	}
	std::cout << "" << std::endl;
}

bool approx(const matrix& A, const matrix& B, double acc, double eps){
	for (int i=0; i < A.nRow; i++){
		for (int j=0; j < A.nCol; j++){
			double a = A(i,j);
			double b = B(i,j);
			if(std::abs(a-b) >= acc) return false;
			if(a > acc && b > acc && std::abs(a-b)/std::max(std::abs(a), std::abs(b)) >= eps) return false;
		}
	}
	return true;
}